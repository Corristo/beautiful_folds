cmake_minimum_required(VERSION 3.12)

project(
  "Beautiful Folds"
  VERSION 0.0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

add_subdirectory(external)
add_subdirectory(examples)
add_subdirectory(include)
