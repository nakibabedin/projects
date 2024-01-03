#ifndef EXECUTE_H
#define EXECUTE_H
void runCommands(char *command);
void runCommand(char **args);
int runProcess(char **args, int start, int in, int out);
#endif
