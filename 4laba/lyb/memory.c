#include "memory.h"

void free_tree(NODE *root) {
    if (root->yes_branch != NULL) {
        free_tree(root->yes_branch);
    }
    if (root->no_branch != NULL) {
        free_tree(root->no_branch);
    }
    free_data(root->data);
    free(root);
}

void free_data(DATA *data) {
    if (data->question != NULL) {
        free(data->question);
    }
    if (data->answer != NULL) {
        free(data->answer);
    }
    free(data);
}

DATA *create_data(const char *question, const char *answer)
{
    DATA *data = malloc(sizeof(DATA));
    if (!data) {
        return NULL;
    }
    data->question = NULL;
    data->answer = NULL;

    if (question) {
        data->question = malloc(strlen(question) + 1);
        if (!data->question) {
            free(data);
            return NULL;
        }
        strcpy(data->question, question);
    }

    if (answer) {
        data->answer = malloc(strlen(answer) + 1);
        if (!data->answer) {
            free(data->question);
            free(data);
            return NULL;
        }
        strcpy(data->answer, answer);
    }

    return data;
}

NODE *create_node(DATA *data) {
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->data = data;
    node->yes_branch = NULL;
    node->no_branch = NULL;
    return node;
}

void add_node(NODE *parent, NODE *node, char direction) {
    if (direction == 'Y') {
        parent->yes_branch = node;
    } else {
        parent->no_branch = node;
    }
}
