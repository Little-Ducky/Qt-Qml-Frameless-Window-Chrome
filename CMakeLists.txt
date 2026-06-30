cmake_minimum_required(VERSION 3.16)

project(AppChromeExample)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)

add_subdirectory(core)
add_subdirectory(example)