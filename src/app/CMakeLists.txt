cmake_minimum_required(VERSION 3.15.0)

set(srcs 
    app.cpp
)

add_executable(qtNodeEditor WIN32 ${srcs})
target_include_directories(qtNodeEditor PRIVATE ${CMAKE_SOURCE_DIR}/include)
#target_link_libraries(qtNodeEditor PRIVATE qtNodeEditorCore)
target_link_libraries(qtNodeEditor PRIVATE qtNodeEditorForms)
target_link_libraries(qtNodeEditor PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)