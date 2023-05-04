#ifndef INC_5LABA_CACHE_H
#define INC_5LABA_CACHE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "checks.h"
#include "memory.h"
#include "other.h"
#include "structures.h"
#define CACHE_SIZE 10
#define MAX_LINE_LENGTH 1024


void dell_oldest_from_cache(CACHE **cache);
void add_to_cache(CACHE *cache, const char *key, const char *value);
int calculate_hash(const char *key);
char *find_in_cache(const char *key, const CACHE *cache);
void print_cache(const CACHE *cache);
void print_hash(const CACHE *cache);
void update_position(CACHE **cache, const char *value);

char* get(CACHE *cache, const char *key);

void put(CACHE *cache, const char *key, const char *value);

void dell_tail(CACHE *cache);
#endif //INC_5LABA_CACHE_H
