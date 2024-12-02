cmake_minimum_required(VERSION 3.10)

project(Comm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS system)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(Comm ${SOURCES})
target_link_libraries(Comm PRIVATE Boost::boost Boost::system)
target_include_directories(Comm PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(tests)