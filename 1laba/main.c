#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() {
    int x = 0;
    int y = 10;
    char ch;

    while(1) {
        system("cls"); // очищаем экран

        // выводим персонажа на экран
        for(int i = 0; i < x; i++) {
            printf(" ");
        }
        printf("O\n");

        // обработка клавиш управления
        if(kbhit()) {
            ch = getch();
            if(ch == 'a') {
                x--;
            }
            if(ch == 'd') {
                x++;
            }
        }

        // задержка
        for(int i = 0; i < 100000000; i++);

        // движение персонажа вниз
        y++;
        if(y >= 20) {
            y = 10;
        }
    }

    return 0;
}
