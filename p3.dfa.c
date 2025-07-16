#include <stdio.h>
#include <string.h>

// Automaton using else-if ladder for accepting "abb"
int main() {
    char input[100];
    int state = 0, i = 0;

    printf("Enter a string: ");
    scanf("%s", input);

    while (input[i] != '\0') {
        if (state == 0 && input[i] == 'a') {
            state = 1;
        } 
        else if (state == 1 && input[i] == 'b') {
            state = 2;
        } 
        else if (state == 2 && input[i] == 'b') {
            state = 3;
        } 
        else {
            // Invalid character or unexpected input
            state = -1;
            break;
        }
        i++;
    }

    // Final state must be 3 for valid "abb"
    if (state == 3 && input[i] == '\0') {
        printf("String ACCEPTED by automaton.\n");
    } else {
        printf("String REJECTED by automaton.\n");
    }

    return 0;
}
