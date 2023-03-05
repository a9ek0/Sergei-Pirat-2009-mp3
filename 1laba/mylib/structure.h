#ifndef INC_1LABA_STRUCTURE_H
#define INC_1LABA_STRUCTURE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdnoreturn.h>
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
void print_name(TV *structure, int size);
void check_in_range(int *value, int left_boarder, int right_boarder);
void dell_struct(TV **structure, int *size);
void remove_tv(TV **structure, int index, int *size);

void double_sort(TV *structure, int num_of_elements);
void single_sort(TV *structure, int num_of_elements);
void check_same(int *first_number, const int *second_number);
void menu(TV *structure, int size);
void parce(TV *structure);
void sort_TV(TV *structure, int num_tvs, int sort_field_1, int sort_field_2);
int compare_resolution_desc(const TV *tv1, const TV *tv2);
int compare_name_asc(const TV *tv1, const TV *tv2);
void sort_tvs(TV *tvs, int num_tvs, int compare1, int compare2);
void free_memory(TV *structure, int size);
/////////////////////////////////
int compare(const TV *tv1,const TV *tv2, int sort_by);
void sort(TV *structure, int size, int sort_by);
void d_sort(TV *tvs, int size, int field1, int field2);
//////////////////////single comp
int compare_smart_TV(const void *p1, const void *p2);
int compare_price(const void *p1, const void *p2);
int compare_number_of_hdmi(const void *p1, const void *p2);
int compare_resolution(const void *p1, const void *p2);
int compare_name(const void *p1, const void *p2);
int compare_by_two_param(const void *p1, const void *p2);
/////////////////////compare by two
int compare_by_name_res(const void *p1, const void *p2);
int compare_by_name_hdmi(const void *p1, const void *p2);
int compare_by_name_price(const void *p1, const void *p2);
int compare_by_price_smart_tv(const void *p1, const void *p2);
int compare_by_name_smart_tv(const void *p1, const void *p2);
int compare_by_hdmi_smart_tv(const void *p1, const void *p2);
int compare_by_hdmi_price(const void *p1, const void *p2);

#endif //INC_1LABA_STRUCTURE_H
