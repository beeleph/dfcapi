cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(curl_test
  VERSION 0.2.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
)

find_package(CURL REQUIRED) 
add_executable (dfcapi dfcapi.cpp)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(dfcapi ${CURL_LIBRARIES})