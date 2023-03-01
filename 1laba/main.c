#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#define SWAP(A, B) { int t = A; A = B; B = t; }
#define SWAP_FLT(A, B) { float t = A; A = B; B = t; }
#define SWAP_STR(A, B) { char t[50]; strcpy(t, A); strcpy(A, B); strcpy(B, t); }
#define COMPARE(A, B, C) {if(A >= B) C = 1; else C = 0;}
#define COMPARE_STR(A, B, C) {if((int)A > (int)B) C = 1; else C = 0;}

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
    float price;
    enum smart_tv smart_TV;
}TV;

void create_struct_arr(TV **structure, int *size);
void initiate_struct(TV *structure, int size);
void print_struct(TV *structure, int size);
void sort_by_name(TV *structure, int size);
void sort_by_resolution(TV *structure, int size);
void sort_by_number_of_hdmi(TV *structure, int size);
void sort_by_price(TV *structure, int size);
void sort_by_avail_of_stv(TV *structure, int size);
void check_in_range(int *value, int left_boarder, int right_boarder);
void dell_struct(TV *structure, int *size);
void double_sort(TV *structure, int num_of_elements);
void single_sort(TV *structure, int num_of_elements);
void param_sort(TV *structure, int num_of_elements, int first, int second);
void check_same(int *first_number, const int *second_number);
void menu(TV *structure, int size);
void parce(TV *structure);
void sort_TV(TV *structure, int num_tvs, int sort_field_1, int sort_field_2);
int compare_resolution_desc(const TV *tv1, const TV *tv2);
int compare_name_asc(const TV *tv1, const TV *tv2);
void sort_tvs(TV *tvs, int num_tvs, int compare1, int compare2);
void free_struct(TV *structure, int size);

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    TV *tv;
    typedef int (*compare_func_t)(const TV *, const TV *);
    int size = 0;
    menu(tv, size);
    printf("\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠛⠛⠛⠉⠉⠉⠋⠛⠛⠛⠻⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠛⠉⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠉⠙⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠏⠄⠄⠄⠄⠄⠄⠄⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠹⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠘⢻⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⠄⢠⠄⠄⡀⠄⠄⢀⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄⡁⠄⠄⢛⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠐⡈⢔⠸⣐⢕⢕⢵⢰⢱⢰⢐⢤⡡⡢⣕⢄⢢⢠⠄⠄⠄⠄⠄⠄⠙⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡁⠂⠅⢕⠌⡎⡎⣎⢎⢮⢮⣳⡳⣝⢮⢺⢜⢕⢕⢍⢎⠪⡐⠄⠁⠄⠸⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⠏⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠐⠄⠄⢅⠣⡡⡣⣣⡳⡵⣝⡮⣗⣗⡯⣗⣟⡮⡮⣳⣣⣳⢱⢱⠱⣐⠄⠂⠄⢿⣿\n"
           "⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⠄⠄⠄⠂⠄⠄⠄⠄⠄⠄⢂⢈⠢⡱⡱⡝⣮⣿⣟⣿⣽⣷⣿⣯⣿⣷⣿⣿⣿⣾⣯⣗⡕⡇⡇⠄⠂⡀⢹⣿\n"
           "⣿⣿⣿⣿⣿⡟⠄⠄⠄⠄⠄⠄⠂⠄⠄⠄⠄⠄⠄⠐⢀⢂⢕⢸⢨⢪⢳⡫⣟⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡺⡮⡣⡣⠠⢂⠒⢸⣿\n"
           "⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⠐⠄⡂⠆⡇⣗⣝⢮⢾⣻⣞⣿⣿⣿⣿⣿⣿⣿⣿⢿⣽⣯⡯⣺⢸⢘⠨⠔⡅⢨⣿\n"
           "⣿⣿⠋⠉⠙⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠁⠄⠄⠄⡂⡪⡪⡪⡮⡮⡯⣻⣽⣾⣿⣿⣿⣟⣿⣿⣿⣽⣿⣿⡯⣯⡺⡸⡰⡱⢐⡅⣼⣿\n"
           "⣿⠡⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⠈⠆⠱⠑⠝⠜⠕⡝⡝⣞⢯⢿⣿⣿⡿⣟⣿⣿⣿⡿⡿⣽⣷⣽⡸⡨⡪⣂⠊⣿⣿\n"
           "⣿⠡⠄⡨⣢⠐⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠐⠍⡓⣗⡽⣝⠽⠍⠅⠑⠁⠉⠘⠘⠘⠵⡑⢜⢀⢀⢉⢽\n"
           "⣿⠁⠠⢱⢘⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠈⠱⣁⠜⡘⠌⠄⠄⡪⣳⣟⡮⢅⠤⠠⠄⠄⣀⣀⡀⡀⠄⠈⡂⢲⡪⡠⣿\n"
           "⣿⡇⠨⣺⢐⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡀⠄⠄⠄⠤⡠⡢⢒⠦⠠⠄⠄⠄⡸⢽⣟⢮⠢⡂⡐⠄⡈⡀⠤⡀⠄⠑⢄⠨⢸⡺⣐⣿\n"
           "⣿⣿⠈⠕⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡂⡪⡐⡥⢤⣰⣰⣰⡴⡮⠢⠂⠄⠄⡊⢮⢺⢕⢵⢥⡬⣌⣒⡚⣔⢚⢌⢨⢚⠌⣾⡪⣾⣿\n"
           "⣿⣿⣆⠄⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡑⢕⢕⡯⡷⣕⢧⢓⢭⠨⡀⠄⡂⠨⡨⣪⡳⣝⢝⡽⣻⣻⣞⢽⣲⢳⢱⢡⠱⠨⣟⢺⣿⣿\n"
           "⣿⣿⣿⡆⠄⡅⠇⡄⠄⠄⠄⠄⠄⠄⠄⠐⠨⢪⢹⢽⢽⣺⢝⠉⠁⠁⠄⠄⠄⢌⢎⡖⡯⡎⡗⢝⠜⣶⣯⣻⢮⡻⣟⣳⡕⠅⣷⣿⣿⣿\n"
           "⣿⣿⣿⣿⣶⣶⣿⣷⠄⠄⠄⠄⠄⠄⠄⠄⠈⠔⡑⠕⠝⠄⡀⠄⠄⠊⢆⠂⠨⡪⣺⣮⣿⡾⡜⣜⡜⣄⠙⢞⣿⢿⡿⣗⢝⢸⣾⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⠄⡀⠄⠄⠄⠄⢀⠄⠠⠄⠠⠄⠄⠄⠄⠄⠄⠊⠺⡹⠳⡙⡜⡓⡭⡺⡀⠄⠣⡻⡹⡸⠨⣣⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⠄⠠⠄⠄⣂⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢄⠤⡤⡄⡆⡯⡢⡣⡣⡓⢕⠽⣄⠄⠨⡂⢌⣼⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡆⠄⠄⠄⠄⠈⠆⠄⠸⡂⠄⠄⠄⢀⠄⢀⠈⠄⠂⠁⠙⠝⠼⠭⠣⠣⠣⠑⠌⠢⠣⡣⡠⡘⣰⣱⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⢑⠄⠈⡱⠄⢘⠄⡀⠨⢐⣧⣳⣷⣶⣦⣤⣴⣶⣶⣶⡶⠄⡠⡢⡕⣜⠎⡮⣣⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⠄⠢⠄⠨⠄⠄⠣⡀⠄⢀⢀⢙⠃⡿⢿⠿⡿⡿⢟⢋⢔⡱⣝⢜⡜⡪⡪⣵⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡁⠄⠄⠄⠄⠄⠄⠄⠅⠄⠡⠄⠄⠡⢀⢂⠢⡡⠡⠣⡑⣏⢯⡻⡳⣹⡺⡪⢎⠎⡆⢣⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣇⠄⠄⠄⠄⠄⠄⠄⠐⠄⠄⠁⠄⢈⠄⢂⠕⡕⡝⢕⢎⢎⢮⢎⢯⢺⢸⢬⠣⢃⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⠨⡐⠌⢆⢇⢧⢭⣣⡳⣵⢫⣳⢱⠱⢑⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣆⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠁⡊⢌⢢⢡⢣⢪⡺⡪⡎⡎⡎⡚⣨⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠕⡅⢗⢕⡳⡭⣳⢕⠕⡱⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠌⠄⠑⠩⢈⢂⣱⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡀⢄⠄⣀⠄⡀⣀⢠⢄⣖⣖⣞⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣱⡐⡕⡕⡽⣝⣟⣮⣾⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣵⣽⣸⣃⣧⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    return 0;
}


void menu(TV *structure, int size)
{
    int index = 0;
    int k = 0;
    while(k != 3)
    {
    printf("٩(✿∂‿∂✿)۶(░S░I░m░P░o░T░я░Ж░к░@░)ヾ(o✪‿✪o)ｼ*");
    printf("\n1.Initiate structure array.\n"
           "2.Enter structure array.\n"
           "3.Double sort structure.\n"
           "4.Print structures.\n"
           "5.Delete structure from array.\n"
           "6.Parce.\n"
           "7.Single sort structure.\n"
           "8.Exit.\n");
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
            printf("%d", size);
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
            structure = (TV*) calloc(62, sizeof (TV));
            parce(structure);
            k = 2;
            size = 61;
            break;
        case 7:
            if(k != 2)
            {
                printf("You didn't fill/create an array.\n");
                break;
            }
            single_sort(structure, size);
            break;
        case 8:
            k = 3;
            break;
        default:
            printf("Wrong input!");
            break;
    }
    }
    free_struct(structure, size);
}


void dell_struct(TV *structure, int *size)
{
    int dell;
    int index = *size;
    printf("\nChoose TV that you want to delete.\n");
    for (int k = 0; k < index; k++)
    {
        printf("%d: %s\n", k, structure[k].name);
    }
    check_in_range(&dell, 0, index - 1);
    for (int j = dell; j < index - 1; j++)
    {
        structure[j] = structure[j + 1];
    }
    free(structure[*size - 1].name);
    free(&structure[*size - 1]);
    (*size)--;
    structure = (TV*)realloc(structure, *size * sizeof (TV));
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
        printf("\nEnter price\n");
        scanf_s("%f", &structure[i].price);
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
        printf("\nPrice is: %1.2f", structure[i].price);
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
                SWAP_FLT(structure[j].price, structure[j + 1].price)
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
                SWAP_FLT(structure[j].price, structure[j + 1].price)
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
                SWAP_FLT(structure[j].price, structure[j + 1].price)
                SWAP(structure[j].smart_TV, structure[j + 1].smart_TV)
            }
        }
    }
}

void sort_by_price(TV *structure, int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size - 1; ++j)
        {
            if(structure[j].price < structure[j + 1].price)
            {
                SWAP_STR(structure[j].name, structure[j + 1].name)
                SWAP(structure[j].resolution.w, structure[j + 1].resolution.w)
                SWAP(structure[j].resolution.h, structure[j + 1].resolution.h)
                SWAP(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi)
                SWAP_FLT(structure[j].price, structure[j + 1].price)
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
                SWAP_FLT(structure[j].price, structure[j + 1].price)
                SWAP(structure[j].smart_TV, structure[j + 1].smart_TV)
            }
        }
    }
}

void check_in_range(int *value, int left_boarder, int right_boarder)
{
    while (scanf_s("%d", value) == 0 || getchar() !='\n' || *value < left_boarder || *value > right_boarder)
    {
        printf("Wrong input");
        rewind(stdin);
    }
}

void single_sort(TV *structure, int num_of_elements) {
    int first;
        printf("\nChoose sorting field.\n 1.Sort by name.\n 2.Sort by resolution."
               "\n 3.Sort by number of hdmi\n 4.Sort by price\n 5.Sort by available of Smart TV\n");
            check_in_range(&first, 1, 5);
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
                sort_by_price(structure, num_of_elements);
                break;
            case 5:
                sort_by_avail_of_stv(structure, num_of_elements);
                break;
            default:
                printf("Wrong input!");
                break;
        }
}

void double_sort(TV *structure, int num_of_elements)
{
    int first;
    int second;
    int cnt = 0;
    while(cnt != 2) {
        printf("\nChoose sorting field.\n 1.Sort by name.\n 2.Sort by resolution."
               "\n 3.Sort by number of hdmi\n 4.Sort by price\n 5.Sort by available of Smart TV\n");
        if(cnt == 1)
        {
            check_in_range(&second, 1, 5);
            check_same(&second, &first);
        }
        else
            check_in_range(&first, 1, 5);
        cnt++;
    }
    param_sort(structure, num_of_elements, first, second);
}

void param_sort(TV *structure, int num_of_elements, int first, const int second)
{
    TV temp;
    int arr[7];
    for (int i = 0; i < num_of_elements; ++i)
    {
        for (int j = i + 1; j < num_of_elements - 1; ++j)
        {
            COMPARE(structure[j].price, structure[j + 1].price, arr[4])
            COMPARE(structure[j].smart_TV, structure[j + 1].smart_TV, arr[5])
            COMPARE(structure[j].number_of_hdmi, structure[j + 1].number_of_hdmi, arr[3])
            COMPARE(structure[j].resolution.w * structure[i + 1].resolution.h, structure[j].resolution.w * structure[j].resolution.h, arr[2])
            arr[1] = strcmp(structure[j].name, structure[j + 1].name);
            if(arr[first] > 0 && arr[second] > 0)
            {
                temp = structure[j];
                structure[j] = structure[j + 1];
                structure[j + 1] = temp;
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

void parce(TV *structure)
{
    ///NAME --- class="" alt="Телевизор
    ///RESOLUTION --- Разрешение</td><td class='result__attr_val  cr-result__attr_odd'>
    ///SMART TV --- Smart TV</td><td class='result__attr_val '>
    ///HDMI --- Количество HDMI</td><td class='result__attr_val  cr-result__attr_odd'>
    ///PRICE --- data-price="
    FILE *f;
    f = fopen("parce.txt", "rt+");
    char c;
    char NAME[24] = "alt=\"Телевизор"; ///-
    char PRICE[13] = "data-price="; ///"
    char RESOLUTION[76] = "Разрешение</td><td class='result__attr_val  cr-result__attr_odd'"; ///<
    char HDMI[35] = ">Количество HDMI</td><td"; ///<
    char SMART_TV[44] = "Smart TV</td><td class='result__attr_val '>"; ///<
    int i = 1;
    int j = 0;
    int k = 0;
////////////////////////////////////////NAME
    while(!feof(f)) {
        c = (char)fgetc(f);


        if (c == NAME[0]) {
            c = (char)fgetc(f);
            while (c == NAME[i])
            {
                i++;
                c = (char)fgetc(f);
            }
        }


        if(i == strlen(NAME))
        {
            c = (char)fgetc(f);
            structure[j].name = (char*) malloc(1);
            while(c != '-')
            {
                structure[j].name = (char*) realloc(structure[j].name, (k + 1));
                structure[j].name[k] = c;
                c = (char)fgetc(f);
                k++;
            }
            structure[j].name = (char*) realloc(structure[j].name, k);
            k = 0;
        }
        else
        {
            i = 1;
            continue;
        }


        j++;
        i = 1;
    }
    j = 0;
    i = 1;
    fclose(f);
////////////////////////////////////////////HDMI
    f = fopen("parce.txt", "rt+");
    while(!feof(f)) {
        c = (char)fgetc(f);


        if (c == HDMI[0]) {
            c = (char)fgetc(f);
            while (c == HDMI[i])
            {
                i++;
                c = (char)fgetc(f);
            }
        }


        if(i == strlen(HDMI))
        {
            structure[j].number_of_hdmi = 0;
            c = (char)fgetc(f);
            while((int)c > 57 || (int)c < 48)
            {
                c = (char)fgetc(f);
            }
            structure[j].number_of_hdmi = atoi(&c);
        }
        else
        {
            i = 1;
            continue;
        }


        j++;
        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
//////////////////////////////////////////PRICE
    f = fopen("parce.txt", "rt+");
    while(!feof(f)) {
        c = (char)fgetc(f);

        if (c == PRICE[0]) {
            c = (char)fgetc(f);
            while (c == PRICE[i])
            {
                i++;
                c = (char)fgetc(f);
            }
        }


        if(i == strlen(PRICE))
        {
            fscanf(f, "%f", &structure[j].price);
        }
        else
        {
            i = 1;
            continue;
        }


        j++;
        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
///////////////////////////////////////////////////////////SMART TV
    f = fopen("parce.txt", "rt+");
    while(!feof(f)) {
        c = (char)fgetc(f);

        if (c == SMART_TV[0]) {
            c = (char)fgetc(f);
            while (c == SMART_TV[i])
            {
                i++;
                c = (char)fgetc(f);
            }
            c = (char)fgetc(f);
            c = (char)fgetc(f);
        }

        if(i == strlen(SMART_TV))
        {
            if((int)c == -47)
                structure[j].smart_TV = 1;
            if((int)c == -48)
                structure[j].smart_TV = 0;
        }
        else
        {
            i = 1;
            continue;
        }


        j++;
        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
////////////////////////////////////RESOLUTION
    f = fopen("parce.txt", "rt+");
    while(!feof(f)) {
        c = (char)fgetc(f);

        if (c == RESOLUTION[0]) {
            c = (char)fgetc(f);
            while (c == RESOLUTION[i])
            {
                i++;
                c = (char)fgetc(f);
            }
        }

        if(i == strlen(RESOLUTION))
        {
            fscanf(f, "%d", &structure[j].resolution.w);
            c = (char)fgetc(f);
            fscanf(f, "%d", &structure[j].resolution.h);
        }
        else
        {
            i = 1;
            continue;
        }
        j++;
        i = 1;
    }
    fclose(f);
}


void free_struct(TV *structure, int size)
{
    for (int i = 0; i < size; ++i)
    {
        free(structure[i].name);
        free(&structure[i]);
    }
}