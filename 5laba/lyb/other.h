#ifndef INC_5LABA_OTHER_H
#define INC_5LABA_OTHER_H
#include "cache.h"
#include "structures.h"
#include "menu.h"
int check_input(const char *input, const char *str1, const char *str2);
void get_input(char *input, const char *str1, const char *str2);
int contains_indents(const char *str);
int contains_multiple_dots(const char *str);
void get_line(char **line);
char *add_extension(char *word, const char *extension);
void get_ip_and_domain(const CACHE *cache, const char *file_name, char **domain, char **ip);
char *get_ip_from_file(FILE *file, const char *key);
#endif //INC_5LABA_OTHER_H
