#include "functions.h"

FILE* open_bmp_file(const char *file_name, const char *extension){
    FILE *bmp_file;
    if(is_bmp_file(file_name)){
        bmp_file = fopen(file_name, extension);
        if (bmp_file == NULL){
            fprintf(stderr, "Error: unable to open file.\n");
            exit(EXIT_FAILURE);
        }
        BITMAPINFOHEADER info_header;
        fseek(bmp_file, 14, SEEK_SET);
        fread(&info_header, sizeof(BITMAPINFOHEADER), 1, bmp_file);
        if (info_header.biBitCount != 24){
            fprintf(stderr, "Error: BMP image is not 24-bit.\n");
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
        pixel->r = (uint8_t)(255 * pow(pixel->r / 255.0, gamma));
        pixel->g = (uint8_t)(255 * pow(pixel->g / 255.0, gamma));
        pixel->b = (uint8_t)(255 * pow(pixel->b / 255.0, gamma));
    }

    fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, output_file);
    fwrite(&header, sizeof(BITMAPINFOHEADER), 1, output_file);
    fseek(output_file, file_header.bfOffBits, SEEK_SET);
    fwrite(pixels, sizeof(PIXEL), pixel_count, output_file);

    free(pixels);
}

void median_filtering(FILE *input_file, FILE *output_file, int window_size)
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

    size_t* valuesr = malloc(window_size * window_size * sizeof(size_t));
    size_t* valuesg = malloc(window_size * window_size * sizeof(size_t));
    size_t* valuesb = malloc(window_size * window_size * sizeof(size_t));

    for (size_t i = window_size / 2; i < header.biHeight - window_size / 2; i++) {
        for (size_t j = window_size / 2; j < header.biWidth - window_size / 2; j++) {
            size_t row = i - window_size / 2;
            size_t col = j - window_size / 2;
            for (size_t k = 0; k < window_size * window_size; k++) {
                size_t idx = k / window_size;
                size_t jdx = k % window_size;
                valuesr[k] = pixels[(row + idx) * header.biWidth + col + jdx].r;
                valuesg[k] = pixels[(row + idx) * header.biWidth + col + jdx].g;
                valuesb[k] = pixels[(row + idx) * header.biWidth + col + jdx].b;
            }
            pixels[i * header.biWidth + j].r = (uint8_t)get_median_value(valuesr, window_size * window_size);
            pixels[i * header.biWidth + j].g = (uint8_t)get_median_value(valuesg, window_size * window_size);
            pixels[i * header.biWidth + j].b = (uint8_t)get_median_value(valuesb, window_size * window_size);
        }
    }
    free(valuesr);
    free(valuesg);
    free(valuesb);

    fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, output_file);
    fwrite(&header, sizeof(BITMAPINFOHEADER), 1, output_file);
    fseek(output_file, file_header.bfOffBits, SEEK_SET);
    fwrite(pixels, sizeof(PIXEL), pixel_count, output_file);

    free(pixels);
}

size_t get_median_value(size_t *values, const size_t count) {
    if (count == 0 || values == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = i + 1; j < count; j++) {
            const size_t temp_i = values[i];
            const size_t temp_j = values[j];
            if (temp_j < temp_i) {
                values[i] = temp_j;
                values[j] = temp_i;
            }
        }
    }

    size_t median_value;
    if (count % 2 == 0) {
        median_value = (values[count / 2 - 1] + values[count / 2]) / 2;
    } else {
        median_value = values[count / 2];
    }

    return median_value;
}






void add_white_noise(FILE* input_file, FILE* output_file, float noise_factor) {
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

    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < pixel_count; i++) {
        PIXEL* pixel = &pixels[i];

        int noise_r = rand() % (int)(noise_factor * 255);
        int noise_g = rand() % (int)(noise_factor * 255);
        int noise_b = rand() % (int)(noise_factor * 255);

        pixel->r = (pixel->r + noise_r) > 255 ? 255 : (uint8_t)(pixel->r + noise_r);
        pixel->g = (pixel->g + noise_g) > 255 ? 255 : (uint8_t)(pixel->g + noise_g);
        pixel->b = (pixel->b + noise_b) > 255 ? 255 : (uint8_t)(pixel->b + noise_b);
    }

    fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, output_file);
    fwrite(&header, sizeof(BITMAPINFOHEADER), 1, output_file);
    fseek(output_file, file_header.bfOffBits, SEEK_SET);
    fwrite(pixels, sizeof(PIXEL), pixel_count, output_file);

    free(pixels);
}

void check_in_range_int(int *value, int left_boarder, int right_boarder)
{
    while (scanf_s("%d", value) == 0 || getchar() !='\n' || *value < left_boarder || *value > right_boarder)
    {
        printf("Wrong input");
        rewind(stdin);
    }
}

void check_in_range_float(float *value, float left_boarder, float right_boarder)
{
    while (scanf_s("%f", value) == 0 || getchar() !='\n' || *value < left_boarder || *value > right_boarder)
    {
        printf("Wrong input");
        rewind(stdin);
    }
}

void copy_file(FILE* inputFile, FILE* outputFile) {
    char *buffer;
    size_t bufferSize;

    if (inputFile == NULL) {
        printf("Cannot open %s for reading\n", inputFile);
        exit(EXIT_FAILURE);
    }

    if (outputFile == NULL) {
        printf("Cannot open %s for writing\n", outputFile);
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    fseek(inputFile, 0, SEEK_END);
    bufferSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    buffer = (char *) malloc(bufferSize * sizeof(char));
    if (buffer == NULL) {
        printf("Memory allocation error\n");
        fclose(inputFile);
        fclose(outputFile);
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(char), bufferSize, inputFile);
    fwrite(buffer, sizeof(char), bufferSize, outputFile);

    free(buffer);

}

void menu(FILE *input_file, FILE *output_file, const char* output_file_name)
{
    int expression;
    float value = 0;
    while(1) {
        printf("Choose an image processing option:"
               "\n1.Convert to negative"
               "\n2.Convert to black/white"
               "\n3.Gamma correction"
               "\n4.Add white noise to the image"
               "\n5.Perform median filtering"
               "\n6.View image"
               "\n7.Reset changes"
               "\n8.Exit\n");
        check_in_range_int(&expression, 1, 8);
        switch (expression) {
            case 1:
                convert_to_negative(output_file, output_file);
                break;
            case 2:
                convert_to_bw(output_file, output_file);
                break;
            case 3:
                printf("Enter gamma value."
                       "\nRecommended value from 1 to 2.5\n");
                check_in_range_float(&value, 0, 100);

                gamma_correction(output_file, output_file, value);
                break;
            case 4:
                printf("Enter noise value."
                       "\nMaximum noise level at value 1\n");
                check_in_range_float(&value, 0, 1);

                add_white_noise(output_file, output_file, value);
                break;
            case 5:
                printf("Enter field size for median filtering\n");
                check_in_range_float(&value, 0, 10);

                median_filtering(output_file, output_file, (int)value);
                break;
            case 6:
                fclose(output_file);

                char command[100];

                strcpy(command,  "start ");
                strcat(command , output_file_name);

                system(command);
                output_file = open_bmp_file(output_file_name, "rb+");
                break;
            case 7:
                output_file = copy_binary_file(input_file, output_file, output_file_name);
                break;
            case 8:
                fclose(output_file);
                return;
            default:
                printf("Wrong input!");
                break;
        }
    }
}

FILE *copy_binary_file(FILE *input_file, FILE *output_file, const char *output_file_name) {
    unsigned char *buffer;
    size_t bytes_read;

    fseek(input_file, 0, SEEK_END);
    bytes_read = ftell(input_file);

    buffer = (unsigned char*) malloc(bytes_read * sizeof (unsigned char));
    fseek(input_file, 0, SEEK_SET);
    fread(buffer, sizeof(unsigned char), bytes_read, input_file);
    fseek(output_file, 0, SEEK_SET);
    fwrite(buffer, sizeof(unsigned char), bytes_read, output_file);


    fclose(output_file);
    output_file = open_bmp_file(output_file_name, "rb+");

    return output_file;
}
