#include "memory.h"
void free_memory(TV *structure, int size) {
    if(structure == NULL)
        return;
    for (int i = 0; i < size; i++) {
        if (structure[i].name == NULL)
            return;
        else
            free(structure[i].name);
    }
    free(structure);
}