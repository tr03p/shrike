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

#ifndef SHRIKE_HTTPRESPONSE_H
#define SHRIKE_HTTPRESPONSE_H

#include <string>
#include <vector>


namespace shrike
{

class http_response
{
public:
	enum status_codes
	{
		HTTP_STATUS_OK = 200,
		HTTP_STATUS_CREATED = 201,
		HTTP_STATUS_BAD_REQUEST = 400,
		HTTP_STATUS_FORBIDDEN = 403,
		HTTP_STATUS_NOT_FOUND = 404,
		HTTP_STATUS_INTERNAL_SERVER_ERROR = 500
	};

	static constexpr const char* CONTENT_TYPE_APPLICATION_JSON = "application/json";

public:
	http_response();
	http_response(int status_code);
	http_response(const std::string& data, const std::string& content_type, int status_code = HTTP_STATUS_OK);
	http_response(const std::vector<uint8_t>& data, const std::string& content_type, int status_code = HTTP_STATUS_OK);

	operator bool () const { return _valid; }

	void set_status_code(int status_code) { _status_code = status_code; }
	void set_data(const void* data, size_t length);
	void set_content_type(const std::string& content_type) { _content_type = content_type; }

	int status_code() const { return _status_code; }
	std::string content_type() const { return _content_type; }

	const std::vector<uint8_t>& data() const { return _data; }

	// TODO: Specify string codec, throw exceptions
	const std::string data_to_string() const;

private:
	bool _valid;
	int _status_code;
	std::string _content_type;
	std::vector<uint8_t> _data;
};

}

#endif
