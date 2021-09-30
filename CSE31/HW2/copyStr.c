/* Write a C function named copyStrArray that, given an integer "count" and an array "strArray" that contains "count" strings, returns a pointer to a complete ("deep") copy of the array.
You may assume that there is sufficient free memory in which to build the copied structure. Make no assumptions about the size of a pointer or a char (ie 64-bits vs 32-bits machine). Include all necessary casts, and allocate only as much memory as necessary. You may use any function in the stdio, stdlib, or string libraries.   */

#include <stdio.h>
#include <string.h>

char* copyStrArray(int count, char* strArray) {
    size_t numChars = 0;

    //Find the number of characters
    for(int i = 0; i < count; i++) {
        numChars = numChars + strlen(strArray + numChars) + 1;
    }
    //Allocate the space for the copy
    char* arrayCopy = (char*) malloc((numChars) * sizeof(char));

    //Fill the copy
    for(int i = 0; i < numChars; i++) {
        *(arrayCopy + i) = *(strArray + i);
    }         
    return arrayCopy;
}

int main() {
    char* str1;
    char* str2;
    while (1) {
        printf ("str1 = ");
        if (!gets (str1)) {
            return 0;
        };
        str2 = copyStrArray(1, str1);
        printf ("The copy of str1 is %s.\n", str2);
    }
}

