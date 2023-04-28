#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LEN 1024

char **environ;

/*
 * Display the prompt and wait for user input
 */
void prompt(void)
{
	printf("$ ");
	fflush(stdout);
}

/*
 * Parses the user input to get the command
 */
char *parse_input(char *buffer)
{
	char *command;

	command = strtok(buffer, "\n");
	return command;
}

/*
 * Execute the command entered by the user
 */
void execute_command(char *command)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork()");
		exit(1);
	}
	else if (pid == 0)
	{
		char *args[2];

		args[0] = command;
		args[1] = NULL;
		if (execve(command, args, environ) < 0)
		{
			perror("execve()");
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}
}

int main(void)
{
	char buffer[MAX_LEN];
	char *command;

	while (1)
	{
		prompt();
		fgets(buffer, MAX_LEN, stdin);
		strtok(buffer, "\n");

		command = parse_input(buffer);

		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		if (strlen(command) == 0)
		{
			continue;
		}

		execute_command(command);
	}

	return 0;
}
