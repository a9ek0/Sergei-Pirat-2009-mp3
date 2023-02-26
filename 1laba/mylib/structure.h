#ifndef INC_1LABA_STRUCTURE_H
#define INC_1LABA_STRUCTURE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif //INC_1LABA_STRUCTURE_H
