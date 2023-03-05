//
// Created by asduw on 06.03.2023.
//

#ifndef INC_1LABA_STRUCTURE_TV_H
#define INC_1LABA_STRUCTURE_TV_H

enum smart_tv{
    AVAILABLE,
    NOT_AVAILABLE
};

typedef struct{
    int w;
    int h;
}res;

typedef struct{
    char *name;
    res resolution;
    int number_of_hdmi;
    float price;
    enum smart_tv smart_TV;
}TV;

#endif //INC_1LABA_STRUCTURE_TV_H
