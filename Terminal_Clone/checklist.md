# Project (Shell) Overview

## Requirements
* Read a line at a time, parse the line to separate the command from its arguments. It should then fork and exec the command. The parent process should wait until the exec’d program exits and then it should read the next command.
Note: exit and cd cannot be run through a forked child process, you will have to implement these commands on your own. (These are not programs! Why you ask? think about it...)

* check out the chdir() function
* Read and separate multiple commands on one line with ;. That is, the line ls -l ; echo hello should first run the command ls -l and then echo hello.
* Implement simple redirection using > (redirecting stdout) and < (redirecting stdin).
This will be explained in class later.
* Implement simple pipes, that is: ls | wc would run ls and use the output from ls as the input for wc.
This will be explained in class.
Check out popen() for this.
* All of these commands work in bash, so use it to check out the functionality of each feature if you are unclear about anything.
Specific requirements
* Every function you write must have a function header comment describing the arguments, return value and what the function does.

## You should have a readme file with the following:
* A description of what features your shell implements
* A description of what features you attempted to implement but were unsuccessful
* Any bugs or things you want me to know about your program
* A copy of every function header

* The project should be built using make and a makefile, I will only compile by using make.

## Try starting with these restrictions on input:
To make your life easier, you could require that all items on the command line are to be separated by a single space.
When parsing the line, it might help to count the number of tokens (individual pieces), before parsing.
You can restrict the locations and ordering of > and <.
You can limit piping (|) to a single pipe.
If you would like to implement other features after getting these ones down, please do. Look at what bash does and see what else you can do!
