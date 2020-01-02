FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/Corristo/metal.git
  GIT_TAG c17c8ad6d65e07b2eb2903f0f404bc5792a0c28c
)

FetchContent_GetProperties(metal)
if(NOT metal_POPULATED)
  set(TMP_BUILD_TESTS OFF CACHE BOOL "Do not build tmp's tests")
  FetchContent_MakeAvailable(metal)
endif()

add_library(Metal::Metal ALIAS Metal)
