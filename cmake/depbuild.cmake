set(PROJECT_DEPS_DIR ${PROJECT_SOURCE_DIR}/deps)
set(PROJECT_CMAKE_MOD_DIR ${PROJECT_SOURCE_DIR}/cmake)

configure_file(
  ${PROJECT_CMAKE_MOD_DIR}/CMakeLists.txt.in
  ${PROJECT_DEPS_DIR}/CMakeLists.txt
  )

execute_process(
  COMMAND ${CMAKE_COMMAND} ${PROJECT_DEPS_DIR}
  WORKING_DIRECTORY ${PROJECT_DEPS_DIR}
  )

execute_process(
  COMMAND ${CMAKE_COMMAND} --build ${PROJECT_DEPS_DIR}
  WORKING_DIRECTORY ${PROJECT_DEPS_DIR}
  )

include_directories(
  ${PROJECT_DEPS_DIR}/poco/include
  )

link_directories(
  ${PROJECT_DEPS_DIR}/poco/lib
  )
