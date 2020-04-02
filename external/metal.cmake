FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/Corristo/metal.git
  GIT_TAG 9a0df5d1a9a82c8a17dc9c1026091df4748b7184
)

FetchContent_GetProperties(metal)
if(NOT metal_POPULATED)
  set(METAL_BUILD_TESTS OFF CACHE BOOL "Do not build metal's tests")
  set(METAL_BUILD_EXAMPLES OFF CACHE BOOL "Do not build metal's examples")
  set(METAL_BUILD_DOC OFF CACHE BOOL "Do not build metal's documentation")
  FetchContent_MakeAvailable(metal)
endif()

add_library(Metal::Metal ALIAS Metal)
