#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 50
#define MAX_TRIES 6

struct WordHint {
    char word[MAX_LEN];
    char hint[MAX_LEN];
};

void showWord(const char w[], const bool guessed[])
{
    printf("Word: ");
    for (int i = 0; w[i] != '\0'; i++) {
        if (guessed[w[i] - 'a']) {
            printf("%c ", w[i]);
        }
        else {
            printf("_ ");
        }
    }
    printf("\n");
}

void draw(int t)
{
    const char* hangman[] = {
        "     _________",
        "    |         |",
        "    |         O",
        "    |        /|\\",
        "    |        / \\",
        "    |"
    };

    printf("\n");
    for (int i = 0; i <= t; i++) {
        printf("%s\n", hangman[i]);
    }
}


int main()
{
    srand(time(NULL));
    struct WordHint words[] = {
        { "dsa" , "Important Coding Concept"},
        { "elephant", "A large mammal with a trunk" },
        { "pizza", "A popular Italian dish" },
        { "beach", "Sandy shore by the sea" },
    };

    int idx = rand() % 4;

    const char* secret = words[idx].word;
    const char* clue = words[idx].hint;

    int len = strlen(secret);
    char guessW[MAX_LEN] = { 0 };
    bool guessed[26] = { false };

    printf("Welcome to Hangman!\n");
    printf("Hint: %s\n", clue);

    int t = 0;

    while (t < MAX_TRIES) {
        printf("\n");
        showWord(guessW, guessed);
        draw(t);

        char g;
        printf("Enter a letter: ");
        scanf(" %c", &g);
        g = tolower(g);

        if (guessed[g - 'a']) {
            printf("You've already guessed that letter. Try again.\n");
            continue;
        }

        guessed[g - 'a'] = true;

        bool found = false;
        for (int i = 0; i < len; i++) {
            if (secret[i] == g) {
                found = true;
                guessW[i] = g;
            }
        }

        if (found) {
            printf("Good guess!\n");
        }
        else {
            printf("Sorry, the letter '%c' is not in the word.\n", g);
            t++;
        }

        if (strcmp(secret, guessW) == 0) {
            printf("\nCongratulations! You've guessed the word: %s\n", secret);
            break;
        }
    }

    if (t >= MAX_TRIES) {
        printf("\nSorry, you've run out of tries. The word was: %s\n", secret);
    }

    return 0;
}
