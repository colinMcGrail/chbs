#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "text.h"

#define WORDNUM 4096
#define WORDPAD 9
#define DEF_LEN 7
#define DEF_SEP '-'

void wordgen(char);

void processargs(int, char**, char[], long unsigned int*);

int main(int argc, char** argv)
{
    unsigned long i, wordcount = DEF_LEN;
    unsigned int entropyTest;
    char flags[] = {'\0', '\0'};

    // Checks to make sure entropy source is available.
    if(getentropy(&entropyTest, sizeof(unsigned int)) == -1){
        perror(ENT_ERR);
        exit(EXIT_FAILURE);
    }
    processargs(argc, argv, flags, &wordcount);

    for(i = 0; i < wordcount; i++){
        wordgen(flags[0]);
        if (i < wordcount - 1 && flags[1] != 1){
            putc(flags[1], stdout);
        }
    }
    putc('\n', stdout);

    exit(EXIT_SUCCESS);
}

void errmsg(){
    fputs(USAGE, stderr);
    fputs(HELPMSG, stderr);
    exit(EXIT_FAILURE);
}

void processargs(int argc, char **argv, char flags[], long unsigned int* wordcount){
    char* endptr;
    char c;

    while ((c = getopt(argc, argv, "+:ns:w:cCh")) != -1) {
        switch(c) {
            case 'h':
                fputs(USAGE, stderr);
                fputs(HELP, stderr);
                exit(EXIT_SUCCESS);
            case 'c': // Capitalize first letter of each word
                if (!flags[0])
                    flags[0] = 1;
                break;
            case 'C': // Capitalize all letters
                flags[0] = 2;
                break;
            case 'n':
                if (flags[1])
                    errmsg();
                else {
                    flags[1] = 1;
                }
                break;
            case 's':
                if (flags[1])
                    errmsg();
                else if (optarg[0] < 32  ||
                         optarg[0] > 126 ||
                         optarg[1] != '\0') {
                    fputs(BAD_SEP_ERR, stderr);
                    errmsg();
                } else {
                    flags[1] = optarg[0];
                }
                break;
            case 'w':
                errno = 0;
                *wordcount = strtoul(optarg, &endptr, 0);
                if (endptr[0] != '\0' || errno == EINVAL) {
                    fputs(NOT_INT_ERR, stderr);
                    errmsg();
                }
                if (*wordcount == 0 || errno == ERANGE){
                    fputs(BAD_INT_ERR, stderr);
                    errmsg();
                }
                break;
            case ':':
                fprintf(stderr, NO_ARG_ERR, optopt);
                errmsg();
            case '?':
                fprintf(stderr, HUH_OPT_ERR, optopt);
                errmsg();
        }
    }
    if(flags[1]=='\0'){
        flags[1] = DEF_SEP;
    }
}

unsigned int genNum() // generates random word index
{
    unsigned int randomNumber;

    getentropy(&randomNumber, sizeof(unsigned int));
    return (randomNumber % WORDNUM);
}

void wordgen(char flag) // gets random word from words[]
{
    extern char words[];

    int randword = (genNum() * WORDPAD);
    for(char i = 0; i < WORDPAD && words[randword + i] != '\0'; i++){
        if(flag == 2 || (flag == 1 && i == 0)){
            putc((words[randword + i] - 32), stdout);
        } else {
           putc((words[randword + i]), stdout);
        }
    }
}

