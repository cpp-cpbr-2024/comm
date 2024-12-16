cmake_minimum_required(VERSION 3.10)

project(Comm)

# set(OVERRIDE_BOOST_PATH "/opt/homebrew/Cellar/boost/1.87.0/include")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED COMPONENTS system)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(Comm ${SOURCES})
#target_link_libraries(Comm PRIVATE Boost::boost Boost::system Boost::asio)
if(DEFINED OVERRIDE_BOOST_PATH)
    target_include_directories(Comm PUBLIC ${PROJECT_SOURCE_DIR}/include ${OVERRIDE_BOOST_PATH})
else()
    target_link_libraries(Comm PRIVATE Boost::boost Boost::system)
    target_include_directories(Comm PUBLIC ${PROJECT_SOURCE_DIR}/include)
endif()

add_subdirectory(tests)