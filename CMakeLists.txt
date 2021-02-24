cmake_minimum_required(VERSION 3.17)

project(ft_containers)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

add_executable(test main.cpp)
include_directories(src/Iterator src/Misc test_related src/List src/Trees src)