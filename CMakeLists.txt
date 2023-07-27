cmake_minimum_required(VERSION 3.16)

project(qtqml-framework VERSION ${BUILD_VERSION})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(BUILD_DOC "Build document using doxygen" OFF)
option(BUILD_TEST "Build test application" ON)
option(BUILD_SHARED_LIBS "Build share library" ON)

if(BUILD_DOC)
    add_subdirectory(doc)
endif()

# Install header files
file(GLOB INSTALL_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*)

# Build header files
file(GLOB INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

# Build source files
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

find_package(
    Qt6
    COMPONENTS Core Gui Qml Quick AppManLauncherPrivate DBus
    REQUIRED
)

# Need to add inc files to generate the moc files
add_library(${PROJECT_NAME} ${INC_FILES} ${SRC_FILES})

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
target_compile_definitions(${PROJECT_NAME} PRIVATE AM_COMPILING_LAUNCHER)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::AppManLauncherPrivate
                            Qt6::DBus
)

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
