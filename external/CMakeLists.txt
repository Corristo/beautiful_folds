include(FetchContent)

FetchContent_Declare(
  tmp
  GIT_REPOSITORY https://github.com/Corristo/tmp.git
  GIT_TAG f8d65da
)

FetchContent_GetProperties(tmp)
if(NOT tmp_POPULATED)
  set(TMP_BUILD_TESTS OFF CACHE BOOL "Do not build tmp's tests")
  FetchContent_MakeAvailable(tmp)
endif()

add_library(Boost::tmp ALIAS boost_tmp)
