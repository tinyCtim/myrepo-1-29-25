#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* lrb */

/* lrb - 6/21/25 */
/* written by ChatGPT */
/* using command tail argument */
/* replaced hardcoded text w/ file input */

/* 
This program was motivated by reading James McBride's "Deacon King Kong."
There is a particular paragraph in this book that has a bunch of
sentences of increasingly long length. The program takes the name of a
text file and displays the longest sentence etc. 
*/

#define MAX_TEXT_LENGTH 10000  // lrb
#define MAX_SENTENCES 300

int main(int argc, char *argv[]) {
    int max_length = 0;
    int save_i;
    int save_words;
    char save_text[1000] = "";  // lrb
    char text[MAX_TEXT_LENGTH];
    printf("\nking_kong_new.c - lrb - 6/25/25\n");
    if (argc != 2) {printf("\nUsage: king_kong_new file_in\n"); exit(1);}
    FILE *fp = fopen(argv[1], "r");
    int br;
    br = fread(text, 1, MAX_TEXT_LENGTH, fp);
    text[br - 1] = 0; // fix end of buffer
    char *sentences[MAX_SENTENCES];
    int sentence_count = 0;

    // Tokenize sentences by . ? !
    char *token = strtok(text, ".!?");
    while (token != NULL && sentence_count < MAX_SENTENCES) {
        sentences[sentence_count++] = token;
        token = strtok(NULL, ".!?");
    }

    printf("Total number of sentences: %d\n\n", sentence_count);

    for (int i = 0; i < sentence_count; i++) {
        int letters = 0, words = 0, length = 0;
        int in_word = 0;
        char *s = sentences[i];

        for (int j = 0; s[j] != '\0'; j++) {
            char c = s[j];
            length++;

            if (isalpha(c))
                letters++;

            if (!isspace(c) && !in_word) {
                in_word = 1;
                words++;
            } else if (isspace(c)) {
                in_word = 0;
            }
        }

        // Trim leading spaces
        while (*s && isspace(*s)) s++;
        if (length > max_length) {
            max_length = length;
            save_i = i + 1;
            save_words  = words;
            strcpy(save_text, s);
            }
    }

    printf("Sentence %d:\n", save_i);
    printf("  Text   : %s\n", save_text);
    printf("  Words  : %d\n", save_words);
    printf("  Length : %d characters\n\n", max_length);

    return 0;
}

