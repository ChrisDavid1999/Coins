#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/******************************
Name: Christopher Logan
Purpose: Takes a coins.txt input and records the data from it and allows the user to search and see what the most efficent coin return for that person is
Date: 26/02/2020 - 11/03/2020
*******************************/

typedef struct people
{
    char name[256];
    int change;
} people;

typedef struct peopleHold
{
    char name[256];
    int change;
    int coins[10];
    int coinCount[10];
} peopleHold;

int inputChoice()
{
    int choice;

    do
    {
        printf("Please enter an option\n1 to compare a name\n2 to exit the program\nENTER: ");
        scanf("%d", &choice);
        if(choice > 2 || choice < 1)
        {
            printf("ERROR! Invalid input, please enter a 1 or 2!\n");
        }
    }
    while(choice > 2 && choice < 1);

    return choice;
}

int compareStrings(char * name, char * search)
{
    int compare;

    compare = stricmp(name, search);

    return compare;
}

int countCoins(int coin, int change)
{
    int check = 0, count = 0;
    printf(count);

    while(check == 0)
    {
        if((change - coin) >= 0)
        {
            count++;
            change -= coin;
        }
        else
        {
            check = 1;
        }
    }

    return count;
}

void printInformation(char * name, int change, int *coins, int *coinCount, int count)
{
    int i;

    printf("Customer: \n");
    printf("%s %d cents\n\n", name, change);
    printf("Change: \n");

    for(i = 0; i < count; i++)
    {
        if(coinCount[i] >= 1)
        {
            printf("%d cents: %d\n", coins[i], coinCount[i]);
        }
    }

    printf("\n");
}

void writeToOutput(FILE *file, peopleHold * names, int count, int j)
{
    int i;

    fprintf(file, "%s,%d", names[j].name, names[j].change);
    printf("%s,%d", names[j].name, names[j].change);

    for(i = 0; i < count; i++)
    {
        fprintf(file, ",%d", names[j].coinCount[i]);
        printf(",%d", names[j].coinCount[i]);
    }

    fprintf(file, "\n");
    printf("\n");
}

int countLines(FILE *input, int SIZE)
{
    char name[256];
    int change;
    int count = 0;

    while(EOF != fscanf(input, "%s %d", name, &change))
    {
        count++;

        if(count == SIZE)
        {
            return count;
        }
    }

    return count;
}

void readFile(FILE *input, people * names, int z)
{
    int i, x = 0, change;
    char str[256];
    for(i = 0; i < z; i++)
    {
        fscanf(input, "%s %d", str, &change);
        strcpy(names[i].name, str);
        names[i].change = change;
    }
}

void transferInformation(char * name, int change, int *coins, int *coinCount, int count, char * name2, int *change2, int **coins2, int **coinCount2)
{
    int i;

    strcpy(name2, name);
    *change2 = change;

    for(i = 0; i < count; i++)
    {
        coins2[i] = coins[i];
        coinCount2[i] = coinCount[i];
    }
}

int getCoinTypesCounter(FILE *file, int SIZE)
{
    char str[256];
    int count;

    fscanf(file, "%s %d", str, &count);

    if(strcmp(str, "COINS") != 0 || file == NULL)
    {
        printf("Please put coins at the front of the coinTypes.txt file!");
        return -1;
    }

    if(count > SIZE)
    {
        count = SIZE;
    }
    return count;
}

void inputString(char *name)
{
    printf("Please enter a name to compare: ");
    scanf("%s", name);
}

int main()
{
    //Constants
    const int SIZE = 10;
    //Files
    FILE *input = fopen("coins.txt", "r");
    FILE *coinTypes = fopen("coinTypes.txt", "r");
    FILE *output = fopen("change.csv", "w");
    //Structs
    people names[SIZE];
    peopleHold namesHold[SIZE];
    //Ints
    int choice, i, comp, change, hold, count, holdChange, z, j = 0;
    int coins[SIZE];
    int coinCount[SIZE];
    //Strings
    char search[256];

    if(input == NULL || output == NULL)
    {
        printf("ERROR! Something has gone wrong, closing the program!");
    }

    z = countLines(input, SIZE);//Returns how many lines are in input unless there is more then 10, which then returns 10
    rewind(input);//Sends input back to the start of the file
    readFile(input, &names, z);//Places the information from the input file into the names array
    count = getCoinTypesCounter(coinTypes, SIZE);//Gets the count input from the coinTypes file, which is the first integer of the file

    if(count != -1)
    {
        for(i = 0; i < count; i++)
        {
            fscanf(coinTypes, "%d", &coins[i]);//Puts the value for coins into the coins array
        }
    }
    else//If there is the wrong file input or Null coinTypes file, it sets the coins to default values of 50, 20, 10, 5 and count to 4 to go with these numbers
    {
        count = 4;
        coins[0] = 50;
        coins[1] = 20;
        coins[2] = 10;
        coins[3] = 5;
    }

    fclose(input);
    fclose(coinTypes);

    do
    {
        choice = inputChoice();

        switch(choice)
        {
        case 1:
            for(i = 0; i < count; i++)
            {
                coinCount[i] = 0;
            }

            hold = -1;
            comp = 1;
            change = 0;
            inputString(&search);

            for(i = 0; i < z; i++)
            {
                comp = compareStrings(names[i].name, search);

                if(comp == 0)
                {
                    change += names[i].change;
                    hold = i;
                }
            }

            if(hold != -1)
            {
                holdChange = change;
                for(i = 0; i < count; i++)
                {
                    coinCount[i] = countCoins(coins[i], holdChange);

                    if(coinCount[i] > 0)
                    {
                        holdChange -= (coinCount[i] * coins[i]);
                    }
                }

                printInformation(names[hold].name, change, &coins, &coinCount, count);
                transferInformation(names[hold].name, change, &coins, &coinCount, count, &namesHold[j].name, &namesHold[j].change, &namesHold[j].coins, &namesHold[j].coinCount);

                for(i = 0; i < j; i++)
                {
                    if((compareStrings(names[i].name, namesHold[j].name)) == 0)
                    {
                        j--;
                        break;//If there is 2 of the same name, it will start taking more then one away
                    }
                }

                j++;
            }
            else
            {
                printf("Name: %s\nNot Found\n", search);
            }
            break;

        case 2:
            printf("You are exiting the program, thank you!");
            for(i = 0; i < j ; i++)
            {
                writeToOutput(output, &namesHold, count, i);
            }
            break;

        default:
            printf("ERROR! Something has gone wrong, closing the program!");
            return 0;
        }
    }
    while(choice != 2);
    fclose(output);

    return 0;
}
