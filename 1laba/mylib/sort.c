//
// Created by asduw on 06.03.2023.
//

#include "sort.h"
void sort(TV *structure, int size, int sort_by) {
    TV temp;
    if(structure == NULL){
        printf("Struct uninitialized!\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++)
        {
            if (compare(&structure[j], &structure[j + 1], sort_by) < 0)
            {
                temp = structure[j];
                structure[j] = structure[j + 1];
                structure[j + 1] = temp;
            }
        }
    }
}

int compare(const TV *tv1,const TV *tv2, int sort_by) {
    int result = 0;
    switch(sort_by) {
        case 1:
            if(tv1->name == NULL || tv2->name == NULL)
                exit(EXIT_FAILURE);
            if (strcmp(tv1->name, tv2->name) > 0) {
                result = -1;
            }
            else if (strcmp(tv1->name, tv2->name) < 0) {
                result = 1;
            } else {
                result = 0;
            }
            break;
        case 2:
            if (tv1->resolution.w * tv1->resolution.h < tv2->resolution.w * tv2->resolution.h) {
                result = -1;
            } else if (tv1->resolution.w * tv1->resolution.h > tv2->resolution.w * tv2->resolution.h) {
                result = 1;
            } else {
                result = 0;
            }
            break;
        case 3:
            if (tv1->number_of_hdmi > tv2->number_of_hdmi) {
                result = 1;
            }
            else if (tv1->number_of_hdmi < tv2->number_of_hdmi) {
                result = -1;
            }else {
                result = 0;
            }
            break;
        case 4:
            if (tv1->price > tv2->price) {
                result = 1;
            }
            else if (tv1->price < tv2->price) {
                result = -1;
            }else {
                result = 0;
            }
            break;
        case 5:
            if (tv1->smart_TV > tv2->smart_TV) {
                result = 1;
            }
            else if (tv1->smart_TV < tv2->smart_TV) {
                result = -1;
            }else {
                result = 0;
            }
            break;
        default:
            break;
    }
    return result;
}

void d_sort(TV *tvs, int size, int field1, int field2) {
    TV temp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++)
        {
            if (compare(&tvs[j], &tvs[j + 1], field1) == 0 && compare(&tvs[j], &tvs[j + 1], field2) < 0)
            {
                temp = tvs[j];
                tvs[j] = tvs[j + 1];
                tvs[j + 1] = temp;
            }
        }
    }
}

void double_sort(TV *structure, int num_of_elements)
{
    int first;
    int second;
    printf("\nChoose sorting fields.\n 1.Sort by name.\n 2.Sort by resolution."
           "\n 3.Sort by number of hdmi\n 4.Sort by price\n 5.Sort by available of Smart TV\n");
    check_in_range(&first, 0, 5);
    check_in_range(&second, 0, 5);
    sort(structure, num_of_elements, first);
    d_sort(structure, num_of_elements, first, second);

}

void single_sort(TV *structure, int num_of_elements) {
    int first;
    printf("\nChoose sorting field.\n 1.Sort by name.\n 2.Sort by resolution."
           "\n 3.Sort by number of hdmi\n 4.Sort by price\n 5.Sort by available of Smart TV\n");
    check_in_range(&first, 1, 5);
    sort(structure, num_of_elements, first);
}