FetchContent_Declare(
  tmp
  GIT_REPOSITORY https://github.com/Corristo/tmp.git
  GIT_TAG 616affe19921eba0d27e1b79cbf539edce39c6d8
)

FetchContent_GetProperties(tmp)
if(NOT tmp_POPULATED)
  set(TMP_BUILD_TESTS OFF CACHE BOOL "Do not build tmp's tests")
  FetchContent_MakeAvailable(tmp)
endif()

add_library(Boost::tmp ALIAS boost_tmp)
