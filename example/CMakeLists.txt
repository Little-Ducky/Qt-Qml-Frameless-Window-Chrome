cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(exampleTarget
    main.cpp
)

qt_add_qml_module(exampleTarget
    URI exampleModule

    QML_FILES
        Main.qml
        qml/customcaption/controls/CustomCaptionButton.qml
        qml/customcaption/CustomCaption.qml

)

target_link_libraries(exampleTarget
    PRIVATE Qt6::Quick
    PRIVATE AppChrome
)

install(TARGETS exampleTarget
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)