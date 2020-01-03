FetchContent_Declare(
  rapidcheck
  GIT_REPOSITORY https://github.com/Corristo/rapidcheck.git
  GIT_TAG 4df02602aae74ff1711611b64630d3fd8ae40571
)

set(RC_ENABLE_TESTS OFF)
set(RC_ENABLE_EXAMPLES OFF)

FetchContent_MakeAvailable(rapidcheck)
add_library(Rapidcheck::Rapidcheck ALIAS rapidcheck)
