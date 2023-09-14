#ifndef MY_STRING_H
#define MY_STRING_H

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

void fill_null(char* p1, int size);
int equal_check(char* string);
char* skip_spaces(char* string);
char** string_val_get(char* line);
int read_line(char* buff);
void free_string_array(char** arr);

#endif