#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main();
void type_prompt();
void read_command();


int main() {
	char sheel[100], command[100], *param[20];
//		 to hold the command and to poiter this command and last CommandAfterEditing (parameters)to wirite command
	char *environment[] = { (char *) "PATH=/bin", 0}; // arr to defines the environment.

    while (1) { 
        type_prompt(); // display prompt
        read_command (command, param); // input from terminal
		if (strcmp(command, "exit") == 0) break; 
        if (fork() != 0) {        // Parent 
            wait(NULL);
        } else {
        strcpy(sheel, "/bin/"); // in this line we will copy path of "bin" in sheel CommandAfterEditing
        strcat(sheel, command); // in this line of code we will connect the path of bin file and the command for example the command is "ls" if we are print printf("%s\n", strcat(sheel, command)); 										the output /bin/ls
	    execve (sheel, param, environment); //  this statement for creat ovelap in current excution and excution in path file name (first arrgumant)
	    
	    perror("\033[1;31mThis command Not found");
	    printf("\033[0m");
	  
	   
	}
		if (strcmp(command, "exit") == 0) break; 
	}
	return 0;
}

void type_prompt(){
	
	char *curser = ">>  ";
	write(STDOUT_FILENO, curser, 3);
	/**
		STDOUT_FILENO: stdin is a default file pointer used to get input from none other than standard in. STDIN_FILENO is the default standard input file descriptor number which is 0 . It is 			essentially a defined directive for general use
		curser: the symbol 
		3 : how many bit you need away after curser in this case i choose 3 bit
	*/
}

void read_command(char sheel[], char *par[]) {
	char lineCommand[1000];
    int count = 0, i= 0, j = 0;
    char *CommandAfterEditing[100], *sepCommand;
    
    while(1) {
        int character = fgetc(stdin);
        /*
        The STDIN is the short form of the “standard input”, in C programming the term “stdin” is used for the inputs which are taken from the keyboard either by the user or from a file. The “stdin” 			is also known as the pointer because the developers access the data from the users or files and can perform an action on them.
        
        fgetc() is used to obtain input from a file single character at a time. This function returns the ASCII code of the character read by the function. It returns the character present at 				position indicated by file pointer. After reading the character, the file pointer is advanced to next character.
        */
        lineCommand[count++] = (char) character;
        if (character == '\n') break; // This meain the command is end
    }

    if (count == 1) { 
        printf("\033[1;31mNot found a Command\n");
        printf("\033[0m");
    }
	

  	 sepCommand = strtok (lineCommand, " \n"); // separated line of command

    // parse the line Command into words
    while (sepCommand != NULL) {
        CommandAfterEditing[i++] = strdup(sepCommand);
        sepCommand = strtok(NULL, " \n");
    }
    
    // select first word in command
    strcpy(sheel, CommandAfterEditing[0]);
    
    for(int j = 0; j < i; j++)
        par[j] = CommandAfterEditing[j];
    par[i] = NULL;

}
