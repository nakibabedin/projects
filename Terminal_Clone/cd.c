#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "helpers.h"

void cd(char** args)
{
    /*
    void cd(char** args)
    Arguments:
      args: pointer to list of parsed strings from command line
    Return:
      void
    Functionality:
    */

    //init PATH
    char PATH[1000] = "";
    getcwd(PATH, 1000);

    if(args[1] == NULL || strncmp(args[1], "~",1) == 0)
    {
      /*
        if
          cd ~
          cd
        then 
          change directory to home directory
      */

      // split up all of the directories in PATH
      char** directories = parse(PATH, "/");
      
      // copy over the username into a buffer
      char username[1000] = "";
      getlogin_r(username, 1000); 

      // homeDir will store the PATH for the home directory
      char homeDir[1000] = "/";
      int i = 1;

      while(1)
      {
        // figure out where the home directory is by matching the name of the username to the username in the PATH
        strcat(homeDir, directories[i]);
        if(strcmp(directories[i], username) == 0){break;}
        strcat(homeDir, "/");
        i++;     
      }

      strcat(homeDir, "/");
      chdir(homeDir);


      if(args[1] == NULL) return; // if there is no other input, exit the function here because we are now in root director
      if(strlen(args[1]) > 2) args[1] += 2; // Move the args[1] pointer over so that it goes past the ~/ if the user wants to navigate from the root directory (e.g. ~/Desktop/.../...)
      if(strlen(args[1]) <= 2) return; // If the args[1] is ~ or ~/ then exit the function; otherwise there will be a segfault
    }

    if(strncmp(args[1], "/",1) == 0)
    {
      // if the user is trying to cd using PATH from the root directory
      chdir(args[1]);
      return;
    }

    getcwd(PATH, 1000);
    strcat(PATH, "/"); //add a slash to complete the path
    strcat(PATH, args[1]); //append the directory they want to cd to

    //change to new directory if it exists
	  //check if it exists by using a DIR*
    DIR* stream = opendir(PATH);
	  if(stream == NULL) printf("%s\n", strerror(errno));
	  else chdir(PATH);

    closedir(stream);
}
