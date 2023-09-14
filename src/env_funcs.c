#include "../include/env_funcs.h"

void set_environment(char** args){
    if (!args[1])
        printf("Invalid syntax!");

    char* key = args[1];
    int index;
    
    if ((index = equal_check(key))){

        key[index]=0;
        if (!key[index+1])
            setenv(args[1], args[2], 1);
        else
            setenv(args[1], &key[index+1], 1);
        return;
    }

    if (!args[0])
        printf("Invalid syntax!");
    else if (args[2][0]=='=')
        setenv(args[1], args[3], 1);
    else
        setenv(args[1], args[2], 1);
}


char* get_env_val(char* key){
    char* env_val = getenv(key);
    if(env_val != NULL){
        return env_val;
    }
    return "not found";
}


void p_env(char** env){
    int i=0;
    while(env[i]){
        printf("%s\n", env[i]);
        i++;
    }
}
