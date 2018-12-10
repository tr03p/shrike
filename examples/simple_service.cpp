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

#include "simple_data.h"

#include <shrike/shrike.h>

#include <iostream>
#include <thread>


shrike::http_response sum_array(const shrike::http_request& request)
{
	std::cout << "Request received" << std::endl;

	sum_array_request request_obj;
	request_obj.deserialize(request.data_to_string(), shrike::json_serializer::create);

	int sum = 0;
	for (const auto& i : request_obj.values) {
		sum += i;
	}

	sum_array_response response_obj(sum);

	return shrike::http_response(
		response_obj.serialize(shrike::json_serializer::create),
		shrike::http_response::CONTENT_TYPE_APPLICATION_JSON);
}

int main(int argc, char* argv[])
{
	std::cout << "Starting service on localhost:5555" << std::endl;

	shrike::http_service service(5555);

	service.register_method("simple_service/sum_array", &sum_array);

	std::cout << "Waiting for requests ..." << std::endl;

	while (1) {
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	return 0;
}
