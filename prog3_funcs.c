#include <stdio.h>          
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "prog3_funcs.h"
#include "syscalls.h"
#include "globaldefs.h" 

void parseArgs(int argc, char* argv [], char* x){
    if(argc> 2 ||argc<1 ) help();
    if(argc ==2){
        if(strlen(argv[1])>108){help();}
        strcpy(x,argv[1]);
    }else{
        strcpy(x,SOCK_PATH);
    }
    //printf("done\n");       
}

void help(){
    fprintf(stdout,"Usage:\n");
    fprintf(stdout,"    prog3_server [socketFilename]\n");
    fprintf(stdout,"    prog3_client [socketFilename]\n");
    fprintf(stdout,"prog3_server creates a socket file named 'socketoomee' (or argument passed on command line)\n");
    fprintf(stdout,"and waits for a client to connect. Once connected, users can communicate via the socket.");
    fprintf(stdout,"Maximum length of socketFilename (including optional path) is 108 characters.");
    exit(0);
}

int queryMsg(char *buffer){
    fprintf(stdout, "Enter your message or CTRL+D to close connection\n");
    //sscanf(buffer, "%s", )
    size_t size=32;
    int num = 0;
    num = getline(&buffer, &size, stdin);
    while (num != 0){
        if(num == -1){
            return -1; //if user enters CTRL+D
        }
        else if((num -1) == 0){
            fprintf(stdout, "Enter a nonempty message or CTRL+D to quit\n");
            num = getline(&buffer, &size, stdin);
        }
        else {
            fprintf(stdout,"s = %s\n",buffer);
            return num -1;
        }
    }
    //fprintf(stdout,"s = %s\n",buffer);
    return num -1;
    }
