#ifndef INC_5LABA_STRUCTURES_H
#define INC_5LABA_STRUCTURES_H
#define CACHE_SIZE 10
#define CACHE_SIZE 10
#define MAX_LINE_LENGTH 1024

typedef struct node {
    char *key;
    char *value;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct cache {
    int size;
    NODE *head;
    NODE *tail;
    NODE **hash;
}CACHE;

#endif //INC_5LABA_STRUCTURES_H
