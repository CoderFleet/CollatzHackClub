#include <stdio.h>
#include <stdlib.h>

void calculateHailstoneSequence(int startingNumber) {
    FILE *fp = fopen("hailstone.dat", "w");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int currentNumber = startingNumber;
    fprintf(fp, "%d\n", currentNumber);
    while (currentNumber != 1) {
        if (currentNumber % 2 == 0) {
            currentNumber = currentNumber / 2;
        } else {
            currentNumber = 3 * currentNumber + 1;
        }
        fprintf(fp, "%d\n", currentNumber);
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
    fprintf(gnuplotPipe, "plot 'hailstone.dat' with linespoints\n");

    fclose(gnuplotPipe);
}

int main() {
    int startingNumber;
    printf("Enter a starting number for the Hailstone Sequence: ");
    scanf("%d", &startingNumber);

    calculateHailstoneSequence(startingNumber);
    plotHailstoneSequence();

    printf("Hailstone Sequence plotted successfully.\n");

    return 0;
}
