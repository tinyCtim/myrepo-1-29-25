#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_POINTS 6
#define TRIALS 1

// Generate random coordinate in range [0,9]
int rand_coord() {
    return rand() % 10;
}

// Compute Euclidean distance between two points
double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    double total_length_sum = 0.0;

    FILE *fp = fopen("pairs.txt","w");

    for (int t = 0; t < TRIALS; t++) {
        printf("\n"); 
        int x[NUM_POINTS];
        int y[NUM_POINTS];

        // Generate random coordinates
        for (int i = 0; i < NUM_POINTS; i++) {
            x[i] = rand_coord();
            y[i] = rand_coord();
            printf("\n%d %d",x[i],y[i]);
            fprintf(fp,"%d,%d\n",x[i],y[i]);
        }
        printf("\n");
        // Compute total length for this trial
        double length = 0.0;
        for (int i = 0; i < NUM_POINTS - 1; i++) {
            length += distance(x[i], y[i], x[i+1], y[i+1]);
        }

        printf("\nTrial %d: length = %.2f", t , length);
        total_length_sum += length;
    }

    double average_length = total_length_sum / TRIALS;
    printf("\n\nAverage length over %d trials: %.2f\n", TRIALS, average_length);

    return 0;
}
