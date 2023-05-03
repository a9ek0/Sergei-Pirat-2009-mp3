#include "cache.h"
void dell_oldest_from_cache(CACHE **cache){
    if ((*cache)->head == NULL) {
        return;
    }

    NODE *tail_node = (*cache)->tail;
    if (tail_node == (*cache)->head) {
        dell_from_hash((*cache)->hash, tail_node->key);
        free_node(tail_node);
        free(*cache);
        *cache = NULL;
        return;
    }

    tail_node->prev->next = NULL;
    (*cache)->tail = tail_node->prev;

    dell_from_hash((*cache)->hash, tail_node->key);
}

void dell_from_hash(HASH *hash, const char *key) {
    int bucket = calculate_hash(key) % CACHE_SIZE;
    NODE *curr_node = hash->buckets[bucket];

    if (curr_node != NULL && strcmp(curr_node->key, key) == 0) {
        hash->buckets[bucket] = curr_node->next;
        free_node(curr_node);
        return;
    }

    while (curr_node != NULL) {
        if (strcmp(curr_node->key, key) == 0) {
            curr_node->prev->next = curr_node->next;
            if (curr_node->next != NULL) {
                curr_node->next->prev = curr_node->prev;
            }
            free_node(curr_node);
            return;
        }
        curr_node = curr_node->next;
    }
}

void add_to_cache(CACHE *cache, const char *key, const char *value) {
    int hash = calculate_hash(key) % CACHE_SIZE;
    NODE *hash_node = (NODE*) malloc(sizeof(NODE));
    NODE *cache_node = (NODE*) malloc(sizeof(NODE));
    cache_node->key = strdup(key);
    hash_node->value = strdup(value);
    hash_node->next = cache_node->next = NULL;
    hash_node->prev = cache_node->prev = NULL;

    if(cache->hash->buckets[hash] == NULL) {
        cache->hash->buckets[hash] = hash_node;
    } else {
        NODE *tmp = cache->hash->buckets[hash];
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = hash_node;
        hash_node->prev = tmp;
    }

    if(cache->head == NULL) {
        cache->head = cache_node;
        cache->tail = cache_node;
    } else {
        cache_node->next = cache->head;
        cache->head->prev = cache_node;
        cache->head = cache_node;
        cache->tail->next = NULL;
    }
    cache->size++;

    if(cache->size > CACHE_SIZE) {
        cache->size--;
        dell_oldest_from_cache(&cache);
    }

}

int calculate_hash(const char *key){
    int hash = 0;
    for (int i = 0; i < strlen(key); ++i) {
        hash += key[i];
    }
    return hash;
}

NODE *find_in_cache(const char *key, const CACHE *cache) {
    NODE *tmp = cache->head;
    if(tmp == NULL)
        return NULL;
    for (int i = 0; i < cache->size; ++i) {
        if(strcmp(tmp->key, key) == 0){
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void print_cache(const CACHE *cache) {
    NODE *tmp = cache->head;
    int hash;
    while (tmp != NULL) {
        hash = calculate_hash(tmp->key) % CACHE_SIZE;
        printf("%d - %s ",hash, tmp->key);
        printf("%s", cache->hash->buckets[hash]->value);
        tmp = tmp->next;
    }
}

void print_hash(const CACHE *cache){
    NODE *tmp;
    for (int i = 0; i < CACHE_SIZE; ++i) {
        tmp = cache->hash->buckets[i];
        while (tmp != NULL) {
            printf("%d - %s ", i, cache->hash->buckets[i]->key);
            printf("%s", cache->hash->buckets[i]->value);
            tmp = tmp->next;
        }
    }
}

void update_position(CACHE **cache, NODE *node){
    if(node == (*cache)->tail && node == (*cache)->head) {
        return;
    } else if(node != (*cache)->head && node != (*cache)->tail) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        (*cache)->head->prev = node;
        node->next = (*cache)->head;
        node->prev = NULL;
        (*cache)->head = node;
    } else if(node == (*cache)->tail)
    {
        node->prev->next = NULL;
        (*cache)->tail = node->prev;
        (*cache)->head->prev = node;
        node->next = (*cache)->head;
        node->prev = NULL;
        (*cache)->head = node;
    }
}
