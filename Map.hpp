#pragma once

#include "Arena.hpp"

#include <cstring>

#define MAP_BUCKETS 2048

typedef struct MapElement {
    const unsigned char* key = nullptr;
    void* value = nullptr;
    MapElement* next = nullptr;
} MapElement;

typedef struct Map {
    Arena* arena;
    MapElement* buckets;
} Map;

Map* mapCreate();
void mapSet(Map* map, const unsigned char* key, void* value);
void* mapGet(Map* map, const unsigned char* key);
Map* mapClear(Map* map);
void mapDestroy(Map* map);

#ifndef MAP_IMPLEMENTATION
#define MAP_IMPLEMENTATION

    unsigned long djb2(const unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while ((c = *str++))
            hash = ((hash << 5) + hash) + c;

        return hash;
    }

    Map* mapCreate() {
        Arena* arena = arenaCreate();

        Map* map = (Map*)arenaAlloc(arena, sizeof(Map));
        map->arena = arena;
        map->buckets = (MapElement*)arenaAlloc(arena, sizeof(MapElement) * MAP_BUCKETS);

        if(map->buckets != nullptr) {
            for(int i = 0; i < MAP_BUCKETS; i++) {
                map->buckets[i].key   = nullptr;
                map->buckets[i].value = nullptr;
                map->buckets[i].next  = nullptr;
            }
        }

        return map;
    }

    void mapSet(Map* map, const unsigned char* key, void* value) {
        unsigned long hash = djb2(key);
        unsigned long index = hash % MAP_BUCKETS;

        if(map->buckets[index].key == nullptr) {
            map->buckets[index].key = key;
            map->buckets[index].value = value;
            return;
        }

        MapElement* last = &map->buckets[index];
        while(last->next != nullptr) {
            last = last->next;
        }
          
        last->next = (MapElement*)arenaAlloc(map->arena, sizeof(MapElement));
        last->next->key = key;
        last->next->value = value;
        last->next->next = nullptr;
    }

    void* mapGet(Map* map, const unsigned char* key) {
        unsigned long hash = djb2(key);
        unsigned long index = hash % MAP_BUCKETS;

        MapElement* element = &map->buckets[index];
        do {
            if(strcmp((const char*)element->key, (const char*)key) == 0)
                return element->value;

            element = element->next;
        } while(element->next != nullptr);

        return nullptr;
    }

    void mapRemove(Map* map, const unsigned char* key) {
        unsigned long hash = djb2(key);
        unsigned long index = hash % MAP_BUCKETS;

        MapElement* previous_element = nullptr;
        MapElement* element = &map->buckets[index];
        do {
            if(strcmp((const char*)element->key, (const char*)key) == 0) {
                if(element->next != nullptr) {
                    *element = *(element->next);
                    return;
                } else {
                    *element = MapElement {
                        .key   = nullptr,
                        .value = nullptr,
                        .next  = nullptr,
                    };

                    if(previous_element == nullptr)
                        return;

                    previous_element->next = nullptr;
                }
            }
            previous_element = element;
            element = element->next;
        } while(element->next != nullptr);
    }

    Map* mapClear(Map* map) {
        Arena* arena = map->arena;
        arenaClear(arena);
        return mapCreate();
    }

    void mapDestroy(Map* map) {
        Arena* arena = map->arena;
        arenaDestroy(arena);
    }

#endif //MAP_IMPLEMENTATION