FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG master
)

set(INSTALL_GTEST OFF)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

FetchContent_MakeAvailable(googletest)

add_library(GTest::gtest ALIAS gtest)
add_library(GTest::main ALIAS gtest_main)
add_library(GMock::gmock ALIAS gmock)
add_library(GMock::main ALIAS gmock_main)
