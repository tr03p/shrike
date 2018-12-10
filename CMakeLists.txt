project(libshrike)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)


file(GLOB_RECURSE HEADER_FILES "include/*.h")
add_custom_target(shrike_header_files SOURCES ${HEADER_FILES})


add_library(
	shrike
	STATIC

	source/http/httprequest.cpp
	source/http/httpresponse.cpp
	source/http/httpservice.cpp
	source/http/httpservice_impl.cpp
	source/http/httpclient.cpp
	source/http/httpclient_impl.cpp
	source/http/tokenizer.cpp
	source/http/url_codec.cpp

	source/serialization/jsonserializer.cpp
	source/serialization/objectserializer.cpp
	source/serialization/serializableobject.cpp
)

target_include_directories(shrike PUBLIC include)

target_link_libraries(shrike PRIVATE microhttpd curl pthread jsoncpp b64)



add_executable(simple_client examples/simple_client.cpp)
target_link_libraries(simple_client shrike)

add_executable(simple_service examples/simple_service.cpp)
target_link_libraries(simple_service shrike)
