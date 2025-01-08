add_executable(CommTest test.cpp)
target_link_libraries(CommTest PRIVATE Comm ws2_32)
add_test(NAME CommTest COMMAND CommTest)