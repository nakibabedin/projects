#ifndef HELPER_H
#define HELPER_H
/*
parameters:
- char* line : string that needs to be parsed
- char* sep : string that will act as seperator
function:
- seperate line into tokens at occurences of sep
return value:
- returns a list of string tokens
*/
char** parse(char* line, char* sep);
char* trimArg(char* input);
#endif
