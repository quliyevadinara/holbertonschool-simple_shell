#include "shell.h"

/**
 * main - Entry point for simple shell
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 * Return: Exit status of last command
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	char **args = NULL;
	int status = 1;
	int last_status = 0;
	int cmd_count = 0;

	(void)ac;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_line();
		if (line == NULL)
			break;

		args = parse_line(line);
		if (args[0] != NULL)
		{
			cmd_count++;
			status = execute(args, env, &last_status, av[0], cmd_count);
		}

		free(line);
		free(args);
	}

	return (last_status);
}
