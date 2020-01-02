include(FetchContent)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

include(metal)

if (BEAUTIFOLDS_BUILD_TESTS)
  include(gtest)
endif()

