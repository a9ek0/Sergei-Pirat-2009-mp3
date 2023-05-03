#include "memory.h"
void free_cache(CACHE *cache) {
    NODE *current = cache->head;
    while (current != NULL) {
        NODE *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }

    for (int i = 0; i < CACHE_SIZE; i++) {
        NODE *bucket = cache->hash->buckets[i];
        while (bucket != NULL) {
            NODE *next = bucket->next;
            free(bucket->value);
            free(bucket);
            bucket = next;
        }
    }
    free(cache->hash);

    free(cache);
}

void free_node(NODE *node) {
    free(node->key);
    free(node->value);
    free(node);
}

CACHE *create_cache() {
    CACHE *cache = (CACHE*) malloc(sizeof(CACHE));
    if (cache == NULL) {
        return NULL;
    }
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;

    cache->hash = (HASH*) malloc(sizeof(HASH));
    if (cache->hash == NULL) {
        free(cache);
        return NULL;
    }
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache->hash->buckets[i] = NULL;
    }

    return cache;
}