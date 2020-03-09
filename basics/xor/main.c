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


const char * buffer1_string = "1c0111001f010100061a024b53535009181c";
const char * buffer2_string = "686974207468652062756c6c277320657965";
const char * result_string = "746865206b696420646f6e277420706c6179";

unsigned int char2num(char c);
char * string2array(char * c);
char * xor_buffer(char * buffer1, char *buffer2, int buffer_len);
char hexnum2char(char num);
char * hexarray2string(char * array, int array_len);


int main(int args, char ** argv){
    printf("string1:\n%s\n", buffer1_string);
    printf("string2:\n%s\n", buffer2_string);
    printf("target:\n%s\n\n", result_string);

    char *buffer1 = string2array((char *)buffer1_string);
    char *buffer2 = string2array((char *)buffer2_string);
    char *target = string2array((char *)result_string);
    int buffer_len = strlen(buffer1_string);
    char *output = xor_buffer(buffer1, buffer2, buffer_len); 
    char *output_string = hexarray2string(output, buffer_len);
    printf("output:\n%s\n", output_string);
    int cmp_result = strcmp(result_string, output_string);
    if (cmp_result == 0){
        printf(" target == output\n");
    } else {
        printf(" target != output\n");
    }

    free(buffer1);
    free(buffer2);
    free(target);
    free(output);
    free(output_string);
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
