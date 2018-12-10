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

#include "shrike/http/httpresponse.h"
#include <string.h>


namespace shrike
{

http_response::http_response() :
	_valid(false)
{
}

http_response::http_response(int status_code) :
	_valid(true),
	_status_code(status_code)
{

}

http_response::http_response(const std::string& data, const std::string& content_type, int status_code) :
	_valid(true),
	_status_code(status_code),
	_content_type(content_type),
	_data(data.begin(), data.end())
{

}


http_response::http_response(const std::vector<uint8_t>& data, const std::string& content_type, int status_code) :
	_valid(true),
	_status_code(status_code),
	_content_type(content_type),
	_data(data)
{

}

void http_response::set_data(const void* data, size_t length)
{
	const uint8_t* ptr = (const uint8_t*)data;
	_data.reserve(length);
	_data.insert(_data.end(), ptr, ptr + length);
}

const std::string http_response::data_to_string() const
{
	return std::string((const char*)_data.data(), (const char*)_data.data() + _data.size());
}


}
