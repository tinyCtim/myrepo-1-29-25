#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* lrb */

/* lrb - 6/21/25 */
/* written by ChatGPT */
/* using command tail argument */
/* replaced hardcoded text w/ file input */
/* note: name of program motivated by book by James McBride */

#define MAX_TEXT_LENGTH 5000
#define MAX_SENTENCES 100

int main(int argc, char *argv[]) {

    char text[MAX_TEXT_LENGTH];
    if (argc != 2) {printf("\nUsage: king_kong_new file_in\n"); exit(1);}
    FILE *fp = fopen(argv[1], "r");
    int br;
    br = fread(text, 1, MAX_TEXT_LENGTH, fp);
    text[br-1] = 0; // fix end of buffer
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

        printf("Sentence %d:\n", i + 1);
        printf("  Text   : %s\n", s);
        printf("  Letters: %d\n", letters);
        printf("  Words  : %d\n", words);
        printf("  Length : %d characters\n\n", length);
    }

    return 0;
}

