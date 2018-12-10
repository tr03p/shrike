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

#ifndef SIMPLE_DATA_H
#define SIMPLE_DATA_H

#include <shrike/shrike.h>


class sum_array_request : public shrike::serializable_object
{
public:
	sum_array_request()
	{

	}

	sum_array_request(const std::vector<int>& values) :
		values(values)
	{

	}

	void serialize_fields(shrike::object_serializer* serializer)
	{
		serializer->serialize("values", values);
	}

	void deserialize_fields(shrike::object_serializer* serializer)
	{
		serializer->deserialize("values", values);
	}

	std::vector<int> values;
};


class sum_array_response : public shrike::serializable_object
{
public:
	sum_array_response() :
		result(0)
	{

	}

	sum_array_response(int result) :
		result(result)
	{

	}

	void serialize_fields(shrike::object_serializer* serializer)
	{
		serializer->serialize("result", result);
	}

	void deserialize_fields(shrike::object_serializer* serializer)
	{
		serializer->deserialize("result", result);
	}

	int result;
};

#endif
