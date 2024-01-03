#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "helpers.h"

int MAX = 256;

char** parse(char* line, char* sep){
	/*
		char** parse(char* line, char* sep)
		Arguments:
			line: pointer to stdin input string
			sep: character to separate the string by
		Return:
			tmp: pointer to list of pointers to each parsed string
		Functionality:
			Separates a string by the separator and places parsed string
				into a list of pointers containing parsed string
	*/
	char** retVal = (char**)malloc(MAX*8);
	int ctr = 0;
	retVal[ctr] = strsep(&line, sep);
	while(retVal[ctr] != NULL){
		retVal[++ctr] = strsep(&line, sep);
	}
	for(int i = 0; i < ctr; i++)
	{
		retVal[i] = trimArg(retVal[i]);
	}
	return retVal;
}

char* trimArg(char* input){
	/*
	char** trimArg(char* input)
	Arguments:
		input: parsed String
	Return:
		tmp: trimmed parsed String
	Functionality:
		trims the parsed String by removing all whitespaces
	*/
	char* tmp = input;
	int len = strlen(input);
	int counter = 0;
	// printf("BEFORE: %s\n", input);
	while(counter < len)
	{   // trim from the left
		if(tmp[counter] != ' ') break;
		//moves the pointer to the first non-space character in the string
		tmp++;
	}

	while(len > 0)
	{   // trim from the right
		if(tmp[len-1] != ' ') break;
		tmp[len-1] = '\0';
		len--;
		// replaces the space with a NULL
		// effectively gets rid of the space
	}

	return tmp;
}
