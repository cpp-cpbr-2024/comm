add_executable(CommTest test.cpp)
target_link_libraries(CommTest PRIVATE Comm)
add_test(NAME CommTest COMMAND CommTest)