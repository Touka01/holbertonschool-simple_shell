#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LEN 1024

extern char **environ;

void prompt(void);
char **parse_input(char *buffer);
void execute_command(char **args);
int main(int argc, char **argv);

#endif
