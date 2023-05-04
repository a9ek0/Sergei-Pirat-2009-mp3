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
        NODE *bucket = cache->hash[i];
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

CACHE* create_cache() {
    CACHE *cache = (CACHE*) malloc(sizeof(CACHE));
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->hash = (NODE**) malloc(CACHE_SIZE * sizeof(NODE*));
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache->hash[i] = NULL;
    }
    return cache;
}

NODE* create_node(char *key, char *value) {
    NODE *node = (NODE*) malloc(sizeof(NODE));
    node->key = key;
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}