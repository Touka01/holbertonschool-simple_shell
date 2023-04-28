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
 * parse_input - Parses the user input to get the command and arguments.
 *
 * This function takes a string as an argument, which is expected to be
 * the user input. It then parses this string to extract the command
 * and arguments and returns them as an array of strings.
 *
 * @buffer: the user input\n *
 * Return: an array of strings containing the command and arguments
 */
char **parse_input(char *buffer)
{
	const char *delim = " \n";
	char **tokens = malloc(MAX_LEN * sizeof(char *));
	int i = 0;

	if (!tokens)
	{
	perror("malloc failed");
	exit(EXIT_FAILURE);
	}

	tokens[i] = strtok(buffer, delim);
	while (tokens[i] != NULL)
	{
	i++;
	tokens[i] = strtok(NULL, delim);
	}

	return tokens;
}

/**
 * execute_command - Executes the command entered by the user with arguments.
 *
 * This function takes an array of strings as an argument, which is expected
 * to contain the command and arguments entered by the user. It creates a new
 * child process and executes the command within that child process using
 * the execvp system call.
 *
 * @args: an array of strings containing the command and arguments
 *
 * Return: void
 */
void execute_command(char **args)
{
    pid_t pid;
    int status;
    char *path, *full_path;
    path = getenv("PATH");

    pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Check if the command is the 'env' built-in
        if (strcmp(args[0], "env") == 0)
        {
            // Print the current environment variables
            char **env = environ;
            while (*env)
            {
                printf("%s
", *env++);
            }
            exit(EXIT_SUCCESS);
        }

        // Search for the command in all directories specified in PATH
        full_path = strtok(path, ":");
        while (full_path != NULL)
        {
            char *command_path = malloc(strlen(full_path) + strlen(args[0]) + 2);
            sprintf(command_path, "%s/%s", full_path, args[0]);
            if (access(command_path, X_OK) == 0)
            {
                // Execute the command
                if (execve(command_path, args, environ) < 0)
                {
                    perror("execve()");
                    exit(EXIT_FAILURE);
                }
            }
            free(command_path);
            full_path = strtok(NULL, ":");
        }
        // Command not found
        printf("Command not found: %s", args[0]);
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}


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
