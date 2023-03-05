#ifndef INC_1LABA_STRUCTURE_H
#define INC_1LABA_STRUCTURE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "structure_TV.h"
#include "check.h"
/*▀▄▀▄▀▄▀▄▀▄[̲̲̅̅т̲̲̅̅а̲̲̅̅к̲̲̅̅с̲̲̅̅и̲̲̅̅с̲̲̅̅т̲̲̅̅]▄▀▄▀▄▀▄▀▄▀*/
/*٩(✿∂‿∂✿)۶(░S░I░m░P░o░T░я░Ж░к░@░)ヾ(o✪‿✪o)ｼ*/
/*[̲̅0̲̅][̲̅0̲̅][̲̅7̲̅]░J░a░m░e░s░ ░B░o░n░d░(⌐■_■)--︻╦╤─ - - -*/


//////STRUCTURE
void create_struct_arr(TV **structure, int *size);
void initiate_struct(TV *structure, int size);
void print_struct(TV *structure, int size);
void dell_struct(TV **structure, int *size);
void remove_tv(TV **structure, int index, int *size);

#endif //INC_1LABA_STRUCTURE_H
