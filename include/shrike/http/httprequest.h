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

#ifndef SHRIKE_HTTPREQUEST_H
#define SHRIKE_HTTPREQUEST_H

#include <map>
#include <string>
#include <vector>


namespace shrike
{

class http_request
{
public:
	http_request(const std::string& uri);
	http_request(const std::string& uri, const std::string& data);
	http_request(const std::string& uri, const std::vector<uint8_t>& data);

	std::string uri() const { return _uri; }
	std::vector<std::string> uriPath() const { return _uri_path; }

	void set_header(const std::string& key, const std::string& value);
	std::string header(const std::string& name) const;
	const std::map<std::string, std::string>& headers() const;

	void set_parameter(const std::string& key, const std::string& value);
	std::string parameter(const std::string& name) const;

	const std::vector<uint8_t>& data() const { return _data; }

	const std::string data_to_string() const;

private:
	std::string _uri;
	std::vector<std::string> _uri_path;
	std::map<std::string, std::string> _headers;
	std::map<std::string, std::string> _parameters;
	std::vector<uint8_t> _data;
};

}

#endif
