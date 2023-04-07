#ifndef INC_3LABA_FUNCTIONS_H
#define INC_3LABA_FUNCTIONS_H
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <time.h>

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
int compare(const void* a, const void* b);
size_t find_median_value(const PIXEL *pixels,const BITMAPINFOHEADER *info_header, size_t num_of_pixel);
void median_filtering(FILE *input_file, FILE *output_file, int window_size);
size_t get_median_value(size_t* values, size_t count);
void add_white_noise(FILE* input_file, FILE* output_file, float noise_factor);


int is_bmp_file(const char* file_name);
FILE* open_bmp_file(const char *file_name, const char *extension);
void check_in_range_int(int *value, int left_boarder, int right_boarder);
void check_in_range_float(float *value, float left_boarder, float right_boarder);
void copy_file(FILE* inputFile, FILE* outputFile);
void menu(FILE *input_file, FILE *output_file, const char* output_file_name);
FILE *copy_binary_file(FILE *input_file, FILE *output_file, const char *output_file_name);
#endif //INC_3LABA_FUNCTIONS_H
