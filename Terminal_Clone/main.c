#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "execute.h"
#include "helpers.h"

int mainProcess; //keep track of the master process (shell)

static void handler(int sig){
	/*
	static void handler(int sig)
	Arguments:
		sig: integer value of signal called by user
	Returns:
		nothing
	Functionality:
		takes the appropriate action based on the sig inputted
	*/
	if(sig == SIGINT){
		if(getpid() == mainProcess) printf("\nterminating process...\n");
		else exit(0);
	}
}

int main(){
	//startup
	char input[256];
	mainProcess = getpid();
	signal(SIGINT, handler);
	printf("\033c"); //clear screen

	//shell runs infinitely
	while(1){
		//prompt user for input
		char PATH[1000];
		getcwd(PATH, 1000);
		printf("\e[1;32m"); //green
		printf("mykolyk:");
		printf("\e[1;34m"); //blue
		printf("%s$ ", PATH);
		printf("\e[0;37m"); //white
		fgets(input, 256, stdin);

		//format input
		input[strlen(input)-1] = 0; //get rid of newline
		char **commands = parse(input, ";"); //seperate all individual commands

		//go through each command and run
		int cur = 0;
		while(commands[cur] != NULL){
			//printf("running %s:\n", commands[cur++]);
			
			runCommands(commands[cur++]);
		}
		free(commands);
	}
	//cleanup
	return 0;
}
