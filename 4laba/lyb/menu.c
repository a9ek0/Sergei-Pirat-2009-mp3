#include "menu.h"

void menu(NODE **root)
{
////выбор режим
    char *log_name;
    log_name = get_current_time();
    log_name = add_extension(log_name, ".txt");
    add_word_to_beginning(log_name, "logs/");
    FILE *log_file;
    log_file = fopen(log_name, "wt");

    if(log_file == NULL)
    {
        return;
    }

    char *choose;
    choose = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
    printf("Do you want to start new game or continue?(New/Continue)\n");
    fgets(choose, MAX_LINE_LENGTH, stdin);
    choose = realloc(choose, (strlen(choose) + 1) * sizeof (char));

    get_input(choose, "New\n", "Continue\n");
///если новая игра
    if(strcmp("New\n", choose) == 0){
        fputs("User start new game\n", log_file);
        DATA *data;
        char *root_word;
        root_word = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));

        printf("Let's start with the first word!\n");

        fflush(stdin);
        fgets(root_word, MAX_LINE_LENGTH, stdin);
        get_question_or_answer(root_word);
        root_word = realloc(root_word, (strlen(root_word) + 1) * sizeof (char));
        replace_char(root_word, '\n', '\0');

        data = create_data(NULL, root_word);
        *root = create_node(data);

        manual_tree_filling(root, log_file);
        print_tree(*root, 0);

        printf("Do you want to save this game?\n");
        fflush(stdin);
        fgets(choose, MAX_LINE_LENGTH, stdin);

        get_input(choose, "Yes\n", "No\n");

        if(strcmp(choose, "No\n") == 0)
        {
            fprintf(log_file, "The user has not saved the game.\n");
            exit(EXIT_SUCCESS);
        }else {
            FILE *file;
            char *game_name;

            file = fopen("games/game_list/games_list.txt", "r+t");
            if(file == NULL) {
                fclose(log_file);
                return;
            }

            game_name = (char*) malloc(MAX_LINE_LENGTH * sizeof (char));
            printf("Enter name of the game.\n");
            fflush(stdin);
            fgets(game_name, MAX_LINE_LENGTH, stdin);

            while(is_in_file(file , game_name) || strcmp(game_name, "\n\0") == 0)
            {
                printf("Unacceptable name or a game with that name already exists!\n");
                fflush(stdin);
                fgets(game_name, MAX_LINE_LENGTH, stdin);
            }

            fseek(file, 0, SEEK_END);
            fputs(game_name, file);

            fclose(file);

            replace_char(game_name, '\n', '\0');
            fprintf(log_file, "The user saved the game under the name: %s.\n", game_name);
            game_name = add_extension(game_name, ".txt");
            add_word_to_beginning(game_name, "games/");
            file = fopen(game_name, "wt");

            if(file == NULL)
            {
                fclose(log_file);
                free(game_name);
                return;
            }

            tree_to_file(*root, file, 0);
            fclose(file);
            free(game_name);
        }
//////здесь выбор уже существующей игры
    } else if(strcmp("Continue\n", choose) == 0){
        char *game_name;
        char *buff_game_name;
        game_name = choose_game();
        replace_char(game_name, '\n', '\0');
        fprintf(log_file, "User continued game %s.\n", game_name);
        buff_game_name = (char*) malloc((strlen(game_name) + 1) * sizeof (char));
        strcpy(buff_game_name, game_name);
        game_name = add_extension(game_name, ".txt");
        add_word_to_beginning(game_name, "games/");

        FILE *file;
        file = fopen(game_name, "rt");
        if(file == NULL){
            fclose(log_file);
            free(buff_game_name);
            free(game_name);
            return;
        }
        file_to_tree(root, file, 0);

        manual_tree_filling(root, log_file);

        fclose(file);
        printf("Do you want to save this game?\n");
        fflush(stdin);
        fgets(choose, MAX_LINE_LENGTH, stdin);

        get_input(choose, "Yes\n", "No\n");

        if(strcmp(choose, "No\n") == 0)
        {
            fprintf(log_file, "The user has not saved the game.\n");
            exit(EXIT_SUCCESS);
        }else{
            file = fopen(game_name, "wt");
            if (file == NULL)
            {
                fclose(log_file);
                free(buff_game_name);
                free(game_name);
                return;
            }
            tree_to_file(*root, file, 0);
            fclose(file);
        }
        fprintf(log_file, "The user saved the game under the name: %s.\n", buff_game_name);
        free(buff_game_name);
        free(game_name);
    }
    fclose(log_file);
}
