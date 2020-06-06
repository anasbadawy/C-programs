#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct hand
{
    int index;
    char secret[20];
    char guess_list[20][10];
    int attempt_count;
    int result;
};

void generate_secret(char *secret, int count)
{
    int i;
    char val;
    srand(time(0));

    for (i = 0; i < count; i++)
    {

        int exist = 0;
        do
        {
            exist = 0;
            val = (rand() % 10) + '0';
            for (int j = 0; j < i; j++)
            {
                if (val == secret[j])
                {
                    exist = 1;
                }
            }

        } while (exist == 1);
        secret[i] = val;
    }
    secret[i] = '\0';
    printf("\nOk i have chosen a number.\n");
    printf("The Number is = %s\n", secret);
}

void validate_guess(char guess[], int count)
{
    int valid = 0;

    while (!valid)
    {
        printf("What is your guess: ");
        scanf("%s", guess);

        if (strcmp(guess, "quit") == 0)
        {
            return;
        }
        valid = 1;
        if (strlen(guess) != count)
        {
            printf("Guess must have length of %d, try again.\n", count);
            valid = 0;
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                if (guess[i] < '0' || guess[i] > '9')
                {
                    printf("Contains non-numbers, try again.\n");
                    valid = 0;
                    break;
                }
            }
        }
    }
}

void evaluate_guess(char *secret, char guess[], int count, int *cows, int *bulls)
{

    int found = 0;
    for (int i = 0; i < count; i++) // for calculating bulls
    {
        if (guess[i] == secret[i])
        {
            (*bulls)++;
        }
    }

    for (int i = 0; i < count; i++) // for calculating all
    {
        for (int j = 0; j < count; j++)
        {
            if (secret[i] == guess[j])
            {
                found++;
            }
        }
    }
    *cows = found - *bulls; // for calculating cows
}

void save_file(struct hand game[], int length) // function for saving game data into txt file
{
    FILE *file;
    file = fopen("history.txt", "w"); // creating history.txt file
    for (int i = 0; i <= length; i++)
    {
        fprintf(file, "%d %s ", game[i].index, game[i].secret); // writing indexs and secrets of game  
        for (int j = 0; j < game[i].attempt_count; j++)
        {
            fprintf(file, "%s ", game[i].guess_list[j]);// writing guess list of the game 
        }
        fprintf(file, "%d %d\n", game[i].attempt_count, game[i].result); // writing game attempts count and result
    }
    fclose(file); // closing file
}

int main(void)
{

    struct hand game[20];
    int handCount = 0;
    int attempt = 0;
    char guess[20];
    int bulls;
    int cows;
    int digitCount;
    int MAX = 5;
    int startGame = 1;
    char *secret;
    char choices[5];

    while (startGame == 1)
    {
        bulls = 0;
        cows = 0;

        printf("\n***Welcome to Bulls & Cows Game***\n");

        printf("Enter the digit count that you desire: ");
        scanf("%d", &digitCount);

        secret = (char *)malloc(digitCount * sizeof(char));
        generate_secret(secret, digitCount);

        game[handCount].index = handCount + 1;
        strcpy(game[handCount].secret, secret);
        int stopGame = 0;
        while (stopGame == 0)
        {
            attempt++;
            validate_guess(guess, digitCount);
            strcpy(game[handCount].guess_list[attempt - 1], guess);

            if (strcmp(guess, "quit") == 0) // strcmp =>> string compare
            {
                printf("You lose!\n");
                game[handCount].result = 0;
                stopGame = 1;
            }
            else
            {
                evaluate_guess(secret, guess, digitCount, &cows, &bulls);
                if (bulls == digitCount)
                {
                    printf("You win!\n");
                    game[handCount].result = 1;
                    stopGame = 1;
                }
                else
                {

                    if (attempt == MAX)
                    {
                        printf("You lose!\n");
                        game[handCount].result = 0;
                        stopGame = 1;
                    }
                    else
                    {
                        printf("Bulls:%d Cows:%d\n", bulls, cows);
                        bulls = 0;
                        cows = 0;
                    }
                }
            }
        }
        game[handCount].attempt_count = attempt;

        printf("Do you want to play one more time (yes/no): ");
        scanf("%s", choices);

        if (strcmp(choices, "yes") == 0)
        {
            handCount++;
            attempt = 0;
        }
        else
        {
            startGame = 0;
        }
    }
    save_file(game, handCount);
    free(secret);
    return -1;
}