# Systems-Project-the-Second-Myshell

## Implemented Shell Features ##
	Redirecting Output '>'
	- Working

	Redirecting Input '<'
	- Working

	Executing Pipe '|'
	- Working

	Executing Regular Functions
	- Working

	Executing CD
	- Working

	Command Line Stdin with semicolons ';'
	- Working

## Function Headers ##

### Main.c ###
	static void handler(int sig)
	Arguments:
		sig: integer value of signal called by user
	Returns:
    	nothing
	Functionality:
    	takes the appropriate action based on the sig inputted

### Execute.c ###
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

  	int runProcess(char **args, int start, int in, int out)  
		Arguments:  
			args: pointer to list of pointer of command   arguments  
			including flags  
		Returns:  
			status: if successful, returns the value of the child PID  
							if unsuccessful, returns -1  
		Functionality:  
			Save the file descriptors for stdin and stdout  
			Change the file descriptors to specified file descriptors for redirect and pipe  
			Run the process  
			Set the stdin and stdout back to original file descriptors  

### Helpers.c ###
	char** parse(char* line, char* sep)  
		Arguments:  
			line: pointer to stdin input string  
			sep: character to separate the string by  
		Return:  
			tmp: pointer to list of pointers to each parsed string  
		Functionality:  
			Separates a string by the separator and places parsed string  
			   into a list of pointers containing parsed string  

	char* trimArg(char* input)   
		Arguments:  
			input: parsed String  
		Return:  
			tmp: trimmed parsed String  
		Functionality:  
			trims the parsed String by removing all whitespaces  

### Cd.c ###
	void cd(char** args)
    	Arguments:
      		args: pointer to list of parsed strings from command line
    	Return:
      		void
   		Functionality:
			changes working directory based on given PATH (which is args[1])
			supports cd from root directory (e.g. "/home/...")
			supports "cd .."

