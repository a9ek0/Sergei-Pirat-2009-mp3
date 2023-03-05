//
// Created by asduw on 06.03.2023.
//

#include "parce.h"
void find_parce_str(const char *find_str, char ch, int *find_len, FILE *parce_file)
{

    if (ch == find_str[0]) {
        ch = (char)fgetc(parce_file);
        while (ch == find_str[*find_len])
        {
            (*find_len)++;
            ch = (char)fgetc(parce_file);
        }
    }
}

void parce(TV *structure)
{
    ///NAME --- class="" alt="Телевизор
    ///RESOLUTION --- Разрешение</td><td class='result__attr_val  cr-result__attr_odd'>
    ///SMART TV --- Smart TV</td><td class='result__attr_val '>
    ///HDMI --- Количество HDMI</td><td class='result__attr_val  cr-result__attr_odd'>
    ///PRICE --- data-price="
    FILE *f;
    fopen_s(&f, "parce.txt", "r");
    char c;
    char NAME[24] = "alt=\"Телевизор"; ///-
    char PRICE[13] = "data-price="; ///"
    char RESOLUTION[76] = "Разрешение</td><td class='result__attr_val  cr-result__attr_odd'"; ///<
    char HDMI[35] = ">Количество HDMI</td><td"; ///<
    char SMART_TV[44] = "Smart TV</td><td class='result__attr_val '>"; ///<
    int i = 1;
    int j = 0;
    int k;
////////////////////////////////////////NAME
    while(!feof(f)) {
        c = (char)fgetc(f);

        find_parce_str(NAME, c, &i, f);

        if(i == strlen(NAME))
        {
            k = 0;
            c = (char)fgetc(f);
            structure[j].name = (char*) malloc(10);
            while(c != '-')
            {
                structure[j].name = (char*) realloc(structure[j].name, k + 1);
                structure[j].name[k] = c;
                c = (char)fgetc(f);
                k++;
            }
            structure[j].name = (char*) realloc(structure[j].name, k + 1);
            structure[j].name[k] = '\0';
            j++;
        }

        i = 1;
    }
    j = 0;
    i = 1;
    fclose(f);
////////////////////////////////////////////HDMI
    fopen_s(&f, "parce.txt", "r");
    while(!feof(f)) {
        c = (char)fgetc(f);

        find_parce_str(HDMI, c, &i, f);

        if(i == strlen(HDMI))
        {
            structure[j].number_of_hdmi = 0;
            c = (char)fgetc(f);
            while((int)c > 57 || (int)c < 48)
            {
                c = (char)fgetc(f);
            }
            structure[j].number_of_hdmi = atoi(&c);
            j++;
        }

        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
//////////////////////////////////////////PRICE
    fopen_s(&f, "parce.txt", "r");
    while(!feof(f)) {
        c = (char)fgetc(f);

        find_parce_str(PRICE, c, &i, f);

        if(i == strlen(PRICE))
        {
            fscanf_s(f, "%f", &structure[j].price);
            j++;
        }

        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
///////////////////////////////////////////////////////////SMART TV
    fopen_s(&f, "parce.txt", "r");
    while(!feof(f)) {
        c = (char)fgetc(f);

        find_parce_str(SMART_TV, c, &i, f);

        c = (char)fgetc(f);
        c = (char)fgetc(f);
        if(i == strlen(SMART_TV))
        {
            switch ((int)c) {
                case -47:
                    structure[j].smart_TV = 1;
                    break;
                case -48:
                    structure[j].smart_TV = 0;
                    break;
                default:
                    continue;
            }
            j++;
        }

        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
////////////////////////////////////RESOLUTION
    fopen_s(&f, "parce.txt", "r");
    while(!feof(f)) {
        c = (char)fgetc(f);

        find_parce_str(RESOLUTION, c, &i, f);

        if(i == strlen(RESOLUTION))
        {
            fscanf_s(f, "%d", &structure[j].resolution.w);
            c = (char)fgetc(f);
            fscanf_s(f, "%d", &structure[j].resolution.h);
            j++;
        }

        i = 1;
    }
    fclose(f);
}