#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void plotHailstoneSequence(int saveAsImage) {
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
    if (saveAsImage) {
        fprintf(gnuplotPipe, "set terminal png\n");
        fprintf(gnuplotPipe, "set output 'hailstone.png'\n");
    }
    fprintf(gnuplotPipe, "plot 'hailstone.dat' using 1:2 with linespoints title 'Hailstone Sequence'\n");

    fclose(gnuplotPipe);
}

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Generate a new hailstone sequence plot\n");
    printf("2. Save the current plot as a PNG image\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int startingNumber, stepCount, choice;

    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter a starting number for the Hailstone Sequence: ");
                if (scanf("%d", &startingNumber) != 1 || startingNumber <= 0) {
                    printf("Wrong input. Please enter a positive integer.\n");
                    while (getchar() != '\n');
                    continue;
                }

                calculateHailstoneSequence(startingNumber, &stepCount);
                plotHailstoneSequence(0);
                printf("It took %d steps for the number %d to reach 1.\n", stepCount, startingNumber);
                printf("Hailstone Sequence plotted successfully.\n");
                break;

            case 2:
                plotHailstoneSequence(1);
                printf("Hailstone Sequence plot saved as 'hailstone.png'.\n");
                break;

            case 3:
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
                break;
        }
    }

    return 0;
}
