#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_LEN 1024

char **environ;

/**
 * main - Runs the shell loop.
 *
 * This function is the entry point for the program. It first checks if
 * arguments were passed to the program, and if so, it executes the provided
 * command. If no arguments were passed, it creates an endless loop that
 * repeatedly prompts the user for input or reads input from stdin if it
 * was redirected or piped. It then parses the input to extract the command
 * and arguments, and then executes the command using the execute_command
 * function.
 *
 * @argc: the number of arguments passed to the program
 * @argv: an array of strings containing the arguments passed to the program
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char buffer[MAX_LEN];
	char **args;

	if (argc > 1)
	{
	args = &argv[1];
	execute_command(args);
	return EXIT_SUCCESS;
	}

	while (1)
	{
	if (isatty(fileno(stdin)))
	{
	prompt();
	}

	if (fgets(buffer, MAX_LEN, stdin) == NULL)
	{
	break;
	}

	args = parse_input(buffer);

	if (args[0] == NULL)
	{
	continue;
	}

	if (strcmp(args[0], "exit") == 0)
	{
	break;
	}

	execute_command(args);

	free(args);
	}

	return EXIT_SUCCESS;
}
