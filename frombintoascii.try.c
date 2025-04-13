
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// ChatGPT generated the original
// 4/11/25 - lrb

// Converts a binary file to an ascii file
int input_to_output(const char *bin, const char *asc) {
    FILE *binf = fopen(bin, "rb");
    if (binf == NULL) {
        printf("Error opening %s for reading",bin);
        return 1;
    }

    FILE *ascf = fopen(asc, "w");
    if (asc == NULL) {
        printf("Error opening %s for writing",asc);
        fclose(ascf);
        return 1;
    }

    int byte;
    while ((byte = fgetc(binf)) != EOF) {
        fprintf(ascf, "%02X ", byte);
    }

    fclose(binf);
    fclose(ascf);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <bin> <asc>\n", argv[0]);
        return 1;
    }

    const char *bin = argv[1];
    const char *asc = argv[2];

    printf("Converting bin to asc...\n");

    if (input_to_output(bin, asc) != 0) {
        return 1;
    }

    printf("Conversion of %s to %s successful.\n", bin,asc);

    return 0;
}

