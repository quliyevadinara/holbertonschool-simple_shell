#include "shell.h"

/**
 * main - Entry point for simple shell
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	char **args = NULL;
	int status = 1;

	(void)ac;
	(void)av;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_line();
		if (line == NULL)
			break;

		args = parse_line(line);
		if (args[0] != NULL)
			status = execute(args, env);

		free(line);
		free(args);
	}

	return (0);
}
