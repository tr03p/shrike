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

#ifndef SHRIKE_HTTPCLIENT_IMPL_H
#define SHRIKE_HTTPCLIENT_IMPL_H

#include <shrike/http/httprequest.h>
#include <shrike/http/httpresponse.h>

#include <shrike/http/httpclient.h>

#include <string>
#include <vector>
#include <stdint.h>
#include <stddef.h>
#include <curl/curl.h>


namespace shrike
{

class http_client::impl
{
public:
	http_response post(const http_request& request);
	http_response get(const http_request& request);
	http_response get(const http_request& request, const std::string& path);


private:
	struct curl_callback_context
	{
		std::vector<uint8_t> data;
	};

private:
	static size_t curl_get_callback(void* contents, size_t size, size_t nmemb, void* userp);
	static size_t curl_get_file_callback(void* contents, size_t size, size_t nmemb, void* userp);
	static size_t curl_post_callback(void* contents, size_t size, size_t nmemb, void* userp);
};

}

#endif
