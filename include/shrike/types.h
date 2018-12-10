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

#ifndef SHRIKE_TYPES_H
#define SHRIKE_TYPES_H


namespace shrike
{

template<typename T>
class nullable
{
public:
	nullable() : _null(true) {}
	nullable(const nullable& value) : _null(value._null), _value(value._value) {}
	nullable(const T& value) : _null(false), _value(value) {}
	bool isNull() const { return _null; }

	void setValue(const T& value) { _value = value; _null = false; }
	const T& value() const { return _value; }
	void setNull() { _null = true; }

	operator T() const { return _value; }
	nullable& operator = (const T& value) { _value = value; _null = false; }
	nullable& operator = (const nullable& value) { _value = value._value; _null = value._null; }

private:
	bool _null;
	T _value;
};

}

#endif
