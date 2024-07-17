#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 100

void calculateHailstoneSequence(int startingNumber, int *stepCount, const char *filename) {
    FILE *fp = fopen(filename, "w");
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

void plotHailstoneSequences(int numSequences, int *startingNumbers) {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        perror("Error opening pipe to gnuplot");
        exit(EXIT_FAILURE);
    }

    fprintf(gnuplotPipe, "set title 'Hailstone Sequences'\n");
    fprintf(gnuplotPipe, "set xlabel 'Steps'\n");
    fprintf(gnuplotPipe, "set ylabel 'Value'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set key left top\n");

    for (int i = 0; i < numSequences; i++) {
        char filename[50];
        sprintf(filename, "hailstone_%d.dat", startingNumbers[i]);
        int stepCount;
        calculateHailstoneSequence(startingNumbers[i], &stepCount, filename);
        if (i == 0) {
            fprintf(gnuplotPipe, "plot '%s' using 1:2 with linespoints title 'Start=%d'", filename, startingNumbers[i]);
        } else {
            fprintf(gnuplotPipe, ", '%s' using 1:2 with linespoints title 'Start=%d'", filename, startingNumbers[i]);
        }
    }
    fprintf(gnuplotPipe, "\n");
    fclose(gnuplotPipe);
}

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Generate new hailstone sequences plot\n");
    printf("2. Save the current plot as a PNG image\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int startingNumbers[MAX_NUMBERS];
    int numSequences, choice;

    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter the number of sequences you want to plot: ");
                if (scanf("%d", &numSequences) != 1 || numSequences <= 0 || numSequences > MAX_NUMBERS) {
                    printf("Invalid input. Please enter a positive number up to %d.\n", MAX_NUMBERS);
                    while (getchar() != '\n');
                    continue;
                }
                for (int i = 0; i < numSequences; i++) {
                    printf("Enter starting number %d: ", i + 1);
                    if (scanf("%d", &startingNumbers[i]) != 1 || startingNumbers[i] <= 0) {
                        printf("Invalid input. Please enter a positive integer.\n");
                        while (getchar() != '\n');
                        i--;
                        continue;
                    }
                }
                plotHailstoneSequences(numSequences, startingNumbers);
                printf("Hailstone Sequences plotted successfully.\n");
                break;

            case 2:
                plotHailstoneSequences(numSequences, startingNumbers);
                FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
                if (gnuplotPipe == NULL) {
                    perror("Error opening pipe to gnuplot");
                    exit(EXIT_FAILURE);
                }
                fprintf(gnuplotPipe, "set terminal png\n");
                fprintf(gnuplotPipe, "set output 'hailstone_sequences.png'\n");
                fprintf(gnuplotPipe, "set title 'Hailstone Sequences'\n");
                fprintf(gnuplotPipe, "set xlabel 'Steps'\n");
                fprintf(gnuplotPipe, "set ylabel 'Value'\n");
                fprintf(gnuplotPipe, "set grid\n");
                fprintf(gnuplotPipe, "set key left top\n");

                for (int i = 0; i < numSequences; i++) {
                    char filename[50];
                    sprintf(filename, "hailstone_%d.dat", startingNumbers[i]);
                    if (i == 0) {
                        fprintf(gnuplotPipe, "plot '%s' using 1:2 with linespoints title 'Start=%d'", filename, startingNumbers[i]);
                    } else {
                        fprintf(gnuplotPipe, ", '%s' using 1:2 with linespoints title 'Start=%d'", filename, startingNumbers[i]);
                    }
                }
                fprintf(gnuplotPipe, "\n");
                fclose(gnuplotPipe);
                printf("Hailstone Sequence plot saved as 'hailstone_sequences.png'.\n");
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
