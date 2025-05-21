

foreach(i RANGE 1 7)
  set(SOURCES "${i}.cpp")
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${i}")
    file(GLOB_RECURSE SOURCES "${i}/*.cpp")
  endif()
  add_executable(${i} ${SOURCES} utils.cpp)
endforeach()

include_directories(QUOTE .)

add_custom_target(
  link_inputs ALL
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/../inputs/ ${CMAKE_BINARY_DIR}/bin/inputs
)
