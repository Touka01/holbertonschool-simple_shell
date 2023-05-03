#include "shell.h"

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
