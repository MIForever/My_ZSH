#ifndef EXEC_FUNCS_H
#define EXEC_FUNCS_H

#include <sys/wait.h>
#include <linux/limits.h>

#include "env_funcs.h"

int is_executable(const char *filename);
int find_executable_path(char *executable_path, const char *command);
void executor(char **args, char **env);

#endif