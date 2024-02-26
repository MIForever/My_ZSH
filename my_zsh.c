#include <sys/wait.h>
#include <linux/limits.h>

#include "./include/exec_funcs.h"

#define BUFFER_SIZE 100


void print_path(char* buff, char** last_dir){
    getcwd(buff, BUFFER_SIZE-1);
    if( *last_dir == NULL ){
        *last_dir = calloc(BUFFER_SIZE, sizeof(char));
        strcpy(*last_dir, buff);
    }
    printf("[%s]> ", buff);
    fill_null(buff, BUFFER_SIZE);
}

void redir_func(char** arr, char** env){
    if(strcmp(arr[0], "cd") == 0){
        chdir(arr[1]);
    }else{
        executor(arr,env);
    }
}


int stream_of_funcs(char** arr, char** env, char* last_dir){
    if( strcmp(arr[0], "echo") == 0 && arr[1][0] == '$'){
        printf("%s\n", get_env_val( &arr[1][1]));
    }
    else{
        if( strcmp(arr[0], "cd") == 0 ){
            if (arr[1]==NULL) return 0;
            if(strcmp(arr[1], "-") == 0){
                arr[1] = realloc(arr[1],strlen(last_dir)+1);
                strcpy(arr[1], last_dir);
            }
            memset(last_dir, '\0', BUFFER_SIZE);
            getcwd(last_dir, BUFFER_SIZE-1);
        }
        if ( strcmp(arr[0], "exit") == 0 || strcmp(arr[0], "quit") == 0) return 1;
        else if ( strcmp(arr[0], "env") == 0) p_env(env);
        else if ( strcmp(arr[0], "setenv") == 0) set_environment(arr);
        else if ( strcmp(arr[0], "unsetenv") == 0 && arr[1]) unsetenv(arr[1]);
        else redir_func(arr, env);
    }
    return 0;
}


int main(int argc, char** argv, char** env) {
    if (argc && argv) {}
    char* buff = calloc(BUFFER_SIZE,sizeof(char));
    char** arr = NULL;
    char* last_dir = NULL;
    while(1){
        print_path(buff, &last_dir);
        if (!read_line(buff)) break;
        arr = string_val_get(buff);
        if(arr == NULL) continue;
        if (stream_of_funcs(arr, env, last_dir)){free_string_array(arr); break;}
        fill_null(buff, BUFFER_SIZE);
        free_string_array(arr);
    }
    free(buff);
    free(last_dir);
    return 0;
}
