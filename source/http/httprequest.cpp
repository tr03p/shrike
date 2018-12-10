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

#include "shrike/http/httprequest.h"
#include "tokenizer.h"
#include "url_codec.h"

#include <string.h>

namespace shrike
{

http_request::http_request(const std::string& uri) :
	_uri(uri)
{
	std::list<std::string> tokens(tokenizer::tokenize(uri, "/"));
	_uri_path.reserve(tokens.size());
	std::copy(tokens.begin(), tokens.end(), std::back_inserter(_uri_path));
}

http_request::http_request(const std::string& uri, const std::string& data) :
	_uri(uri)
{
	std::list<std::string> tokens(tokenizer::tokenize(uri, "/"));
	_uri_path.reserve(tokens.size());
	std::copy(tokens.begin(), tokens.end(), std::back_inserter(_uri_path));

	_data.resize(data.size());
	memcpy(_data.data(), data.data(), data.length());
}

http_request::http_request(const std::string& uri, const std::vector<uint8_t>& data) :
	_uri(uri),
	_data(data)
{
	std::list<std::string> tokens(tokenizer::tokenize(uri, "/"));
	_uri_path.reserve(tokens.size());
	std::copy(tokens.begin(), tokens.end(), std::back_inserter(_uri_path));
}

void http_request::set_header(const std::string& key, const std::string& value)
{
	_headers[key] = value;
}

std::string http_request::header(const std::string& name) const
{
	std::map<std::string, std::string>::const_iterator i = _headers.find(name);
	if (i != _headers.end()) {
		return	(*i).second;
	} else {
		return "";
	}
}

const std::map<std::string, std::string>& http_request::headers() const
{
	return _headers;
}

void http_request::set_parameter(const std::string& key, const std::string& value)
{
	_parameters[key] = value;
}

std::string http_request::parameter(const std::string& name) const
{
	std::map<std::string, std::string>::const_iterator i = _parameters.find(name);
	if (i != _parameters.end()) {
		return	(*i).second;
	} else {
		return "";
	}
}

const std::string http_request::data_to_string() const
{
	return std::string((const char*)_data.data(), (const char*)_data.data() + _data.size());
}

}
