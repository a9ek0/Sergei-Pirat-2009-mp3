#include "cache.h"
void dell_oldest_from_cache(CACHE **cache){
    if ((*cache)->head == NULL) {
        return;
    }

    NODE *tail_node = (*cache)->tail;
    if (tail_node == (*cache)->head) {
        free_node(tail_node);
        free(*cache);
        *cache = NULL;
        return;
    }

    tail_node->prev->next = NULL;
    (*cache)->tail = tail_node->prev;

}















void dell_from_hash(CACHE *cache, const char *key) {
    int bucket = calculate_hash(key);
    NODE *curr_node = cache->hash[bucket];

    if (curr_node != NULL && strcmp(curr_node->key, key) == 0) {
        cache->hash[bucket] = curr_node->next;
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



void put(CACHE *cache, const char *key, const char *value) {
    char *existing_value = get(cache, key);
    if (existing_value != NULL) {
        strncpy(existing_value, value, strlen(value) + 1);
        return;
    }
    NODE *node = (NODE*) malloc(sizeof(NODE));
    node->key = (char*) malloc(strlen(key) + 1);
    node->value = (char*) malloc(strlen(value) + 1);
    strncpy(node->key, key, strlen(key) + 1);
    strncpy(node->value, value, strlen(value) + 1);
    node->next = NULL;
    node->prev = NULL;
    if(cache->head == NULL) {
        cache->head = node;
        cache->tail = node;
    } else {
        node->next = cache->head;
        cache->head->prev = node;
        cache->head = node;
        cache->tail->next = NULL;
    }
    //cache->head = node;
    int hash_val = calculate_hash(key);
    //node->next = cache->hash[hash_val];
    //node->prev = NULL;
    if (cache->hash[hash_val] == NULL) {
        cache->hash[hash_val] = node;
    }else{
        NODE *tmp = cache->hash[hash_val];
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = node;
        node->prev = tmp;
    }
    if (cache->size == CACHE_SIZE) {
        dell_tail(cache);
    } else {
        cache->size++;
    }
    cache->tail->next = NULL;
}

void dell_tail(CACHE *cache) {
    NODE *node_to_remove = cache->tail;
    cache->tail = node_to_remove->prev;
    if (cache->tail != NULL) {
        cache->tail->next = NULL;
    }
    int hash_val = calculate_hash(node_to_remove->key);
    NODE *node = cache->hash[hash_val];
    while (node != NULL) {
        if (node == node_to_remove) {
            cache->hash[hash_val] = node_to_remove->next;
        } else if (node->next == node_to_remove) {
            node->next = node_to_remove->next;
        }
        if (node == node_to_remove || node->next == node_to_remove)
            break;
        node = node->next;
    }
    free(node_to_remove->key);
    free(node_to_remove->value);
    free(node_to_remove);
}



void add_to_cache(CACHE *cache, const char *key, const char *value) {

    int hash = calculate_hash(key);
    NODE *hash_node = (NODE*) malloc(sizeof(NODE));
    NODE *cache_node = (NODE*) malloc(sizeof(NODE));
    cache_node->key = strdup(key);
    hash_node->value = strdup(value);
    hash_node->next = cache_node->next = NULL;
    hash_node->prev = cache_node->prev = NULL;

    if(cache->hash[hash] == NULL) {
        cache->hash[hash] = hash_node;
    } else {
        NODE *tmp = cache->hash[hash];
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
    return hash % CACHE_SIZE;
}

char *find_in_cache(const char *key, const CACHE *cache) {
    int hash_val = calculate_hash(key);
    NODE *node = cache->hash[hash_val];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

/*NODE *find_in_cache(const char *key, const CACHE *cache) {
    NODE *tmp = cache->head;
    int hash = calculate_hash(key);
    if(tmp == NULL)
        return NULL;
    for (int i = 0; i < cache->size; ++i) {
        if(strcmp(tmp->key, key) == 0) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}*/

void print_cache(const CACHE *cache) {
    NODE *node = cache->head;
    while (node != NULL) {
        printf("%s: %s", node->key, node->value);
        node = node->next;
    }
}

void print_hash(const CACHE *cache){
    NODE *tmp;
    for (int i = 0; i < CACHE_SIZE; ++i) {
        tmp = cache->hash[i];
        while (tmp != NULL) {
            printf("%d - %s ", i, cache->hash[i]->key);
            printf("%s", cache->hash[i]->value);
            tmp = tmp->next;
        }
    }
}

void update_position(CACHE **cache, const char *value){
    int hash_val = calculate_hash(value);
    NODE *node = (*cache)->hash[hash_val];
    while(node != NULL) {
        if(strcmp(node->key, value) == 0) {
            if (node == (*cache)->tail && node == (*cache)->head) {
                return;
            } else if (node != (*cache)->head && node != (*cache)->tail) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                (*cache)->head->prev = node;
                node->next = (*cache)->head;
                node->prev = NULL;
                (*cache)->head = node;
                return;
            } else if (node == (*cache)->tail) {
                node->prev->next = NULL;
                (*cache)->tail = node->prev;
                (*cache)->head->prev = node;
                node->next = (*cache)->head;
                node->prev = NULL;
                (*cache)->head = node;
                return;
            }
        }
        node = node->next;
    }
}

char* get(CACHE *cache, const char *key) {
    int hash_val = calculate_hash(key);
    NODE *node = cache->hash[hash_val];
    //printf("\n== %s\n", node->value);
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (node != cache->head) {
                cache->tail = (node == cache->tail) ? node->prev : cache->tail;
                node->prev->next = node->next;
                node->next ? node->next->prev = node->prev : 0;
                node->next = cache->head;
                node->prev = NULL;
                cache->head->prev = node;
                cache->head = node;
            }
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}
