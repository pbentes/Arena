#pragma once

#include <cstddef>

#define ARENA_SIZE 2000000

typedef struct Arena {
    void* buffer;
    void* index;
    size_t size;
    Arena* next;
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
        Arena* arena = static_cast<Arena*>(malloc(sizeof(Arena)));
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
        arena->next = nullptr;

        return arena;
    }

    void* arenaAlloc(Arena* arena, unsigned int size) {
        void* ret = arena->index;

        arena->index = static_cast<char*>(arena->index) + size;
        if (arena->index > static_cast<char*>(arena->buffer) + arena->size) {
            if (!arena->next)
                arena->next = arenaCreate(arena->size);
            return arenaAlloc(arena->next, size);
        }

        return ret;
    }

    void arenaClear(Arena* arena) {
        arena->index = arena->buffer;

        if(arena->next)
            arenaDestroy(arena->next);
    }

    void arenaDestroy(Arena* arena) {
        if(arena->next)
            arenaDestroy(arena->next);

        if(arena) {
            free(arena->buffer);
            free(arena);
        }
    }
#endif //ARENA_IMPLEMENTATION