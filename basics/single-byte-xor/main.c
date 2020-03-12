/**
* @file main.c
* @Breif 
* @author Rock Deng
* @version 1.0
* @date 2020-03-12
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>



const char *hex_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
float english_freq[26] = {
0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,  // A-G
0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,  // H-N
0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,  // O-U
0.00978, 0.02360, 0.00150, 0.01974, 0.00074                     // V-Z
};
float rate_array [256][26] = {0};


unsigned int hexchar2hexnum(char c);
char * string2array(char * c);
char * xor_buffer(char * buffer1, char *buffer2, int buffer_len);
char hexnum2char(char num);
char * hexarray2string(char * array, int array_len);
int hexstring2hexarray(char *hexstring, char *hexarray);


int main(int args, char ** argv){

    ///< convert hex_string to hex array
    char * hex_array, decrypt_array;
    int hex_array_len;
    hex_array_len = hexarray2string(hex_string, hex_array);
    decrypt_array = malloc(sizeof(*decrypt_array) * hex_array_len);
    float rate = 0;
    int count = 0;
    
    ///< try key from 0x00 to 0xff
    for (int i=0; i<0xff; i++){
        ///< decrypt message
        for (int j=0; j<hex_array_len; j++){
            *(decrypt_array + j) = *(hex_array + j) ^ i;
        }
        ///< calculate rate of each letter in the message
        for (int k='a'; k<='z'; k++){
            for (int m=0; m<hex_array_len; m++){
                if (k == *(decrypt_array + m)){
                    count++;
                }
            }
            count = 0;
            rate = count / (float)hex_array_len;
            rate_array[i][k-'a'] = rate;
        }
    }
    ///< find the high score corresponding the character frequency in English plaintext.
    
    float score_array[256] = {0};
    for (int i=0; i<256; i++){
        for (int j=0; j<26; j++){
            abs_value = fabs(rate_array[i][j], english_freq[j]);
            kk = abs_value * abs_value / english_freq[j];
            score_array[i] += kk;

        }
    }

    ///< find the least score number
    float least_num = score_array[0];
    int key = 0;
    for (int i=0; i<256; i++){
        if (score_array[i] < least_num){
            least_num = score_array[i];
            key = i;
        }
    }


    printf("the key is 0x%x", key);
    free(hex_array);
    free(decrypt_array);

    return EXIT_SUCCESS;
}


int hexstring2hexarray(char *hexstring, char *hexarray){

    assert(hexstring != NULL);
    int str_len = strlen(hexstring);
    if (str_len % 2 == 1){
        array_len = str_len / 2 + 1;
    } else {
        array_len = str_len / 2;
    }
    hexarray = malloc(sizeof(*hexarray) * array_len);

    int j = 0;
    char result = 0;
    for (int i=0; i<str_len;){
        if (*(hexarray + i + 1) == '\0'){
            result = hexchar2hexnum(*(hexstring + i));
            break;
        } else {
            result = hexchar2hexnum(*(hexstring + i)) << 4 + hexchar2hexnum(*(hexarra + i + 1));

        }
        *(hexarray + j++) = result;
        i += 2;
    }

    return array_len;
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
        *(array + i) = (char)hexchar2hexnum(*(c + i));
    }

    printf("array:  ");
    for (int i=0; i<str_len; i++){
        printf("%x", *(array + i));
    }
    printf("\n\n");

    return array;
}



unsigned int hexchar2hexnum(char c){
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
