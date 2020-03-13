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
int hexstring2hexarray(char *hexstring, char **hexarray);
int calc_letter_freq(char * string, int str_len, int * result);
int cmp_float(const void * p1, const void * p2);


int main(int args, char ** argv){

    ///< convert hex_string to hex array
    char * hex_array = NULL;
    char * decrypt_array = NULL;
    int letter_freq[26] = {0};
    int hex_array_len;
    float score_array[256] = {0};
    hex_array_len = hexstring2hexarray((char *)hex_string, &hex_array);
    decrypt_array = malloc(sizeof(char) * hex_array_len);
    float rate = 0;
    int count = 0;
    printf("hexstring:  %s\n", hex_string);
    printf("hexarray:   ");
    for (int i=0; i<hex_array_len; i++){
        printf("%x", *(hex_array + i));
    }
    printf("\n");
    ///< try key from 0x00 to 0xff
    for (int i=0; i<256; i++){
        ///< decrypt message
        printf("try key=0x%x:\n", i);
        for (int j=0; j<hex_array_len; j++){
            *(decrypt_array + j) = *(hex_array + j) ^ i;
            printf("%c", *(decrypt_array + j));
        }
        printf("\n");

        ///< calculate rate of each letter in the message
        for (int n=0; n<26; n++){
            letter_freq[n] = 0;
        }
        int sum_letter = calc_letter_freq(decrypt_array, hex_array_len, letter_freq);
//        for (int m=0; m<26; m++){
//            printf("%c%d", 'a' + m, *(letter_freq + m));
//        }
//        printf("\n");
//        printf("sum of letters: %d\n", sum_letter);
        for (int k=0; k<26; k++){
            if (sum_letter == 0){
                score_array[i] = -1;
                break;
            } else {
                rate_array[i][k] = (float)letter_freq[k] / sum_letter;
            }
//            printf("%2.5f ", rate_array[i][k]);
        }
        printf("\n\n");
    }

    ///< find the high score corresponding the character frequency in English plaintext.
    float diff;
    float kk;
    for (int i=0; i<256; i++){
        if (score_array[i] == -1){
            continue;
        } else{
            score_array[i] = 0;
            for (int j=0; j<26; j++){
                diff = rate_array[i][j] - english_freq[j];
                kk = diff * diff / english_freq[j];
                score_array[i] += kk;
//                printf("%c: diff=%f; freq=%f; kk=%f; score=%f\n", j+'a', diff, english_freq[j], kk, score_array[i]);
            }
        }
        printf("i=%d; score=%f;  \n", i, score_array[i]);
    }

    ///< find the least score number
    int key = 0;
#if 0
    qsort(score_array, 256, sizeof(float), cmp_float);
    printf("sorted score array: \n");
    for (int i=0; i<256; i++){
        printf("%f  ", score_array[i]);
    }
    printf("\n");
    for (int i=0; i<256; i++){
        if (score_array[i] != -1){
            key = i;
        }
    }
#endif
    float score_least = 1000000;
    for (int i=0; i<256; i++){
        if (score_array[i] != -1){
            if (score_array[i] < score_least){
                score_least = score_array[i];
                key = i;
            }
        }
    }
    

    printf("\nthe key is 0x%x\n", key);
    printf("the decrypt_array is:\n");
    for (int j=0; j<hex_array_len; j++){
        *(decrypt_array + j) = *(hex_array + j) ^ key;
        printf("%c", *(decrypt_array + j));
    }
    printf("\n");
    
//    free(hex_array);
//    free(decrypt_array);

    return EXIT_SUCCESS;
}


int hexstring2hexarray(char *hexstring, char **hexarray){

    assert(hexstring != NULL);
    int array_len = 0;
    int str_len = strlen(hexstring);
    if (str_len % 2 == 1){
        array_len = str_len / 2 + 1;
    } else {
        array_len = str_len / 2;
    }
    *hexarray = malloc(sizeof(char) * array_len);

    int j = 0;
    char result = 0;
    for (int i=0; i<str_len;){
        if (*(hexstring + i + 1) == '\0'){
            result = (char)hexchar2hexnum(*(hexstring + i));
            break;
        } else {
            result = (char)hexchar2hexnum(*(hexstring + i)) * 16 + (char)hexchar2hexnum(*(hexstring + i + 1));

        }
        *(*hexarray + j++) = result;
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


int calc_letter_freq(char * string, int str_len, int * result){
    int sum_chars = 0;
    char c = 0;
    for (int i=0; i<str_len; i++){
        if (*(string + i) >= 'a' && *(string + i) <= 'z'){
            sum_chars++;
            c = *(string + i);
            (*(result + c - 'a'))++;
        }else if (*(string + i) >= 'A' && *(string + i) <= 'Z'){
            sum_chars++;
            c = *(string + i);
            (*(result + c - 'A'))++;
            
        }
    }
            
    return sum_chars;
}

int cmp_float(const void * p1, const void * p2){
    float a = *((float *)p1);
    float b = *((float *)p2);
    if(a > b){
        return 1;
    } else if (a < b){
        return -1;
    } else {
        return 0;
    }

}
