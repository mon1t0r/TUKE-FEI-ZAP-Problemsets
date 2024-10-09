#include <stdio.h>
#include <string.h>
#include "hangman.h"
#include "morse.h"

int main() {
    char output[150];
    text_to_morse("Hello0123", output);
    puts(output);
    //prints: .... . .-.. .-.. ---

    morse_to_text(".--. .-. ..- -. ... -.... --... .-. .-. -.-- ", output);
    puts(output);
    //prints: HELLO

    if(is_morse_code_valid(".-- .... .- -.-- - .... ..-")) {
        printf("Code is valid! \n");
    } else {
        printf("Code is invalid! \n");
    }
    //prints: Code is valid!

    //....
    if(is_morse_code_valid(".... . .-.--. .-.. ---")) {
        printf("Code is valid! \n");
    } else {
        printf("Code is invalid! \n");
    }
    //prints: Code is invalid!

    char secret[15];
    if(!get_word(secret))
        hangman(secret);
}