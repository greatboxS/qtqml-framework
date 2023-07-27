cmake_minimum_required(VERSION 3.10)

project(doxygen-doc VERSION 1.0)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(Doxygen.in ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(
        doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
        SOURCES ${PROJECT_BINARY_DIR}/Doxyfile
        COMMENT "Generating API documentation with Doxygen"
    )
endif(DOXYGEN_FOUND)
