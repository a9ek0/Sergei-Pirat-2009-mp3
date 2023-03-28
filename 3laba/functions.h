#ifndef INC_3LABA_FUNCTIONS_H
#define INC_3LABA_FUNCTIONS_H
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

typedef unsigned long long ull;

typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} __attribute__((packed)) BITMAPINFOHEADER;


typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} __attribute__((packed)) PIXEL;


void convert_to_bw(FILE *input_file, FILE *output_file);
void convert_to_negative(FILE *input_file, FILE *output_file);
void gamma_correction(FILE *input_file, FILE *output_file, float gamma);

int is_bmp_file(const char* file_name);
FILE* open_bmp_file(const char *file_name, const char *extension);
#endif //INC_3LABA_FUNCTIONS_H
