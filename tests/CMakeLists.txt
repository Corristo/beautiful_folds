include(GoogleTest)

add_executable(size_tests sizes.cpp)
target_link_libraries(size_tests
  PRIVATE
    folds::folds
    GMock::main
)
gtest_discover_tests(size_tests)

add_executable(construction_tests construction.cpp)
target_link_libraries(construction_tests
  PRIVATE
    folds::folds
    GMock::main
)
gtest_discover_tests(construction_tests)

add_executable(noexcept_propagation_tests noexcept_propagation.cpp)
target_link_libraries(noexcept_propagation_tests
  PRIVATE
    folds::folds
    GMock::main
)
gtest_discover_tests(noexcept_propagation_tests)

add_executable(operators_tests operators.cpp)
target_link_libraries(operators_tests
  PRIVATE
    folds::folds
    GMock::main
)
gtest_discover_tests(operators_tests)
