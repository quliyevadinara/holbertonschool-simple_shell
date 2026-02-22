#include "shell.h"

/**
 * check_absolute_path - Check if command is absolute path
 * @command: The command to check
 * Return: command if exists, NULL otherwise
 */
char *check_absolute_path(char *command)
{
	struct stat buffer;

	if (command[0] == '/')
	{
		if (stat(command, &buffer) == 0)
			return (command);
		return (NULL);
	}
	return (NULL);
}

/**
 * build_path - Build full path for command
 * @directory: Directory path
 * @command: Command name
 * Return: Full path
 */
char *build_path(char *directory, char *command)
{
	int command_length, directory_length;
	char *file_path;

	command_length = strlen(command);
	directory_length = strlen(directory);
	file_path = malloc(command_length + directory_length + 2);

	if (!file_path)
		return (NULL);

	strcpy(file_path, directory);
	strcat(file_path, "/");
	strcat(file_path, command);

	return (file_path);
}

/**
 * search_in_path - Search command in PATH directories
 * @path: PATH string
 * @command: Command to find
 * Return: Full path or NULL
 */
char *search_in_path(char *path, char *command)
{
	char *path_copy, *path_token, *file_path;
	struct stat buffer;

	path_copy = strdup(path);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		file_path = build_path(path_token, command);
		if (file_path && stat(file_path, &buffer) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * get_path - Get the full path of a command
 * @command: The command to find
 * @env: Environment variables
 * Return: Full path or NULL
 */
char *get_path(char *command, char **env)
{
	char *path = NULL;
	char *result;
	int i;

	result = check_absolute_path(command);
	if (result)
		return (result);

	for (i = 0; env[i]; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
	}

	if (path)
		return (search_in_path(path, command));

	return (NULL);
}
