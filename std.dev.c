
/*
C program to input real numbers and find the mean, variance and standard
deviation
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 1000

// execute ./st.dev -i file

int main(int argc, char *argv[])
{
    printf("\nstd.dev.c - 5/31/24 - lrb\n\n");
    double x[MAXSIZE];
    int  i, n;
    double average, variance, std_deviation, sum = 0, sum1 = 0;
    FILE *fp;
    if (argc==1) {printf("\nUsage ./std.dev -i file\n");exit(1);}
    fp=fopen(argv[2],"r");
    if (fp==NULL) {printf("\ncan't open input file\n");exit(1);}
    fscanf(fp,"%d", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(fp,"%lf", &x[i]);
    }
    /*  Compute the sum of all elements */
    for (i = 0; i < n; i++)
    {
        sum += x[i];
    }
    average = sum / (double)n;
    /*  Compute the variance and the standard deviation  */
    for (i = 0; i < n; i++)
    {
        sum1 += pow(x[i] - average, 2);
    }
    variance = sum1 / (double)n;
    std_deviation = sqrt(variance);
    printf("Average of all elements = %.5lf\n", average);
    printf("Variance of all elements = %.5lf\n", variance);
    printf("Standard deviation = %.5lf\n", std_deviation);
    fclose(fp);
    return 0;
}

