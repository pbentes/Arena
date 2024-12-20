#pragma once

#include <cstddef>

#define ARENA_SIZE 64000000

typedef struct Arena {
    void* buffer;
    void* index;
    size_t size;
} Arena;

Arena* arenaCreate(size_t size = ARENA_SIZE);
void* arenaAlloc(Arena* arena, unsigned int size);
void arenaClear(Arena* arena);
void arenaDestroy(Arena* arena);

#ifndef ARENA_IMPLEMENTATION
#define ARENA_IMPLEMENTATION
    #include <cstdlib>
    #include <new>

    Arena* arenaCreate(size_t size) {
        Arena* arena = (Arena*)malloc(sizeof(Arena));
        if (!arena) {
            throw std::bad_alloc();
        }

        arena->size = size;
        arena->buffer = malloc(arena->size);
        if (!arena->buffer) {
            free(arena);
            throw std::bad_alloc();
        }
        arena->index = arena->buffer;

        return arena;
    }

    void* arenaAlloc(Arena* arena, unsigned int size) {
        void* ret = arena->index;

        arena->index = (char*)arena->index + size;
        if (arena->index > (char*)arena->buffer + arena->size)
            return nullptr;

        return ret;
    }

    void arenaClear(Arena* arena) {
        arena->index = arena->buffer;
    }

    void arenaDestroy(Arena* arena) {
        if(arena) {
            free(arena->buffer);
            free(arena);
        }
    }
#endif