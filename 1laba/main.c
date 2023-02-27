#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#define SWAP(A, B) { int t = A; A = B; B = t; }
#define SWAP_FLT(A, B) { float t = A; A = B; B = t; }
#define SWAP_STR(A, B) { char t[50]; strcpy(t, A); strcpy(A, B); strcpy(B, t); }
#define COMPARE(A, B, C) {if(A > B) C = 1; else C = 0;}


/*▀▄▀▄▀▄▀▄▀▄[̲̲̅̅т̲̲̅̅а̲̲̅̅к̲̲̅̅с̲̲̅̅и̲̲̅̅с̲̲̅̅т̲̲̅̅]▄▀▄▀▄▀▄▀▄▀*/
/*٩(✿∂‿∂✿)۶(░S░I░m░P░o░T░я░Ж░к░@░)ヾ(o✪‿✪o)ｼ*/
/*[̲̅0̲̅][̲̅0̲̅][̲̅7̲̅]░J░a░m░e░s░ ░B░o░n░d░(⌐■_■)--︻╦╤─ - - -*/

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
void double_sort(TV *structure, int num_of_elements);
void param_sort(TV *structure, int num_of_elements, int first, const int second);
void check_same(int *first_number, const int *second_number);
void menu(TV *structure, int size);

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    TV *tv;
    int size = 0;
    menu(tv, size);
    return 0;
}

void menu(TV *structure, int size)
{
    int index = 0;
    int k = 0;
    while(k != 3)
    {
    printf("●▬▬▬▬▬▬▬▬▬▬▬▬⍝⍝⍝⍝⍝▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬●\n"
                 "♕░░░░░░░░Я ПЕРСОН  ░V░I░P░  ТЫ ПАЦАН ВЛИП░░░░░░░░░♕\n"
                 "●▬▬▬▬▬▬▬▬▬▬▬▬⍝⍝⍝⍝⍝▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬●");
    printf("\n1.Initiate structure array.\n"
           "2.Enter structure array.\n"
           "3.Sort structure.\n"
           "4.Print structures.\n"
           "5.Delete structure from array.\n"
           "6.Exit.\n");
    fflush(stdin);
    scanf_s("%d", &index);
    switch (index)
    {
        case 1:
            create_struct_arr(&structure, &size);
            k = 1;
            break;
        case 2:
            if(k != 1 )
            {
                printf("You didn't create an array.\n");
                break;
            }
            initiate_struct(structure, size);
            k = 2;
            break;
        case 3:
            if(k != 2)
            {
                printf("You didn't fill/create an array.\n");
                break;
            }
            double_sort(structure, size);
            break;
        case 4:
            if(k != 2)
            {
                printf("You didn't fill/create an array.\n");
                break;
            }
            print_struct(structure, size);
            break;
        case 5:
        {
            if(k != 2)
            {
                printf("You didn't fill/create an array.\n");
                break;
            }
            dell_struct(structure, &size);
            break;
        }
        case 6:
            k = 3;
            break;
        default:
            printf("Wrong input!");
            break;
    }
    }
}

void dell_struct(TV *structure, int *size)
{
    int *dell;
    int index = *size;
    printf("\nChoose TV that you want to delete.\n");
    for (int k = 0; k < index; k++)
    {
        printf("%d: %s\n", k, structure[k].name);
    }
    check_in_range(dell, 0, index - 1);
    for (int j = *dell; j < index - 1; j++)
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
    while (scanf_s("%d", value) == 0 || getchar() !='\n' || *value > left_boarder || *value < right_boarder)
    {
        printf("Wrong input");
        rewind(stdin);
    }
}

void double_sort(TV *structure, int num_of_elements)
{
    int first;
    int second;
    int cnt = 0;
    while(cnt != 2) {
        printf("\nChoose sorting field.\n 1.Sort by name.\n 2.Sort by resolution."
               "\n 3.Sort by number of hdmi\n 4.Sort by panel thickness\n 5.Sort by available of Smart TV\n");
        if(cnt == 1)
        {
            check_in_range(&second, 0, 5);
            check_same(&second, &first);
        }
        else
            check_in_range(&first, 0, 5);

        switch (first) {
            case 1:
                sort_by_name(structure, num_of_elements);
                break;
            case 2:
                sort_by_resolution(structure, num_of_elements);
                break;
            case 3:
                sort_by_number_of_hdmi(structure, num_of_elements);
                break;
            case 4:
                sort_by_panel_thickness(structure, num_of_elements);
                break;
            case 5:
                sort_by_avail_of_stv(structure, num_of_elements);
                break;
            default:
                break;
        }
        cnt++;
    }
    param_sort(structure, num_of_elements, first, second);
}

void param_sort(TV *structure, int num_of_elements, int first, const int second)
{
    int arr[6];
    for (int i = 1; i < num_of_elements; ++i)
    {
        for (int j = 0; j < num_of_elements - 1; ++j)
        {
            //////////////////////float
            COMPARE(structure[j].panel_thickness, structure[j + 1].panel_thickness, arr[4])
            COMPARE(structure[j].smart_TV, structure[j + 1].smart_TV, arr[5])
            COMPARE(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi, arr[3])
            COMPARE(structure[j].resolution.w * structure[j].resolution.h, structure[j + 1].resolution.w * structure[j + 1].resolution.h, arr[2])
            arr[1] = strcmp(structure[j].name, structure[j + 1].name);
            if(arr[first] > 0 && arr[second] > 0)
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

void check_same(int *first_number, const int *second_number) {
    if(*first_number == *second_number)
    {
        printf("You have chosen the same options! Please choose another option");
        while (scanf_s("%d", first_number) == 0 || getchar() != '\n' || *first_number > 3 || *first_number == *second_number) {
            printf("You have chosen the same options! Please choose another option");
            rewind(stdin);
        }
    }
}