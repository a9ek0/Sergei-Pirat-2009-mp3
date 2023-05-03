#include "checks.h"
int validate_ip_address(const char *ip_address) {
    char *temp = strdup(ip_address);
    if (contains_multiple_dots(ip_address) || contains_indents(ip_address)) {
        free(temp);
        return 0;
    }
    int dots_count = 0;
    const char *token = strtok(temp, ".");
    while (token != NULL) {
        dots_count++;
        int len = strlen(token);
        if (len == 0) {
            free(temp);
            return 0;
        }
        for (int i = 0; i < len; i++) {
            if (!isdigit(token[i])) {
                free(temp);
                return 0;
            }
        }
        char *end_ptr;
        long num = strtol(token, &end_ptr, 10);
        if (end_ptr != token + len || num < 0 || num > 255) {
            free(temp);
            return 0;
        }
        token = strtok(NULL, ".");
    }
    free(temp);
    if (dots_count != 4) {
        return 0;
    }
    return 1;
}

void get_valid_ip_address(char **ip) {
    char *buff_ip = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
    get_line(&buff_ip);
    buff_ip[strcspn(buff_ip, "\n")] = '\0';
    while(validate_ip_address(buff_ip) == 0)
    {
        printf("Wrong input!\n");
        get_line(&buff_ip);
        buff_ip[strcspn(buff_ip, "\n")] = '\0';
    }
    add_extension(buff_ip, "\n");
    strcpy(*ip, buff_ip);
    free(buff_ip);
}

void check_in_range_int(int *value, int left_boarder, int right_boarder)
{
    while (scanf_s("%d", value) == 0 || getchar() !='\n' || *value < left_boarder || *value > right_boarder)
    {
        printf("Wrong input");
        rewind(stdin);
    }
}