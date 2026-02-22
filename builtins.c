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
 * @env: Environment variables
 * Return: 1 to continue
 */
int shell_env(char **args, char **env)
{
	int i = 0;

	(void)args;

	while (env[i])
	{
		write(STDOUT_FILENO, env[i], strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}

	return (1);
}
