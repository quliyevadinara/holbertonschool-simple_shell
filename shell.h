#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* Function prototypes */
char *read_line(void);
char **parse_line(char *line);
int execute(char **args, char **env, int *last_status, 
            char *prog_name, int cmd_count);
char *get_path(char *command, char **env);
int shell_exit(char **args);
int shell_env(char **args, char **env);
char *build_full_path(char *dir, char *cmd);
char *find_in_path(char *path_env, char *command);
void print_error(char *prog_name, int cmd_count, char *command);

#endif
