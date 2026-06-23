cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME AppChrome)
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

set(QML_MODULE ${PROJECT_NAME})
set(PLATFORM_SOURCES)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_add_executable(${PROJECT_NAME}
    main.cpp
    qml/appmainwindow/controls/buttons/CaptionButton.qml
    qml/views/AppChrome.qml
)

if(WIN32)
    list(APPEND PLATFORM_SOURCES
        platform/ui/appmainwindow/windows/WindowsPlatform.cpp
        platform/ui/appmainwindow/windows/utils/utils.h
    )

elseif(APPLE)
    list(APPEND PLATFORM_SOURCES
        platform/ui/appmainwindow/mac/MacPlatform.cpp
    )

elseif(UNIX)
    list(APPEND PLATFORM_SOURCES
        platform/ui/appmainwindow/linux/LinuxPlatform.cpp
    )
endif()

target_compile_definitions(${QML_MODULE} PRIVATE
    QML_MODULE="${QML_MODULE}"
)

qt_add_qml_module(${QML_MODULE}
    URI ${QML_MODULE}
    QML_FILES
        Main.qml
        qml/views/AppChrome.qml
        qml/appmainwindow/appcaption/AppCaption.qml
        qml/appmainwindow/controls/buttons/CaptionButton.qml

    SOURCES
        application/Application.h

        platform/ui/appmainwindow/AppMainWindow.h

        ${PLATFORM_SOURCES}

        platform/ui/appmainwindow/appcaption/AppCaption.h platform/ui/appmainwindow/appcaption/AppCaption.cpp

        platform/ui/appmainwindow/appwindowcontroller/AppWindowController.h platform/ui/appmainwindow/appwindowcontroller/AppWindowController.cpp
)

target_include_directories(${QML_MODULE} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/ui
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${QML_MODULE} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Ducky_Player
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${QML_MODULE}
    PRIVATE Qt6::Quick
)

install(TARGETS ${QML_MODULE}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
