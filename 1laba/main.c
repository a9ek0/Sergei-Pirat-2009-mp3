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
int compare_smart_TV(const void *p1, const void *p2);
int compare_price(const void *p1, const void *p2);
int compare_number_of_hdmi(const void *p1, const void *p2);
int compare_resolution(const void *p1, const void *p2);
int compare_name(const void *p1, const void *p2);
int compare_by_two_param(const void *p1, const void *p2);
int compare_by_name_res(const void *p1, const void *p2);
int compare_tv(const void *p1, const void *p2);
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
        //structure[i].name[buffer + 1] = '\n';
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
                qsort(structure, num_of_elements, sizeof (TV), compare_name);
                break;
            case 2:
                qsort(structure, num_of_elements, sizeof (TV), compare_resolution);
                break;
            case 3:
                qsort(structure, num_of_elements, sizeof (TV), compare_number_of_hdmi);
                break;
            case 4:
                qsort(structure, num_of_elements, sizeof (TV), compare_price);
                break;
            case 5:
                qsort(structure, num_of_elements, sizeof (TV), compare_smart_TV);
                break;
            default:
                printf("Wrong input!");
                break;
        }
}

void double_sort(TV *structure, int num_of_elements)
{
    int index;

    printf("\nChoose sorting field.\n 1.Sort by name and resolution.\n 2.Sort by resolution.\n 3.Sort by number of hdmi\n 4.Sort by price\n 5.Sort by available of Smart TV\n");
    check_in_range(&index, 0, 10);
    switch (index) {
        case 1:
        ///name + res
        break;
        case 2:
        ///name + hdmi
        break;
        case 3:
        ///name + price
        break;
        case 4:
        ///name + smart_tv
        break;
        case 5:
        ///res + hdmi
        break;
        case 6:
        ///res + price
        break;
        case 7:
        ///res + smart_tv
        break;
        case 8:
        ///hdmi + price
        break;
        case 9:
        ///hdmi + smart_tv
        break;
        case 10:
        ///price + smart_tv
            qsort(structure, num_of_elements, sizeof(TV), compare_tv);
            break;
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
    if ((f = fopen("parce.txt", "r")) == NULL)
    {
        printf("Открыть файл не удалось\n");
        exit(1);
    }
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
            k = 0;
            c = (char)fgetc(f);
            structure[j].name = (char*) malloc(1);
            while(c != '-')
            {
                structure[j].name = (char*) realloc(structure[j].name, (k + 1));
                structure[j].name[k] = c;
                c = (char)fgetc(f);
                k++;
            }
            structure[j].name[k] = '\0';
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
    f = fopen("parce.txt", "r");
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
    f = fopen("parce.txt", "r");
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
    f = fopen("parce.txt", "r");
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
    f = fopen("parce.txt", "r");
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

int compare_name(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    return strcmp(tv1->name, tv2->name);
}

int compare_resolution(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->resolution.w < tv2->resolution.w) {
        return -1;
    } else if (tv1->resolution.w > tv2->resolution.w) {
        return 1;
    } else {
        return 0;
    }
}

int compare_number_of_hdmi(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->number_of_hdmi < tv2->number_of_hdmi) {
        return -1;
    } else if (tv1->number_of_hdmi > tv2->number_of_hdmi) {
        return 1;
    } else {
        return 0;
    }
}

int compare_price(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->price < tv2->price) {
        return -1;
    } else if (tv1->price > tv2->price) {
        return 1;
    } else {
        return 0;
    }
}

int compare_smart_TV(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->smart_TV < tv2->smart_TV) {
        return -1;
    } else if (tv1->smart_TV > tv2->smart_TV) {
        return 1;
    } else {
        return 0;
    }
}

int compare_by_name_res(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->name < tv2->name) {
        return -1;
    } else if (tv1->name > tv2->name) {
        return 1;
    } else {
        if ((tv1->resolution.w * tv1->resolution.h) < (tv2->resolution.w * tv2->resolution.h)) {
            return -1;
        } else if ((tv1->resolution.w * tv1->resolution.h) > (tv2->resolution.w * tv2->resolution.h)) {
            return 1;
        } else {
            return 0;
        }
    }
}


int compare_tv(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->price < tv2->price) {
        return -1;
    } else if (tv1->price > tv2->price) {
        return 1;
    } else {
        if (tv1->number_of_hdmi < tv2->number_of_hdmi) {
            return -1;
        } else if (tv1->number_of_hdmi > tv2->number_of_hdmi) {
            return 1;
        } else {
            return 0;
        }
    }
}

int compare_by_(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->name < tv2->name) {
        return -1;
    }
    else if (tv1->name > tv2->name) {
        return 1;
    }
    else {
        if (tv1->resolution.w < tv2->resolution.w) {
            return -1;
        }
        else if (tv1->resolution.w > tv2->resolution.w) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

int compare_by_two_(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->name < tv2->name) {
        return -1;
    }
    else if (tv1->name > tv2->name) {
        return 1;
    }
    else {
        if (tv1->resolution.w < tv2->resolution.w) {
            return -1;
        }
        else if (tv1->resolution.w > tv2->resolution.w) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

