#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "folds/folds/fold.hpp"

TEST(Operators, SummingTwoFoldsReturnsAFold) {
  auto const fold_1 = folds::Fold{[](auto const i) { return i; },
                                  [](auto const j) { return 2 * j; }};

  auto const fold_2 = folds::Fold{[](auto const i) { return i / 3; },
                                  [](auto const j) { return j / 2; }};

  auto const sum = fold_1 + fold_2;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(sum)>>);
}

TEST(Operators, SummingAFoldAndAConstantReturnsAFold) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  auto const sum = fold + 1;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(sum)>>);
}

TEST(Operators, SummingAConstantAndAFoldReturnsAFold) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  auto const sum = 1 + fold;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(sum)>>);
}

TEST(Operators, MultiplyingTwoFoldsReturnsAFold) {
  auto const fold_1 = folds::Fold{[](auto const i) { return i; },
                                  [](auto const j) { return 2 * j; }};

  auto const fold_2 = folds::Fold{[](auto const i) { return i / 3; },
                                  [](auto const j) { return j / 2; }};

  auto const product = fold_1 * fold_2;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(product)>>);
}

TEST(Operators, MultiplyingAFoldAndAConstantReturnsAFold) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  auto const product = fold * 2;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(product)>>);
}

TEST(Operators, MultiplyingAConstantAndAFoldReturnsAFold) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  auto const product = 2 * fold;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(product)>>);
}

TEST(Operators, SubtractingTwoFoldsReturnsAFold) {
  auto const fold_1 = folds::Fold{[](auto const i) { return i; },
                                  [](auto const j) { return 2 * j; }};

  auto const fold_2 = folds::Fold{[](auto const i) { return i / 3; },
                                  [](auto const j) { return j / 2; }};

  auto const difference = fold_1 - fold_2;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(difference)>>);
}

TEST(Operators, SubtractingAFoldAndAConstantReturnsAFold) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  auto const difference = fold - 1;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(difference)>>);
}

TEST(Operators, SubtractingAConstantAndAFoldReturnsAFold) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  auto const difference = 1 - fold;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(difference)>>);
}

TEST(Operators, DividingTwoFoldsReturnsAFold) {
  auto const fold_1 = folds::Fold{[](auto const i) { return i; },
                                  [](auto const j) { return 2 * j; }};

  auto const fold_2 = folds::Fold{[](auto const i) { return i / 3; },
                                  [](auto const j) { return j / 2; }};

  auto const quotient = fold_1 / fold_2;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(quotient)>>);
}

TEST(Operators, DividingAFoldAndAConstantReturnsAFold) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  auto const quotient = fold / 1;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(quotient)>>);
}

TEST(Operators, DividingAConstantAndAFoldReturnsAFold) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  auto const quotient = 1 / fold;

  EXPECT_TRUE(folds::is_fold_v<std::remove_const_t<decltype(quotient)>>);
}
