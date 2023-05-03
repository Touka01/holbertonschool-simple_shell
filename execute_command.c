#include "shell.h"

/**
 * search_path - Search for the command in all directories specified in PATH.
 *
 * @args: an array of strings containing the command and arguments
 *
 * Return: the full path of the command if found, NULL otherwise
 */
char *search_path(char **args)
{
	char *path, *full_path, *command_path;

	path = getenv("PATH");
	full_path = strtok(path, ":");

	while (full_path != NULL)
	{
		command_path = malloc(strlen(full_path) + strlen(args[0]) + 2);
		sprintf(command_path, "%s/%s", full_path, args[0]);

		if (access(command_path, X_OK) == 0)
		{
			return command_path;
		}

		free(command_path);
		full_path = strtok(NULL, ":");
	}

	return NULL;
}

/**
 * execute_builtin - Executes a builtin command.
 *
 * @args: an array of strings containing the command and arguments
 *
 * Return: 1 if the command was a builtin, 0 otherwise
 */
int execute_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			printf("%s\n", *env++);
		}

		return 1;
	}

	return 0;
}

/**
 * execute_command - Executes the command entered by the user with arguments.
 *
 * @args: an array of strings containing the command and arguments
 *
 * Return: void
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *command_path;

	if (execute_builtin(args))
	{
		return;
	}

	command_path = search_path(args);

	if (command_path == NULL)
	{
		printf("Command not found: %s\n", args[0]);
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	free(command_path);
}
