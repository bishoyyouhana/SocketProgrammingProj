/* 
 * Program: prog3.c
 * Name: Bishoy Youhana
 * UID: 814457068
 */

/* preprocessor directives */
#include <stdio.h>          /* for FILE */
#include <string.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>    /* errno */
#include <sys/un.h>
#include <stdbool.h>
#include "prog3_funcs.h"
#include "syscalls.h"
#include "globaldefs.h"

/* main */
int main(int argc, char *argv[]) {
    int    socket, connect;
    char *buffer = (char*) Malloc(BUFFER_SIZE);
    struct sockaddr_un serveraddr;

    //create socket
    socket=Socket(DOMAIN, TYPE, PROTOCOL);
    printf("Creating initial/unbound socket...\n");
    memset(&serveraddr, '\0', sizeof(serveraddr));
    parseArgs(argc, argv, serveraddr.sun_path);
    serveraddr.sun_family = DOMAIN;
    unlink(serveraddr.sun_path);    

    //bind the socket and connect it
    Bind(socket,( struct sockaddr *)&serveraddr , sizeof(struct sockaddr_un));
    Listen(socket, BACKLOG);
    printf("Marking initial/unbound socket as accepting connections...\n");
    socklen_t len = sizeof(struct sockaddr_un);
    fprintf(stdout,"Waiting for client...\n");
    connect=Accept(socket, ( struct sockaddr *)&serveraddr , &len);

    //print first message
    char str[128];  
    struct utsname unameData;
    Uname(&unameData);
    sprintf(str,"Welcome to server %s (process %ld) running %s  release %s on %s platform", unameData.nodename,getpid(),unameData.sysname, unameData.release, unameData.machine);
    Send(connect,str, strlen(str), FLAGS);

    //get ready for while loop
    int i=0; int recBytes; int sentBytes; bool loop =1;
    fprintf(stdout,"Connected Successfully\n");
    memset(buffer, '\0', BUFFER_SIZE);

    while(loop== 1){
        // recieve message
        recBytes=Recv(connect, buffer, sizeof(struct sockaddr_un),FLAGS);
        fprintf(stdout,"Recieved message (%d bytes): %s \n",recBytes ,buffer); 
        memset(buffer, '\0', BUFFER_SIZE);  

        //get input
        i= queryMsg(buffer);
        //send input accordingly

        if(i>0&& i>BUFFER_SIZE){
            sentBytes= Send(connect, buffer,BUFFER_SIZE , FLAGS);
            fprintf(stdout, "truncating to 140 - compatible size:");
            memset(buffer, '\0', BUFFER_SIZE);
        }else if(i>0 ){
            sentBytes= Send(connect, buffer,i , FLAGS);
            fprintf(stdout, "Sent message (%ld bytes) waiting for reply...\n", sentBytes);
            memset(buffer, '\0', BUFFER_SIZE);

        }else{
            strcpy(buffer,"Later!\n");
            sentBytes=Send(connect, buffer, i, FLAGS);
            //fprintf(stdout, "\nexitting\n");
            memset(buffer, '\0', BUFFER_SIZE); 
            loop =0;   // end loop
        }
        fprintf(stdout,"%d\n",loop);
    }

    // free memory and close socket
    free(buffer);
    Close(socket);
    Close(connect);
    return 0;
} 