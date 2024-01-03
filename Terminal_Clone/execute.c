#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <errno.h>
#include <string.h>

#include "helpers.h"
#include "execute.h"
#include "cd.h"

void runCommands(char* command)
	/*
	void runCommands(char* command)
	Arguments:
		command: one command line from Stdin
	Returns:
		void
	Functionality:
		Parses the command string by spaces
		If the command is "exit", program will exit
		Else if the command is "cd", program will call cd function
		Else, the program will call runCommand
	*/
{
	char **args = parse(command, " ");
	if(strcmp(args[0], "exit") == 0)
		exit(0);
	else if(strcmp(args[0], "cd") == 0)
		cd(args);
	else
		runCommand(args);
	free(args);
}

void runCommand(char **args){
	/*
	void runCommand(char** args)
	Arguments:
		args: pointer to list of pointer of command arguments
		including flags
	Returns:
		void
	Functionality:
		Iterate through args starting from the first index
		If args contains '<' create a new file and set its file descriptor as stdout
		Else if args contains '>' create a new file and set its file descriptor as stdin
		Else if args contains '|', set the writing end of the pipe to stdout and run the command proceeding the '|'
			set the reading end of the pipe to stdin
		Run the command
	*/
	//by default this is stdout and stdin
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);
	//loop through all args
	int ctr = 0;
	int currentCommand = 0; //keeps track of which command to run next
	while(args[ctr] != NULL){
		//CASE 1: redirect in
		if(strcmp("<", args[ctr]) == 0){
			if(args[ctr+1] == NULL){
				printf("ERROR: no argument provided for <\n");
				return;
			}
			in = open(args[ctr+1], O_RDONLY);
			if(in == -1){
				printf("file not found!\n");
				return;
			}
			args[ctr] = NULL;
		}
		//CASE 2: redirect out
		else if(strcmp(">", args[ctr]) == 0){
			if(args[ctr+1] == NULL){
				printf("ERROR: no argument provided for >\n");
				return;
			}
			out = open(args[ctr+1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if(out == -1){
				printf("file not found!\n");
				return;
			}
			args[ctr] = NULL;
		}
		//CASE 3: pipe
		else if(strcmp("|", args[ctr]) == 0){
			//create pipe file descriptors and store in arr:
			//[read_end, write_end]
			int pipeFileDescrip[2];
			if(pipe(pipeFileDescrip) == -1){
				printf("ERROR: pipe() failed\n");
				return;
			}
			//make the out of the next process the write fd of pipe
			out = pipeFileDescrip[1];
			//run the pipe
			args[ctr] = NULL;
			runProcess(args, currentCommand, in, out);
			currentCommand = ctr+1;
			//the next in will be the read fd of pipe
			in = pipeFileDescrip[0];
		}
		ctr++;
	}
	int status = runProcess(args, currentCommand, in, out);
}

//returns status of process
int runProcess(char **args, int start, int in, int out){
	/*
	void runProcess(char** args)
	Arguments:
		args: pointer to list of pointer of command arguments
		including flags
	Returns:
		status: if successful, returns the value of the child PID
						if unsuccessful, returns -1
	Functionality:
		Save the file descriptors for stdin and stdout
		Change the file descriptors to specified file descriptors for redirect and pipe
		Run the process
		Set the stdin and stdout back to original file descriptors
	*/
	int status;
	//save normal descriptors
	int tmpIn = dup(STDIN_FILENO);
	int tmpOut = dup(STDOUT_FILENO);

	//change to specified
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);

	//run process
	int forkVal = fork();
	if(forkVal == 0){
		execvp(args[start], args+start);
		printf("invalid command\n");
	}
	else wait(&status); //wait for it to run

	//set back to normal and cleanup
	dup2(tmpIn, STDIN_FILENO);
	dup2(tmpOut, STDOUT_FILENO);
	close(in);
	close(out);
	return status;
}
