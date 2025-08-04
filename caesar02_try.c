#include <stdio.h>
#include <ctype.h>

/*

3/23/22 - lrb - caesar01.c

This program is from Dan Gookin's book Tiny C Projects

It reads text input and shifts every letter in the first half of the
alphabet ahead by 13 characters and every letter in the second half of
the alphabet 13 characters back.

8/3/25 - lrb - caesar02.c

This version implements the cipher described in Louise Penny's book The
Brutel Telling
 
ABCDEFGHIJKLMNOPQRSTUVWXYZ
KLMNOPQRSTUVWXYZABCDEFGHIJ

MRKBVYDDO -> CHARLOTTE
OWSVI -> EMILY

now requires file on the command line ... 8/4/25

*/

#define MAXBUFLEN 10000

int main(argc,argv) int argc;char *argv[];

{
	char source[MAXBUFLEN + 1] = "";
    char ch;
    FILE *fp;
    size_t items_read;

    fp = fopen(argv[1],"r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read up to 1000 characters from the file
    items_read = fread(source, sizeof(char), 1000, fp);

	int i=0;

    while( i != items_read )
    {
        ch = source[i];
        if( isalpha(ch) )
        {
            if( toupper(ch)>='K' && toupper(ch)<='Z' )
                ch-= 10;
            else
                ch+= 16;
        }
        putchar(ch);
        i++;
    }

    return(0);
}

