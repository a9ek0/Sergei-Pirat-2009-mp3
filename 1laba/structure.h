#ifndef INC_1_LABA_2S_STRUCTURE_H
#define INC_1_LABA_2S_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <windows.h>
#define SWAP(A, B) { int t = A; A = B; B = t; }
#define SWAP_FLT(A, B) { float t = A; A = B; B = t; }
#define SWAP_STR(A, B) { char t[50]; strcpy(t, A); strcpy(A, B); strcpy(B, t); }

typedef struct film
{
    char *name;
    float rating;
    int length;
   // enum {clrDefault, clrYellow, clrGreen, clrRed};
}film_func;

void arr_structure_print(struct film structure[], int num_of_elements);
void arr_struct_create(struct film structure[], int num_of_elements);
void init_struct_exam(struct film structure);
void name_sort(struct film structure[], int num_of_elements);
void rating_sort(struct film structure[], int num_of_elements);
void length_sort(struct film structure[], int num_of_elements);
void double_sort(struct film structure[], int num_of_elements);
void set_text_color(int color);
void dell_struct(struct film structure[], int* num_of_elements);
void init_struct_arr(struct film *structure, int *num_of_elements);
film_func* init_struct(int *num_of_elements);
film_func* realloc_struct(film_func *structure, int* new_size);
void menu(film_func *structure, int num_of_elements);





#endif //INC_1_LABA_2S_STRUCTURE_H
