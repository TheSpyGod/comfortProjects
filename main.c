#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
// ANSI escape code to reset text color
#define ANSI_COLOR_RESET   "\x1b[0m"

int splitString(const char* string) {
   int result = 0;
    int number = 0;
    char opp = '+';
    //Goes through string ignoring white space, checks if digit then adds to number temp.
    //Checks if symbol, chooses operation via switch, and modifies result.
    for (int i = 0; string[i] != '\0'; i++) {
      if (isdigit(string[i])) {
        number = number * 10 + (string[i] - '0');
      } else if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/') {
        switch(opp) {
                case '+':
                    result += number;
                    break;
                case '-':
                    result -= number;
                    break;
                case '*':
                    result *= number;
                    break;
                case '/':
                    result /= number;
                    break;
            }
        //Reset number temp, update Opperation
        number = 0;
        opp = string[i];
      }
   }
    //Last Opperation
   switch(opp) {
        case '+':
            result += number;
            break;
        case '-':
            result -= number;
            break;
        case '*':
            result *= number;
            break;
        case '/':
            result /= number;
            break;
    }
    
    return result;
}

int x1x2func(const char* string) {
    int result = 0;
    int try = 0;
    int number = 0;
    int num1 = 0, num2 = 0, num3 = 0;
    char operator = '+'; // Start with a default operator

    for (int i = 0; string[i] != '\0'; i++) {
        if (isdigit(string[i])) {
            number = number * 10 + (string[i] - '0');
        } else if (string[i] == '+' || string[i] == '-' || string[i] == '*') {
            switch (try) {
                case 0:
                    num1 = (operator == '+') ? (num1 + number) : (num1 - number);
                    break;
                case 1:
                    num2 = (operator == '+') ? (num2 + number) : (num2 - number);
                    break;
                case 2:
                    num3 = (operator == '+') ? (num3 + number) : (num3 - number);
                    break;
            }
            number = 0; // Reset the number for the next coefficient
            try++; // Increment try to track the number of coefficients found
            operator = string[i]; // Update the operator
        }
    }

    // Assign the last accumulated number to the third coefficient
    switch (try) {
        case 1:
            num2 = (operator == '+') ? (num2 + number) : (num2 - number);
            break;
        case 2:
            num3 = (operator == '+') ? (num3 + number) : (num3 - number);
            break;
    }

    // Print parsed coefficients for debugging
    printf("\t\ta: %d, b: %d, c: %d\n", num1, num2, num3);

    // If there are three coefficients, calculate result
    if (try == 2) {
        result = (num2 * num2) - (4 * num1 * num3);
    } else {
        printf("\t\tInvalid input\n");
    }

    return result;
}

int main() {
    char string[100];
    int result = 0;
    char choice;
    char func;

    printf("\t\tProject Calculator\n");

    do {
        printf("\tEnter operation (c for Calculator, f for custom function): ");
        scanf(" %c", &func);
        getchar(); // consume newline left in buffer

        if (func == 'c') {
            printf("\tEnter numeric expression: ");
            fgets(string, sizeof(string), stdin);
            result = splitString(string);
            printf("\t\tResult: ");
            printf(ANSI_COLOR_GREEN"%d\n" ANSI_COLOR_RESET, result);
            getchar();
        } else if (func == 'f') {
            printf("\tEnter numeric expression: ");
            fgets(string, sizeof(string), stdin);
            result = x1x2func(string);
            printf("\t\tResult: ");
            printf(ANSI_COLOR_GREEN"%d\n"ANSI_COLOR_RESET, result);
        } else {
            printf("\t\tInvalid operation\n");
        }

        printf("\tContinue? (q/Q to quit): ");
        scanf(" %c", &choice);
        getchar(); // consume newline left in buffer
    } while (choice != 'q' && choice != 'Q');

    return 0;
}
