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
#include <pwd.h>
#include <errno.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here
char currentpath[BUFFER_LEN];
char oldPath[BUFFER_LEN];
int userID;
char *userName;

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
            getcwd(currentpath, sizeof(currentpath));
				if (strcmp(arg, "") == 0) {
					printf("%s\n", currentpath);
				} else {
					setenv("PWD", arg, 2);
					printf("\nDirectory: %s", getenv("PWD"));
					if (chdir(getenv("PWD")) == 0) {
						printf("\nThe new directory is: %s\n", getenv("PWD"));
					} else {
						printf("Directory not changed. [%s]\n", strerror(errno));
					}
                }
        }

        // other commands here...
        else if (strcmp(command, "dir") == 0){
           
				DIR *dir;
				struct dirent *ent;
				int dirfound = 1; 
				getcwd(oldPath, sizeof(oldPath));

				if (strcmp(arg, "") != 0) {
					setenv("PWD", arg, 2); 
					if (chdir(getenv("PWD")) != 0) { 
						printf("Directory not found. [%s]", strerror(errno)); 
						dirfound = 0;
					}
				}

				if (dirfound == 1) { 
					getcwd(currentpath, sizeof(currentpath)); 
					dir = opendir(currentpath); 
					while ((ent = readdir (dir)) != NULL) { 
						printf ("%s\n", ent->d_name);
					}
					setenv("PWD", oldPath, 3); 
					chdir(getenv("PWD")); 
					closedir(dir); 
                }     

        }
        else if (strcmp(command, "environ") == 0){
            system("printenv");

        }
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }

        else if (strcmp(command, "pause")== 0){
            char a[BUFFER_LEN];
				struct termios term, term_orig;
				tcgetattr(STDIN_FILENO, &term);
				term_orig = term;
				term.c_lflag &= ~ECHO;
				tcsetattr(STDIN_FILENO, TCSANOW, &term);
                
				
				fflush(stdin);
				fgets(buffer, BUFFER_LEN, stdin);

			
                tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
        }

        else if (strcmp(command, "help") == 0){
            int c ;
            FILE *file;
            file = fopen("README.txt", "r");
            if (file){
                while ((c =getc(file)) != EOF )
                    putchar(c);
                fclose(file);
            }
        }
        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }

        
    }
    return EXIT_SUCCESS;
}
