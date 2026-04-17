#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ENT_ERR "Cannot access secure entropy source.\n"

#define WORDNUM 4096
#define WORDPAD 9
#define DEF_LEN 7
#define DEF_SEP '.'

void wordgen(void);

int main(int argc, char** argv)
{
    unsigned long wordcount, i;
    unsigned int entropyTest;

    if(getentropy(&entropyTest, sizeof(unsigned int)) == -1){
        perror(ENT_ERR);
        return EXIT_FAILURE;
    }

    if (argc >= 2){
        wordcount = strtoul(argv[1], 0, 0);
        if (wordcount == 0 || errno == ERANGE){
            wordcount = DEF_LEN;
        }
    } else {
        wordcount = DEF_LEN;
    }

    for(i = 0; i < wordcount; i++){
        wordgen();
        if (i < wordcount - 1){
            putc(DEF_SEP, stdout);
        }
    }
    putc('\n', stdout);

    return EXIT_SUCCESS;
}

unsigned int genNum()
{
    unsigned int randomNumber;

    getentropy(&randomNumber, sizeof(unsigned int));
    return (randomNumber % WORDNUM);
}

void wordgen()
{
    extern char words[];
    
    int randword = (genNum() * WORDPAD);
    for(char i = 0; i < WORDPAD && words[randword + i] != '\0'; i++){
        putc(words[randword + i], stdout);
    }
}
