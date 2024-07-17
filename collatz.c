#include <stdio.h>

int calculateCollatzSequence(int startingNumber) {
    int steps = 0;
    printf("Starting number: %d\n", startingNumber);
    
    int currentNumber = startingNumber;
    while (currentNumber != 1) {
        printf("%d -> ", currentNumber);
        
        if (currentNumber % 2 == 0) {
            currentNumber = currentNumber / 2;
        } else {
            currentNumber = 3 * currentNumber + 1;
        }
        
        steps++;
    }
    
    printf("1\n");
    return steps;
}

int main() {
    int startingNumber;
    int repeat = 1;
    
    while (repeat) {
        printf("Enter a starting number for the Collatz Conjecture (0 to quit): ");
        scanf("%d", &startingNumber);

        if (startingNumber == 0) {
            repeat = 0;
            continue;
        }

        int numberOfSteps = calculateCollatzSequence(startingNumber);
        printf("Number of steps to reach 1: %d\n", numberOfSteps);
    }

    printf("Exiting the program.\n");

    return 0;
}
