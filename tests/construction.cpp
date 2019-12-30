#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "folds/folds/fold.hpp"

using testing::Eq;

TEST(Construction, FoldCanBeConstructedFromTwoFunctionObjects) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const j) { return 2 * j; }};

  EXPECT_THAT(fold.tally(4), Eq(4));
  EXPECT_THAT(fold.summarize(4), Eq(8));
}

static int id(int const i) { return i; }
static int multiply_by_2(int const i) { return 2 * i; }
TEST(Construction, FoldCanBeConstructedFromTwoFunctionPointers) {
  auto const fold = folds::Fold{id, multiply_by_2};

  EXPECT_THAT(fold.tally(4), Eq(4));
  EXPECT_THAT(fold.summarize(4), Eq(8));
}

TEST(Construction, FoldCanBeConstructedFromAFoldlikeObject) {
  struct foldlike {
    int tally(int i) const { return i; }
    int summarize(int i) const { return 2 * i; }
  };

  auto const fold = folds::Fold{foldlike{}};

  EXPECT_THAT(fold.tally(4), Eq(4));
  EXPECT_THAT(fold.summarize(4), Eq(8));
}
