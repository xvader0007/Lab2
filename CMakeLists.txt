cmake_minimum_required(VERSION 3.28)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab2
        main.cpp
        dynamic_array.h
        linked_list.h
        sequence.h
        array_sequence.h
        mutable_array_sequence.h
        list_sequence.h
        immutable_array_sequence.h
        mutable_list_sequence.h
        immutable_list_sequence.h)
