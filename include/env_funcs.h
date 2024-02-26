#ifndef ENV_FUNCS_H
#define ENV_FUNCS_H

#include "my_string.h"

void set_environment(char** args);
char* get_env_val(char* key);
void p_env(char** env);

#endif