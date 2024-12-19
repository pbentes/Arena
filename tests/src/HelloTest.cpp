#include <gtest/gtest.h>

#include <Core.h>

TEST(Core, AddInts) {
    EXPECT_EQ(Core::AddInts(5, 3), 8);
}
