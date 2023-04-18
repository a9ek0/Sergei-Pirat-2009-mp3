#ifndef INC_4LABA_TREE_SRUCUTRE_H
#define INC_4LABA_TREE_SRUCUTRE_H
typedef struct {
    char *question;
    char *answer;
} DATA;

typedef struct Node {
    DATA *data;
    struct Node *yes_branch;
    struct Node *no_branch;
} NODE;
#endif //INC_4LABA_TREE_SRUCUTRE_H
