// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include "shell.h"
// --------------------------------------------
// Currently only two builtin commands for this
// assignment exist, however in future, more could 
// be added to the builtin command array.
// --------------------------------------------
const char* valid_builtin_commands[] = {"cd", "exit", NULL};


void parse( char* line, command_t* p_cmd ) {

        int argc;
        int i;
        char* path;

        char p1[strlen(line)]; 
        strcpy(p1, line);
        
        // count the the number of arguments in the command
        char* token = strtok(line, " "); 
        //path = (char*) malloc(strlen(token));
        path = token;

        argc = 0;
        while(token != NULL){
            token = strtok(NULL, " ");
            argc = argc + 1;
        }
        
        // initialize argv with the first string in the array as the path
        char *argv[argc + 1]; 
        argv[0] = path;

        // go through the rest of line and put each argument into argv
        char* tok = strtok(p1, " ");
        i = 1;
        while(tok != NULL){
            tok = strtok(NULL, " ");
            argv[i] = tok;
            i = i +1;
        }

        printf("The value of the path is: %s\n", path);
        printf("The value of the argc is: %d\n", argc);
        for(int j = 0; j <= argc; j ++){
            printf("the value of argv[%d] is %s\n ", j, argv[j]);
        }       

        p_cmd->path = path;
        p_cmd->argc = argc;
        for(int j = 0; j <= argc; j ++){
            (*p_cmd).argv[j] = argv[j];
        }       

        
} // end parse function


int execute( command_t* p_cmd ) {

	// ----------------------------------------
	// TODO: you fully implement this function
        return 0;

} // end execute function


int find_fullpath( char* command_name, command_t* p_cmd ) {


	char* path = getenv( "PATH" );
	
	// ----------------------------------------
	// TODO: you fully implement this function
        return 0;

} // end find_fullpath function


int is_builtin( command_t* p_cmd ) {

	int cnt = 0;

	while ( valid_builtin_commands[cnt] != NULL ) {

		if ( equals( p_cmd->path, valid_builtin_commands[cnt] ) ) {

			return TRUE;

		}

		cnt++;

	}

	return FALSE;

} // end is_builtin function


int do_builtin( command_t* p_cmd ) {

	// only builtin command is cd

	if ( DEBUG ) printf("[builtin] (%s,%d)\n", p_cmd->path, p_cmd->argc);

	struct stat buff;
	int status = ERROR;


        printf("folder: %s\n", p_cmd->argv[1]);
	if ( p_cmd->argc == 1 ) {

		// -----------------------
		// cd with no arg
		// -----------------------
		// change working directory to that
		// specified in HOME environmental 
		// variable

		status = chdir( getenv("HOME") );

	} else if ( ( stat( p_cmd->argv[1], &buff ) == 0 && ( S_IFDIR & buff.st_mode ) ) ) {


		// -----------------------
		// cd with one arg 
		// -----------------------
		// only perform this operation if the requested
		// folder exists

		status = chdir( p_cmd->argv[1] );

	} 

	return status;

} // end do_builtin function



void cleanup( command_t* p_cmd ) {

	int i=0;
	
	while ( p_cmd->argv[i] != NULL ) {
		free( p_cmd->argv[i] );
		i++;
	}

	free( p_cmd->argv );
	free( p_cmd->path );	

} // end cleanup function


int equals( char* str1, const char* str2 ) {

	// First check length

	int len[] = {0,0};

	char* b_str1 = str1;
	const char* b_str2 = str2;

	while( (*str1) != '\0' ) { 
		len[0]++;
		str1++;
	}

	while( (*str2) != '\0' ) {
		len[1]++;
		str2++;
	}

	if ( len[0] != len[1] ) {

		return FALSE;

	} else {

		while ( (*b_str1) != '\0' ) {

			// don't care about case (you did not have to perform
			// this operation in your solution

			if ( tolower( (*b_str1)) != tolower((*b_str2)) ) {

				return FALSE;

			}

			b_str1++;
			b_str2++;

		}

	} 

	return TRUE;


} // end compare function definition
