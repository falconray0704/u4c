
add_executable(Timestamp_unittest Timestamp_unittest.cc)
target_link_libraries(Timestamp_unittest u4c_base gtest gtest_main)
add_test(NAME Timestamp_unittest COMMAND Timestamp_unittest)

add_executable(Date_unittest Date_unittest.cc)
target_link_libraries(Date_unittest u4c_base gtest gtest_main)
add_test(NAME Date_unittest COMMAND Date_unittest)

add_executable(Vector_unittest Vector_unittest.cc)
target_link_libraries(Vector_unittest u4c_base gtest gtest_main)
add_test(NAME Vector_unittest COMMAND Vector_unittest)

add_executable(UAtomic_unittest UAtomic_unittest.cc)
target_link_libraries(UAtomic_unittest u4c_base gtest gtest_main)
add_test(NAME UAtomic_unittest COMMAND UAtomic_unittest)
