cmake_minimum_required(VERSION 3.15.0)

set(srcs 
    lib.hpp
    lib.cpp
)

add_library(qtNodeEditorCore SHARED ${srcs})