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

#define BUFFER_SIZE 1024

extern char **environ;

/* Function prototypes */
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
char *get_path(char *command);
int shell_exit(char **args);
int shell_env(char **args);

#endif
