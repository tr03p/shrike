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

#include "httpclient_impl.h"
#include <stdio.h>


namespace shrike
{

http_response http_client::impl::post(const http_request& request)
{
	curl_callback_context context;
	long response_code;
	CURL* ch;

	ch = curl_easy_init();
	if (!ch) {
		return http_response(false);
	}

	// Headers
	struct curl_slist* headers = NULL;
	for (const auto& i : request.headers()) {
		std::string header_string(i.first + ": " + i.second);
		headers = curl_slist_append(headers, header_string.c_str());
	}

	// Options
	curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(ch, CURLOPT_POSTFIELDS, request.data().data());
	curl_easy_setopt(ch, CURLOPT_URL, request.uri().c_str());
	curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_post_callback);
	curl_easy_setopt(ch, CURLOPT_WRITEDATA, &context);
	curl_easy_setopt(ch, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_setopt(ch, CURLOPT_CONNECTTIMEOUT, 30);
	curl_easy_setopt(ch, CURLOPT_TIMEOUT, 60);
	curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(ch, CURLOPT_MAXREDIRS, 1);

	// Perform
	CURLcode result = curl_easy_perform(ch);

	// Check for errors
	if (result != CURLE_OK) {
		return http_response();
	}

	// Get the response code
	curl_easy_getinfo(ch, CURLINFO_RESPONSE_CODE, &response_code);

	// Get the content type
	char* content_type_ptr;
	std::string content_type;
	curl_easy_getinfo(ch, CURLINFO_CONTENT_TYPE, &content_type_ptr);
	if (content_type_ptr) {
		content_type = content_type_ptr;
	}

	curl_easy_cleanup(ch);
	curl_slist_free_all(headers);

	// Return the response
	return http_response(context.data, content_type, response_code);
}


http_response http_client::impl::get(const http_request& request)
{
	curl_callback_context context;
	long response_code;
	CURL* ch;

	ch = curl_easy_init();
	if (!ch) {
		return http_response();
	}

	// Headers
	struct curl_slist* headers = NULL;
	for (const auto& i : request.headers()) {
		std::string header_string(i.first + ": " + i.second);
		headers = curl_slist_append(headers, header_string.c_str());
	}

	const std::string queryString = request.parameter_string();
	std::string url = request.uri();
	if (!queryString.empty())
		url += '?' + queryString;

	// Options
	curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(ch, CURLOPT_URL, url.c_str());
	curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_get_callback);
	curl_easy_setopt(ch, CURLOPT_WRITEDATA, &context);
	curl_easy_setopt(ch, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_setopt(ch, CURLOPT_CONNECTTIMEOUT, 30);
	curl_easy_setopt(ch, CURLOPT_TIMEOUT, 60);
	curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(ch, CURLOPT_MAXREDIRS, 1);

	// Perform
	CURLcode result = curl_easy_perform(ch);

	// Check for errors
	if (result != CURLE_OK) {
		return http_response();
	}

	// Get the response code
	curl_easy_getinfo(ch, CURLINFO_RESPONSE_CODE, &response_code);

	// Get the content type
	char* content_type_ptr;
	std::string content_type;
	curl_easy_getinfo(ch, CURLINFO_CONTENT_TYPE, &content_type_ptr);
	if (content_type_ptr) {
		content_type = content_type_ptr;
	}

	curl_easy_cleanup(ch);
	curl_slist_free_all(headers);

	// Return the response
	return http_response(context.data, content_type, response_code);
}

http_response http_client::impl::get(const http_request& request, const std::string& path)
{
	long response_code;
	CURL* ch;

	FILE* file = fopen(path.c_str(), "w");
	if (!file) {
		return http_response(false);
	}

	ch = curl_easy_init();
	if (!ch) {
		fclose(file);
		return http_response();
	}

	// Options
	curl_easy_setopt(ch, CURLOPT_URL, request.uri().c_str());
	curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_get_file_callback);
	curl_easy_setopt(ch, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(ch, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_setopt(ch, CURLOPT_CONNECTTIMEOUT, 30);
	curl_easy_setopt(ch, CURLOPT_TIMEOUT, 60);
	curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(ch, CURLOPT_MAXREDIRS, 1);

	// Perform
	CURLcode result = curl_easy_perform(ch);

	// Check for errors
	if (result != CURLE_OK) {
		fclose(file);
		return http_response();
	}

	// Get the response code
	curl_easy_getinfo(ch, CURLINFO_RESPONSE_CODE, &response_code);

	// Get the content type
	char* content_type_ptr;
	std::string content_type;
	curl_easy_getinfo(ch, CURLINFO_CONTENT_TYPE, &content_type_ptr);
	if (content_type_ptr) {
		content_type = content_type_ptr;
	}

	curl_easy_cleanup(ch);
	fclose(file);

	// Return the response
	return http_response(std::vector<uint8_t>(), content_type, response_code);
}

size_t http_client::impl::curl_get_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	curl_callback_context* context = (curl_callback_context*)userp;
	const uint8_t* start = (const uint8_t*)contents;
	const uint8_t* end = start + (size * nmemb);

	context->data.insert(context->data.end(), start, end);

	return size * nmemb;
}

size_t http_client::impl::curl_get_file_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	FILE* file = (FILE*)userp;
	return fwrite(contents, size, nmemb, file);
}

size_t http_client::impl::curl_post_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	curl_callback_context* context = (curl_callback_context*)userp;
	const uint8_t* start = (const uint8_t*)contents;
	const uint8_t* end = start + (size * nmemb);

	context->data.insert(context->data.end(), start, end);

	return size * nmemb;
}

}
