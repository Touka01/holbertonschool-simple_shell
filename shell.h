#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LEN 1024
extern char **environ;

/*
 * Display the prompt and wait for user input 
*/
void prompt(void);

/*
 * Parses the user input to get the command
 */
char *parse_input(char buffer);

/*
 * Execute the command entered by the user
 */
void execute_command(char *command);

#endif /* SHELL_H */
