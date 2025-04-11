
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Converts an input file to an output file
int input_to_output(const char *input, const char *output) {
    FILE *inputf = fopen(input, "rb");
    if (inputf == NULL) {
        perror("Error opening input for reading");
        return 1;
    }

    FILE *outputf = fopen(output, "w");
    if (outputf == NULL) {
        perror("Error opening output for writing");
        fclose(outputf);
        return 1;
    }

    int byte;
    while ((byte = fgetc(inputf)) != EOF) {
        fprintf(outputf, "%02X ", byte);
    }

    fclose(inputf);
    fclose(outputf);
    return 0;
}

// Converts output back to input
int output_to_input(const char *output, const char *reconstructed) {
    FILE *outputf = fopen(output, "r");
    if (outputf == NULL) {
        perror("Error opening input for reading");
        return 1;
    }

    FILE *inputf = fopen(reconstructed, "wb");
    if (inputf == NULL) {
        perror("Error opening output for writing");
        fclose(inputf);
        return 1;
    }

    int byte1, byte2;
    while (fscanf(outputf, "%2x ", &byte1) == 1) {
        fputc(byte1, inputf);
    }

    fclose(outputf);
    fclose(inputf);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input> <output> <reconstructed>\n", argv[0]);
        return 1;
    }

    const char *input = argv[1];
    const char *output = argv[2];
    const char *reconstructed = argv[3];

    printf("Converting input to output...\n");
    if (input_to_output(input, output) != 0) {
        return 1;
    }
    printf("Conversion successful. output in %s\n", output);

    printf("Converting output back to input ...\n");
    if (output_to_input(output, reconstructed) != 0) {
        return 1;
    }
    printf("Conversion successful. input reconstructed in %s\n", reconstructed);

    return 0;
}

