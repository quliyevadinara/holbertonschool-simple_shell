#include "shell.h"

/**
 * execute - Execute a command
 * @args: Array of arguments
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
	pid_t pid;
	int status;
	char *command;

	if (strcmp(args[0], "exit") == 0)
		return (shell_exit(args));
	if (strcmp(args[0], "env") == 0)
		return (shell_env(args));

	command = get_path(args[0]);
	if (command == NULL)
	{
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("Error");
	else
	{
		waitpid(pid, &status, 0);
	}

	if (command != args[0])
		free(command);

	return (1);
}
