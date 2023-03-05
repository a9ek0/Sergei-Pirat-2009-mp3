#include "structure.h"

void dell_struct(TV **structure, int *size)
{
    if (structure == NULL || *structure == NULL) {
        printf("Structure doesn't exist!");
        return;
    }
    int dell;
    int index = *size;
    printf("\nChoose TV that you want to delete.\n");
    for (int k = 0; k < index; k++)
    {
        printf("%d: %s\n", k, (*structure)[k].name);
    }
    check_in_range(&dell, 0, index - 1);
    remove_tv(structure, dell, size);
}

void remove_tv(TV **structure, int index, int *size) {
    if (index < 0 || index >= *size) {
        printf("Error: index is out of bounds.\n");
        return;
    }
    free((*structure)[index].name);
    for (int i = index; i < *size - 1; i++) {
        (*structure)[i] = (*structure)[i + 1];
    }
    *size -= 1;
    if(*size == 0){
        free(*structure);
        *structure = NULL;
    }
    else {
        TV *new_tvs = (TV *) realloc(*structure, *size * sizeof(TV));
        if (new_tvs == NULL) {
            printf("Error: memory reallocation failed.\n");
            return;
        }
        *structure = new_tvs;
    }
}

void create_struct_arr(TV **structure, int *size) {
    printf("Enter number of structures in array.\n");
    scanf_s("%d", size);
    if(*structure != NULL){
        free(*structure);
    }
    *structure = (TV *) malloc(*size * sizeof(TV));
    if (*structure == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}


void initiate_struct(TV *structure, int size)
{
    if (structure == NULL) {
        printf("Structure doesn't exist!");
        return;
    }
    char buffer[255];
    for (int i = 0; i < size; ++i)
    {
        printf("\nEnter Name\n");
        scanf_s("%s", buffer);
        structure[i].name = (char *) calloc(strlen(buffer) + 1, sizeof(char));
        strcpy_s(structure[i].name, strlen(buffer) + 1,buffer);
        fflush(stdin);
        printf("\nEnter width of screen\n");
        scanf_s("%d", &structure[i].resolution.w);
        printf("\nEnter height of screen\n");
        scanf_s("%d", &structure[i].resolution.h);
        printf("\nEnter number of hdmi ports\n");
        scanf_s("%d", &structure[i].number_of_hdmi);
        printf("\nEnter price\n");
        scanf_s("%f", &structure[i].price);
        printf("\nDoes the TV have smart tv\n0 - No\n1 - Yes");
        scanf_s("%d", &structure[i].smart_TV);
    }
}

void print_struct(TV *structure, int size)
{
    for (int i = 0; i < size; ++i)
    {
        rewind(stdout);
        printf("\nName is: %s", structure[i].name);
        printf("\nResolution is: %d x %d", structure[i].resolution.w, structure[i].resolution.h);
        printf("\nNumber of hdmi ports is: %d", structure[i].number_of_hdmi);
        printf("\nPrice is: %1.2f", structure[i].price);
        if(structure[i].smart_TV == 1 )
            printf("\nSmart TV allowed.\n");
        else
            printf("\nSmart TV not allowed.\n");
    }
}

