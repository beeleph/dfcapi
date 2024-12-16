cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(curl_test
  VERSION 0.2.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
)

find_package(CURL REQUIRED) 
#add_executable (dfcapi dfcapi.hpp)
add_executable (test test.cpp)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(test ${CURL_LIBRARIES})
set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
