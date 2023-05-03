#ifndef INC_5LABA_CHECKS_H
#define INC_5LABA_CHECKS_H
#include "cache.h"
#include "structures.h"

int validate_ip_address(const char *ip_address);
void get_valid_ip_address(char **ip);
void check_in_range_int(int *value, int left_boarder, int right_boarder);
void dell_from_hash(HASH *hash, const char *key);
#endif //INC_5LABA_CHECKS_H
