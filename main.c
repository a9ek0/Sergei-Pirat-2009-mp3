#include "structure.h"
#include <conio.h>
#include <ctype.h>
#include <locale.h>
void print_file_char(char* file_name, int size);
void print_file_int(char* file_name, int size);
void parce_name(char *parce_file_name, char * data_file);


//////////////////////////////ПРОВЕРКИ НАДО СДЕЛАТЬ
int main()
{
    setlocale(LC_ALL, "Rus");
    int x = 0;
    struct film const *da;
    int i = 0, j = 0;
    char c;
    char ch;
    char name[100] = "E://GITrepos//antonenko//1_laba_2s/1.txt";
    char name1[100] = "E://GITrepos//antonenko//1_laba_2s/2.txt";
    //char str[3] = "<b>";
    char str[20] = "<div class=\"rating\">";
    char str1[30] = "<div class=\"nameRus\"><a href=\"";
    int size = 20;
    FILE *f, *f1;
    f = fopen(name, "rt");
    f1 = fopen(name1, "wt");


    //////////////////////////////
    while (!feof(f))
    {
        /////FILM RATING
        c = fgetc(f);
        if(c == str[0])
        {
            i++;
            j++;
            while(i < size)
            {
                c = fgetc(f);
                if(c == str[i])
                {
                    j++;
                }
                else
                {
                    i = 0;
                    j = 0;
                    break;
                }
                i++;
            }
        }

        if(j == size)
        {
            c = getc(f);
            while(c != '>')
            {
                c = getc(f);
                //fprintf(stdout, "%c", c);
            }

            while(c != '<')
            {

                c = getc(f);
                if(c == '<')
                    break;

                fprintf(f1, "%c", c);
            }
                fprintf(f1, "\n");
        }
        //////FILM_RATING

        j = 0;
        i = 0;
    }
    //////////////////////////////

    //////////////////////////////





    fclose(f);
    fclose(f1);

    //parce_name(name, name1);

    f1 = fopen(name1, "rt+");
    while (!feof(f1)){
        c = fgetc(f1);
        fprintf(stdout, "%c", c);
    }
    fclose(f1);
    //menu(da, x);
    return 0;
}
/*/////FILM NAME
        c = fgetc(f);
        if(c == str[0])
        {
            i++;
            j++;
            while(i < size)
            {
                c = fgetc(f);
                if(c == str[i])
                {
                    j++;
                }
                else
                {
                    i = 0;
                    j = 0;
                    break;
                }
                i++;
            }
        }

        if(j == size)
        {
            while(c != '>')
                c = getc(f);

            while(c != '(')
            {

                c = getc(f);
                if(c == '&')
                    break;
                if(c == '(')
                    break;

                fprintf(f1, "%c", c);
            }
                fprintf(f1, "\n");
        }
        //////FILM_NAME

        j = 0;
        i = 0;*/

/*

void parce_rating()
{

}

void parce_name(char *parce_file_name, char * data_file)
{
    char str[30] = "<div class=\"nameRus\"><a href=\"";
    int size = 30;
    char c;
    int i = 0;
    int j = 0;

    FILE *f, *f1;
    f = fopen(parce_file_name, "rt");
    f1 = fopen(data_file, "at");
    while (!feof(f))
    {
        if (c == str[0]) {
            i++;
            j++;
            while (i < size) {
                c = fgetc(f);
                if (c == str[i]) {
                    j++;
                } else {
                    i = 0;
                    j = 0;
                    break;
                }
                i++;
            }
        }

    if (j == size) {
        while (c != '>')
            c = getc(f);

        while (c != '(') {

            c = getc(f);
            if (c == '&')
                break;
            if (c == '(')
                break;

            fprintf(f1, "%c", c);
        }
        fprintf(f1, "\n");
    }
    //////FILM_NAME

    j = 0;
    i = 0;
    }
    fclose(f);
    fclose(f1);
}

void parce_length()
{

}*/
