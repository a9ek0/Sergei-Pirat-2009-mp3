//
// Created by asduw on 06.03.2023.
//
#include "check.h"
void check_in_range(int *value, int left_boarder, int right_boarder)
{
    while (scanf_s("%d", value) == 0 || getchar() !='\n' || *value < left_boarder || *value > right_boarder)
    {
        printf("Wrong input");
        rewind(stdin);
    }
}

