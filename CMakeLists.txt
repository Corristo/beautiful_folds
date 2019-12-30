cmake_minimum_required(VERSION 3.12)

project(
  "Beautiful Folds"
  VERSION 0.0.1
  LANGUAGES CXX
)

option(BEAUTIFOLDS_BUILD_TESTS "Whether to build the tests of the beautifolds library" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(external)
add_subdirectory(examples)
add_subdirectory(include)

if (BEAUTIFOLDS_BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
    --force-new-ctest-process --output-on-failure
    --build-config "$<CONFIGURATION>")
  add_subdirectory(tests)
endif()
