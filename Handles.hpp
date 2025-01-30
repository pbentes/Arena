#pragma once

#include "Arena.hpp"
#include <cstddef>
#include <cstdlib>

typedef unsigned long long handle;

typedef struct HandleStore {
    Arena* arena;
    size_t element_size;
} HandleStore;

HandleStore handleStoreCreate(size_t element_size, int element_count);
handle handleStoreAdd(HandleStore* handle_store, void* data);
void* handleStoreGet(HandleStore* handle_store, handle h);
void handleStoreDestroy(HandleStore* handle_store);

#ifndef HANDLES_IMPLEMENTATION
#define HANDLES_IMPLEMENTATION
    HandleStore handleStoreCreate(size_t element_size, int element_count) {
        return HandleStore {
            .arena = arenaCreate(element_size * element_count),
            .element_size = element_size
        };
    }

    handle handleStoreAdd(HandleStore* handle_store, void* data) {
        handle index = ((char*)handle_store->arena->index - (char*)handle_store->arena->buffer) / handle_store->element_size;

        arenaAlloc(handle_store->arena, handle_store->element_size);

        return index;
    }

    void* handleStoreGet(HandleStore* handle_store, handle h) {
        if(h > handle_store->arena->size / handle_store->element_size)
            return nullptr;
        return (void*)((char*)handle_store->arena->buffer + handle_store->element_size * h);
    }

    void handleStoreDestroy(HandleStore* handle_store) {
        arenaDestroy(handle_store->arena);
        free(handle_store);
    }
#endif //HANDLES_IMPLEMENTATION