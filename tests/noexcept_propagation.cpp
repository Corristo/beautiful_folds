#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "folds/folds/fold.hpp"

TEST(NoexceptPropagation, TallyIsNoexceptWhenTallyFunctionObjectIsNoexcept) {
  auto const fold = folds::Fold{[](auto const i) noexcept { return i; },
                                [](auto const i) { return i; }};

  EXPECT_TRUE(noexcept(fold.tally(3)));
}

TEST(NoexceptPropagation,
     TallyIsNotNoexceptWhenTallyFunctionObjectIsNotNoexcept) {
  auto const fold = folds::Fold{[](auto const i) noexcept(false) { return i; },
                                [](auto const i) { return i; }};

  EXPECT_FALSE(noexcept(fold.tally(3)));
}

TEST(NoexceptPropagation,
     SummarizeIsNoexceptWhenSummarizeFunctionObjectIsNoexcept) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const i) noexcept { return i; }};

  EXPECT_TRUE(noexcept(fold.summarize(3)));
}

TEST(NoexceptPropagation,
     SummarizeIsNotNoexceptWhenSummarizeFunctionObjectIsNotNoexcept) {
  auto const fold = folds::Fold{[](auto const i) { return i; },
                                [](auto const i) noexcept(false) { return i; }};

  EXPECT_FALSE(noexcept(fold.summarize(3)));
}

TEST(NoexceptPropagation,
     TallyIsNoexceptWhenTallyMemberFunctionOfFoldLikeIsNoexcept) {
  struct foldlike {
    int tally(int const i) const noexcept { return i; }

    int summarize(int const i) const { return i; }
  };

  auto const fold = folds::Fold{foldlike{}};

  EXPECT_TRUE(noexcept(fold.tally(3)));
}

TEST(NoexceptPropagation,
     TallyIsNotNoexceptWhenTallyMemberFunctionOfFoldLikeIsNotNoexcept) {
  struct foldlike {
    int tally(int const i) const { return i; }

    int summarize(int const i) const { return i; }
  };
  auto const fold = folds::Fold{foldlike{}};

  EXPECT_FALSE(noexcept(fold.tally(3)));
}

TEST(NoexceptPropagation,
     SummarizeIsNoexceptWhenSummarizeMemberFunctionOfFoldLikeIsNoexcept) {
  struct foldlike {
    int tally(int const i) const { return i; }

    int summarize(int const i) const noexcept { return i; }
  };

  auto const fold = folds::Fold{foldlike{}};

  EXPECT_TRUE(noexcept(fold.summarize(3)));
}

TEST(NoexceptPropagation,
     SummarizeIsNotNoexceptWhenSummarizeMemberFunctionOfFoldLikeIsNotNoexcept) {
  struct foldlike {
    int tally(int const i) const { return i; }

    int summarize(int const i) const { return i; }
  };
  auto const fold = folds::Fold{foldlike{}};

  EXPECT_FALSE(noexcept(fold.summarize(3)));
}
