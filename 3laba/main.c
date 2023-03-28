#include "functions.h"

int main()
{
    FILE *input_file;
    FILE *output_file;

    char *input_file_name;
    char *output_file_name;

    input_file_name = (char*) malloc(256 * sizeof(char));
    output_file_name = (char*) malloc(8 * sizeof (char));

    strcpy(output_file_name, "edited_");

    printf("Enter name of the image that you want to edit.\n");
    scanf_s("%s", input_file_name);

    input_file_name = realloc(input_file_name, (strlen(input_file_name) + 1) * sizeof (char));
    output_file_name = realloc(output_file_name, (strlen(input_file_name) + strlen(output_file_name) + 1) * sizeof (char));

    strcat(output_file_name, input_file_name);

    input_file = open_bmp_file(input_file_name, "rb");
    output_file = open_bmp_file(output_file_name, "wb");

    output_file = copy_binary_file(input_file, output_file, output_file_name);

    menu(input_file, output_file, output_file_name);

    fclose(input_file);
    fclose(output_file);

    free(input_file_name);
    free(output_file_name);
    return 0;
}




