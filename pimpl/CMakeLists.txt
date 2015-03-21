cmake_minimum_required(VERSION 2.8.4)
project(pimpl)

# modify as needed
set(SOURCE_FILES
        main.cpp
        book.cpp
    )

# modify as needed
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic -Wall -Wextra -Weffc++")

add_executable(pimpl ${SOURCE_FILES})
