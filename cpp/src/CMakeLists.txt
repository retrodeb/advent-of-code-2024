

foreach(i RANGE 1 5)
  add_executable(${i} ${i}.cpp utils.cpp)
endforeach()

add_custom_target(
  link_inputs ALL
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/../inputs/ ${CMAKE_BINARY_DIR}/bin/inputs
)
