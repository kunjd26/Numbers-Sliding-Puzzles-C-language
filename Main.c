#include "gameio.h"

int main(void)
{
    char name[20], ch;
    int size, totalMoves, remain, checkWin = 0;
    int Matrix[6][6];
    printf("Input Your Name: ");
    fflush(stdin);
    fgets(name, 20, stdin);
    name[strlen(name) - 1] = '\0';
    ruleOfGame();
    while (1)
    {
        size = setLevel();
        remain = totalMoves = 50 * size;
        generateRandomNumber(size, Matrix);
        system("cls");
        do
        {
            system("cls");
            printMatrix(size, Matrix);
            if (remain <= totalMoves / 2)
            {
                setColor("red");
                printf("\n\tRemaining Moves: %d\n", remain--);
                setColor("reset");
            }
            else
            {
                setColor("green");
                printf("\n\tRemaining Moves: %d\n", remain--);
                setColor("reset");
            }
            moveNumbers(size, Matrix);
            checkWin = checkForWin(size, Matrix);
        } while (checkWin == 0 && remain != 0);
        if (checkWin == 1)
        {
            system("cls");
            printMatrix(size, Matrix);
            setColor("green");
            printf("\n\n\t %s You WIN This Game!\n", name);
            printf("\t :)");
            setColor("reset");
        }
        else
        {
            system("cls");
            printMatrix(size, Matrix);
            setColor("red");
            printf("\n\n\t %s You LOSS This Game!\n", name);
            printf("\t :(");
            setColor("reset");
        }
        printf("\n\n\nFor Play Game Again, Press ('Y' or 'y')");
        printf("\nOR NOT, Press Any Key: ");
        setColor("yellow");
        fflush(stdin);
        scanf("%c", &ch);
        setColor("reset");
        if (!(ch == 'Y' || ch == 'y'))
            exit(0);
    }
    return 0;
}