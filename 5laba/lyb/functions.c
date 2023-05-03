#include "functions.h"

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

void add_to_hash(CACHE *cache, const char *key, NODE *node){
    int hash = calculate_hash(key) % CACHE_SIZE;
    if(cache->hash->buckets[hash] == NULL) {
        cache->hash->buckets[hash] = node;
    } else {
        NODE *tmp = cache->hash->buckets[hash];
        while(tmp->next != NULL) {
            if(strcmp(tmp->key, key) == 0)
                return;
            tmp = tmp->next;
        }
        tmp->next = node;
        node->prev = tmp;
    }
}





void get_input(char *input, const char *str1, const char *str2) {
    while (!check_input(input, str1, str2)) {
        printf("Wrong input!\n");
        fflush(stdin);
        fgets(input, MAX_LINE_LENGTH, stdin);
    }
}






void get_domains_associated_with_ip(const CACHE *cache, const char *value){
    NODE *tmp = cache->head;
    while(tmp != NULL){
        if (strcmp(tmp->value, value) == 0)
            printf("%s\n", tmp->key);
        tmp = tmp->next;
    }
}




