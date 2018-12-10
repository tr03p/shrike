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

#ifndef SHRIKE_EXCEPTIONS_H
#define SHRIKE_EXCEPTIONS_H

#include <stdexcept>
#include <sstream>


namespace shrike
{

class strfmt
{
public:
	strfmt() {}

	template <typename Type>
	strfmt& operator << (const Type & value)
	{
		_stream << value;
		return *this;
	}

	operator std::string () const { return _stream.str(); }

private:
	std::stringstream _stream;

	strfmt(const strfmt &) = delete;
	strfmt & operator = (strfmt &) = delete;
};

class serializer_exception : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

class serializer_field_not_found_exception : public serializer_exception
{
public:
	serializer_field_not_found_exception(const std::string& name) :
		serializer_exception(strfmt() << "Field '" << name << "' not found in JSON object")
	{}
};

class http_service_exception : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

}

#endif
