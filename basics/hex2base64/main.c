


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



const char * hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
const char * base64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
const char * base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";



char * hex2base64(char *hex, int char_num);

int main(int argc, char ** argv){

//    while(*hex != '\0'){
//    }
    
    int num_o, num_t;

    printf("Original hex string:\n%s\n", hex);
    printf("Target base64 string:\n%s\n\n", base64);
    num_o = strlen(hex);
    num_t = strlen(base64);
    printf("Number of characters in original: %d\n", num_o);
    printf("Number of characters in target: %d\n", num_t);
    //char output[num_t+1] = "";
    char * output;
    output = hex2base64((char *)hex, num_o);
    printf("Converted string is %s", output);


    free(output);
    return EXIT_SUCCESS;
}

unsigned int char2num(char c){
    assert((c <= '9' && c >= 0) || (c <= 'f' && c >= 'a'));
    unsigned int n;
    if (c > '9'){
        n = 10 + c - 'a';
    } else{
        n = c - '0';
    }
    return n;
}

void printf_binary(int num){
    while(num){
        if (num & 1){
            printf("1");
        } else {
            printf("0");
        }
        num >>= 1;
    }
}


char* hex2base64(char *hex, int char_num){
    assert(char_num > 0);
    int x = char_num % 3;
    if (x != 0){
        printf("munber of char is not 3x\n");
    } else {

    }
    printf("hex2base64 hex:\n");
    printf("%s\n", hex);
    int num_base64 = char_num / 3 * 2;
    char *out = malloc(sizeof(char) * (num_base64 + 1));
    *(out + num_base64) = '\0';
    unsigned int base_char = 0;
    unsigned int num = 0;
    char low_letter, high_letter;
    printf(" char_num=%d\n", char_num);
    for (int i=0; i<char_num/3; i++){
        printf(" i = %d; letters: 0x0%c%c%c\n", i, *hex, *(hex+1), *(hex+2));
        unsigned int base = 0;
        num = 0;
        for (int j=0; j<3; j++){
            num <<= 4;
            num |= char2num(*(hex++));
            printf("num=0x%02x\n", num);
        }
        printf(" binary form: ");
        printf_binary(num);
        printf("\n");
        printf(" base64 indexes: %2d %2d\n", num >> 6, num & 0x3f);
        low_letter = base64_table[num & 0x3f];
        high_letter = base64_table[num >> 6];
        *(out++) = high_letter;
        *(out++) = low_letter;
    }
    printf("exit hex2base64\n");

    return out;
}






