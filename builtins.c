#include "shell.h"

/**
 * shell_exit - Exit the shell
 * @args: Array of arguments
 * Return: 0 to exit
 */
int shell_exit(char **args)
{
	(void)args;
	return (0);
}

/**
 * shell_env - Print environment variables
 * @args: Array of arguments
 * Return: 1 to continue
 */
int shell_env(char **args)
{
	int i = 0;

	(void)args;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}

	return (1);
}
