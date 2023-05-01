#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CACHE_SIZE 10
#define MAX_DOMAIN_LENGTH 256
#define MAX_LINE_LENGTH 1024

typedef struct node {
    char *key; // Domain
    char *value; // ip address
    struct node *next;
    struct node *prev;
}NODE;

typedef struct hash_table{
    NODE *buckets[CACHE_SIZE];
}HASH;

typedef struct cache {
    int size;
    NODE *head;
    NODE *tail;
    HASH *hash;
}CACHE;

CACHE *create_cache();
void free_cache(CACHE *cache);
void free_node(NODE *node);
void dell_oldest_from_cache(CACHE **cache);
void add_to_cache(CACHE *cache, const char *key, const char *value);
int calculate_hash(const char *key);
NODE *find_in_cache(const char *key, const CACHE *cache);
void print_cache(const CACHE *cache);
void print_hash(const CACHE *cache);
char *get_ip_from_file(FILE *file, const char *key);
void update_position(CACHE **cache, NODE *node);
int check_input(const char *input, const char *str1, const char *str2);
void get_input(char *input, const char *str1, const char *str2);

/// dobavit proverku na nalichie v faile domena
/// dobavit udalenie v hashe v add_to_chache

///NE RABOTAET KALIZIA
int main() {
    FILE *file;

    CACHE *cache;

    char file_name[16] = "domain_list.txt";
    char *domain = malloc(MAX_DOMAIN_LENGTH * sizeof (char));
    char *ip;
    char choose[6];

    cache = create_cache();

    file = fopen(file_name, "rt");
    if(file == NULL)
        exit(EXIT_FAILURE);

    while(1) {
        printf("Enter domain name of the site to get IP.\n");

        fflush(stdin);
        fgets(domain, MAX_DOMAIN_LENGTH, stdin);
        domain[strcspn(domain, "\n")] = '\0';



        while(find_in_cache(domain, cache) == NULL && get_ip_from_file(file, domain) == NULL)
        {
            printf("This domain is not in the database try another one or add this domain.(Try/Add)\n");

            fgets(choose, 6, stdin);
            get_input(choose, "Try\n", "Add\n");

            if (strcmp("Try\n", choose) == 0) {
                printf("Enter domain name of the site to get IP.\n");
                fgets(domain, MAX_DOMAIN_LENGTH, stdin);
                domain[strcspn(domain, "\n")] = '\0';
            }
            else if (strcmp("Add\n", choose) == 0)
            {

            }
        }
        domain = realloc(domain, (strlen(domain) + 1) * sizeof(char));




        NODE *tmp = find_in_cache(domain, cache);
        if (tmp == NULL) {
            ip = get_ip_from_file(file, domain);
            add_to_cache(cache, domain, ip);
            printf("1 - %s", ip);
        } else {
            update_position(&cache, tmp);
            printf("2 - %s", cache->hash->buckets[calculate_hash(domain)]->value);
        }
        //print_hash(cache);
        print_cache(cache);
        rewind(file);
    }

    free(ip);
    fclose(file);
    free(domain);
    free_cache(cache);
    /// dobavit ochistku hesha
    return 0;
}

void add_to_cache(CACHE *cache, const char *key, const char *value) {
    int hash = calculate_hash(key);
    NODE *new_node = (NODE*) malloc(sizeof(NODE));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;
    new_node->prev = NULL;


    if(cache->hash->buckets[hash] == NULL) {
        cache->hash->buckets[hash] = new_node;
    } else {
        NODE *tmp = cache->hash->buckets[hash];
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        new_node->prev = tmp;
    }

    if(cache->head == NULL) {
        cache->head = new_node;
        cache->tail = new_node;
    } else {
        new_node->next = cache->head;
        cache->head->prev = new_node;
        cache->head = new_node;
        cache->tail->next = NULL;
    }
    cache->size++;

    if(cache->size > CACHE_SIZE) {
        cache->size--;
        dell_oldest_from_cache(&cache);
    }
}

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

    NODE *new_tail_node = tail_node->prev;
    new_tail_node->next = NULL;
    (*cache)->tail = new_tail_node;

    free_node(tail_node);
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

void free_node(NODE *node) {
    free(node->key);
    free(node->value);
    free(node);
}

void free_cache(CACHE *cache) {
    NODE *current_node = cache->head;
    while (current_node != NULL) {
        NODE *next_node = current_node->next;
        free_node(current_node);
        current_node = next_node;
    }
    free(cache);
}

int calculate_hash(const char *key){
    int hash = 0;
    for (int i = 0; i < strlen(key); ++i) {
        hash += key[i];
    }
    return (hash % CACHE_SIZE);
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
    int hash = calculate_hash(key);
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

void print_cache(const CACHE *cache) {
    NODE *tmp = cache->head;
    while (tmp != NULL) {
        printf("%s ", tmp->key);
        printf("%s", tmp->value);
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

char *get_ip_from_file(FILE *file, const char *key){
    char *line;
    char *buff_line = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
    char *ip = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
    line = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
    rewind(file);
    while(fgets(line, MAX_LINE_LENGTH, file) != NULL){
        strcpy(buff_line, line);
        buff_line[strcspn(buff_line, " ")] = '\0';

        if(strcmp(buff_line, key) == 0)
        {
            if(line[strlen(buff_line) + 4] == 'A')
            {
                strcpy(ip, (line + strlen(buff_line) + 6));
                free(line);
                free(buff_line);
                return ip;
            }
            else if(line[strlen(buff_line) + 4] == 'C')
            {
                strcpy(ip, (line + strlen(buff_line) + 9));
                ip[strcspn(ip, "\n")] = '\0';
                rewind(file);
                char *buff_ip;
                ip = get_ip_from_file(file, ip);
                free(line);
                free(buff_line);
                return ip;
            }

        }
    }
    free(ip);
    free(line);
    free(buff_line);
    return NULL;
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

void get_input(char *input, const char *str1, const char *str2) {
    while (!check_input(input, str1, str2)) {
        printf("Wrong input!\n");
        fflush(stdin);
        fgets(input, MAX_LINE_LENGTH, stdin);
    }
}

int check_input(const char *input, const char *str1, const char *str2) {
    int match1 = strcmp(input, str1);
    int match2 = strcmp(input, str2);
    if (match1 == 0 || match2 == 0) {
        return 1;
    } else {
        return 0;
    }
}




