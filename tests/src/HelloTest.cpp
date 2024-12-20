#include <gtest/gtest.h>

#include "../../Arena.hpp"

TEST(Arena, Create) {
    Arena* arena = arenaCreate();
    ASSERT_TRUE(arena);
}

TEST(Arena, Alloc) {
    Arena* arena = arenaCreate();
    int* i = static_cast<int*>(arenaAlloc(arena, sizeof(int)));
    ASSERT_NE(i, nullptr);
}

TEST(Arena, Clear) {
    Arena* arena = arenaCreate();
    
    int* i = static_cast<int*>(arenaAlloc(arena, sizeof(int)));
    arenaClear(arena);
    int* d = static_cast<int*>(arenaAlloc(arena, sizeof(int)));

    ASSERT_EQ(i, d);
}