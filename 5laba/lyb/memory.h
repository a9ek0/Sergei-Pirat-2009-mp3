#ifndef INC_5LABA_MEMORY_H
#define INC_5LABA_MEMORY_H
#include "cache.h"
#include "structures.h"
void free_cache(CACHE *cache);
void free_node(NODE *node);
NODE* create_node(char *key, char *value);
CACHE *create_cache();
#endif //INC_5LABA_MEMORY_H
