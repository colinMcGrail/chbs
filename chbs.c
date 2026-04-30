#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdnoreturn.h>

#include "text.h"

#define WORDNUM 4096
#define WORDPAD 9
#define DEF_LEN 7

struct Input {
    unsigned long wordcount;
    char separator;
    enum Caps {NONE, FIRST, ALL} caps;
};

void wordgen(enum Caps);

void processargs(int, char**, struct Input*);

int main(int argc, char** argv)
{
    struct Input input = {DEF_LEN, '\0', FIRST};
    unsigned int entropyTest;

    // Checks to make sure entropy source is available.
    if(getentropy(&entropyTest, sizeof(unsigned int)) == -1){
        perror(ENT_ERR);
        exit(EXIT_FAILURE);
    }

    processargs(argc, argv, &input);

    for(unsigned long i = 0; i < input.wordcount; i++){
        wordgen(input.caps);
        if (i < input.wordcount - 1 && input.separator != '\0'){
            putc(input.separator, stdout);
        }
    }
    putc('\n', stdout);

    exit(EXIT_SUCCESS);
}

noreturn void errmsg(const char * msg, char option)
{
    if(option == '\0')
        fputs(msg, stderr);
    else
        fprintf(stderr, msg, option);
    fputs(USAGE, stderr);
    fputs(HELPMSG, stderr);
    exit(EXIT_FAILURE);
}

void processargs(int argc, char** argv, struct Input* input)
{
    char* endptr;
    int c;

    while ((c = getopt(argc, argv, "+:hcls:n:")) != -1) {
        switch(c) {
            case 'h': // Print help and exit
                fputs(USAGE, stderr);
                fputs(HELP, stderr);
                exit(EXIT_SUCCESS);
            case 'c': // capitalize all letters
                if(input->caps == NONE) errmsg(CL_BOTH_ERR, '\0');
                input->caps = ALL;
                break;
            case 'l': // lowercase all letters
                if(input->caps == ALL) errmsg(CL_BOTH_ERR, '\0');
                input->caps = NONE;
                break;
            case 's': // print separator between words
                if (isprint(optarg[0]) && optarg[1] == '\0')
                    input->separator = optarg[0];
                else errmsg(BAD_SEP_ERR,'\0');
                break;
            case 'n':
                errno = 0;
                input->wordcount = strtoul(optarg, &endptr, 0);
                if (endptr[0] != '\0' || errno == EINVAL)
                    errmsg(NOT_INT_ERR, '\0');
                if (input->wordcount == 0 || errno == ERANGE)
                    errmsg(BAD_INT_ERR, '\0');
                break;
            case ':':
                errmsg(NO_ARG_ERR, optopt);
            case '?':
                errmsg(HUH_OPT_ERR, optopt);
        }
    }
}

unsigned int genNum() // generates random word index
{
    unsigned int randomNumber;

    getentropy(&randomNumber, sizeof(unsigned int));
    return (randomNumber % WORDNUM);
}

void wordgen(enum Caps caps) // gets random word from words[]
{
    extern char words[];

    int randword = (genNum() * WORDPAD);
    for(char i = 0; i < WORDPAD && words[randword + i] != '\0'; i++){
        if(caps == ALL || (caps == FIRST && i == 0)){
            putc(toupper(words[randword + i]), stdout);
        } else {
           putc((words[randword + i]), stdout);
        }
    }
}

