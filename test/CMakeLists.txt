cmake_minimum_required(VERSION 3.16)

project(test)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

qt_add_resources(QT_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/qml.qrc)
qt_add_executable(${PROJECT_NAME} ${SRC_FILES} ${QT_RESOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE qtqml-framework)
