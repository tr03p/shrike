/*
	Copyright (c) 2018 Willem Kemp, willem@eneritix.co.za

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
 */

#include "httpservice_impl.h"
#include "tokenizer.h"

#include "shrike/http/httprequest.h"
#include "shrike/http/httpresponse.h"

#include <list>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string.h>


namespace shrike
{

http_service::impl::impl(int port)
{
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_aton("127.0.0.1", &addr.sin_addr);

	_daemon = MHD_start_daemon(
		MHD_USE_SELECT_INTERNALLY,
		port,
		NULL,
		NULL,
		&connection_callback,
		this,
		MHD_OPTION_SOCK_ADDR,
		&addr,
		MHD_OPTION_END);
}

http_service::impl::~impl()
{
	MHD_stop_daemon(_daemon);
}

http_response http_service::impl::dispatch(const http_request& request)
{
	// Find the service for the request
	std::vector<std::string> tokens = request.uriPath();
	uri_lookup_node* lookup_node(&_dispatch);

	for (const auto& token : tokens) {
		auto i = lookup_node->children.find(token);
		if (i != lookup_node->children.end()) {
			lookup_node = &lookup_node->children[token];
		} else {
			return http_response(http_response::HTTP_STATUS_NOT_FOUND);
		}
	}

	if (!lookup_node->func) {
		return http_response(http_response::HTTP_STATUS_FORBIDDEN);
	}

	return lookup_node->func(request);
}

void http_service::impl::register_method(const std::string& uri, std::function<http_response(const http_request&)> func)
{
	// Tokenize the uri
	std::list<std::string> tokens(tokenizer::tokenize(uri, "/"));

	// Register
	uri_lookup_node* lookup_node(&_dispatch);


	for(const auto& token : tokens) {
		lookup_node = &lookup_node->children[token];
	}

	lookup_node->func = func;
}

int http_service::impl::connection_callback(
	void* cls,
	struct MHD_Connection* connection,
	const char* url,
	const char* method,
	const char* version,
	const char* upload_data,
	size_t* upload_data_size,
	void** con_cls)
{
	http_service::impl* serviceProvider = (http_service::impl*)cls;
	struct MHD_Response* mhd_response = NULL;
	int result = MHD_NO;

	// GET request
	if (strcmp(method, MHD_HTTP_METHOD_GET) == 0) {

		// Build the request
		http_request request(url);

		// Add headers
		MHD_get_connection_values(connection, MHD_HEADER_KIND, parse_headers_callback, &request);

		// Add parameters
		MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, parse_arguments_callback, &request);

		// Dispatch
		http_response response(serviceProvider->dispatch(request));

		// Return the response
		mhd_response = MHD_create_response_from_buffer (response.data().size(), (void*)response.data().data(), MHD_RESPMEM_MUST_COPY);
		MHD_add_response_header(mhd_response, "Content-Type", response.content_type().c_str());
		result = MHD_queue_response(connection, response.status_code(), mhd_response);
		MHD_destroy_response(mhd_response);

		return result;
	}

	// POST request
	if (strcmp(method, MHD_HTTP_METHOD_POST) == 0) {

		if (*con_cls == NULL) {
			struct post_context* ctx = new post_context();
			*con_cls = ctx;
			return MHD_YES;
		}

		if (*upload_data_size) {
			struct post_context* ctx = (struct post_context*)*con_cls;
			ctx->data.insert(ctx->data.end(), upload_data, upload_data + *upload_data_size);

			*upload_data_size = 0;
			return MHD_YES;

		} else {
			struct post_context* ctx = (struct post_context*)*con_cls;

			// Build the request
			http_request request(url, ctx->data);

			// Add headers
			MHD_get_connection_values(connection, MHD_HEADER_KIND, parse_headers_callback, &request);

			// Add parameters
			MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, parse_arguments_callback, &request);

			// Dispatch
			http_response response(serviceProvider->dispatch(request));

			// Return the response
			mhd_response = MHD_create_response_from_buffer (response.data().size(), (void*)response.data().data(), MHD_RESPMEM_MUST_COPY);
			MHD_add_response_header(mhd_response, "Content-Type", response.content_type().c_str());
			result = MHD_queue_response(connection, response.status_code(), mhd_response);
			MHD_destroy_response(mhd_response);

			delete ctx;

			return result;
		}
	}

	return MHD_NO;
}

int http_service::impl::parse_headers_callback(
	void *cls,
	enum MHD_ValueKind kind,
	const char *key,
	const char *value)
{

	http_request* r = (http_request*)cls;

	if (kind == MHD_HEADER_KIND) {
		r->set_header(key, value);
	}

	return MHD_YES;
}

int http_service::impl::parse_arguments_callback(
	void *cls,
	enum MHD_ValueKind kind,
	const char *key,
	const char *value)
{

	http_request* r = (http_request*)cls;

	if (kind == MHD_GET_ARGUMENT_KIND) {
		r->set_parameter(key, value);
	}

	return MHD_YES;
}

}
