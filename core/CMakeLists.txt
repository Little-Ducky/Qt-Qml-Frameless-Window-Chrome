cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME AppChrome)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PLATFORM_SOURCES)
set(PLATFORM_QML_FILES)
set(PLATFORM_INCLUDE_PLATFORM)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

if(WIN32)
    list(APPEND PLATFORM_SOURCES
        platform/windowsplatform/WindowsPlatform.h
        platform/windowsplatform/WindowsPlatform.cpp
        platform/windowsplatform/utils/WindowsUtils.h
        platform/windowsplatform/utils/WindowsUtils.cpp
    )

    list(APPEND PLATFORM_QML_FILES
        qml/appchrome/appcaption/windows/DefaultAppCaption.qml
    )

    list(APPEND PLATFORM_INCLUDE_PLATFORM
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/windowsplatform
    )

elseif(APPLE)
    list(APPEND PLATFORM_SOURCES
        platform/macplatform/MacPlatform.h
        platform/macplatform/MacPlatform.mm
        platform/macplatform/utils/MacUtils.h
        platform/macplatform/utils/MacUtils.cpp
    )

    list(APPEND PLATFORM_QML_FILES
        qml/appchrome/appcaption/mac/DefaultAppCaption.qml
    )

    list(APPEND PLATFORM_INCLUDE_PLATFORM
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/macplatform
    )

elseif(UNIX)
    list(APPEND PLATFORM_SOURCES
        platform/linuxplatform/LinuxPlatform.h
        platform/linuxplatform/LinuxPlatform.cpp
        platform/linuxplatform/utils/LinuxUtils.h
        platform/linuxplatform/utils/LinuxUtils.cpp
    )

    list(APPEND PLATFORM_QML_FILES
        qml/appchrome/appcaption/linux/DefaultAppCaption.qml
    )

    list(APPEND PLATFORM_INCLUDE_PLATFORM
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/linuxplatform
    )
endif()

qt_add_library(${TARGET_NAME} STATIC)

qt_add_qml_module(${TARGET_NAME}
    URI ${TARGET_NAME}

    VERSION 1.0

    QML_FILES
        qml/appchrome/appcaption/BaseCaption.qml

        qml/views/AppChrome.qml

        qml/appchrome/controls/buttons/DefaultCaptionButton.qml

        ${PLATFORM_QML_FILES}

    SOURCES
        domain/WindowConstants.h

        platform/IPlatform.h
        platform/BaseWindow.h

        controllers/captioncontroller/CaptionController.h
        controllers/captioncontroller/CaptionController.cpp

        controllers/windowcontroller/WindowController.h
        controllers/windowcontroller/WindowController.cpp

        ${PLATFORM_SOURCES}
)

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${PLATFORM_INCLUDE_PLATFORM}
)
set_target_properties(${TARGET_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

target_link_libraries(${TARGET_NAME}
    PRIVATE Qt6::Quick
)

install(TARGETS ${TARGET_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
