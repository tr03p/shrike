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

#ifndef SHRIKE_OBJECTSERIALIZER_H
#define SHRIKE_OBJECTSERIALIZER_H

#include <shrike/types.h>

#include <string>
#include <vector>

#include <stdint.h>


namespace shrike
{

class serializable_object;

class object_serializer
{
public:
	typedef object_serializer* (*create_serializer)(const std::string& request);

public:
	virtual ~object_serializer() {}
	object_serializer(const std::string& request);

	// Serialization

	// Basic types
	virtual void serialize(const std::string& name, int value) = 0;
	virtual void serialize(const std::string& name, unsigned int value) = 0;
	virtual void serialize(const std::string& name, int64_t value) = 0;
	virtual void serialize(const std::string& name, uint64_t value) = 0;
	virtual void serialize(const std::string& name, double value) = 0;
	virtual void serialize(const std::string& name, bool value) = 0;
	virtual void serialize(const std::string& name, const std::string& value) = 0;
	virtual void serialize(const std::string& name, const std::vector<uint8_t>& value) = 0;

	// Nullable basic types
	virtual void serialize(const std::string& name, const nullable<int>& value) = 0;
	virtual void serialize(const std::string& name, const nullable<unsigned int>& value) = 0;
	virtual void serialize(const std::string& name, const nullable<int64_t>& value) = 0;
	virtual void serialize(const std::string& name, const nullable<uint64_t>& value) = 0;
	virtual void serialize(const std::string& name, const nullable<double>& value) = 0;
	virtual void serialize(const std::string& name, const nullable<bool>& value) = 0;
	virtual void serialize(const std::string& name, const nullable<std::string>& value) = 0;
	virtual void serialize(const std::string& name, const nullable<std::vector<uint8_t>>& value) = 0;

	// Basic type arrays
	virtual void serialize(const std::string& name, const std::vector<int>& array) = 0;
	virtual void serialize(const std::string& name, const std::vector<unsigned int>& array) = 0;
	virtual void serialize(const std::string& name, const std::vector<int64_t>& array) = 0;
	virtual void serialize(const std::string& name, const std::vector<uint64_t>& array) = 0;
	virtual void serialize(const std::string& name, const std::vector<double>& array) = 0;
	virtual void serialize(const std::string& name, const std::vector<bool>& array) = 0;
	virtual void serialize(const std::string& name, const std::vector<std::string>& array) = 0;

	// Nullable basic type arrays
	virtual void serialize(const std::string& name, const nullable<std::vector<int>>& array) = 0;
	virtual void serialize(const std::string& name, const nullable<std::vector<unsigned int>>& array) = 0;
	virtual void serialize(const std::string& name, const nullable<std::vector<int64_t>>& array) = 0;
	virtual void serialize(const std::string& name, const nullable<std::vector<uint64_t>>& array) = 0;
	virtual void serialize(const std::string& name, const nullable<std::vector<double>>& array) = 0;
	virtual void serialize(const std::string& name, const nullable<std::vector<bool>>& array) = 0;
	virtual void serialize(const std::string& name, const nullable<std::vector<std::string>>& array) = 0;

	// Object and object array
	virtual void serialize(const std::string& name, serializable_object* object) = 0;
	virtual void serialize(const std::string& name, const std::vector<serializable_object*> object_array) = 0;

	// Deserialization

	// Basic types
	virtual void deserialize(const std::string& name, int& value) = 0;
	virtual void deserialize(const std::string& name, unsigned int& value) = 0;
	virtual void deserialize(const std::string& name, int64_t& value) = 0;
	virtual void deserialize(const std::string& name, uint64_t& value) = 0;
	virtual void deserialize(const std::string& name, double& value) = 0;
	virtual void deserialize(const std::string& name, bool& value) = 0;
	virtual void deserialize(const std::string& name, std::string& value) = 0;
	virtual void deserialize(const std::string& name, std::vector<uint8_t>& value) = 0;

	// Nullable basic types
	virtual void deserialize(const std::string& name, nullable<int>& value) = 0;
	virtual void deserialize(const std::string& name, nullable<unsigned int>& value) = 0;
	virtual void deserialize(const std::string& name, nullable<int64_t>& value) = 0;
	virtual void deserialize(const std::string& name, nullable<uint64_t>& value) = 0;
	virtual void deserialize(const std::string& name, nullable<double>& value) = 0;
	virtual void deserialize(const std::string& name, nullable<bool>& value) = 0;
	virtual void deserialize(const std::string& name, nullable<std::string>& value) = 0;
	virtual void deserialize(const std::string& name, nullable<std::vector<uint8_t>>& value) = 0;

	// Basic type arrays
	virtual void deserialize(const std::string& name, std::vector<int>& array) = 0;
	virtual void deserialize(const std::string& name, std::vector<unsigned int>& array) = 0;
	virtual void deserialize(const std::string& name, std::vector<int64_t>& array) = 0;
	virtual void deserialize(const std::string& name, std::vector<uint64_t>& array) = 0;
	virtual void deserialize(const std::string& name, std::vector<double>& array) = 0;
	virtual void deserialize(const std::string& name, std::vector<bool>& array) = 0;
	virtual void deserialize(const std::string& name, std::vector<std::string>& array) = 0;

	// Nullable basic type arrays
	virtual void deserialize(const std::string& name, nullable<std::vector<int>>& array) = 0;
	virtual void deserialize(const std::string& name, nullable<std::vector<unsigned int>>& array) = 0;
	virtual void deserialize(const std::string& name, nullable<std::vector<int64_t>>& array) = 0;
	virtual void deserialize(const std::string& name, nullable<std::vector<uint64_t>>& array) = 0;
	virtual void deserialize(const std::string& name, nullable<std::vector<double>>& array) = 0;
	virtual void deserialize(const std::string& name, nullable<std::vector<bool>>& array) = 0;
	virtual void deserialize(const std::string& name, nullable<std::vector<std::string>>& array) = 0;

	// Object and object arrays
	virtual void deserialize(const std::string& name, serializable_object* object) = 0;
	virtual void deserialize(const std::string& name, std::vector<serializable_object*> object_array) = 0;

	virtual bool contains(const std::string& name) = 0;
	virtual int array_length(const std::string& name) = 0;
	virtual std::string commit() = 0;

protected:
	const std::string _request;
};

}

#endif
