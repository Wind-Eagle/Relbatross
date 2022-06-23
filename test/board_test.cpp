#include "../src/board/board.h"

#include <gtest/gtest.h>

TEST(TempFunction, Main) {
  EXPECT_EQ(TempFunction(2, 2), 4);
  EXPECT_EQ(TempFunction(-2, 2), 0);
}