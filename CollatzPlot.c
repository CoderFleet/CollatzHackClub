#include <stdio.h>
#include <stdlib.h>

void calculateHailstoneSequence(int startingNumber, int *stepCount) {
    FILE *fp = fopen("hailstone.dat", "w");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int currentNumber = startingNumber;
    *stepCount = 0;
    fprintf(fp, "# Step Value\n");
    fprintf(fp, "%d %d\n", *stepCount, currentNumber);
    while (currentNumber != 1) {
        (*stepCount)++;
        if (currentNumber % 2 == 0) {
            currentNumber = currentNumber / 2;
        } else {
            currentNumber = 3 * currentNumber + 1;
        }
        fprintf(fp, "%d %d\n", *stepCount, currentNumber);
    }

    fclose(fp);
}

void plotHailstoneSequence() {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        perror("Error opening pipe to gnuplot");
        exit(EXIT_FAILURE);
    }

    fprintf(gnuplotPipe, "set title 'Hailstone Sequence'\n");
    fprintf(gnuplotPipe, "set xlabel 'Steps'\n");
    fprintf(gnuplotPipe, "set ylabel 'Value'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set key left top\n");
    fprintf(gnuplotPipe, "plot 'hailstone.dat' using 1:2 with linespoints title 'Hailstone Sequence'\n");

    fclose(gnuplotPipe);
}

int main() {
    int startingNumber, stepCount;

    printf("Enter a starting number for the Hailstone Sequence: ");

    if (scanf("%d", &startingNumber) != 1 || startingNumber <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    calculateHailstoneSequence(startingNumber, &stepCount);

    plotHailstoneSequence();

    printf("It took %d steps for the number %d to reach 1.\n", stepCount, startingNumber);
    printf("Hailstone Sequence plotted successfully.\n");

    return 0;
}
