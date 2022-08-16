#ifndef gameio
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

int k, l;

int arrowKey(void)
{
    int ch;
    fflush(stdin);
    ch = getch();
    if (ch == 0 || ch == 224)
        switch (getch())
        {
        case 72:
            return 1; // UP ARROW
        case 75:
            return 4; // LEFT ARROW
        case 77:
            return 2; // RIGHT ARROW
        case 80:
            return 3; // DOWN ARROW
        }
    else if (ch == 'e' || ch == 'E')
        return 101;
    return 0;
}

void setColor(char s[])
{
    if (0 == strcmp(s, "black"))
        printf("\033[0;30m");
    else if (0 == strcmp(s, "red"))
        printf("\033[0;31m");
    else if (0 == strcmp(s, "green"))
        printf("\033[0;32m");
    else if (0 == strcmp(s, "yellow"))
        printf("\033[0;33m");
    else if (0 == strcmp(s, "blue"))
        printf("\033[0;34m");
    else if (0 == strcmp(s, "purple"))
        printf("\033[0;35m");
    else if (0 == strcmp(s, "cyan"))
        printf("\033[0;36m");
    else if (0 == strcmp(s, "white"))
        printf("\033[0;37m");
    else
        printf("\033[0m");
}

void printStartingEndingLine(int size)
{
    if (size == 2)
        printf("+----+----+\n");
    else if (size == 3)
        printf("+--------------+\n");
    else if (size == 4)
        printf("+-------------------+\n");
    else if (size == 5)
        printf("+------------------------+\n");
    else if (size == 6)
        printf("+-----------------------------+\n");
    else if (size == 7)
        printf("+----------------------------------+\n");
}

void printCenterLine(int size)
{
    if (size == 2)
        printf("|----+----|\n");
    else if (size == 3)
        printf("|----+----+----|\n");
    else if (size == 4)
        printf("|----+----+----+----|\n");
    else if (size == 5)
        printf("|----+----+----+----+----|\n");
    else if (size == 6)
        printf("|----+----+----+----+----+----|\n");
    else if (size == 7)
        printf("|----+----+----+----+----+----+----|\n");
}

void printMatrix(int size, int Matrix[size][size])
{
    int i, j, c1, c2;
    printStartingEndingLine(size);
    for (i = 0, c1 = 1; i < size; i++, c1++)
    {
        for (j = 0, c2 = 1; j < size; j++, c2++)
        {
            if (Matrix[i][j] == size * size)
            {
                printf("|");
                setColor("yellow");
                printf("%3c ", 32);
                setColor("reset");
            }
            else
            {
                printf("|");
                setColor("yellow");
                printf("%3d ", Matrix[i][j]);
                setColor("reset");
            }
            if (c2 == size)
                printf("|\n");
        }
        if (c1 != size)
            printCenterLine(size);
    }
    printStartingEndingLine(size);
}

void makeMatrixZero(int size, int Matrix[size][size])
{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            Matrix[i][j] = 0;
}

int checkForRandomNumber(int size, int num, int Matrix[size][size])
{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (num == Matrix[i][j])
                return 0;
    return 1;
}

void findEmptyBox(int size, int Matrix[size][size])
{
    int i, j, temp, flag = 0;
    k = l = size - 1;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            if (Matrix[i][j] == (size * size))
            {
                temp = Matrix[i][j];
                Matrix[i][j] = Matrix[k][l];
                Matrix[k][l] = temp;
                // k = i;
                // l = j;
                // flag = 1;
                break;
            }
        if (flag)
            break;
    }
}

void generateRandomNumber(int size, int Matrix[size][size])
{
    srand(time(0));
    int lower = 1, upper = size * size, num = 0;
    int i, j;
    makeMatrixZero(size, Matrix);
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
        {
            while (1)
            {
                num = (rand() % (upper - lower + 1)) + lower;
                if (1 == checkForRandomNumber(size, num, Matrix))
                    break;
            }
            Matrix[i][j] = num;
        }
    findEmptyBox(size, Matrix);
}

int checkForWin(int size, int Matrix[size][size])
{
    int p = 1;
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
        {
            if (p != Matrix[i][j])
                return 0;
            p++;
        }
    return 1;
}

void moveNumbers(int size, int Matrix[size][size])
{
    int temp;
    int move = arrowKey();
    if (move == 101)
        exit(0);
    switch (move)
    {
    case 1:
        if (0 <= k + 1 && k + 1 < size)
        {
            temp = Matrix[k][l];
            Matrix[k][l] = Matrix[k + 1][l];
            Matrix[k + 1][l] = temp;
            k++;
        }
        else
            Beep(600, 300);
        break;
    case 2:
        if (0 <= l - 1 && l - 1 < size)
        {
            temp = Matrix[k][l];
            Matrix[k][l] = Matrix[k][l - 1];
            Matrix[k][l - 1] = temp;
            l--;
        }
        else
            Beep(600, 300);
        break;
    case 4:
        if (0 <= l + 1 && l + 1 < size)
        {
            temp = Matrix[k][l];
            Matrix[k][l] = Matrix[k][l + 1];
            Matrix[k][l + 1] = temp;
            l++;
        }
        else
            Beep(600, 300);
        break;
    case 3:
        if (0 <= k - 1 && k - 1 < size)
        {
            temp = Matrix[k][l];
            Matrix[k][l] = Matrix[k - 1][l];
            Matrix[k - 1][l] = temp;
            k--;
        }
        else
            Beep(600, 300);
        break;
    }
}

void ruleOfGame(void)
{
    system("cls");
    setColor("yellow");
    printf("\t\t\t# RULE OF THIS GAME #\n");
    setColor("white");
    printf("\n\n 1) You can move only 1 step at a time by arrow key.\n");
    setColor("cyan");
    printf("\tMove Up    : by UP arrow key\n");
    printf("\tMove Down  : by DOWN arrow key\n");
    printf("\tMove Left  : by LEFT arrow key\n");
    printf("\tMove Right : by RIGHT arrow key\n");
    setColor("white");
    printf("\n 2) You can move number at empty position only.\n");
    printf("\n 3) For each valid move, your total number of move will decreased by 1.\n");
    printf("\n 4) Wining situation, number in a 4x4 matrix should be in order from 1 to 15.\n");
    setColor("cyan");
    printf("\t+-------------------+\n");
    printf("\t|  1 |  2 |  3 |  4 |\n");
    printf("\t|----+----+----+----|\n");
    printf("\t|  5 |  6 |  7 |  8 |\n");
    printf("\t|----+----+----+----|\n");
    printf("\t|  9 | 10 | 11 | 12 |\n");
    printf("\t|----+----+----+----|\n");
    printf("\t| 13 | 14 | 15 |    |\n");
    printf("\t+-------------------+\n");
    setColor("white");
    printf("\n 5) You can exit the game at any time by pressing 'E' or 'e'.\n");
    setColor("purple");
    printf("\n\tEnter any key to start game...");
    setColor("reset");
    getch();
    fflush(stdin);
}

int setLevel(void)
{
    int level;
    system("cls");
    setColor("blue");
    printf("\n\nChoose Level:\n");
    setColor("white");
    printf("\t Press 1) for Easy 3x3\n");
    printf("\t Press 2) for Medium 4x4\n");
    printf("\t Press 3) for Hard 5x5\n");
    printf("\t Press 4) for Very Hard 6x6\n");
    setColor("reset");
    scanf("%d", &level);
    switch (level)
    {
    case 1:
        return 3;
    case 2:
        return 4;
    case 3:
        return 5;
    case 4:
        return 6;
    default:
        return 3;
    }
}

#define gameio
#endif