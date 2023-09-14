#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/my_string.h"
#include "../include/env_funcs.h"

void fill_null(char* p1, int size){
    for(int  i = 0; i < size; i++){
        p1[i] = '\0';
    }
}


int equal_check(char* string){
    for (int i=0; string[i]; i++){
        if (string[i] == '='){
            return i;
        }
    }
    return 0;
}


char* skip_spaces(char* string) {
    int length = strlen(string);
    int first_spaces = 1;
    int found = 0 ;
    int index = 0;

    char* result = calloc(length+1,sizeof(char));
    for (int i=0; i<length; i++){
        if (isspace(string[i])){
            if (!first_spaces && !found){
                found=1;
                result[index]=' ';
                index++;
            }
        }
        else{
            first_spaces=0;
            found=0;
            result[index]=string[i];
            index++;
        }
    }
    length = strlen(result);
    if (length){
        while(length>0 && isspace(result[length-1])){
            length--;
            result[length]='\0';
        }
    }

    return result;
}


char** string_val_get(char* line_) {
    char* line = skip_spaces(line_);
    if (!line){
        return NULL;
    }
    if (*line == '\0') {
        free(line);
        return NULL;
    }

    int count = 1;
    for (char* ch = line; *ch; ch++) {
        if (*ch == ' ') {
            count++;
        }
    }

    char** arr = (char**)malloc(sizeof(char*) * (count + 1));

    int index = 0;
    char* token = strtok(line, " ");
    while (token) {
        arr[index] = strdup(token);
        if (!arr[index]) {
            for (int i = 0; i < index; i++) {
                free(arr[i]);
            }
            free(arr);
            free(line);
            return NULL;
        }
        index++;
        token = strtok(NULL, " ");
    }
    
    arr[index] = NULL;
    free(line);
    return arr;
}


int read_line(char* buff){
    fflush(stdout);

    char c;
    int i = 0;
    int read_sum=0;
    while(read(0, &c, 1)){
        read_sum++;
        if(c == '\n'){
            return read_sum;
        }
        buff[i++] = c;
    }
    *buff = '\0';
    return read_sum;
}

void free_string_array(char** arr) {

    if(arr){
        for (int i = 0; arr[i] != NULL; i++) {
            free(arr[i]);
        }
    
        free(arr);
    }
}
