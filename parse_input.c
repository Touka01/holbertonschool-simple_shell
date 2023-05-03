#include "shell.h"

/**
 * parse_input - Parses the user input to get the command and arguments.
 *
 * This function takes a string as an argument, which is expected to be
 * the user input. It then parses this string to extract the command
 * and arguments and returns them as an array of strings.
 *
 * @buffer: the user input
 *
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
