#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void encode_char(const char character, bool bits[8]) {
    for(int i = 0; i < 8; ++i)
        bits[7 - i] = (character >> i) & 1;
}

char decode_byte(const bool bits[8]) {
    char c = 0;
    for(int i = 0; i < 8; ++i)
        c = (c << 1) | bits[i];
    return c;
}

void encode_string(const char string[], bool bytes[strlen(string) + 1][8]) {
    int len = strlen(string) + 1;
    for(int i = 0; i < len; ++i)
        encode_char(string[i], bytes[i]);
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]) {
    for(int i = 0; i < rows; ++i)
        string[i] = decode_byte(bytes[i]);
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]) {
    for(int i = 0; i < cols; ++i)
        for(int j = 0; j < offset; ++j)
            for(int k = 0; k < 8; ++k) {
                blocks[j * 8 + k][i] = (j * cols + i < rows) ? bytes[j * cols + i][k] : 0;
            }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]) {
    for(int i = 0; i < cols; ++i)
        for(int j = 0; j < offset; ++j)
            for(int k = 0; k < 8; ++k) {
                if(j * cols + i < rows)
                    bytes[j * cols + i][k] = blocks[j * 8 + k][i];
            }
}

int main() {
    // bool bits1[8];
    // encode_char('A', bits1);
    // for(int i = 0; i < 8; i++){
    //     printf("%d", bits1[i]);
    // }
    // printf("\n");
    // // prints: 01000001

    // bool bits2[8] = {0,1,0,0,0,0,0,1};
    // printf("%c\n", decode_byte(bits2));
    // // prints: A

    // char* text = "Hello, how are you?";
    // const int len = strlen(text);
    // bool bytes1[len+1][8];
    // encode_string(text, bytes1);
    // for(int j = 0; j <= len; j++){
    //     printf("%c: ", text[j]);
    //     for(int i = 0; i < 8; i++){
    //         printf("%d", bytes1[j][i]);
    //     }
    //     printf("\n");
    // }
    // // prints:
    // // H: 01001000
    // // e: 01100101
    // // l: 01101100
    // // l: 01101100
    // // o: 01101111
    // // ,: 00101100
    // //  : 00100000
    // // h: 01101000
    // // o: 01101111
    // // w: 01110111
    // //  : 00100000
    // // a: 01100001
    // // r: 01110010
    // // e: 01100101
    // //  : 00100000
    // // y: 01111001
    // // o: 01101111
    // // u: 01110101
    // // ?: 00111111
    // // : 00000000

    // bool bytes2[7][8] = {
    //     {0,1,0,0,1,0,0,0},
    //     {0,1,1,0,0,1,0,1},
    //     {0,1,1,0,1,1,0,0},
    //     {0,1,1,0,1,1,0,0},
    //     {0,1,1,0,1,1,1,1},
    //     {0,0,1,0,0,0,0,1},
    //     {0,0,0,0,0,0,0,0}
    // };
    // char string[7];
    // decode_bytes(7, bytes2, string);
    // printf("%s\n", string);
    // // prints: Hello!

    // int length = 4+1, cols = 3, offset = 2;
    // bool bytes1[4+1][8] = {
    //     {0,1,0,0,0,0,0,1},
    //     {0,1,1,0,1,0,0,0},
    //     {0,1,1,0,1,1,1,1},
    //     {0,1,1,0,1,0,1,0},
    //     {0,0,0,0,0,0,0,0}
    // };
    // bool blocks1[offset*8][cols];
    // bytes_to_blocks(cols, offset, blocks1, length, bytes1);
    // for(int j = 0; j < offset*8; j++){
    //     for(int i = 0; i < cols; i++){
    //         printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
    //     }
    //     printf("\n");
    //     if(j % 8 == 7){
    //         printf("\n");
    //     }
    // }
    // // prints:
    // // 0 0 0 
    // // 1 1 1 
    // // 0 1 1 
    // // 0 0 0 
    // // 0 1 1 
    // // 0 0 1 
    // // 0 0 1 
    // // 1 0 1 
    // // 
    // // 0 0 0 
    // // 1 0 0 
    // // 1 0 0 
    // // 0 0 0 
    // // 1 0 0 
    // // 0 0 0 
    // // 1 0 0 
    // // 0 0 0

    // bool blocks2[2*8][3] = {
    //     {0,0,0},
    //     {1,1,1},
    //     {0,1,1},
    //     {0,0,0},
    //     {0,1,1},
    //     {0,0,1},
    //     {0,0,1},
    //     {1,0,1},
    //     {0,0,0},
    //     {1,0,0},
    //     {1,0,0},
    //     {0,0,0},
    //     {1,0,0},
    //     {0,0,0},
    //     {1,0,0},
    //     {0,0,0}
    // };
    // bool bytes2[length][8];
    // blocks_to_bytes(3, 2, blocks2, length, bytes2);
    // for(int j = 0; j < length; j++){
    //     for(int i = 0; i < 8; i++){
    //         printf("%d", bytes2[j][i]);
    //     }
    //     printf("\n");
    // }
    // // prints:
    // // 01000001
    // // 01101000
    // // 01101111
    // // 01101010
    // // 00000000

    return 0;
}