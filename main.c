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

int main() {
    char string[100];
    char choice;

    printf("\tProject Calculator\n");
 
    do {
    printf("\tEnter numeric expression: ");
    fgets(string, sizeof(string), stdin);
    int result = splitString(string);
    printf("\tResult: ");
    printf(ANSI_COLOR_GREEN " %.2d\n" ANSI_COLOR_RESET,result);
    printf("Continue? q/Q");
    scanf(" %c", &choice);
    getchar();
    } while (choice != 'q' && choice != 'Q');
    return 0;
}

