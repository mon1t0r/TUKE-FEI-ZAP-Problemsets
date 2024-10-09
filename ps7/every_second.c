#include <stdio.h>
#include <stdbool.h>

#define WORD_START "START"
#define WORD_STOP "STOP"

#define WORD_BUFFER_LENGHT 5

bool strings_equal(const char *str1, int str1_lenght, const char *str2, int str2_lenght);

int main(int argc, char **argv) {
    if(argc < 3)
        return 1;

    FILE *file_source = fopen(argv[1], "r+");
    FILE *file_dest = fopen(argv[2], "w+");

    const char *word_start = WORD_START;
    const int word_start_len = sizeof(WORD_START) / sizeof(char) - 1;
    const char *word_stop = WORD_STOP;
    const int word_stop_len = sizeof(WORD_STOP) / sizeof(char) - 1;

    char word_buffer[WORD_BUFFER_LENGHT];
    int word_buffer_lenght = 0;

    bool is_processing = false;
    bool should_write_word = false;
    bool should_put_space = false;

    int c;
    while((c = fgetc(file_source)) != EOF) {
        if(c == ' ') {
            if(is_processing) {
                should_write_word = !should_write_word;
                if(strings_equal(word_buffer, word_buffer_lenght, word_stop, word_stop_len))
                    break;

                if(should_put_space)
                {
                    fputc(' ', file_dest);
                    should_put_space = false;
                }

                if(!should_write_word)
                    should_put_space = true;
            } else {
                is_processing = strings_equal(word_buffer, word_buffer_lenght, word_start, word_start_len);
            }
            
            word_buffer_lenght = 0;
            continue;
        }

        if(is_processing && should_write_word)
            fputc(c, file_dest);

        if(word_buffer_lenght < WORD_BUFFER_LENGHT)
            word_buffer[word_buffer_lenght++] = c;
    }

    fclose(file_source);
    fclose(file_dest);

    return 0;
}

bool strings_equal(const char *str1, int str1_lenght, const char *str2, int str2_lenght) {
    if(str1_lenght != str2_lenght)
        return false;

    for(int i = 0; i < str1_lenght; ++i)
        if(str1[i] != str2[i])
            return false;

    return true;
}