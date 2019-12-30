include(FetchContent)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

include(boost_tmp)

if (BEAUTIFOLDS_BUILD_TESTS)
  include(gtest)
endif()

