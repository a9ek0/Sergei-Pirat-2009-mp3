#ifndef INC_5LABA_MENU_H
#define INC_5LABA_MENU_H
#include "cache.h"
#include "structures.h"
void menu(CACHE *cache, const char *file_name);
void domain_to_ip(CACHE *cache, const char *file_name);
void ip_to_domains(FILE *file, const char *ip);
void print_ip(const CACHE *cache);
int find_ip(CACHE *cache, const char *value);
void find_ip_domains(const CACHE *cache, const char *file_name);
void find_ip_domains1(const char *file_name, char *ip);
void domain_to_ips(const char *filename, const char *domain);

void find_original(FILE *file, const char *domain, const char *ip, const char *print);
int is_in_file(const char *file_name, const char *ip);
#endif //INC_5LABA_MENU_H
