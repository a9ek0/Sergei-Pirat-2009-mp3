#include "structure.h"

void menu(TV *structure, int size)
{
    int index = 0;
    int k = 0;
    while(1)
    {
        printf("٩(✿∂‿∂✿)۶(░S░I░m░P░o░T░я░Ж░к░@░)ヾ(o✪‿✪o)ｼ*");
        printf("\n1.Initiate structure array.\n"
               "2.Enter structure array.\n"
               "3.Double sort structure.\n"
               "4.Print structures.\n"
               "5.Delete structure from array.\n"
               "6.Parce.\n"
               "7.Single sort structure.\n"
               "8.Obama.\n"
               "9.Exit.\n");
        fflush(stdin);
        scanf_s("%d", &index);
        switch (index)
        {
            case 1:
                create_struct_arr(&structure, &size);
                k = 1;
                break;
            case 2:
                if(k < 1 )
                {
                    printf("You didn't create an array.\n");
                    break;
                }
                initiate_struct(structure, size);
                k = 2;
                break;
            case 3:
                if(k < 2)
                {
                    printf("You didn't fill/create an array.\n");
                    break;
                }
                double_sort(structure, size);
                break;
            case 4:
                if(k < 2)
                {
                    printf("You didn't fill/create an array.\n");
                    break;
                }
                printf("%d", size);
                print_struct(structure, size);
                break;
            case 5:
            {
                if(k < 2)
                {
                    printf("You didn't fill/create an array.\n");
                    break;
                }
                dell_struct(&structure, &size);
                break;
            }
            case 6:
                if(k == 3)
                {
                    printf("You already parced file! \n");
                    break;
                }
                structure = (TV*) calloc(62, sizeof (TV));
                if(structure == NULL)
                    break;
                parce(structure);
                k = 3;
                size = 61;
                break;
            case 7:
                if(k < 2)
                {
                    printf("You didn't fill/create an array.\n");
                    break;
                }
                single_sort(structure, size);
                break;
            case 8:
                printf("\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠛⠛⠛⠉⠉⠉⠋⠛⠛⠛⠻⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠛⠉⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠉⠙⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠏⠄⠄⠄⠄⠄⠄⠄⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠹⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠘⢻⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⠄⢠⠄⠄⡀⠄⠄⢀⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄⡁⠄⠄⢛⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠐⡈⢔⠸⣐⢕⢕⢵⢰⢱⢰⢐⢤⡡⡢⣕⢄⢢⢠⠄⠄⠄⠄⠄⠄⠙⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡁⠂⠅⢕⠌⡎⡎⣎⢎⢮⢮⣳⡳⣝⢮⢺⢜⢕⢕⢍⢎⠪⡐⠄⠁⠄⠸⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⠏⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠐⠄⠄⢅⠣⡡⡣⣣⡳⡵⣝⡮⣗⣗⡯⣗⣟⡮⡮⣳⣣⣳⢱⢱⠱⣐⠄⠂⠄⢿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⠄⠄⠄⠂⠄⠄⠄⠄⠄⠄⢂⢈⠢⡱⡱⡝⣮⣿⣟⣿⣽⣷⣿⣯⣿⣷⣿⣿⣿⣾⣯⣗⡕⡇⡇⠄⠂⡀⢹⣿\n"
                       "⣿⣿⣿⣿⣿⡟⠄⠄⠄⠄⠄⠄⠂⠄⠄⠄⠄⠄⠄⠐⢀⢂⢕⢸⢨⢪⢳⡫⣟⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡺⡮⡣⡣⠠⢂⠒⢸⣿\n"
                       "⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⠐⠄⡂⠆⡇⣗⣝⢮⢾⣻⣞⣿⣿⣿⣿⣿⣿⣿⣿⢿⣽⣯⡯⣺⢸⢘⠨⠔⡅⢨⣿\n"
                       "⣿⣿⠋⠉⠙⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠁⠄⠄⠄⡂⡪⡪⡪⡮⡮⡯⣻⣽⣾⣿⣿⣿⣟⣿⣿⣿⣽⣿⣿⡯⣯⡺⡸⡰⡱⢐⡅⣼⣿\n"
                       "⣿⠡⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⠈⠆⠱⠑⠝⠜⠕⡝⡝⣞⢯⢿⣿⣿⡿⣟⣿⣿⣿⡿⡿⣽⣷⣽⡸⡨⡪⣂⠊⣿⣿\n"
                       "⣿⠡⠄⡨⣢⠐⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠐⠍⡓⣗⡽⣝⠽⠍⠅⠑⠁⠉⠘⠘⠘⠵⡑⢜⢀⢀⢉⢽\n"
                       "⣿⠁⠠⢱⢘⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠈⠱⣁⠜⡘⠌⠄⠄⡪⣳⣟⡮⢅⠤⠠⠄⠄⣀⣀⡀⡀⠄⠈⡂⢲⡪⡠⣿\n"
                       "⣿⡇⠨⣺⢐⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡀⠄⠄⠄⠤⡠⡢⢒⠦⠠⠄⠄⠄⡸⢽⣟⢮⠢⡂⡐⠄⡈⡀⠤⡀⠄⠑⢄⠨⢸⡺⣐⣿\n"
                       "⣿⣿⠈⠕⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡂⡪⡐⡥⢤⣰⣰⣰⡴⡮⠢⠂⠄⠄⡊⢮⢺⢕⢵⢥⡬⣌⣒⡚⣔⢚⢌⢨⢚⠌⣾⡪⣾⣿\n"
                       "⣿⣿⣆⠄⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⡑⢕⢕⡯⡷⣕⢧⢓⢭⠨⡀⠄⡂⠨⡨⣪⡳⣝⢝⡽⣻⣻⣞⢽⣲⢳⢱⢡⠱⠨⣟⢺⣿⣿\n"
                       "⣿⣿⣿⡆⠄⡅⠇⡄⠄⠄⠄⠄⠄⠄⠄⠐⠨⢪⢹⢽⢽⣺⢝⠉⠁⠁⠄⠄⠄⢌⢎⡖⡯⡎⡗⢝⠜⣶⣯⣻⢮⡻⣟⣳⡕⠅⣷⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣶⣶⣿⣷⠄⠄⠄⠄⠄⠄⠄⠄⠈⠔⡑⠕⠝⠄⡀⠄⠄⠊⢆⠂⠨⡪⣺⣮⣿⡾⡜⣜⡜⣄⠙⢞⣿⢿⡿⣗⢝⢸⣾⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⠄⡀⠄⠄⠄⠄⢀⠄⠠⠄⠠⠄⠄⠄⠄⠄⠄⠊⠺⡹⠳⡙⡜⡓⡭⡺⡀⠄⠣⡻⡹⡸⠨⣣⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⠄⠠⠄⠄⣂⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢄⠤⡤⡄⡆⡯⡢⡣⡣⡓⢕⠽⣄⠄⠨⡂⢌⣼⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⡆⠄⠄⠄⠄⠈⠆⠄⠸⡂⠄⠄⠄⢀⠄⢀⠈⠄⠂⠁⠙⠝⠼⠭⠣⠣⠣⠑⠌⠢⠣⡣⡠⡘⣰⣱⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⢑⠄⠈⡱⠄⢘⠄⡀⠨⢐⣧⣳⣷⣶⣦⣤⣴⣶⣶⣶⡶⠄⡠⡢⡕⣜⠎⡮⣣⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠄⠄⠢⠄⠨⠄⠄⠣⡀⠄⢀⢀⢙⠃⡿⢿⠿⡿⡿⢟⢋⢔⡱⣝⢜⡜⡪⡪⣵⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⡁⠄⠄⠄⠄⠄⠄⠄⠅⠄⠡⠄⠄⠡⢀⢂⠢⡡⠡⠣⡑⣏⢯⡻⡳⣹⡺⡪⢎⠎⡆⢣⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣇⠄⠄⠄⠄⠄⠄⠄⠐⠄⠄⠁⠄⢈⠄⢂⠕⡕⡝⢕⢎⢎⢮⢎⢯⢺⢸⢬⠣⢃⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠠⠨⡐⠌⢆⢇⢧⢭⣣⡳⣵⢫⣳⢱⠱⢑⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣆⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠁⡊⢌⢢⢡⢣⢪⡺⡪⡎⡎⡎⡚⣨⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠕⡅⢗⢕⡳⡭⣳⢕⠕⡱⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠌⠄⠑⠩⢈⢂⣱⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⡀⢄⠄⣀⠄⡀⣀⢠⢄⣖⣖⣞⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣱⡐⡕⡕⡽⣝⣟⣮⣾⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
                       "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣵⣽⣸⣃⣧⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
                break;
            case 9:
                free_memory(structure, size);
                exit(EXIT_SUCCESS);
            default:
                printf("Wrong input!");
                break;
        }
    }
}


void dell_struct(TV **structure, int *size)
{
    if (structure == NULL || *structure == NULL) {
        printf("Structure doesn't exist!");
        return;
    }
    int dell;
    int index = *size;
    printf("\nChoose TV that you want to delete.\n");
    for (int k = 0; k < index; k++)
    {
        printf("%d: %s\n", k, (*structure)[k].name);
    }
    check_in_range(&dell, 0, index - 1);
    remove_tv(structure, dell, size);
}

void remove_tv(TV **structure, int index, int *size) {
    if (index < 0 || index >= *size) {
        printf("Error: index is out of bounds.\n");
        return;
    }
    free((*structure)[index].name);
    for (int i = index; i < *size - 1; i++) {
        (*structure)[i] = (*structure)[i + 1];
    }
    *size -= 1;
    if(*size == 0){
        free(*structure);
        *structure = NULL;
    }
    else {
        TV *new_tvs = (TV *) realloc(*structure, *size * sizeof(TV));
        if (new_tvs == NULL) {
            printf("Error: memory reallocation failed.\n");
            return;
        }
        *structure = new_tvs;
    }
}

void create_struct_arr(TV **structure, int *size) {
    printf("Enter number of structures in array.\n");
    scanf_s("%d", size);
    if(*structure != NULL){
        free(*structure);
    }
    *structure = (TV *) malloc(*size * sizeof(TV));
    if (*structure == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}


void initiate_struct(TV *structure, int size)
{
    char buffer[255];
    for (int i = 0; i < size; ++i)
    {
        printf("\nEnter Name\n");
        scanf_s("%s", buffer);
        structure[i].name = (char *) calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(structure[i].name, buffer);
        fflush(stdin);
        printf("\nEnter width of screen\n");
        scanf_s("%d", &structure[i].resolution.w);
        printf("\nEnter height of screen\n");
        scanf_s("%d", &structure[i].resolution.h);
        printf("\nEnter number of hdmi ports\n");
        scanf_s("%d", &structure[i].number_of_hdmi);
        printf("\nEnter price\n");
        scanf_s("%f", &structure[i].price);
        printf("\nDoes the TV have smart tv\n0 - No\n1 - Yes");
        scanf_s("%d", &structure[i].smart_TV);
    }
}

void print_name(TV *structure, int size)
{
    for (int i = 0; i < size; ++i)
    {
        rewind(stdout);
        printf("%d : %s\n", i, structure[i].name);
    }
}

void print_struct(TV *structure, int size)
{
    for (int i = 0; i < size; ++i)
    {
        rewind(stdout);
        printf("\nName is: %s", structure[i].name);
        printf("\nResolution is: %d x %d", structure[i].resolution.w, structure[i].resolution.h);
        printf("\nNumber of hdmi ports is: %d", structure[i].number_of_hdmi);
        printf("\nPrice is: %1.2f", structure[i].price);
        if(structure[i].smart_TV == 1 )
            printf("\nSmart TV allowed.\n");
        else
            printf("\nSmart TV not allowed.\n");
    }
}

void check_in_range(int *value, int left_boarder, int right_boarder)
{
    while (scanf_s("%d", value) == 0 || getchar() !='\n' || *value < left_boarder || *value > right_boarder)
    {
        printf("Wrong input");
        rewind(stdin);
    }
}

void single_sort(TV *structure, int num_of_elements) {
    int first;
    printf("\nChoose sorting field.\n 1.Sort by name.\n 2.Sort by resolution."
           "\n 3.Sort by number of hdmi\n 4.Sort by price\n 5.Sort by available of Smart TV\n");
    check_in_range(&first, 1, 5);
    sort(structure, num_of_elements, first);
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

void parce(TV *structure)
{
    ///NAME --- class="" alt="Телевизор
    ///RESOLUTION --- Разрешение</td><td class='result__attr_val  cr-result__attr_odd'>
    ///SMART TV --- Smart TV</td><td class='result__attr_val '>
    ///HDMI --- Количество HDMI</td><td class='result__attr_val  cr-result__attr_odd'>
    ///PRICE --- data-price="
    FILE *f;
    if ((f = fopen("parce.txt", "r")) == NULL)
    {
        printf("Открыть файл не удалось\n");
        exit(1);
    }
    char c;
    char NAME[24] = "alt=\"Телевизор"; ///-
    char PRICE[13] = "data-price="; ///"
    char RESOLUTION[76] = "Разрешение</td><td class='result__attr_val  cr-result__attr_odd'"; ///<
    char HDMI[35] = ">Количество HDMI</td><td"; ///<
    char SMART_TV[44] = "Smart TV</td><td class='result__attr_val '>"; ///<
    int i = 1;
    int j = 0;
    int k = 0;
////////////////////////////////////////NAME
    while(!feof(f)) {
        c = (char)fgetc(f);


        if (c == NAME[0]) {
            c = (char)fgetc(f);
            while (c == NAME[i])
            {
                i++;
                c = (char)fgetc(f);
            }
        }

        if(i == strlen(NAME))
        {
            k = 0;
            c = (char)fgetc(f);
            structure[j].name = (char*) malloc(1);
            while(c != '-')
            {
                structure[j].name = (char*) realloc(structure[j].name, (k + 1));
                structure[j].name[k] = c;
                c = (char)fgetc(f);
                k++;
            }
            structure[j].name[k] = '\0';
        }
        else
        {
            i = 1;
            continue;
        }


        j++;
        i = 1;
    }
    j = 0;
    i = 1;
    fclose(f);
////////////////////////////////////////////HDMI
    f = fopen("parce.txt", "r");
    while(!feof(f)) {
        c = (char)fgetc(f);


        if (c == HDMI[0]) {
            c = (char)fgetc(f);
            while (c == HDMI[i])
            {
                i++;
                c = (char)fgetc(f);
            }
        }


        if(i == strlen(HDMI))
        {
            structure[j].number_of_hdmi = 0;
            c = (char)fgetc(f);
            while((int)c > 57 || (int)c < 48)
            {
                c = (char)fgetc(f);
            }
            structure[j].number_of_hdmi = atoi(&c);
        }
        else
        {
            i = 1;
            continue;
        }


        j++;
        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
//////////////////////////////////////////PRICE
    f = fopen("parce.txt", "r");
    while(!feof(f)) {
        c = (char)fgetc(f);

        if (c == PRICE[0]) {
            c = (char)fgetc(f);
            while (c == PRICE[i])
            {
                i++;
                c = (char)fgetc(f);
            }
        }


        if(i == strlen(PRICE))
        {
            fscanf(f, "%f", &structure[j].price);
        }
        else
        {
            i = 1;
            continue;
        }


        j++;
        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
///////////////////////////////////////////////////////////SMART TV
    f = fopen("parce.txt", "r");
    while(!feof(f)) {
        c = (char)fgetc(f);

        if (c == SMART_TV[0]) {
            c = (char)fgetc(f);
            while (c == SMART_TV[i])
            {
                i++;
                c = (char)fgetc(f);
            }
            c = (char)fgetc(f);
            c = (char)fgetc(f);
        }

        if(i == strlen(SMART_TV))
        {
            if((int)c == -47)
                structure[j].smart_TV = 1;
            if((int)c == -48)
                structure[j].smart_TV = 0;
        }
        else
        {
            i = 1;
            continue;
        }


        j++;
        i = 1;
    }
    fclose(f);
    j = 0;
    i = 1;
////////////////////////////////////RESOLUTION
    f = fopen("parce.txt", "r");
    while(!feof(f)) {
        c = (char)fgetc(f);

        if (c == RESOLUTION[0]) {
            c = (char)fgetc(f);
            while (c == RESOLUTION[i])
            {
                i++;
                c = (char)fgetc(f);
            }
        }

        if(i == strlen(RESOLUTION))
        {
            fscanf(f, "%d", &structure[j].resolution.w);
            c = (char)fgetc(f);
            fscanf(f, "%d", &structure[j].resolution.h);
        }
        else
        {
            i = 1;
            continue;
        }
        j++;
        i = 1;
    }
    fclose(f);
}


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

int compare(const TV *tv1,const TV *tv2, int sort_by) {
    int result = 0;
    switch(sort_by) {
        case 1:
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
//////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////
int compare_name(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    return strcmp(tv1->name, tv2->name);
}

int compare_resolution(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->resolution.w < tv2->resolution.w) {
        return -1;
    } else if (tv1->resolution.w > tv2->resolution.w) {
        return 1;
    } else if (tv1->resolution.h < tv2->resolution.h) {
        return -1;
    } else if (tv1->resolution.h > tv2->resolution.h) {
        return 1;
    } else {
        return 0;
    }
}

int compare_number_of_hdmi(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->number_of_hdmi < tv2->number_of_hdmi) {
        return -1;
    } else if (tv1->number_of_hdmi > tv2->number_of_hdmi) {
        return 1;
    } else {
        return 0;
    }
}

int compare_price(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->price < tv2->price) {
        return -1;
    } else if (tv1->price > tv2->price) {
        return 1;
    } else {
        return 0;
    }
}

int compare_smart_TV(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->smart_TV < tv2->smart_TV) {
        return -1;
    } else if (tv1->smart_TV > tv2->smart_TV) {
        return 1;
    } else {
        return 0;
    }
}
/////////////////////////////////////////////////////////////////////
int compare_by_name_res(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->name < tv2->name) {
        return -1;
    } else if (tv1->name > tv2->name) {
        return 1;
    } else {
        if (tv1->resolution.w < tv2->resolution.w) {
            return -1;
        } else if (tv1->resolution.w > tv2->resolution.w) {
            return 1;
        } else if (tv1->resolution.h < tv2->resolution.h) {
            return -1;
        } else if (tv1->resolution.h > tv2->resolution.h) {
            return 1;
        } else {
            return 0;
        }
    }
}

int compare_by_name_hdmi(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->name < tv2->name) {
        return -1;
    } else if (tv1->name > tv2->name) {
        return 1;
    } else {
        if (tv1->number_of_hdmi < tv2->number_of_hdmi) {
            return -1;
        } else if (tv1->number_of_hdmi > tv2->number_of_hdmi) {
            return 1;
        } else {
            return 0;
        }
    }
}

int compare_by_name_price(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->name < tv2->name) {
        return -1;
    } else if (tv1->name > tv2->name) {
        return 1;
    } else {
        if (tv1->price < tv2->price) {
            return -1;
        } else if (tv1->price > tv2->price) {
            return 1;
        } else {
            return 0;
        }
    }
}

int compare_by_name_smart_tv(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->name < tv2->name) {
        return -1;
    } else if (tv1->name > tv2->name) {
        return 1;
    } else {
        if (tv1->smart_TV < tv2->smart_TV) {
            return -1;
        } else if (tv1->smart_TV > tv2->smart_TV) {
            return 1;
        } else {
            return 0;
        }
    }
}

int compare_by_price_smart_tv(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->price < tv2->price) {
        return -1;
    } else if (tv1->price > tv2->price) {
        return 1;
    } else {
        if (tv1->smart_TV < tv2->smart_TV) {
            return -1;
        } else if (tv1->smart_TV > tv2->smart_TV) {
            return 1;
        } else {
            return 0;
        }
    }
}

int compare_by_hdmi_smart_tv(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->number_of_hdmi < tv2->number_of_hdmi) {
        return -1;
    } else if (tv1->number_of_hdmi > tv2->number_of_hdmi) {
        return 1;
    } else {
        if (tv1->smart_TV < tv2->smart_TV) {
            return -1;
        } else if (tv1->smart_TV > tv2->smart_TV) {
            return 1;
        } else {
            return 0;
        }
    }
}

int compare_by_hdmi_price(const void *p1, const void *p2) {
    const TV *tv1 = p1;
    const TV *tv2 = p2;
    if (tv1->number_of_hdmi < tv2->number_of_hdmi) {
        return -1;
    } else if (tv1->number_of_hdmi > tv2->number_of_hdmi) {
        return 1;
    } else {
        if (tv1->price < tv2->price) {
            return -1;
        } else if (tv1->price > tv2->price) {
            return 1;
        } else {
            return 0;
        }
    }
}

