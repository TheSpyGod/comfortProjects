#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void splitString(const char string[]) {
    int length = strlen(string);
    int start = 0;
    int end;

    for (int i = 0; i <= length; i++) {
        if (string[i] == ' ' || string[i] == '\0') {
            end = i;
            for (int j = start; j < end; j++) {
                putchar(string[j]);
            }
            putchar('\n');
            start = i + 1;
        }
    }
}

double calc(char symbol, const char *num1, const char *num2) {
    int number1 = atoi(num1);
    int number2 = atoi(num2);
    double result;
    switch (symbol) {
        case '+': 
            result = number1 + number2;
            break;
        case '-': 
            result = number1 - number2;
            break;
        case '*': 
            result = number1 * number2;
            break;
        case '/': 
            result = (double)number1 / number2;
            break;
        default:
            printf("Invalid symbol\n");
            result = 0.0; // Default result in case of invalid symbol
    }

    return result;
}

int main() {
    char symbol;
    char string[100];
    char choice;
    char num1[20], num2[20];

    printf("\tProject Calculator\n");
 
    do {
    /*
    printf("Enter the first number: ");
    scanf("%s", num1);

    printf("Enter the second number: ");
    scanf("%s", num2);

    
     printf("Enter symbol (+, -, *, /): ");
    scanf(" %c", &symbol); // Note the space before %c to consume any leading whitespace
    */
    printf("Enter numeric expression: ");
    fgets(string, sizeof(string), stdin);
    splitString(string);
    sscanf(string, "%s %c %s", num1, &symbol, num2);
    double result = calc(symbol, num1, num2);
    printf("Result: %.2f\n", result);
    printf("Continue? q/Q");
    scanf(" %c", &choice);
    getchar();
    } while (choice != 'q' && choice != 'Q');
    return 0;
}

