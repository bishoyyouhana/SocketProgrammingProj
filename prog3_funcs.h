/*
 * File: prog3_funcs.h
 * Name: Mark Erle
 * UID:  mae5
 */

#ifndef PROG3_FUNCS
#define PROG3_FUNCS

void parseArgs(int, char *[], char *);   /* call help or set optional socket file name and optional path */
int queryMsg(char *);                    /* query user for message to send or disconnect */
void help(void);                         /* print help message */

#endif
