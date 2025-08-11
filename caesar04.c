#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*

3/23/22 - lrb - caesar01.c

This program is from Dan Gookin's book Tiny C Projects

It reads text input and shifts every letter in the first half of the
alphabet ahead by 13 characters and every letter in the second half of
the alphabet 13 characters back.

8/3/25 - lrb - caesar02.c

This version implements the cipher described in Louise Penny's book The
Brutal Telling
 
ABCDEFGHIJKLMNOPQRSTUVWXYZ
KLMNOPQRSTUVWXYZABCDEFGHIJ

MRKBVYDDO -> CHARLOTTE
OWSVI -> EMILY

now requires file on the command line ... 8/4/25

use -c to cipher, -d to decipher - 8/7/25

added shift option - 8/10/25

*/

#define MAXBUFLEN 10000

int main(argc,argv) int argc;char *argv[];

{
    char source[MAXBUFLEN + 1] = "";
    char ch;
    FILE *fp;
    size_t items_read;

    if (argc < 3) {printf("\nUsage: caesar filename {-c|-d} [-s shift]\n"); exit(1);}

    fp = fopen(argv[1],"r");
    if (fp == NULL) {
        perror("Error opening file");
        return (1);
    }

    // Read up to MAXBUFLEN characters from the file
    items_read = fread(source, sizeof(char), MAXBUFLEN, fp);

    int i=0;
    int shift = 10;
    if (argc == 5) {
        if (strcmp(argv[3], "-s") == 0) shift = atoi(argv[4]);
        }

    while( i != items_read )
    {
        ch = source[i];
        if ( isalpha(ch) )
        {
            if (strcmp(argv[2], "-c") == 0) {
                if ( toupper(ch)>='A' && toupper(ch)<='A'+25-shift )
                    ch+= shift;
                else
                    ch-= 26-shift;
                }
            if (strcmp(argv[2], "-d") == 0) {
                if ( toupper(ch)>='Z'-(25-shift) && toupper(ch)<='Z' )
                    ch-= shift;
                else
                    ch+= 26-shift;
                }
        }
        putchar(ch);
        i++;
    }

    return(0);
}

