cmake_minimum_required(VERSION 3.16)

project(qtqml_framework VERSION ${BUILD_VERSION})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(BUILD_DOC "Build document using doxygen" OFF)
option(BUILD_TEST "Build test application" ON)
option(BUILD_SHARED_LIBS "Build share library" ON)

# Install header files
file(GLOB INSTALL_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

# Build header files
file(
    GLOB
    INC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.hpp
)

# Build source files
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.c
)

# Qml file
list(APPEND QML_FILES qml/LoaderContainer.qml qml/LoaderScreen.qml)

# Use to set the singleton in qmldir file
# set_source_files_properties(${QML_FILES} PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

find_package(
    Qt6
    COMPONENTS Core Gui Qml Quick AppManLauncherPrivate DBus
    REQUIRED
)

if(NOT BUILD_SHARED_LIBS)
    qt6_add_library(${PROJECT_NAME} STATIC)
endif()

# Need to add inc files to generate the moc files
qt6_add_qml_module(
    ${PROJECT_NAME}
    URI
    "QtQml.HMI"
    VERSION
    ${PROJECT_VERSION}
    RESOURCE_PREFIX
    "modules/qml"
    QML_FILES
    ${QML_FILES}
    SOURCES
    ${INC_FILES}
    ${SRC_FILES}
    # OUTPUT_DIRECTORY
    # ${CMAKE_INSTALL_PREFIX}/modules
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/src/*/
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/*/>
           $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

# This define flags us as a "launcher" and allows us to link against the AppMan's private libraries
target_compile_definitions(${PROJECT_NAME} PUBLIC AM_COMPILING_LAUNCHER)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::AppManLauncherPrivate
                           Qt6::DBus
)

if(BUILD_TEST)
    add_subdirectory(test)
endif()

if(BUILD_DOC)
    add_subdirectory(doc)
endif()

# Update version to output libraries
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_property(TARGET ${PROJECT_NAME} PROPERTY PUBLIC_HEADER ${INSTALL_HEADER_FILES})

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)
