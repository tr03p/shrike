# Overview

This project aims to implement an easy to use microservice API framework in C++.
It is built on existing proven libraries such as libmicrohttpd and libcurl. The API
consists of three main parts:

## HTTP service API

The HTTP service API runs a listening HTTP service and marshals HTTP requests to user-supplied callback functions.

## HTTP client API

The HTTP client API is used to perform GET or POST calls to other services.

## Object serialization API

The object serialization API is used to serialize and deserialize data objects to a transport format suitable for
HTTP requests such as JSON.
