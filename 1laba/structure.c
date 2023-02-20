#include "structure.h"

void menu(film_func *structure, int num_of_elements)
{
    int a;
    int k = 0;
    while(k != 3)
    {
        printf("\n1.Initiate structure array.\n"
               "2.Enter structure array.\n"
               "3.Sort structure.\n"
               "4.Print structures.\n"
               "5.Delete structure from array.\n"
               "6.Exit.\n");
        fflush(stdin);
        scanf_s("%d", &a);
        switch (a)
        {
            case 1:
                structure = init_struct(&num_of_elements);
                k = 1;
                break;
            case 2:
                if(k != 1)
                {
                    printf("You didn't initialize the array.\n");
                    break;
                }
                arr_struct_create(structure, num_of_elements);
                k = 2;
                break;
            case 3:
                if(k != 2)
                {
                    printf("You didn't fill/initialize the array.\n");
                    break;
                }
                double_sort(structure, num_of_elements);
                break;
            case 4:
                if(k != 2)
                {
                    printf("You didn't fill/initialize the array.\n");
                    break;
                }
                arr_structure_print(structure, num_of_elements);
                break;
            case 5:
            {
                if(k != 2)
                {
                    printf("You didn't fill/initialize the array.\n");
                    break;
                }
                dell_struct(structure, &num_of_elements);
                break;
            }
            case 6:
                k = 3;
                break;
        }
    }
}

film_func* realloc_struct(film_func *structure, int* new_size)
{
    return (film_func*) calloc(*new_size, sizeof (film_func));
}

film_func* init_struct(int *num_of_elements)
{
    int size;
    printf("Enter number of structures in array.\n");
    scanf_s("%d", &size);
    film_func *films = (film_func *) calloc(size, sizeof(film_func));
    *num_of_elements = size;
    return films;
}

void dell_struct(struct film structure[], int* num_of_elements)
{
    int film_name;
    printf("\nChoose film that you want to dellete.\n");
    for (int k = 0; k < *num_of_elements; k++)
    {
        printf("%d: %s\n", k, structure[k].name);
    }
    scanf_s("%d", &film_name);
    *num_of_elements -= 1;
    for (; film_name < *num_of_elements; film_name++)
    {
        strcpy(structure[film_name].name, structure[film_name + 1].name);
        structure[film_name].length = structure[film_name + 1].length;
        structure[film_name].rating = structure[film_name+ 1].rating;
    }
    structure = realloc_struct(structure, num_of_elements);
}

void set_text_color(int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (color)
    {
        case clrDefault:
            SetConsoleTextAttribute(handle, 7);
            break;
        case clrYellow:
            SetConsoleTextAttribute(handle, 14);
            break;
        case clrGreen:
            SetConsoleTextAttribute(handle, 2);
            break;
        case clrRed:
            SetConsoleTextAttribute(handle, 4);
            break;
    }
}

void double_sort(struct film structure[], int num_of_elements)
{
    int k = 0;
    int first = 0;
    int second = 0;
    while(k != 2)
    {
        printf("\nChoose sorting field.\n 1.Sort by name.\n 2.Sort by rating.\n 3.Sort by length\n");
        if(k == 0)
        {
            scanf_s( "%d", &first);
        }
        if(k == 1)
        {
            scanf_s("%d", &second);
            while(first == second)
            {
                printf("This field is already selected. Please select another field!\n");
                scanf_s("%d", &second);
            }
        }
        k++;
    }
    if(first == 1)
        name_sort(structure, num_of_elements);
    if(first == 2)
        rating_sort(structure, num_of_elements);
    if(first == 3)
        length_sort(structure, num_of_elements);
    for (int i = 1; i < num_of_elements; ++i)
    {
        for (int j = 0; j < num_of_elements - 1; ++j)
        {
            if((((int)structure[j].name[0] > (int)structure[j + 1].name[0]) && (first == 1 || second == 1) && (structure[j].rating <= structure[j + 1].rating && (first == 2 || second == 2)))
               ||(((int)structure[j].name[0] > (int)structure[j + 1].name[0]) && (first == 1 || second == 1) && structure[j].length <= structure[j + 1].length && (first == 3 || second == 3))
               ||(structure[j].rating <= structure[j + 1].rating && (first == 2 || second == 2) && (structure[j].length <= structure[j + 1].length && (first == 3 || second == 3))))
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].length, structure[j + 1].length)
                SWAP_FLT(structure[j].rating, structure[j + 1].rating)
            }
        }
    }
}

void name_sort(struct film structure[], int num_of_elements)
{
    for (int i = 1; i < num_of_elements; ++i)
    {
        for (int j = 0; j < num_of_elements - 1; ++j)
        {
            if(strcmp(structure[j].name, structure[j + 1].name) > 0)
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].length, structure[j + 1].length)
                SWAP_FLT(structure[j].rating, structure[j + 1].rating)
            }
        }
    }
}

void rating_sort(struct film structure[], int num_of_elements)
{
    for (int i = 1; i < num_of_elements; ++i)
    {
        for (int j = 0; j < num_of_elements - 1; ++j)
        {
            if(structure[j].rating < structure[j + 1].rating)
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].length, structure[j + 1].length)
                SWAP_FLT(structure[j].rating, structure[j + 1].rating)
            }
        }
    }
}

void length_sort(struct film structure[], int num_of_elements)
{
    for (int i = 1; i < num_of_elements; ++i)
    {
        for (int j = 0; j < num_of_elements - 1; ++j)
        {
            if(structure[j].length < structure[j + 1].length)
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].length, structure[j + 1].length)
                SWAP_FLT(structure[j].rating, structure[j + 1].rating)
            }
        }
    }
}

void arr_structure_print(struct film structure[], int num_of_elements)
{
    rewind(stdin);
    for (int i = 0; i < num_of_elements; ++i)
    {
        printf("\nName is: %s", structure[i].name);
        printf("\nLength is: %d", structure[i].length);
        printf("\nRating is: ");
        if(structure[i].rating >= 8.5 && structure[i].rating <= 10)
            set_text_color(clrGreen);
        if (structure[i].rating >= 7 && structure[i].rating < 8.5)
            set_text_color(clrYellow);
        if(structure[i].rating >= 0 && structure[i].rating < 7)
            set_text_color(clrRed);
        printf("%1.3f\n", structure[i].rating);
        set_text_color(clrDefault);
        printf("\n");
    }
}


void arr_struct_create(struct film structure[], int num_of_elements)
{
    char buffer[100];
    for (int i = 0; i < num_of_elements; ++i)
    {
        printf("\nEnter Name\n");
        scanf_s("%s", buffer);
        structure[i].name = (char *) calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(structure[i].name, buffer);
        fflush(stdin);
        printf("\nEnter Length\n");
        scanf_s("%d", &structure[i].length);
        printf("\nEnter Rating\n");
        scanf_s("%f", &structure[i].rating);
    }
}