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

#ifndef SHRIKE_JSONSERIALIZER_H
#define SHRIKE_JSONSERIALIZER_H

#include <shrike/serialization/objectserializer.h>

#include <jsoncpp/json/json.h>

#include <stack>


namespace shrike
{

class json_serializer : public object_serializer
{
public:
	static object_serializer* create(const std::string& request);

	json_serializer(const std::string& request);

public:

	// Serialization

	// Basic types
	void serialize(const std::string& name, int value);
	void serialize(const std::string& name, unsigned int value);
	void serialize(const std::string& name, int64_t value);
	void serialize(const std::string& name, uint64_t value);
	void serialize(const std::string& name, double value);
	void serialize(const std::string& name, bool value);
	void serialize(const std::string& name, const std::string& value);
	void serialize(const std::string& name, const std::vector<uint8_t>& value);

	// Nullable basic types
	void serialize(const std::string& name, const nullable<int>& value);
	void serialize(const std::string& name, const nullable<unsigned int>& value);
	void serialize(const std::string& name, const nullable<int64_t>& value);
	void serialize(const std::string& name, const nullable<uint64_t>& value);
	void serialize(const std::string& name, const nullable<double>& value);
	void serialize(const std::string& name, const nullable<bool>& value);
	void serialize(const std::string& name, const nullable<std::string>& value);
	void serialize(const std::string& name, const nullable<std::vector<uint8_t>>& value);

	// Basic type arrays
	void serialize(const std::string& name, const std::vector<int>& array);
	void serialize(const std::string& name, const std::vector<unsigned int>& array);
	void serialize(const std::string& name, const std::vector<int64_t>& array);
	void serialize(const std::string& name, const std::vector<uint64_t>& array);
	void serialize(const std::string& name, const std::vector<double>& array);
	void serialize(const std::string& name, const std::vector<bool>& array);
	void serialize(const std::string& name, const std::vector<std::string>& array);

	// Nullable basic type arrays
	void serialize(const std::string& name, const nullable<std::vector<int>>& array);
	void serialize(const std::string& name, const nullable<std::vector<unsigned int>>& array);
	void serialize(const std::string& name, const nullable<std::vector<int64_t>>& array);
	void serialize(const std::string& name, const nullable<std::vector<uint64_t>>& array);
	void serialize(const std::string& name, const nullable<std::vector<double>>& array);
	void serialize(const std::string& name, const nullable<std::vector<bool>>& array);
	void serialize(const std::string& name, const nullable<std::vector<std::string>>& array);

	// Object and object array
	void serialize(const std::string& name, serializable_object* object);
	void serialize(const std::string& name, const std::vector<serializable_object*> object_array);

	// Deserialization

	// Basic types
	void deserialize(const std::string& name, int& value);
	void deserialize(const std::string& name, unsigned int& value);
	void deserialize(const std::string& name, int64_t& value);
	void deserialize(const std::string& name, uint64_t& value);
	void deserialize(const std::string& name, double& value);
	void deserialize(const std::string& name, bool& value);
	void deserialize(const std::string& name, std::string& value);
	void deserialize(const std::string& name, std::vector<uint8_t>& value);

	// Nullable basic types
	void deserialize(const std::string& name, nullable<int>& value);
	void deserialize(const std::string& name, nullable<unsigned int>& value);
	void deserialize(const std::string& name, nullable<int64_t>& value);
	void deserialize(const std::string& name, nullable<uint64_t>& value);
	void deserialize(const std::string& name, nullable<double>& value);
	void deserialize(const std::string& name, nullable<bool>& value);
	void deserialize(const std::string& name, nullable<std::string>& value);
	void deserialize(const std::string& name, nullable<std::vector<uint8_t>>& value);

	// Basic type arrays
	void deserialize(const std::string& name, std::vector<int>& array);
	void deserialize(const std::string& name, std::vector<unsigned int>& array);
	void deserialize(const std::string& name, std::vector<int64_t>& array);
	void deserialize(const std::string& name, std::vector<uint64_t>& array);
	void deserialize(const std::string& name, std::vector<double>& array);
	void deserialize(const std::string& name, std::vector<bool>& array);
	void deserialize(const std::string& name, std::vector<std::string>& array);

	// Nullable basic type arrays
	void deserialize(const std::string& name, nullable<std::vector<int>>& array);
	void deserialize(const std::string& name, nullable<std::vector<unsigned int>>& array);
	void deserialize(const std::string& name, nullable<std::vector<int64_t>>& array);
	void deserialize(const std::string& name, nullable<std::vector<uint64_t>>& array);
	void deserialize(const std::string& name, nullable<std::vector<double>>& array);
	void deserialize(const std::string& name, nullable<std::vector<bool>>& array);
	void deserialize(const std::string& name, nullable<std::vector<std::string>>& array);

	// Object and object arrays
	void deserialize(const std::string& name, serializable_object* object);
	void deserialize(const std::string& name, std::vector<serializable_object*> object_array);


	int array_length(const std::string& name);
	std::string commit();

private:
	static std::string base64_encode(const std::vector<uint8_t>& in);
	static std::vector<uint8_t> base64_decode(const std::string& in);

private:
	std::stack<Json::Value> _serializer_stack;
	std::stack<Json::Value*> _deserializer_stack;
	Json::Value _deserializer_value;
};

}

#endif
