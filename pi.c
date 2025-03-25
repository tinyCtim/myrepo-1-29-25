#include <stdio.h>
#include <string.h>

#define MAX_SIZE 2050  // Maximum array size to accommodate up to 2000 digits + extra precision

// Enum for array indices
enum { PW = 0, TR = 1, RESULT = 2 };

// Global array to store digits: ar[column][place], where place 1 is units, 2 onwards are decimals
int ar[3][MAX_SIZE];
int size;  // Global variable for array size (digits + 5)

// Function to divide an array by a divisor, updating it in place
void divide(int array_index, int dv, int *zero) {
    int digit = 0;
    *zero = 0;  // Flag to indicate if the result is non-zero
    for (int place = 1; place <= size; place++) {
        digit += ar[array_index][place];
        int quotient = digit / dv;
        int residue = digit - quotient * dv;
        ar[array_index][place] = quotient;
        digit = 10 * residue;  // Base 10 for next digit
        if (quotient != 0 || residue != 0) *zero = 1;  // Set if term is significant
    }
}

// Function to add TR array to RESULT array
void add() {
    int carry = 0;
    for (int place = size; place >= 0; place--) {
        int sum = ar[RESULT][place] + ar[TR][place] + carry;
        carry = 0;
        if (sum >= 10) {
            sum -= 10;
            carry = 1;
        }
        ar[RESULT][place] = sum;
    }
}

// Function to subtract TR array from RESULT array
void subtract() {
    int borrow = 0;
    for (int place = size; place >= 0; place--) {
        int diff = ar[RESULT][place] - ar[TR][place] - borrow;
        borrow = 0;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        ar[RESULT][place] = diff;
    }
}

// Function to copy one array to another
void copy(int from, int to) {
    for (int place = 0; place <= size; place++) {
        ar[to][place] = ar[from][place];
    }
}

int main() {
    // Introductory messages
    printf("Pi Version 3.14\n");
    printf("This program computes the value of pi to up to 2000 places.\n");

    // Get number of digits from user
    int digits;
    printf("How many digits do you want (less than 2000)? ");
    scanf("%d", &digits);
    size = digits + 5;  // Add 5 extra digits for precision

    // Initialize arrays to zero
    memset(ar, 0, sizeof(ar));

    // Constants for division: 25 = 5^2, 239 = 239^1 (used with additional division)
    int knst[2] = {25, 239};

    // Two passes: one for each sum
    for (int pass = 1; pass <= 2; pass++) {
        // Initialization for each pass
        if (pass == 2) {
            // Clear PW and TR arrays for second pass
            for (int place = 0; place <= size; place++) {
                ar[PW][place] = 0;
                ar[TR][place] = 0;
            }
        }
        // Set initial term: 16 for pass 1, 4 for pass 2
        ar[PW][1] = 16 / (pass * pass);
        int dv = (pass == 1) ? 5 : 239;  // Initial divisor: 5 or 239
        int zero;  // Flag for term significance
        divide(PW, dv, &zero);

        int ex = 1;              // Exponent starts at 1 (for 2*k-1)
        int sn = 3 - 2 * pass;  // Sign: 1 for pass 1, -1 for pass 2

        printf("Starting pass %d.\n", pass);

        // Compute terms until they become insignificant
        do {
            copy(PW, TR);          // Copy current power to term
            divide(TR, ex, &zero); // Divide term by (2*k-1)
            if (sn > 0) {
                add();             // Add term to result
            } else {
                subtract();        // Subtract term from result
            }
            ex += 2;               // Next odd number for (2*k-1)
            sn = -sn;              // Alternate sign
            divide(PW, knst[pass - 1], &zero);  // Divide power by 25 or 239
            if (pass == 2) {
                divide(PW, 239, &zero);  // Extra division by 239 for pass 2
            }
            printf(".");  // Progress indicator
        } while (zero);   // Continue while term is non-zero
        printf("\n");
    }

    // Print the result
    printf("Done.\n");
    printf("Pi to %d decimal places is:\n", digits);
    printf("%d.", ar[RESULT][1]);  // Units digit
    int count = 0;
    for (int place = 2; place <= size - 5; place++) {
        printf("%d", ar[RESULT][place]);  // Decimal digits
        count++;
        if (count % 80 == 0) {  // New line every 80 digits
            printf("\n");
        }
    }
    printf("\n");

    return 0;
}

