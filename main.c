#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int splitString(const char* string) {
    /*int length = strlen(string);
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
    }*/
    int result = 0;
    int number = 0;
    char opp = '+';

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
        number = 0;
        opp = string[i];
      }
   }
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

int main() {
    char string[100];
    char choice;

    printf("\tProject Calculator\n");
 
    do {
    printf("Enter numeric expression: ");
    fgets(string, sizeof(string), stdin);
    int result = splitString(string);
    printf("Result: %.2d\n", result);
    printf("Continue? q/Q");
    scanf(" %c", &choice);
    getchar();
    } while (choice != 'q' && choice != 'Q');
    return 0;
}

