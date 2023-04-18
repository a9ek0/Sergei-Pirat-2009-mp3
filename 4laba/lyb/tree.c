#include "tree.h"

void run_through_tree(NODE **root, FILE *log_file)
{
    NODE *tmp = *root;

    char answer[4];

    int expression = 0;

    while (expression != 1) {

        if(tmp != NULL && tmp->data != NULL && tmp->data->question == NULL)
        {
            printf("It's %s\n", tmp->data->answer);
            fprintf(log_file, "User get answer: %s.\n", tmp->data->answer);
            rebase_tree(&tmp, log_file);
            return;
        }

        if(tmp != NULL && tmp->data != NULL && tmp->data->question != NULL) {
            printf("%s\n", tmp->data->question);
            fflush(stdin);
            check_answer(answer);
            fprintf(log_file, "User get question: %s and answered: %s.\n", tmp->data->question, answer);
            expression = ask_question(&tmp, answer);
        }
    }

    printf("It's %s!\n", strcmp("Yes", answer) == 0 ? tmp->yes_branch->data->answer : tmp->no_branch->data->answer);
    fprintf(log_file, "User get answer: %s.\n", strcmp("Yes", answer) == 0 ? tmp->yes_branch->data->answer : tmp->no_branch->data->answer);
    rebase_tree(strcmp("Yes", answer) == 0 ? &tmp->yes_branch : &tmp->no_branch, log_file);
}

void print_tree(NODE *root, int depth) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    if (root->data->question != NULL) {
        printf("Question: %s\n", root->data->question);
    } else {
        printf("Answer: %s\n", root->data->answer);
    }

    print_tree(root->yes_branch, depth + 1);
    print_tree(root->no_branch, depth + 1);
}

void rebase_tree(NODE **node, FILE *log_file)
{
    char *answer;
    char *new_question;
    char *correct_answer;

    answer = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));

    printf("I'm right?\n");
    fflush(stdin);
    fgets(answer, MAX_LINE_LENGTH, stdin);
    get_input(answer, "Yes\n", "No\n");
    answer = realloc(answer, (strlen(answer) + 1) * sizeof (char));

    if (strcmp("Yes\n", answer) == 0)
    {
        fprintf(log_file, "Krutoi chel gave the correct answer\n");
        printf("Ura!!!\n");
    }
    else
    {
        new_question = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
        correct_answer = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
        fprintf(log_file, "Krutoi chel gave the wrong answer\n");
        printf("Who was that?\n");
        fflush(stdin);
        fgets(correct_answer, MAX_LINE_LENGTH, stdin);
        get_question_or_answer(correct_answer);
        correct_answer = realloc(correct_answer, (strlen(correct_answer) + 1) * sizeof (char));
        replace_char(correct_answer, '\n', '\0');
        fprintf(log_file, "The user said that the correct answer is :%s\n", correct_answer);

        printf("What is the difference?\n");
        fflush(stdin);
        fgets(new_question, MAX_LINE_LENGTH, stdin);
        get_question_or_answer(new_question);
        new_question = realloc(new_question, (strlen(new_question) + 1) * sizeof (char));
        replace_char(new_question, '\n', '\0');
        fprintf(log_file, "The user said that the difference is that :%s\n", new_question);
        add_extension(new_question, "?");

        DATA *yes_data = create_data(NULL , correct_answer);
        NODE *yes_node = create_node(yes_data);

        DATA *no_data = create_data(NULL , (*node)->data->answer);
        NODE *no_node = create_node(no_data);

        NODE* tmp = *node;
        tmp->yes_branch = yes_node;
        tmp->no_branch = no_node;

        tmp->data->question = malloc(strlen(new_question) + 1);
        strcpy(tmp->data->question, new_question );

        char *new_answer = malloc(strlen(tmp->data->answer) + 1);
        strcpy(new_answer, tmp->data->answer);
        tmp->data->answer = new_answer;
        free(new_question);
        free(correct_answer);
    }
    free(answer);
}

void tree_to_file(NODE *root, FILE *file, int depth)
{
    if (root == NULL) {
        return;
    }

    if (root->data->question != NULL) {
        fputs("Q ", file);
        fputs(root->data->question, file);
        fputs("\n", file);
    } else {
        fputs("A ", file);
        fputs(root->data->answer, file);
        fputs("\n", file);
    }

    tree_to_file(root->yes_branch, file, depth + 1);
    tree_to_file(root->no_branch, file, depth + 1);
}

void file_to_tree(NODE **root, FILE *file, int depth)
{
    char line[MAX_LINE_LENGTH];

    if (root == NULL || file == NULL) {
        return;
    }

    if(fgets(line, MAX_LINE_LENGTH, file) == NULL)
    {
        return;
    }

    replace_char(line, '\n', '\0');

    NODE *node = malloc(sizeof(NODE));
    node->data = malloc(sizeof(DATA));

    if (line[0] == 'Q') {
        DATA *data = node->data;
        data->question = strdup(line + 2);
        data->answer = NULL;
        node->yes_branch = NULL;
        node->no_branch = NULL;
        *root = node;
        file_to_tree(&((*root)->yes_branch), file, depth + 1);
        file_to_tree(&((*root)->no_branch), file, depth + 1);
    } else {
        DATA *data = node->data;
        data->answer = strdup(line + 2);
        data->question = NULL;
        node->yes_branch = NULL;
        node->no_branch = NULL;
        *root = node;
    }
}

void manual_tree_filling(NODE **root, FILE *log_file){
    char *choose;

    choose = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
    strcpy(choose, "Yes\n");

    while(strcmp(choose, "Yes\n") == 0) {
        //print_tree(*root, 0);
        run_through_tree(root, log_file);

        printf("Do you want to continue?\n");

        fflush(stdin);
        fgets(choose, MAX_LINE_LENGTH, stdin);

        get_input(choose, "Yes\n", "No\n");
        if(strcmp(choose, "Yes\n") == 0)
            fprintf(log_file, "The user continued the game.\n");
    }
    fprintf(log_file, "The user has finished the game.\n");
    free(choose);
}

char *choose_game()
{
    char *file_name;

    FILE *file;
    file = fopen("games/game_list/games_list.txt", "rt");
    if(file == NULL)
        return NULL;

    file_name = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));

    printf("Choose game.\n");
    while(fgets(file_name, MAX_LINE_LENGTH, file) != NULL)
    {
        printf("%s", file_name);
    }

    fflush(stdin);
    fgets(file_name, MAX_LINE_LENGTH, stdin);
    while(!is_in_file(file, file_name))
    {
        printf("Incorrect name!\n");
        fflush(stdin);
        fgets(file_name, MAX_LINE_LENGTH, stdin);
    }


    fclose(file);

    return file_name;
}

