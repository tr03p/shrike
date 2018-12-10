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


int main(int argc, char* argv[])
{
	shrike::http_client http_client;

	std::vector<int> array = { 1, 2, 3, 4, 5 };

	sum_array_request request_obj(array);

	shrike::http_request request(
		"http://localhost:5555/simple_service/sum_array",
		request_obj.serialize(shrike::json_serializer::create));

	shrike::http_response response(http_client.post(request));

	if (!response) {
		std::cout << "HTTP response is not valid" << std::endl;
		return 1;
	}

	std::cout << "HTTP status code: " << response.status_code() << std::endl;

	sum_array_response response_obj;
	response_obj.deserialize(response.data_to_string(), shrike::json_serializer::create);

	std::cout << "Sum of elements: " << response_obj.result << std::endl;

	return 0;
}
