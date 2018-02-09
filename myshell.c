/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char *strtok(char *str, const char *delim);
    // Parse the commands provided using argc and argv

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument
        
        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        char* token = strtok(buffer, " \n");
		int i = 0;
		while (token){
			printf("%s \n", token);
			if (i == 0) {
				strcpy(command, token);
			}
			else {
				strcpy(arg, token);
			}
			i++;

			token = strtok(NULL, " ");
	    }
    
		// tests for the splitting of commands and arguments
		printf("Command:%s", command);
		printf("\n");
        printf("argument:%s", arg);

        if (strcmp(command, "cd") == 0)
        {
            // your code here
        }

        // other commands here...
        
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }

        else if (strcmp(command, "help") == 0){
            
        }
        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }

        
    }
    return EXIT_SUCCESS;
}
