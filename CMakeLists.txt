cmake_minimum_required(VERSION 3.20..)
project(serde)

set(CMAKE_CXX_STANDARD 23)
include_directories(reflect-cpp/include reflect-cpp/include/rfl/thirdparty glaze/include)
add_executable(serde main.cpp  reflect-cpp/src/reflectcpp.cpp reflect-cpp/src/reflectcpp_json.cpp reflect-cpp/src/yyjson.c)
