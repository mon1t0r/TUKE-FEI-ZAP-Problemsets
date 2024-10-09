#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "hangman.h"

#define MAX_WORD_SIZE 15
#define ALPHABET_SIZE 26

int get_word(char secret[]) {
    if(secret == NULL)
        return 1;

    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if(fp == NULL) {
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do {
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if(result != EOF)
            break;
    } while(true);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
    int secret_len = strlen(secret);
    int guessed_len = strlen(letters_guessed);

    int checked_count = 0;
    for(int i = 0; i < secret_len; ++i) {
        for(int j = 0; j < guessed_len; ++j) {
            if(secret[i] == letters_guessed[j]) {
                checked_count++;
                break;
            }
        }
    }

    return checked_count >= secret_len;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    strcpy(guessed_word, secret);
    
    int secret_len = strlen(secret);
    int guessed_len = strlen(letters_guessed);
    bool no_letter;

    for(int i = 0; i < secret_len; ++i) {
        no_letter = true;
        for(int j = 0; j < guessed_len; ++j) {
            if(secret[i] == letters_guessed[j]) {
                no_letter = false;
                break;
            }
        }

        if(no_letter)
            guessed_word[i] = '_';
    }
}

void get_available_letters(const char letters_guessed[], char available_letters[]) {
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    int guessed_len = strlen(letters_guessed);
    int filled_index = 0;
    bool no_letter;

    for(int i = 0; i < ALPHABET_SIZE; ++i) {
        no_letter = true;
        for(int j = 0; j < guessed_len; ++j) {
            if(alphabet[i] == letters_guessed[j]) {
                no_letter = false;
                break;
            }
        }

        if(no_letter)
            available_letters[filled_index++] = alphabet[i];
    }

    available_letters[filled_index] = 0;
}

bool str_contains(const char text[], const char symbol) {
    int len = strlen(text);

    for(int i = 0; i < len; ++i)
        if(text[i] == symbol)
            return true;
    
    return false;
}

bool str_equal(const char text1[], const char text2[], int text1_len, int text2_len) {
    if(text1_len != text2_len)
        return false;

    for(int i = 0; i < text1_len; ++i)
        if(text1[i] != text2[i])
            return false;
    
    return true;
}

void print_spaces(const char text[]) {
    int len = strlen(text);

    printf("%c", text[0]);

    for(int i = 1; i < len; ++i)
        printf(" %c", text[i]);
    
    printf("\n");
}

char get_user_input(char user_input[], int* input_count, int secret_len) {
    char letter = 0;
    *input_count = 0;

    while(true) {
        scanf("%c", &letter);
        if(!letter || letter == '\n' || *input_count >= secret_len)
            break;
        if (letter >= 'A' && letter <= 'Z')
            letter = letter - 'A' + 'a';
        user_input[(*input_count)++] = letter;
    }

    return user_input[*input_count - 1];
}

void hangman(const char secret[]) {
    int secret_len = strlen(secret);

    int guessed_count = 0;
    char letters_guessed[ALPHABET_SIZE + 1] = { 0 };
    char avaliable_letters[ALPHABET_SIZE + 1] = { 0 };

    char user_input[MAX_WORD_SIZE] = { 0 };
    char guessed_word[MAX_WORD_SIZE] = { 0 };

    int guesses = 8;
    char letter;
    int input_count;

    get_guessed_word(secret, letters_guessed, guessed_word);

    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n", secret_len);

    do {
        get_available_letters(letters_guessed, avaliable_letters);

        printf("-------------\n");
        printf("You have %d guesses left.\n", guesses);
        printf("Available letters: %s\n", avaliable_letters);
        printf("Please guess a letter: ");

        letter = get_user_input(user_input, &input_count, secret_len);

        if(letter < 'a' || letter > 'z') {
            printf("Oops! '%c' is not a valid letter: ", letter);
            print_spaces(guessed_word);
            continue;
        }

        if(input_count > 1) {
            if(str_equal(secret, user_input, secret_len, input_count))
                printf("Congratulations, you won!");
            else
                printf("Sorry, bad guess. The word was %s.", secret);
            break;
        }

        if(str_contains(letters_guessed, letter)) {
            printf("Oops! You've already guessed that letter: ");
            print_spaces(guessed_word);
            continue;
        }

        letters_guessed[guessed_count++] = letter;
        letters_guessed[guessed_count] = 0;

        get_guessed_word(secret, letters_guessed, guessed_word);

        if(str_contains(secret, letter)) {
            printf("Good guess: ");
            print_spaces(guessed_word);
            if(is_word_guessed(secret, letters_guessed)) {
                printf("-------------\n");
                printf("Congratulations, you won!");
                break;
            }
        } else {
            printf("Oops! That letter is not in my word: ");
            print_spaces(guessed_word);
            guesses--;
            if(guesses <= 0)
            {
                printf("-------------\n");
                printf("Sorry, you ran out of guesses. The word was %s.", secret);
                break;
            }
        }
    } while(guesses);

    printf("\n");
}