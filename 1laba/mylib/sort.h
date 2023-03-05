//
// Created by asduw on 06.03.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure_TV.h"
#include "check.h"
#ifndef INC_1LABA_SORT_H
#define INC_1LABA_SORT_H
void sort(TV *structure, int size, int sort_by);
int compare(const TV *tv1,const TV *tv2, int sort_by);
void d_sort(TV *tvs, int size, int field1, int field2);
int compare_smart_TV(const void *p1, const void *p2);
int compare_price(const void *p1, const void *p2);
int compare_number_of_hdmi(const void *p1, const void *p2);
int compare_resolution(const void *p1, const void *p2);
int compare_name(const void *p1, const void *p2);
void double_sort(TV *structure, int num_of_elements);
void single_sort(TV *structure, int num_of_elements);
#endif //INC_1LABA_SORT_H
