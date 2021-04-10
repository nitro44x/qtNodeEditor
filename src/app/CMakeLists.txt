cmake_minimum_required(VERSION 3.15.0)

set(srcs 
app.hpp
app.cpp
)

add_executable(qtNodeEditor ${srcs})
target_link_libraries(qtNodeEditor PRIVATE qtNodeEditorCore)