add_executable(fold_composition
  composition.cpp
)

target_link_libraries(fold_composition
  PRIVATE
    folds::folds
)
