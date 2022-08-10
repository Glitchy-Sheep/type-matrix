cmake_minimum_required(VERSION 3.20)

project(type-matrix)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include_directories(${INCLUDE_DIR})

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/conf.cpp
)

set(HEADERS
    ${INCLUDE_DIR}/conf.h
    ${INCLUDE_DIR}/exit_errors.h
)

add_executable(main ${SOURCES} ${HEADERS})

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(main ${CONAN_LIBS})