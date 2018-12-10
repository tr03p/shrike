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

#include "url_codec.h"

#include <algorithm>


namespace shrike
{

std::string url_codec::decode(const std::string& url)
{
	std::string result;
	result.reserve(url.size());


	std::string url_local(url);
	std::replace(url_local.begin(), url_local.end(), '+', ' ');

	std::string::iterator i = url_local.begin();
	std::string::iterator j = i;

	do {
		j = std::find(i, url_local.end(), '%');
		result.append(i, j);

		if (j != url_local.end()) {

			char value = 0;

			++j;
			if (j == url_local.end()) {
				throw std::exception();
			}
			value = hex_digit_to_int(*j) * 16;

			++j;
			if (j == url_local.end()) {
				throw std::exception();
			}

			value += hex_digit_to_int(*j);

			result += value;

			++j;
		}

		i = j;

	} while (i != url_local.end());

	return result;
}

int url_codec::hex_digit_to_int(char hex)
{
	if ((hex >= '0') && (hex <= '9')) {
		return (hex - '0');
	} else if ((hex >= 'a') && (hex <= 'f')) {
		return 10 + (hex - 'a');
	} else if ((hex >= 'A') && (hex <= 'F')) {
		return 10 + (hex - 'A');
	} else {
		throw std::exception();
	}
}

}
