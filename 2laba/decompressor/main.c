#include <Windows.h>
#include "functions.h"

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Library *lyb = malloc(sizeof(Library));

    initialize_lyb(lyb);

    char input_file_name[110] = "C://Users//Alexander//Documents//GitHub//Sergei-Pirat-2009-mp3//2laba//cmake-build-debug//compressed_file.txt";
    char output_file_name[11] = "source.txt";
    char key[26] = "!1RvD8*ku$%TqFw&zPbN@5sLx";

    FILE *file;
    file = fopen(input_file_name, "r");
    if(file == NULL)
    {
        printf("Ti poputal menchik");
        exit(EXIT_FAILURE);
    }

    file_to_lyb(file, lyb, key);

    fclose(file);

    decompress_file(input_file_name, output_file_name, lyb);

    free_lyb(lyb);

    delete_in_file_lyb(output_file_name, key);

    return 0;
}
