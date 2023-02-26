#include "structure.h"

void menu(TV *structure, int size)
{

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
        scanf_s("%f", &structure[i].number_of_hdmi);
        printf("\nEnter panel thickness\n");
        scanf_s("%f", &structure[i].panel_thickness);
        printf("\nDoes the TV have smart tv\n0 - No\n1 - Yes");
        scanf_s("%f", &structure[i].smart_TV);
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

}

void sort_by_resolution(TV *structure, int size)
{

}

void number_of_hdmi(TV *structure, int size)
{

}

void sort_by_panel_thickness(TV *structure, int size)
{

}

void sort_by_avail_of_stv(TV *structure, int size)
{

}