#include <stdio.h>
#include <string.h>

int main() {
    // Declare required strings to store parts of the production
    char gram[20];           // Input: the full production RHS, e.g. abcd|abxy
    char part1[20], part2[20]; // Two separate alternatives
    char modifiedGram[20];   // To hold the factored common part + new NT (e.g. aX)
    char newGram[20];        // To hold remaining suffixes (e.g. bcd|bxy)
    char tempGram[20];       // (Unused in this code)

    int i, j = 0, k = 0, l = 0, pos;

    // Input production rule (Only RHS part, assumes LHS is 'A->')
    printf("Enter Production : A->");
    gets(gram); // 👈 deprecated, use fgets() in modern code (but okay for now)

    // Step 1: Split into two parts using '|'
    for(i = 0; gram[i] != '|'; i++, j++) {
        part1[j] = gram[i];  // Copy everything before '|' to part1
    }
    part1[j] = '\0';         // Null-terminate part1

    for(j = ++i, i = 0; gram[j] != '\0'; j++, i++) {
        part2[i] = gram[j];  // Copy everything after '|' to part2
    }
    part2[i] = '\0';         // Null-terminate part2

    // Step 2: Find longest common prefix
    for(i = 0; i < strlen(part1) || i < strlen(part2); i++) {
        if(part1[i] == part2[i]) {
            modifiedGram[k++] = part1[i]; // Build the common prefix
            pos = i + 1;                  // Store next index after prefix
        }
    }

    // Step 3: Get remaining suffixes after the prefix in both parts
    for(i = pos, j = 0; part1[i] != '\0'; i++, j++) {
        newGram[j] = part1[i];  // Remaining part of first production
    }

    newGram[j++] = '|';         // Add separator between productions

    for(i = pos; part2[i] != '\0'; i++, j++) {
        newGram[j] = part2[i];  // Remaining part of second production
    }

    // Step 4: Finalize new grammar strings
    modifiedGram[k] = 'X';       // Add new non-terminal (assumes X is safe)
    modifiedGram[++k] = '\0';    // Null-terminate

    newGram[j] = '\0';           // Null-terminate

    // Step 5: Print result
    printf("\nGrammar Without Left Factoring : \n");
    printf(" A->%s", modifiedGram); // e.g. A->abX
    printf("\n X->%s\n", newGram);  // e.g. X->cd|xy

    return 0;
}
