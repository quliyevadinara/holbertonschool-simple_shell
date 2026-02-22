#include "shell.h"

/**
 * print_error - Print error message
 * @prog_name: Program name
 * @cmd_count: Command counter
 * @command: Command that was not found
 */
void print_error(char *prog_name, int cmd_count, char *command)
{
	char count_str[20];

	write(STDERR_FILENO, prog_name, strlen(prog_name));
	write(STDERR_FILENO, ": ", 2);
	
	/* Convert cmd_count to string */
	sprintf(count_str, "%d", cmd_count);
	write(STDERR_FILENO, count_str, strlen(count_str));
	
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * execute - Execute a command
 * @args: Array of arguments
 * @env: Environment variables
 * @last_status: Pointer to last exit status
 * @prog_name: Program name for error messages
 * @cmd_count: Command counter
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args, char **env, int *last_status, 
            char *prog_name, int cmd_count)
{
	pid_t pid;
	int status;
	char *command;

	if (strcmp(args[0], "exit") == 0)
		return (shell_exit(args));
	if (strcmp(args[0], "env") == 0)
		return (shell_env(args, env));

	command = get_path(args[0], env);
	if (command == NULL)
	{
		print_error(prog_name, cmd_count, args[0]);
		*last_status = 127;
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, args, env) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("Error");
		*last_status = 1;
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		else
			*last_status = 1;
	}

	if (command != args[0])
		free(command);

	return (1);
}
