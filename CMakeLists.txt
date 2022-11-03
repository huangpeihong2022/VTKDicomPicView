cmake_minimum_required(VERSION 3.14)

project(VtkDicomPicView VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    list(APPEND CMAKE_PREFIX_PATH D:/VTK_/master/debug/lib/cmake/vtk-9.2)
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    list(APPEND CMAKE_PREFIX_PATH D:/VTK_/master/release/lib/cmake/vtk-9.2)
else()
    message("Missing parameter: -DCMAKE_BUILD_TYPE=Debug(/Release)")
endif()

find_package(VTK REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Charts)

set(PROJECT_SOURCES
        ./src/main.cpp
        ./src/opendcm.h
        ./src/opendcm.cpp
        ./src/mydialog.h
        ./src/mydialog.cpp
        ./src/rewriteinteractor.h
        ./src/rewriteinteractor.cpp
        ./src/rgbachange.h
        ./src/rgbachange.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VtkDicomPicView
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DicomPicView APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(VtkDicomPicView SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(VtkDicomPicView
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(VtkDicomPicView
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(VtkDicomPicView
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick ${VTK_LIBRARIES})

set_target_properties(VtkDicomPicView PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(VtkDicomPicView PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(VtkDicomPicView)
    qt_finalize_executable(VtkDicomPicView)
endif()

install(TARGETS VtkDicomPicView
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)


vtk_module_autoinit(
    TARGETS ${PROJECT_NAME}
    MODULES ${VTK_LIBRARIES}
    )
