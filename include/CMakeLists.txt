add_library(folds INTERFACE)
target_include_directories(folds
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(folds
  INTERFACE
    Metal::Metal
)

target_compile_options(folds
  INTERFACE
    $<$<CXX_COMPILER_ID:GNU>:-fconcepts>
)

add_library(folds::folds ALIAS folds)
