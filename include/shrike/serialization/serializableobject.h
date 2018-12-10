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

#ifndef SHRIKE_SERIALIZABLEOBJECT_H
#define SHRIKE_SERIALIZABLEOBJECT_H


#include <shrike/serialization/objectserializer.h>

#include <algorithm>


namespace shrike
{

class serializable_object
{

public:
	serializable_object();
	void deserialize(const std::string& request, object_serializer::create_serializer create_serializer);
	std::string serialize(object_serializer::create_serializer create_serializer);

	virtual void serialize_fields(object_serializer* serializer) = 0;
	virtual void deserialize_fields(object_serializer* serializer) = 0;

	template <typename T>
	std::vector<serializable_object*> to_object_array(std::vector<T>& source)
	{
		std::vector<serializable_object*> target(source.size());
		std::transform(source.begin(), source.end(), target.begin(), [](T& t) { return &t; });
		return target;
	}
};

}

#endif
