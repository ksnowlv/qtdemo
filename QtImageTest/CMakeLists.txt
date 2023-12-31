cmake_minimum_required(VERSION 3.5)

project(QtImageTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#添加所有的头文件,源文件,.ui文件,资源文件
file(GLOB HEADERS *.h *.hpp)
file(GLOB SOURCES *.cpp *.cxx *.cc)
file(GLOB FORMS *.ui)
file(GLOB RESOURCES *.qrc)

# 设置生成的项目筛选器
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})
source_group("Resource Files" FILES ${RESOURCES})
source_group("Form Files" FILES ${FORMS})
source_group("Translation Files" FILES ${TRANSLATIONS})


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# set(PROJECT_SOURCES
#         main.cpp
#         mainwindow.cpp
#         mainwindow.h
#         mainwindow.ui
# )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtImageTest
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${SOURCES}
        ${FORMS}
        ${RESOURCES}
        ${HEADERS}
        images.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtImageTest APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtImageTest SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtImageTest
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QtImageTest PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QtImageTest)
endif()
set_target_properties(QtImageTest PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtImageTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtImageTest)
endif()
