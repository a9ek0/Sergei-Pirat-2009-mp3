#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(A, B) { int t = A; A = B; B = t; }
#define SWAP_FLT(A, B) { float t = A; A = B; B = t; }
#define SWAP_STR(A, B) { char t[50]; strcpy(t, A); strcpy(A, B); strcpy(B, t); }

enum smart_tv{
    AVAILABLE,
    NOT_AVAILABLE
};

typedef struct{
    int w;
    int h;
}res;

typedef struct{
    char *name;
    res resolution;
    int number_of_hdmi;
    float panel_thickness;
    enum smart_tv smart_TV;
}TV;

void create_struct_arr(TV **structure, int *size);
void initiate_struct(TV *structure, int size);
void print_struct(TV *structure, int size);
void sort_by_name(TV *structure, int size);
void sort_by_resolution(TV *structure, int size);
void sort_by_number_of_hdmi(TV *structure, int size);
void sort_by_panel_thickness(TV *structure, int size);
void sort_by_avail_of_stv(TV *structure, int size);
void check_in_range(int *value, int left_boarder, int right_boarder);
void dell_struct(TV *structure, int *size);

int main() {
    TV *tv;
    int size = 0;
    create_struct_arr(&tv, &size);
    initiate_struct(tv, size);
    print_struct(tv, size);
    dell_struct(tv, &size);
    print_struct(tv, size);
    /////free nado
    free(tv);
    return 0;
}

void menu(TV *structure, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if((structure[j].resolution.w * structure[j].resolution.h) < (structure[j + 1].resolution.w * structure[j].resolution.h))
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].resolution.w, structure[j + 1].resolution.w)
                SWAP(structure[j].resolution.h, structure[j + 1].resolution.h)
                SWAP(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi)
                SWAP_FLT(structure[j].panel_thickness, structure[j + 1].panel_thickness)
                SWAP(structure[j].smart_TV, structure[j + 1].smart_TV)
            }
        }
    }
}

void dell_struct(TV *structure, int *size)
{
    int dell = 0;
    int index = *size;
    printf("\nChoose TV that you want to delete.\n");
    for (int k = 0; k < index; k++)
    {
        printf("%d: %s\n", k, structure[k].name);
    }
    check_in_range(&dell, 0, index);

    for (int j = dell; j < index - 1; ++j)
    {
        structure[j] = structure[j + 1];
    }
    (*size)--;
}


void create_struct_arr(TV **structure, int *size)
{
    printf("Enter number of structures in array.\n");
    scanf_s("%d", size);
    *structure = (TV *) malloc(*size * sizeof(TV));
}

void initiate_struct(TV *structure, int size)
{
    char buffer[255];
    for (int i = 0; i < size; ++i)
    {
        printf("\nEnter Name\n");
        scanf_s("%s", buffer);
        structure[i].name = (char *) calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(structure[i].name, buffer);
        fflush(stdin);
        printf("\nEnter width of screen\n");
        scanf_s("%d", &structure[i].resolution.w);
        printf("\nEnter height of screen\n");
        scanf_s("%d", &structure[i].resolution.h);
        printf("\nEnter number of hdmi ports\n");
        scanf_s("%d", &structure[i].number_of_hdmi);
        printf("\nEnter panel thickness\n");
        scanf_s("%f", &structure[i].panel_thickness);
        printf("\nDoes the TV have smart tv\n0 - No\n1 - Yes");
        scanf_s("%d", &structure[i].smart_TV);
    }
}

void print_struct(TV *structure, int size)
{
    rewind(stdin);
    for (int i = 0; i < size; ++i)
    {
        printf("\nName is: %s", structure[i].name);
        printf("\nResolution is: %d x %d", structure[i].resolution.w, structure[i].resolution.h);
        printf("\nNumber of hdmi ports is: %d", structure[i].number_of_hdmi);
        printf("\nPanel thickness is: %1.3f", structure[i].panel_thickness);
        if(structure[i].smart_TV == 1 )
            printf("\nSmart TV allowed.\n");
        else
            printf("\nSmart TV not allowed.\n");
    }
}

void sort_by_name(TV *structure, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if(strcmp(structure[j].name, structure[j + 1].name) > 0)
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].resolution.w, structure[j + 1].resolution.w)
                SWAP(structure[j].resolution.h, structure[j + 1].resolution.h)
                SWAP(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi)
                SWAP_FLT(structure[j].panel_thickness, structure[j + 1].panel_thickness)
                SWAP(structure[j].smart_TV, structure[j + 1].smart_TV)
            }
        }
    }
}

void sort_by_resolution(TV *structure, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if((structure[j].resolution.w * structure[j].resolution.h) < (structure[j + 1].resolution.w * structure[j].resolution.h))
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].resolution.w, structure[j + 1].resolution.w)
                SWAP(structure[j].resolution.h, structure[j + 1].resolution.h)
                SWAP(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi)
                SWAP_FLT(structure[j].panel_thickness, structure[j + 1].panel_thickness)
                SWAP(structure[j].smart_TV, structure[j + 1].smart_TV)
            }
        }
    }
}

void sort_by_number_of_hdmi(TV *structure, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if(structure[j].number_of_hdmi < structure[j + 1].number_of_hdmi)
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].resolution.w, structure[j + 1].resolution.w)
                SWAP(structure[j].resolution.h, structure[j + 1].resolution.h)
                SWAP(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi)
                SWAP_FLT(structure[j].panel_thickness, structure[j + 1].panel_thickness)
                SWAP(structure[j].smart_TV, structure[j + 1].smart_TV)
            }
        }
    }
}

void sort_by_panel_thickness(TV *structure, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if(structure[j].panel_thickness < structure[j + 1].panel_thickness)
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].resolution.w, structure[j + 1].resolution.w)
                SWAP(structure[j].resolution.h, structure[j + 1].resolution.h)
                SWAP(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi)
                SWAP_FLT(structure[j].panel_thickness, structure[j + 1].panel_thickness)
                SWAP(structure[j].smart_TV, structure[j + 1].smart_TV)
            }
        }
    }
}

void sort_by_avail_of_stv(TV *structure, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if(structure[j].smart_TV < structure[j + 1].smart_TV)
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].resolution.w, structure[j + 1].resolution.w)
                SWAP(structure[j].resolution.h, structure[j + 1].resolution.h)
                SWAP(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi)
                SWAP_FLT(structure[j].panel_thickness, structure[j + 1].panel_thickness)
                SWAP(structure[j].smart_TV, structure[j + 1].smart_TV)
            }
        }
    }
}

void check_in_range(int *value, int left_boarder, int right_boarder)
{
    while (scanf_s("%d", value) == 0 || getchar() !='\n' || *value > right_boarder || *value < left_boarder)
    {
        printf("Wrong input");
        rewind(stdin);
    }
}