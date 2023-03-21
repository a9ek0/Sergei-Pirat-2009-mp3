#include "functions.h"

void initialize_lyb(Library *lyb) {
    lyb->num_of_words = 0;
    lyb->words = malloc(1 * sizeof(replacement_words));
    for (int i = 0; i < 1; i++) {
        lyb->words[i].word1 = NULL;
        lyb->words[i].word2 = NULL;
    }
}

void free_lyb(Library *lyb)
{
    for (int i = 0; i < lyb->num_of_words; i++) {
        free(lyb->words[i].word1);
        free(lyb->words[i].word2);
    }
    free(lyb->words);
    free(lyb);
}

void file_to_lyb(FILE *file, Library *lyb, const char *key)
{
    if(file == NULL)
        return;
    find_key(file, key);
    char word[MAX_WORD_LEN];
    char next_char;
    while(fscanf(file, "%50s", word) == 1)
    {
        next_char = (char)fgetc(file);
        fseek(file, -1, SEEK_CUR);
        if(next_char == ' ')
            lyb->words[lyb->num_of_words].word1 = strdup(word);
        if(next_char == '\n')
        {
            lyb->words[lyb->num_of_words].word2 = strdup(word);
            lyb->num_of_words++;
            lyb->words = realloc(lyb->words, (lyb->num_of_words + 1) * sizeof (replacement_words));
        }
    }
}

void delete_in_file_lyb(const char *file_name, const char *key)
{
    FILE *file;
    file = fopen(file_name, "r");
    if(file == NULL)
        return;
    ull pos;
    find_key(file, key);
    pos = ftell(file);
    fseek(file, (long)(pos - strlen(key)), SEEK_SET);
    pos = ftell(file);
    fclose(file);

    truncate_file(file_name, pos);
}

void truncate_file(const char *file_name, ull pos)
{
    int fd = open(file_name, O_RDWR);
    ftruncate(fd, lseek(fd, (long)pos, SEEK_SET));
    close(fd);
}

void find_key(FILE *file, const char *key)
{
    if(file == NULL)
        exit(EXIT_FAILURE);
    char word[MAX_WORD_LEN];
    while(fscanf(file, "%50s", word) == 1)
    {
        if(strcmp(word, key) == 0)
        {
            return;
        }
    }
}

char* dell_punct_marks(char *word_ptr) {
    if (word_ptr == NULL || *word_ptr == '\0') {
        return NULL;
    }
    char *word = word_ptr;
    size_t size = strlen(word);
    while (size > 0 && !isalpha(word[0])) {
        size--;
        memmove(word, word + 1, size);
    }
    while (size > 0 && !isalpha(word[size - 1])) {
        word[--size] = '\0';
    }

    return word;
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
    {
        printf("File doesn't exist!");
        fclose(fr);
        return;
    }


    char word[MAX_WORD_LEN];
    char tmp_word[MAX_WORD_LEN];
    const char *cleaned_word;
    int flag = 1;

    while(fscanf(fr, "%50s", word) == 1)
    {
        strcpy(tmp_word, word);
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
    fclose(fr);
    fclose(fw);
}

void save_control_characters(FILE* file, FILE* file1) {
    int next_char = fgetc(file1);
    while(next_char == ' ' || next_char == '\n' || next_char == '\t' || next_char == '\r' || next_char == '\v' || next_char == '\f') {
        fputc(next_char, file);
        next_char = fgetc(file1);
    }
    if(next_char != EOF)
        fseek(file1, -1, SEEK_CUR);
}

void replace_word(char* text, const char* old_word, const char* new_word) {
    char* pos = text;
    ull old_len = strlen(old_word);
    ull new_len = strlen(new_word);

    while ((pos = strstr(pos, old_word)) != NULL) {
        memmove(pos + new_len, pos + old_len, strlen(pos + old_len) + 1);
        memcpy(pos, new_word, new_len);
        pos += new_len;
    }
}
