#ifndef COMMAND_EXEC_H
#define COMMAND_EXEC_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LEN 1024

void prompt();
char* parse_input(char* buffer);
void execute_command(char* command);

#endif /* COMMAND_EXEC_H */
