#include "menu.h"


void menu(CACHE *cache, const char *file_name){
    int choose = 0;
    printf("Choose option:\n"
           "1.Find IP for domain.\n"
           "2.Find domains for IP\n"
           "3.Exit\n");
    check_in_range_int(&choose, 1, 2);
    switch (choose) {
        case 1:
            domain_to_ip(cache, file_name);
            break;
        case 2:

            break;
        case 3:
            return;
        default:
            break;
    }
}

void domain_to_ip(CACHE *cache, const char *file_name)
{
    FILE *file;

    char *domain = (char*)malloc(MAX_LINE_LENGTH * sizeof (char));
    char *ip = (char*)malloc(MAX_LINE_LENGTH * sizeof (char));
    char *expression = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));

    strcpy(expression, "Yes\n");

    while(strcmp(expression, "Yes\n") == 0 && strcmp(expression, "No\n") != 0){

        get_ip_and_domain(cache, file_name, &domain, &ip);

        NODE *tmp = find_in_cache(domain, cache);

        if (tmp == NULL) {

            file = fopen(file_name, "rt");
            if(file == NULL)
                exit(EXIT_FAILURE);

            ip = get_ip_from_file(file, domain);
            add_to_cache(cache, domain, ip);
            printf("New - %s", ip);
        } else {
            update_position(&cache, tmp);
            printf("Cache - %s", cache->hash->buckets[calculate_hash(domain) % CACHE_SIZE]->value);
        }
        print_cache(cache);

        printf("Do you want to continue?\n");
        get_line(&expression);
        get_input(expression, "Yes\n", "No\n");
    }
    free(expression);
    free(ip);
    free(domain);
}

void ip_to_domains(CACHE *cache, const char *value)
{

    NODE *tmp = cache->head;
    int hash;
    while(tmp != NULL){
        hash = calculate_hash(tmp->value) & CACHE_SIZE;
        if (strcmp(cache->hash->buckets[hash]->value, value) == 0)
            printf("%s\n", cache->hash->buckets[hash]->value);
        tmp = tmp->next;
    }
}

void print_ip(CACHE *cache){
    NODE *tmp = cache->head;
    int hash;
    while(tmp != NULL){
        hash = calculate_hash(tmp->value) & CACHE_SIZE;
        printf("%s\n", cache->hash->buckets[hash]->value);
        tmp = tmp->next;
    }
}

int find_ip(CACHE *cache, const char *ip){
    NODE *tmp = cache->head;
    int hash;
    while(tmp != NULL){
        hash = calculate_hash(tmp->value) & CACHE_SIZE;
        if (strcmp(cache->hash->buckets[hash]->value, ip) == 0)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void find_ip_domains(CACHE *cache){
    char *ip = (char*)malloc(MAX_LINE_LENGTH * sizeof (char));
    printf("Select the ip whose domains you want to see.\n");
    print_ip(cache);
    print_ip(cache);
    get_valid_ip_address(&ip);
    while(find_ip(cache, ip) == 0)
    {
        get_valid_ip_address(&ip);
    }

}