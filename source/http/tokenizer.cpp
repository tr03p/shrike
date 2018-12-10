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

#include "tokenizer.h"

#include <algorithm>
#include <iterator>


namespace shrike
{

std::list<std::string> tokenizer::tokenize(const std::string& input, const std::string& delimiters)
{
	std::list<std::string> result;
	std::string::const_iterator i = input.begin();

	do {
		std::string::const_iterator j = std::find_first_of(i, input.end(), delimiters.begin(), delimiters.end());

		if (std::distance(i, j) > 0) {
			result.push_back(std::string(i, j));
		}

		if (j != input.end()) {
			++j;
		}

		i = j;

	} while (i != input.end());

	return result;
}

}
