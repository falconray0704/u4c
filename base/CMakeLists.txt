set(base_SRCS
  timestamp.c
  )

add_library(u4c_base ${base_SRCS})
target_link_libraries(u4c_base pthread)

install(TARGETS u4c_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/u4c/base)

if(NOT CMAKE_BUILD_NO_EXAMPLES)
  add_subdirectory(tests)
endif()
