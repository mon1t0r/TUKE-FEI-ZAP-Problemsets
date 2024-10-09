#include <stdio.h>

#define WORD "ananas"
#define MAX_RESULT_DIGITS 10

int count_words(FILE *file);
void write_num(FILE *file, int num);
int to_lower(int c);

int main(int argc, char **argv) {
    if(argc < 2)
        return 1;

    FILE *file;
    
    file = fopen(argv[1], "r+");
    int words_count = count_words(file);
    fclose(file);

    file = fopen(argv[1], "w+");
    write_num(file, words_count);
    fclose(file);

    return 0;
}

int count_words(FILE *file) {
    const char *word = WORD;
    const int word_len = sizeof(WORD) / sizeof(char) - 1;

    int words_count = 0;
    int word_strike = 0;

    int c;
    while((c = to_lower(fgetc(file))) != EOF) {
        if(c != word[word_strike]) {
            word_strike = 0;
            continue;
        }

        word_strike++;

        if(word_strike >= word_len) {
            words_count++;
            word_strike = 0;
        }
    }

    return words_count;
}

void write_num(FILE *file, int num) {
    char digits[MAX_RESULT_DIGITS];
    int digits_count = 0;

    do {
        digits[digits_count++] = num % 10;
        num /= 10;
        if(digits_count >= MAX_RESULT_DIGITS)
            break;
    } while(num > 0);

    for(int i = digits_count - 1; i >= 0; --i)
        fputc('0' + digits[i], file);
}

int to_lower(int c)
{
    if(c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}