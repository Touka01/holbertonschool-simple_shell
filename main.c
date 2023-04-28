#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LEN 1024

char **environ;

/**
 * prompt - Display the prompt and wait for user input.
 *
 * This function simply displays the '$' prompt and flushes the
 * standard output. It does not take any arguments or return anything.
 *
 * Return: void
 */
void prompt(void)
{
	printf("$ ");
	fflush(stdout);
}

/**
 * parse_input - Parses the user input to get the command.
 *
 * This function takes a string as an argument, which is expected to be
 * the user input. It then parses this string to extract the command
 * and return the command as a new string.
 *
 * @buffer: the user input
 *
 * Return: the command entered by the user
 */
char *parse_input(char *buffer)
{
	char *command;

	command = strtok(buffer, "\n");
	return (0);
}

/**
 * execute_command - Executes the command entered by the user.
 *
 * This function takes a string as an argument, which is expected
 * to be the command entered by the user. It creates a new child process
 * and executes the command within that child process using the execve
 * system call.
 *
 * @command: the command entered by the user
 *
 * Return: void
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

/**
 * main - Runs the shell loop.
 *
 * This function is the entry point for the program. It creates
 * an endless loop that repeatedly prompts the user for input,
 * parses the input to extract the command, and then executes
 * the command using the execute_command function.
 *
 * Return: 0 on success
 */
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

	return (EXIT_SUCCESS);
}
