#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "folds/folds/fold.hpp"

using ::testing::Eq;

TEST(Sizes, FoldDefinedByTwoEmptyFunctionObjectsHasSize1) {
  auto const fold =
      folds::Fold{[](auto i) { return i; }, [](auto i) { return i; }};

  EXPECT_THAT(sizeof(fold), Eq(1));
}

TEST(Sizes, FoldDefinedByTheSameFunctionObjectTwiceHasSize1) {
  auto const id = [](auto i) { return i; };
  auto const fold = folds::Fold{id, id};

  EXPECT_THAT(sizeof(fold), Eq(1));
}

static int id(int const i) { return i; }

TEST(Sizes, FoldDefinedByTwoFunctionPointersRegularlyHasSizeOfTwoPointers) {
  auto const fold = folds::Fold{id, id};
  EXPECT_THAT(sizeof(fold), Eq(2 * sizeof(void*)));
}

TEST(Sizes, FoldDefinedByTwoFunctionPointersUsingMakeFoldHelperHasSize1) {
  auto const fold = folds::make_fold<id, id>{};
  EXPECT_THAT(sizeof(fold), Eq(1));
}
