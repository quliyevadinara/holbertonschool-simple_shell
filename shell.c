#include "shell.h"

/**
 * main - Entry point for simple shell
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	char **args = NULL;
	int status = 1;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_line();
		if (line == NULL)
			break;

		args = parse_line(line);
		if (args[0] != NULL)
			status = execute(args);

		free(line);
		free(args);
	}

	return (0);
}
