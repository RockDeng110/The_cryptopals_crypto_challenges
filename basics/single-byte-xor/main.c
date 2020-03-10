/**
* @file main.c
* @Breif 
* @author Rock Deng
* @version 1.0
* @date 2020-03-09
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



unsigned int char2num(char c);
char * string2array(char * c);
char * xor_buffer(char * buffer1, char *buffer2, int buffer_len);
char hexnum2char(char num);
char * hexarray2string(char * array, int array_len);


int main(int args, char ** argv){


    return EXIT_SUCCESS;
}

char * xor_buffer(char * buffer1, char *buffer2, int buffer_len){
    assert(buffer1 != NULL && buffer2 != NULL);
    assert(buffer_len > 0);
    
    printf("xor_buffer:\n");
    printf("buffer1:\n");
    for (int i=0; i<buffer_len; i++){
        printf("%3d", *(buffer1 + i));
    }
    printf("\n");
    printf("buffer2:\n");
    for (int i=0; i<buffer_len; i++){
        printf("%3d", *(buffer2 + i));
    } 
    printf("\n");
    char * output = malloc(sizeof(*output) * buffer_len);
    char * return_value = output;
    for (int i=0; i<buffer_len; i++){
        *output++ = *buffer1++ ^ *buffer2++;
    }

    return return_value;
}

char * hexarray2string(char * array, int array_len){
    if (array == NULL){
        return NULL;
    }
    
    printf("hexarray2string, array as below:\n");
    for (int i=0; i<array_len; i++){
        printf("%x", *(array + i));
    }
    printf("\n");
    int i = 8;
    char * string = malloc(sizeof(*string) * (array_len + 1));
    *(string + array_len) = '\0';
    for (int i=0; i<array_len; i++){
        *(string + i) = hexnum2char(*(array + i));
    }

    return string;
}

char * string2array(char * c){
    if (c == NULL){
        
        return NULL;
    }

    printf("string2array:\n");
    printf("string: %s\n", c);
    int str_len = strlen(c);
    if (str_len <= 0){
        return NULL;
    }
    char * array = malloc(sizeof(*array) * str_len);
    for (int i=0; i<str_len; i++){
        *(array + i) = (char)char2num(*(c + i));
    }

    printf("array:  ");
    for (int i=0; i<str_len; i++){
        printf("%x", *(array + i));
    }
    printf("\n\n");

    return array;
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

char hexnum2char(char num){
    assert(num < 16);
    char c;
    if (num <= 9){
        c = num - 0 + '0';
    } else {
        c = num - 10 + 'a';
    }
    return c;
}
