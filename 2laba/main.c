#include "lyb/functions.h"
#include <Windows.h>

void compress_file(const char *input_file, const char* output_file, const Library *lyb);
void decompress_file(const char *input_file, const char *output_file, const Library *lyb);

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Stack *stack;
    stack = create_stack();

    Library *lyb = malloc(sizeof(Library));
    lyb->num_of_words = 0;
    lyb->words = malloc(1 * sizeof(replacement_words));
    for (int i = 0; i < 1; i++) {
        lyb->words[i].word1 = NULL;
        lyb->words[i].word2 = NULL;
    }

    copy_file("rjomba.txt", "compressed_file.txt");

    text_to_stack("rjomba.txt", stack);

    //print_stack(stack);
    stack_to_lyb(stack, lyb);

   // sort_stack_l_h(stack);
    //print_stack(stack);

    //printf("\n\n\n\n");

    //sort_stack_h_l(stack);
    //print_stack(stack);

    compress_file("rjomba.txt", "compressed_file.txt", lyb);

    //compress_file("compressed_file.txt", "temp.txt", lyb);




    FILE *f;
    f = fopen("compressed_file.txt", "at");
    fputs("\n", f);
    fputs("!1RvD8*ku$%TqFw&zPbN@5sLx", f);
    fputs("\n", f);
    for (int i = 0; i < lyb->num_of_words - 1; ++i) {
        fputs(lyb->words[i].word1, f);
        fputs(" ", f);
        fputs(lyb->words[i].word2, f);
        fputs("\n", f);
    }
    fclose(f);
   /* for (int i = 0; i < lyb->num_of_words; ++i) {

        printf("%s - %s\n", lyb->words[i].word1, lyb->words[i].word2);
    }
*/
    free_lyb(lyb);
    return 0;
}

void compress_file(const char *input_file, const char* output_file, const Library *lyb)
{
    FILE *fr;

    fr = fopen(input_file, "rt");
    if(fr == NULL)
        return;

    FILE *fw;

    fw = fopen(output_file, "wt");
    if(fw == NULL)
        return;

    char word[MAX_WORD_LEN];
    char tmp_word[MAX_WORD_LEN];
    char *cleaned_word;
    char next_chars[10];
    int flag = 1;


    while(fscanf(fr, "%s", word) == 1)
    {
        strcpy(tmp_word, word);
        //next_char = (char)getc(fr);
        cleaned_word = dell_punct_marks(word);
        flag = 1;
        for (int i = 0; i < lyb->num_of_words - 1; ++i) {
            if(strcmp(cleaned_word, lyb->words[i].word1) == 0) {
                replace_word(tmp_word, cleaned_word, lyb->words[i].word2);
                fputs(tmp_word, fw);
                save_control_characters(fw, fr);
                flag = 0;
            } else if(strcmp(cleaned_word, lyb->words[i].word2) == 0) {
                replace_word(tmp_word, cleaned_word, lyb->words[i].word1);
                fputs(tmp_word, fw);
                save_control_characters(fw, fr);
                flag = 0;
            }
        } if (flag == 1) {
            fputs(tmp_word, fw);
            save_control_characters(fw, fr);
        }

    }
    //free(cleaned_word);
    fclose(fr);
    fclose(fw);
}

void decompress_file(const char *input_file, const char* output_file, const Library *lyb)
{
    FILE *fr;

    fr = fopen(input_file, "rt");
    if(fr == NULL)
        return;

    FILE *fw;

    fw = fopen(output_file, "wt");
    if(fw == NULL)
        return;

    char word[MAX_WORD_LEN];
    char *cleaned_word;
    char next_char;
    int flag = 1;

    while(fscanf(fr, "%s", word) == 1)
    {
        next_char = (char)getc(fr);
        cleaned_word = dell_punct_marks(word);
        flag = 1;
        for (int i = 0; i < lyb->num_of_words - 1; ++i) {
            if(strcmp(cleaned_word, lyb->words[i].word2) == 0) {
                replace_word(word, cleaned_word, lyb->words[i].word1);
                fputs(word, fw);
                save_control_characters(next_char, fw);
                flag = 0;
            } else if(strcmp(cleaned_word, lyb->words[i].word1) == 0) {
                replace_word(word, cleaned_word, lyb->words[i].word2);
                fputs(word, fw);
                save_control_characters(next_char, fw);
                flag = 0;
            }
        } if (flag == 1) {
            fputs(word, fw);
            save_control_characters(next_char, fw);
        }
    }
    //free(cleaned_word);
    fclose(fr);
    fclose(fw);
}