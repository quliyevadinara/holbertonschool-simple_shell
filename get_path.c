#include "shell.h"

/**
 * build_full_path - Build full path from directory and command
 * @dir: Directory path
 * @cmd: Command name
 * Return: Full path string
 */
char *build_full_path(char *dir, char *cmd)
{
	int len_dir, len_cmd;
	char *full_path;

	len_dir = strlen(dir);
	len_cmd = strlen(cmd);
	full_path = malloc(len_dir + len_cmd + 2);
	
	if (!full_path)
		return (NULL);
	
	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	
	return (full_path);
}

/**
 * find_in_path - Search for command in PATH
 * @path_env: PATH environment string
 * @command: Command to find
 * Return: Full path to command or NULL
 */
char *find_in_path(char *path_env, char *command)
{
	char *path_copy, *token, *full_path;
	struct stat st;

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		full_path = build_full_path(token, command);
		if (full_path && stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	
	free(path_copy);
	return (NULL);
}

/**
 * get_path - Get full path of a command
 * @command: Command name
 * @env: Environment variables array
 * Return: Full path or NULL
 */
char *get_path(char *command, char **env)
{
	struct stat st;
	int i;
	char *path_value;

	/* Handle absolute paths and relative paths (/, ./, ../) */
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}

	/* Search in PATH */
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path_value = env[i] + 5;
			return (find_in_path(path_value, command));
		}
		i++;
	}

	return (NULL);
}
