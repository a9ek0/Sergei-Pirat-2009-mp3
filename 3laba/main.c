
#include "functions.h"


int compare(const void* a, const void* b);
PIXEL find_median_value(const PIXEL *pixels,const BITMAPINFOHEADER *info_header, size_t num_of_pixel);
void median_filtering(FILE *input_file, FILE *output_file);


int main()
{
    FILE *input_file;
    FILE *output_file;
    char input_file_name[11] = "image.bmp";
    char output_file_name[17] = "edited_image.bmp";

    input_file = open_bmp_file(input_file_name, "rb");
    output_file = open_bmp_file(output_file_name, "wb");

    median_filtering(input_file, output_file);
    //gamma_correction(input_file, output_file, 1);
    //convert_to_bw(input_file, output_file);
    //convert_to_negative(input_file, output_file);

    fclose(input_file);
    fclose(output_file);

    system("start edited_image.bmp");

    return 0;
}


void median_filtering(FILE *input_file, FILE *output_file)
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
        pixels[i] = find_median_value(pixels, &header, pixel_count);
    }

    fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, output_file);
    fwrite(&header, sizeof(BITMAPINFOHEADER), 1, output_file);
    fseek(output_file, file_header.bfOffBits, SEEK_SET);
    fwrite(pixels, sizeof(PIXEL), pixel_count, output_file);

    free(pixels);
}

PIXEL find_median_value(const PIXEL *pixels,const BITMAPINFOHEADER *info_header, size_t num_of_pixel){
    size_t pixel_count = info_header->biWidth * info_header->biHeight;
    size_t median_values[9] = {0};

    for (size_t i = num_of_pixel > 0 ? num_of_pixel - 1 : num_of_pixel, j = 0; i < 3 && i < pixel_count; i += info_header->biWidth, j += 3) {
        median_values[j] = (pixels[j].r + pixels[j].b + pixels[j].g) / 3;
        median_values[j + 1] = (pixels[j + 1].r + pixels[j + 1].b + pixels[j + 1].g) / 3;
        median_values[j + 2] = (pixels[j + 2].r + pixels[j + 2].b + pixels[j + 2].g) / 3;
    }
    qsort(median_values, 9, sizeof (size_t), compare);
    return median_values[5];
}

int compare(const void* a, const void* b) {
    int num1 = *(int*)a;
    int num2 = *(int*)b;
    return num1 - num2;
}
