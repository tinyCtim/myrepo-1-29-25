
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// ChatGPT generated the original
// 4/11/25 - lrb

// Converts an ascii file back to a binary file
int output_to_input(const char *asc, const char *bin) {
    FILE *ascf = fopen(asc, "r");
    if (ascf == NULL) {
        printf("Error opening %s for reading",asc);
        return 1;
    }

    FILE *binf = fopen(bin,"wb");
    if (binf == NULL) {
        printf("Error opening %s for writing",bin);
        fclose(binf);
        return 1;
    }

    int byte1;
    while (fscanf(ascf, "%2x ", &byte1) == 1) {
        fputc(byte1, binf);
    }

    fclose(ascf);
    fclose(binf);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <asc> <bin>\n", argv[0]);
        return 1;
    }

    const char *asc = argv[1];
    const char *bin = argv[2];

    printf("Converting asc to bin...\n");

    if (output_to_input(asc, bin) != 0) {
        return 1;
    }

    printf("Conversion of %s to %s successful.\n", asc,bin);

    return 0;
}

