include(FetchContent)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# we don't care about warnings in external projects, turn them off
add_compile_options(
  $<$<CXX_COMPILER_ID:Clang>:-Wno-everything>
  $<$<CXX_COMPILER_ID:MSVC>:/w>
  $<$<CXX_COMPILER_ID:GNU>:-w>
)

include(metal)

if (BEAUTIFOLDS_BUILD_TESTS)
  include(gtest)
  include(rapidcheck)
endif()

