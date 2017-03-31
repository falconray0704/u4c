set(base_SRCS
  timestamp.c
  date.c
  vector.c
  )

add_library(u4c_base ${base_SRCS})
target_link_libraries(u4c_base pthread)


add_library(u4c_base_cpp11 ${base_SRCS})
target_link_libraries(u4c_base_cpp11 pthread)
set_target_properties(u4c_base_cpp11 PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS u4c_base DESTINATION lib)
install(TARGETS u4c_base_cpp11 DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/u4c/base)

if(NOT CMAKE_BUILD_NO_EXAMPLES)
  add_subdirectory(tests)
endif()
