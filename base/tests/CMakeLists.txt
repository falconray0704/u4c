
add_executable(Timestamp_unittest Timestamp_unittest.cc)
target_link_libraries(Timestamp_unittest u4c_base gtest gtest_main)
add_test(NAME Timestamp_unittest COMMAND Timestamp_unittest)

