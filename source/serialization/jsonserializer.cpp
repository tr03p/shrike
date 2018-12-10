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

#include "shrike/serialization/jsonserializer.h"
#include "shrike/serialization/serializableobject.h"
#include "shrike/exceptions.h"


extern "C" {
#include <b64/cdecode.h>
#include <b64/cencode.h>
}

#include <memory>
#include <sstream>

#include <string.h>



namespace shrike
{

object_serializer* json_serializer::create(const std::string& request)
{
	return new json_serializer(request);
}

json_serializer::json_serializer(const std::string& request) :
	object_serializer(request)
{
	_serializer_stack.push(Json::Value());
	Json::Reader().parse("{}", _serializer_stack.top());
}


// Serialization

// Basic types

void json_serializer::serialize(const std::string& name, int value)
{
	_serializer_stack.top()[name] = value;
}

void json_serializer::serialize(const std::string& name, unsigned int value)
{
	_serializer_stack.top()[name] = value;
}

void json_serializer::serialize(const std::string& name, int64_t value)
{
	_serializer_stack.top()[name] = (long long)value;
}

void json_serializer::serialize(const std::string& name, uint64_t value)
{
	_serializer_stack.top()[name] = (unsigned long long)value;
}

void json_serializer::serialize(const std::string& name, double value)
{
	_serializer_stack.top()[name] = value;
}

void json_serializer::serialize(const std::string& name, bool value)
{
	_serializer_stack.top()[name] = value;
}

void json_serializer::serialize(const std::string& name, const std::string& value)
{
	_serializer_stack.top()[name] = value;
}

void json_serializer::serialize(const std::string& name, const std::vector<uint8_t>& value)
{
	_serializer_stack.top()[name] = base64_encode(value);
}

// Nullable basic types

void json_serializer::serialize(const std::string& name, const nullable<int>& value)
{
	if (value.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;
	} else {
		_serializer_stack.top()[name] = value.value();
	}
}

void json_serializer::serialize(const std::string& name, const nullable<unsigned int>& value)
{
	if (value.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;
	} else {
		_serializer_stack.top()[name] = value.value();
	}
}

void json_serializer::serialize(const std::string& name, const nullable<int64_t>& value)
{
	if (value.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;
	} else {
		_serializer_stack.top()[name] = (long long)value.value();
	}
}

void json_serializer::serialize(const std::string& name, const nullable<uint64_t>& value)
{
	if (value.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;
	} else {
		_serializer_stack.top()[name] = (unsigned long long)value.value();
	}
}

void json_serializer::serialize(const std::string& name, const nullable<double>& value)
{
	if (value.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;
	} else {
		_serializer_stack.top()[name] = value.value();
	}
}

void json_serializer::serialize(const std::string& name, const nullable<bool>& value)
{
	if (value.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;
	} else {
		_serializer_stack.top()[name] = value.value();
	}
}

void json_serializer::serialize(const std::string& name, const nullable<std::string>& value)
{
	if (value.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;
	} else {
		_serializer_stack.top()[name] = value.value();
	}
}

void json_serializer::serialize(const std::string& name, const nullable<std::vector<uint8_t>>& value)
{
	if (value.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;
	} else {
		_serializer_stack.top()[name] = base64_encode(value.value());
	}
}

// Basic type arrays

void json_serializer::serialize(const std::string& name, const std::vector<int>& array)
{
	if (array.empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.size(); ++i) {
			arrayValue[i] = array[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const std::vector<unsigned int>& array)
{
	if (array.empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.size(); ++i) {
			arrayValue[i] = array[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const std::vector<int64_t>& array)
{
	if (array.empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.size(); ++i) {
			arrayValue[i] = (long long) array[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const std::vector<uint64_t>& array)
{
	if (array.empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.size(); ++i) {
			arrayValue[i] = (unsigned long long) array[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const std::vector<double>& array)
{
	if (array.empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.size(); ++i) {
			arrayValue[i] = array[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const std::vector<bool>& array)
{
	if (array.empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.size(); ++i) {
			arrayValue[i] = array[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

// Nullable basic type arrays

void json_serializer::serialize(const std::string& name, const nullable<std::vector<int>>& array)
{
	if (array.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;

	} else if (array.value().empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.value().size(); ++i) {
			arrayValue[i] = array.value()[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const nullable<std::vector<unsigned int>>& array)
{
	if (array.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;

	} else if (array.value().empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.value().size(); ++i) {
			arrayValue[i] = array.value()[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const nullable<std::vector<int64_t>>& array)
{
	if (array.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;

	} else if (array.value().empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.value().size(); ++i) {
			arrayValue[i] = (long long) array.value()[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const nullable<std::vector<uint64_t>>& array)
{
	if (array.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;

	} else if (array.value().empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.value().size(); ++i) {
			arrayValue[i] = (unsigned long long) array.value()[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const nullable<std::vector<double>>& array)
{
	if (array.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;

	} else if (array.value().empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.value().size(); ++i) {
			arrayValue[i] = array.value()[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

void json_serializer::serialize(const std::string& name, const nullable<std::vector<bool>>& array)
{
	if (array.isNull()) {
		_serializer_stack.top()[name] = Json::nullValue;

	} else if (array.value().empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {
		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < array.value().size(); ++i) {
			arrayValue[i] = array.value()[i];
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

// Object and object array

void json_serializer::serialize(const std::string& name, serializable_object* object)
{
	if (name != "") {

		if (object) {
			_serializer_stack.push(Json::Value());
			object->serialize_fields(this);
			Json::Value value(_serializer_stack.top());
			_serializer_stack.pop();
			_serializer_stack.top()[name] = value;
		} else {
			_serializer_stack.top()[name] = Json::Value::null;
		}

	} else {
		object->serialize_fields(this);
	}
}

void json_serializer::serialize(const std::string& name, const std::vector<serializable_object*> object_array)
{
	if (object_array.empty()) {
		_serializer_stack.top()[name] = Json::arrayValue;

	} else {

		Json::Value arrayValue;

		for (Json::ArrayIndex i = 0; i < object_array.size(); ++i) {
			_serializer_stack.push(Json::Value());
			object_array[i]->serialize_fields(this);
			Json::Value value(_serializer_stack.top());
			_serializer_stack.pop();
			arrayValue[i] = value;
		}

		_serializer_stack.top()[name] = arrayValue;
	}
}

// Deserialization

// Basic types

void json_serializer::deserialize(const std::string& name, int& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		value = (*_deserializer_stack.top())[name].asInt();
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, unsigned int& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		value = (*_deserializer_stack.top())[name].asUInt();
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, int64_t& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		value = (*_deserializer_stack.top())[name].asInt64();
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, uint64_t& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		value = (*_deserializer_stack.top())[name].asUInt64();
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, double& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		value = (*_deserializer_stack.top())[name].asDouble();
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, bool& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		value = (*_deserializer_stack.top())[name].asBool();
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, std::string& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		value = (*_deserializer_stack.top())[name].asString();
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, std::vector<uint8_t>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		value = base64_decode((*_deserializer_stack.top())[name].asString());
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

// Nullable basic types

void json_serializer::deserialize(const std::string& name, nullable<int>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		if ((*_deserializer_stack.top())[name].isNull()) {
			value.setNull();
		} else {
			value = (*_deserializer_stack.top())[name].asInt();
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<unsigned int>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		if ((*_deserializer_stack.top())[name].isNull()) {
			value.setNull();
		} else {
			value = (*_deserializer_stack.top())[name].asUInt();
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<int64_t>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		if ((*_deserializer_stack.top())[name].isNull()) {
			value.setNull();
		} else {
			value = (*_deserializer_stack.top())[name].asInt64();
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<uint64_t>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		if ((*_deserializer_stack.top())[name].isNull()) {
			value.setNull();
		} else {
			value = (*_deserializer_stack.top())[name].asUInt64();
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<double>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		if ((*_deserializer_stack.top())[name].isNull()) {
			value.setNull();
		} else {
			value = (*_deserializer_stack.top())[name].asDouble();
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<bool>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		if ((*_deserializer_stack.top())[name].isNull()) {
			value.setNull();
		} else {
			value = (*_deserializer_stack.top())[name].asBool();
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<std::string>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		if ((*_deserializer_stack.top())[name].isNull()) {
			value.setNull();
		} else {
			value = (*_deserializer_stack.top())[name].asString();
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<std::vector<uint8_t>>& value)
{
	if (_deserializer_stack.top()->isMember(name)) {
		if ((*_deserializer_stack.top())[name].isNull()) {
			value.setNull();
		} else {
			value = base64_decode((*_deserializer_stack.top())[name].asString());
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

// Basic type arrays

void json_serializer::deserialize(const std::string& name, std::vector<int>& array)
{
	array.clear();

	if (_deserializer_stack.top()->isMember(name)) {
		Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

		for (Json::ArrayIndex i=0; i < count; ++i) {
			array.push_back((*_deserializer_stack.top())[name][i].asInt());
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, std::vector<unsigned int>& array)
{
	array.clear();

	if (_deserializer_stack.top()->isMember(name)) {
		Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

		for (Json::ArrayIndex i=0; i < count; ++i) {
			array.push_back((*_deserializer_stack.top())[name][i].asUInt());
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, std::vector<int64_t>& array)
{
	array.clear();

	if (_deserializer_stack.top()->isMember(name)) {
		Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

		for (Json::ArrayIndex i=0; i < count; ++i) {
			array.push_back((*_deserializer_stack.top())[name][i].asInt64());
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, std::vector<uint64_t>& array)
{
	array.clear();

	if (_deserializer_stack.top()->isMember(name)) {
		Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

		for (Json::ArrayIndex i=0; i < count; ++i) {
			array.push_back((*_deserializer_stack.top())[name][i].asUInt64());
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, std::vector<double>& array)
{
	array.clear();

	if (_deserializer_stack.top()->isMember(name)) {
		Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

		for (Json::ArrayIndex i=0; i < count; ++i) {
			array.push_back((*_deserializer_stack.top())[name][i].asDouble());
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, std::vector<bool>& array)
{
	array.clear();

	if (_deserializer_stack.top()->isMember(name)) {
		Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

		for (Json::ArrayIndex i=0; i < count; ++i) {
			array.push_back((*_deserializer_stack.top())[name][i].asBool());
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

// Nullable basic type arrays

void json_serializer::deserialize(const std::string& name, nullable<std::vector<int>>& array)
{
	std::vector<int> value;

	if (_deserializer_stack.top()->isMember(name)) {

		if ((*_deserializer_stack.top())[name].isNull()) {
			array.setNull();

		} else {

			Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

			for (Json::ArrayIndex i=0; i < count; ++i) {
				value.push_back((*_deserializer_stack.top())[name][i].asInt());
			}

			array = value;
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<std::vector<unsigned int>>& array)
{
	std::vector<unsigned int> value;

	if (_deserializer_stack.top()->isMember(name)) {

		if ((*_deserializer_stack.top())[name].isNull()) {
			array.setNull();

		} else {
			Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

			for (Json::ArrayIndex i=0; i < count; ++i) {
				value.push_back((*_deserializer_stack.top())[name][i].asUInt());
			}

			array = value;
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<std::vector<int64_t>>& array)
{
	std::vector<int64_t> value;

	if (_deserializer_stack.top()->isMember(name)) {

		if ((*_deserializer_stack.top())[name].isNull()) {
			array.setNull();

		} else {
			Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

			for (Json::ArrayIndex i=0; i < count; ++i) {
				value.push_back((*_deserializer_stack.top())[name][i].asInt64());
			}

			array = value;
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<std::vector<uint64_t>>& array)
{
	std::vector<uint64_t> value;

	if (_deserializer_stack.top()->isMember(name)) {

		if ((*_deserializer_stack.top())[name].isNull()) {
			array.setNull();

		} else {
			Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

			for (Json::ArrayIndex i=0; i < count; ++i) {
				value.push_back((*_deserializer_stack.top())[name][i].asUInt64());
			}

			array = value;
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<std::vector<double>>& array)
{
	std::vector<double> value;

	if (_deserializer_stack.top()->isMember(name)) {

		if ((*_deserializer_stack.top())[name].isNull()) {
			array.setNull();

		} else {

			Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

			for (Json::ArrayIndex i=0; i < count; ++i) {
				value.push_back((*_deserializer_stack.top())[name][i].asDouble());
			}

			array = value;
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

void json_serializer::deserialize(const std::string& name, nullable<std::vector<bool>>& array)
{
	std::vector<bool> value;

	if (_deserializer_stack.top()->isMember(name)) {

		if ((*_deserializer_stack.top())[name].isNull()) {
			array.setNull();

		} else {

			Json::ArrayIndex count = (*_deserializer_stack.top())[name].size();

			for (Json::ArrayIndex i=0; i < count; ++i) {
				value.push_back((*_deserializer_stack.top())[name][i].asBool());
			}

			array = value;
		}

	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

// Object and object arrays

void json_serializer::deserialize(const std::string& name, serializable_object* object)
{
	if (name == "") {
		Json::Reader reader;

		const char* data = _request.data();
		size_t length = _request.size();

		reader.parse((const char*)data, (const char*)(data + length), _deserializer_value);

		_deserializer_stack.push(&_deserializer_value);
		object->deserialize_fields(this);

	} else {
		if (_deserializer_stack.top()->isMember(name)) {
			_deserializer_stack.push(&((*_deserializer_stack.top())[name]));
			object->deserialize_fields(this);
			_deserializer_stack.pop();

		} else {
			throw serializer_field_not_found_exception(name.c_str());
		}
	}
}

void json_serializer::deserialize(const std::string& name, std::vector<serializable_object*> object_array)
{
	if (_deserializer_stack.top()->isMember(name)) {
		for (Json::ArrayIndex i=0; i < object_array.size(); ++i) {
			_deserializer_stack.push(&((*_deserializer_stack.top())[name][i]));
			object_array[i]->deserialize_fields(this);
			_deserializer_stack.pop();
		}
	} else {
		throw serializer_field_not_found_exception(name.c_str());
	}
}

int json_serializer::array_length(const std::string& name)
{
	return (*_deserializer_stack.top())[name].size();
}

std::string json_serializer::commit()
{
	std::string json = Json::FastWriter().write(_serializer_stack.top());
	return json;
}

static size_t unwrap(char* buffer, size_t length)
{
	size_t si = 0;
	size_t di = 0;
	while (si < length) {
		if (buffer[si] != '\n') {
			buffer[di++] = buffer[si++];
		} else {
			si++;
		}
	}

	return di;
}

std::string json_serializer::base64_encode(const std::vector<uint8_t>& in)
{
	base64_encodestate s;
	size_t cnt;

	char* output = new char[in.size() * 4];

	base64_init_encodestate(&s);
	cnt = base64_encode_block((const char*)in.data(), in.size(), output, &s);
	cnt += base64_encode_blockend(output + cnt, &s);

	cnt = unwrap(output, cnt);

	std::string result;
	result.reserve(cnt);
	result.resize(cnt);
	memcpy(&result[0], output, cnt);
	delete [] output;

	return result;
}

std::vector<uint8_t> json_serializer::base64_decode(const std::string& in)
{
	base64_decodestate s;
	size_t cnt;

	char* output = new char[in.size()];

	base64_init_decodestate(&s);
	cnt = base64_decode_block(in.c_str(), in.size(), output, &s);

	std::vector<uint8_t> result(output, output + cnt);
	delete [] output;

	return result;
}

}
