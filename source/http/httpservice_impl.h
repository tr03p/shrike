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

#ifndef SHRIKE_HTTPSERVICE_IMPL_H
#define SHRIKE_HTTPSERVICE_IMPL_H

#include "shrike/http/httpservice.h"

#include <microhttpd.h>

#include <map>
#include <vector>

#include <stdint.h>
#include <stdlib.h>



namespace shrike
{

class http_service::impl
{
public:
	impl(int port);
	~impl();

	http_response dispatch(const http_request& request);
	void register_method(const std::string& uri, std::function<http_response(const http_request&)> func);


private:
	static int connection_callback(
		void* cls,
		struct MHD_Connection* connection,
		const char* url,
		const char* method,
		const char* version,
		const char* upload_data,
		size_t* upload_data_size,
		void** con_cls);

	static int parse_headers_callback(
		void *cls,
		enum MHD_ValueKind kind,
		const char *key,
		const char *value
	);

	static int parse_arguments_callback(
		void *cls,
		enum MHD_ValueKind kind,
		const char *key,
		const char *value
	);

private:
	struct post_context
	{
		std::vector<uint8_t> data;
	};

	struct uri_lookup_node
	{
		std::function<http_response(const http_request&)> func;
		std::map<std::string, uri_lookup_node> children;
	};

private:
	struct MHD_Daemon *_daemon;
	uri_lookup_node _dispatch;
};

}

#endif
