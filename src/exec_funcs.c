#include "../include/exec_funcs.h"

int is_executable(const char *filename) {
    if (access(filename, X_OK) == 0) {
        return 1;
    } else {
        return 0;
    }
}


int find_executable_path(char *executable_path, const char *command) {
    if (strchr(command, '/') != NULL) {
        if (realpath(command, executable_path) != NULL && is_executable(executable_path)) {
            return 1;
        }
        return 0;
    }

    const char *path_env = get_env_val("PATH");
    if (!path_env || !*path_env) {
        return 0;
    }

    char *dir_copy = strdup(path_env);
    char *dir = strtok(dir_copy, ":");
    while (dir != NULL) {
        snprintf(executable_path, PATH_MAX + 1, "%s/%s", dir, command);
        if (is_executable(executable_path)) {
            free(dir_copy);
            return 1;
        }
        dir = strtok(NULL, ":");
    }
    free(dir_copy);
    return 0;
}


void executor(char **args, char **env) {
    char executable_path[PATH_MAX + 1];

    if (find_executable_path(executable_path, args[0])) {
        pid_t pid;
        pid = fork();
        if (pid == 0) {
            fflush(stderr);
            if (execve(executable_path, args, env) == -1) {
                perror("my_zsh");
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFSIGNALED(status)) {
                int term_signal = WTERMSIG(status);
                if (term_signal == SIGSEGV) {
                    write(2, "segmentation fault\n", 19);
                }
            }
        }
    } else {
        printf("my_zsh: command not found: %s\n", args[0]);
    }
}