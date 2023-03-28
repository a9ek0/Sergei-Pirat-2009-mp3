#include "functions.h"

FILE* open_bmp_file(const char *file_name, const char *extension){
    const FILE *bmp_file;
    if(is_bmp_file(file_name)){
        bmp_file = fopen(file_name, extension);
        if (bmp_file == NULL){
            fprintf(stderr, "Error: unable to open file.\n");
            exit(EXIT_FAILURE);
        }
        return bmp_file;
    }else{
        fprintf(stderr, "Error: the file has the wrong extension.\n");
        exit(EXIT_FAILURE);
    }
}

int is_bmp_file(const char *file_name) {
    const char* ext = strrchr(file_name, '.');
    if (ext == NULL) return 0;
    return strcmp(ext, ".bmp") == 0;
}

void convert_to_bw(FILE *input_file, FILE *output_file) {

    if (!input_file) {
        perror("Cannot open input file");
        return;
    }

    if (!output_file) {
        perror("Cannot open output file");
        fclose(input_file);
        return;
    }

    PIXEL* pixels;
    BITMAPINFOHEADER header;
    BITMAPFILEHEADER file_header;

    fseek(input_file, 0, SEEK_SET);
    fread(&file_header, sizeof(BITMAPFILEHEADER), 1, input_file);
    fread(&header, sizeof(BITMAPINFOHEADER), 1, input_file);

    size_t pixel_count = header.biWidth * header.biHeight;
    pixels = malloc(pixel_count * sizeof(PIXEL));
    fseek(input_file, file_header.bfOffBits, SEEK_SET);
    fread(pixels, sizeof(PIXEL), pixel_count, input_file);

    for (size_t i = 0; i < pixel_count; i++) {
        PIXEL* pixel = &pixels[i];
        uint8_t brightness = (pixel->r + pixel->b + pixel->g) / 3;
        pixel->r = brightness;
        pixel->g = brightness;
        pixel->b = brightness;
    }

    fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, output_file);
    fwrite(&header, sizeof(BITMAPINFOHEADER), 1, output_file);
    fseek(output_file, file_header.bfOffBits, SEEK_SET);
    fwrite(pixels, sizeof(PIXEL), pixel_count, output_file);

    free(pixels);
}

void convert_to_negative(FILE *input_file, FILE *output_file) {

    if (!input_file) {
        perror("Cannot open input file");
        return;
    }

    if (!output_file) {
        perror("Cannot open output file");
        fclose(input_file);
        return;
    }

    PIXEL* pixels;
    BITMAPINFOHEADER header;
    BITMAPFILEHEADER file_header;

    fseek(input_file, 0, SEEK_SET);
    fread(&file_header, sizeof(BITMAPFILEHEADER), 1, input_file);
    fread(&header, sizeof(BITMAPINFOHEADER), 1, input_file);

    size_t pixel_count = header.biWidth * header.biHeight;
    pixels = malloc(pixel_count * sizeof(PIXEL));
    fseek(input_file, file_header.bfOffBits, SEEK_SET);
    fread(pixels, sizeof(PIXEL), pixel_count, input_file);

    for (size_t i = 0; i < pixel_count; i++) {
        PIXEL* pixel = &pixels[i];
        pixel->r = 255 - pixel->r;
        pixel->g = 255 - pixel->g;
        pixel->b = 255 - pixel->b;
    }

    fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, output_file);
    fwrite(&header, sizeof(BITMAPINFOHEADER), 1, output_file);
    fseek(output_file, file_header.bfOffBits, SEEK_SET);
    fwrite(pixels, sizeof(PIXEL), pixel_count, output_file);

    free(pixels);
}

void gamma_correction(FILE *input_file, FILE *output_file, float gamma)
{
    if (!input_file) {
        perror("Cannot open input file");
        return;
    }

    if (!output_file) {
        perror("Cannot open output file");
        fclose(input_file);
        return;
    }

    PIXEL* pixels;
    BITMAPINFOHEADER header;
    BITMAPFILEHEADER file_header;

    fseek(input_file, 0, SEEK_SET);
    fread(&file_header, sizeof(BITMAPFILEHEADER), 1, input_file);
    fread(&header, sizeof(BITMAPINFOHEADER), 1, input_file);

    size_t pixel_count = header.biWidth * header.biHeight;
    pixels = malloc(pixel_count * sizeof(PIXEL));
    fseek(input_file, file_header.bfOffBits, SEEK_SET);
    fread(pixels, sizeof(PIXEL), pixel_count, input_file);

    for (size_t i = 0; i < pixel_count; i++) {
        PIXEL* pixel = &pixels[i];
        uint8_t brightness = (pixel->r + pixel->b + pixel->g) / 3;
        pixel->r = 255 * pow(pixel->r / 255.0, gamma);
        pixel->g = 255 * pow(pixel->g / 255.0, gamma);
        pixel->b = 255 * pow(pixel->b / 255.0, gamma);
    }

    fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, output_file);
    fwrite(&header, sizeof(BITMAPINFOHEADER), 1, output_file);
    fseek(output_file, file_header.bfOffBits, SEEK_SET);
    fwrite(pixels, sizeof(PIXEL), pixel_count, output_file);

    free(pixels);
}
