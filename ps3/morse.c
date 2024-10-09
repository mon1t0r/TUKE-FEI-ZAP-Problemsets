#include <string.h>

#define MORSE_CODE_SIZE 36
#define MORSE_CODE_NUMBER_OFFSET 26

const char* letter_to_morse(const char letter) {
    const char* morse_code[] = {
        ".-",   //a
        "-...", //b
        "-.-.", //c
        "-..",  //d
        ".",    //e
        "..-.", //f
        "--.",  //g
        "....", //h
        "..",   //i
        ".---", //j
        "-.-",  //k
        ".-..", //l
        "--",   //m
        "-.",   //n
        "---",  //o
        ".--.", //p
        "--.-", //q
        ".-.",  //r
        "...",  //s
        "-",    //t
        "..-",  //u
        "...-", //v
        ".--",  //w
        "-..-", //x
        "-.--", //y
        "--..", //z
        "-----", //0
        ".----", //1
        "..---", //2
        "...--", //3
        "....-", //4
        ".....", //5
        "-....", //6
        "--...", //7
        "---..", //8
        "----."  //9
    };

    int morse_index;

    if(letter >= 'A' && letter <= 'Z')
        morse_index = letter - 'A';
    else if(letter >= 'a' && letter <= 'z')
        morse_index = letter - 'a';
    else if(letter >= '0' && letter <= '9')
        morse_index = letter + MORSE_CODE_NUMBER_OFFSET - '0';
    else
        return NULL;

    return morse_code[morse_index];
}

char morse_to_letter(const char morse[], int start_index, int end_index) {
    const char* morse_code[] = {
        ".-",   //a
        "-...", //b
        "-.-.", //c
        "-..",  //d
        ".",    //e
        "..-.", //f
        "--.",  //g
        "....", //h
        "..",   //i
        ".---", //j
        "-.-",  //k
        ".-..", //l
        "--",   //m
        "-.",   //n
        "---",  //o
        ".--.", //p
        "--.-", //q
        ".-.",  //r
        "...",  //s
        "-",    //t
        "..-",  //u
        "...-", //v
        ".--",  //w
        "-..-", //x
        "-.--", //y
        "--..", //z
        "-----", //0
        ".----", //1
        "..---", //2
        "...--", //3
        "....-", //4
        ".....", //5
        "-....", //6
        "--...", //7
        "---..", //8
        "----."  //9
    };

    int flag;
    for(int i = 0; i < MORSE_CODE_SIZE; ++i) {
        if(strlen(morse_code[i]) != end_index - start_index)
            continue;

        flag = 1;
        for(int j = start_index; j < end_index; ++j) {
            if(morse_code[i][j - start_index] != morse[j]) {
                flag = 0;
                break;
            }
        }

        if(flag)
            return i < MORSE_CODE_NUMBER_OFFSET ? ('A' + i) : ('0' + i - MORSE_CODE_NUMBER_OFFSET);
    }
    
    return 0;
}

void text_to_morse(const char text[], char output[]) {
    int text_len = strlen(text);

    int output_index = 0;
    const char* morse;

    for(int i = 0; i < text_len; ++i) {
        morse = letter_to_morse(text[i]);
        if(morse == NULL)
            continue;

        strcpy(output + output_index, morse);

        output_index += strlen(morse) + 1;
        output[output_index - 1] = ' ';
        output[output_index] = 0;
    }

    output[output_index - 1] = 0;
}

void morse_to_text(const char morse[], char output[]) {
    int morse_len = strlen(morse);

    int output_index = 0;
    int morse_index = 0;
    char letter;

    for(int i = 0; i <= morse_len; ++i) {
        if(i < morse_len && morse[i] != ' ')
            continue;

        if(morse_index < i) {
            letter = morse_to_letter(morse, morse_index, i);
            if(!letter)
                continue;

            output[output_index] = letter;
            output[++output_index] = 0;
        }

        morse_index = i + 1;
    }
}

int is_morse_code_valid(const char morse[]) {
    int morse_len = strlen(morse);
    int morse_index = 0;

    for(int i = 0; i <= morse_len; ++i) {
        if(i < morse_len && morse[i] != ' ')
            continue;

        if(morse_index < i && !morse_to_letter(morse, morse_index, i))
            return 0;

        morse_index = i + 1;
    }

    return 1;
}