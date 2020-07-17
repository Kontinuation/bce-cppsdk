# Integrates googletest at configure time.  Based on the instructions at
# https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project

# Set up the external googletest project, downloading the latest from Github
# master if requested.
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in
  ${CMAKE_BINARY_DIR}/jsoncpp-download/CMakeLists.txt
)

# configure_file(third_party/CMakeLists.txt.in jsoncpp-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-download )
if(result)
  message(FATAL_ERROR "CMake step for jsoncpp failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-download )
if(result)
  message(FATAL_ERROR "Build step for jsoncpp failed: ${result}")
endif()

# Add jsoncpp directly to our build
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-src
                 ${CMAKE_CURRENT_BINARY_DIR}/jsoncpp-build
                 EXCLUDE_FROM_ALL)
