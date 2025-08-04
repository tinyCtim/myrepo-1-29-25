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

*/

int main()
{
    int ch;

    while( (ch = getchar()) != EOF )
    {
        if( isalpha(ch) )
        {
            if( toupper(ch)>='A' && toupper(ch)<='P' )
                ch+= 10;
            else
                ch-= 16;
        }
        putchar(ch);
    }

    return(0);
}

