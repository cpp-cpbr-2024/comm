cmake_minimum_required(VERSION 3.10)

project(Comm)
set(CMAKE_CXX_STANDARD 17)
find_package(Boost REQUIRED COMPONENTS system)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Comm ${SOURCES})
target_link_libraries(Comm Boost::system)