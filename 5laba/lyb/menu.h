#ifndef INC_5LABA_MENU_H
#define INC_5LABA_MENU_H
#include "cache.h"
#include "structures.h"
void menu(CACHE *cache, const char *file_name);
void domain_to_ip(CACHE *cache, const char *file_name);
void ip_to_domains(CACHE *cache, const char *value);
void print_ip(CACHE *cache);
int find_ip(CACHE *cache, const char *ip);
#endif //INC_5LABA_MENU_H
