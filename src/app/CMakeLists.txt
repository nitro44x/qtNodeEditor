cmake_minimum_required(VERSION 3.15.0)

set(srcs 
app.cpp
mainWindow.hpp
mainWindow.cpp
mainWindow.ui
)

add_executable(qtNodeEditor WIN32 ${srcs})
target_link_libraries(qtNodeEditor PRIVATE qtNodeEditorCore)
target_link_libraries(qtNodeEditor PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)