cmake_minimum_required(VERSION 3.15.0)

set(srcs 
    mainWindow.cpp
    mainWindow.ui
    sceneWidget.cpp
    node.hpp
    node.cpp
    edge.hpp
    edge.cpp
)

set(includes
    ${PUBLIC_INCLUDE_DIR}/forms/mainWindow.hpp
    ${PUBLIC_INCLUDE_DIR}/forms/sceneWidget.hpp
    ${PUBLIC_INCLUDE_DIR}/forms/exports.hpp
)

add_library(qtNodeEditorForms SHARED ${srcs} ${includes})

# this was needed when the lib was static.
#set_property(SOURCE ${includes} PROPERTY SKIP_AUTOGEN ON)

target_include_directories(qtNodeEditorForms PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(qtNodeEditorForms PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)
