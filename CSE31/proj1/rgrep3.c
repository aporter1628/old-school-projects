#include <stdio.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
    int count;
    int count2;
    while(*(pattern) != '\0' && *(partial_line) != '\0') {
        /*-----------------Backslash wildcard------------------*/
        if(*(pattern) == '\\') {
            //If there is a plus after the character after the backslash
            if(*(pattern + 2) == '+') {
                if(*(pattern + 1) != *(partial_line)) {
                    return 0;
                }
                else {
                    //The number of characters that match the one before the plus in the partial line must be counted so they can be bypassed
                    count = 0;
                    while(*(pattern + 1) == *(partial_line + count)) {
                        count++;
                    }
                    //If there is another backslash after the plus, the character after it might be the same as the one before the plus: check for both
                    if(*(pattern + 3) == *(pattern) && *(pattern + 1) == *(pattern + 4)) {
                        //There may be multiple so count them
                        count2 = 0;
                        for(int i = 0; *(pattern + 3 + i) == *(pattern); i+=2) {
                            if(*(pattern + i + 4) == *(pattern + 1)) {
                                count2++;
                            }
                            else {
                                break;
                            }
                        }
                        if(count < (count2 + 1)) {
                            return 0;
                        }
                        else {
                            count = count - count2;
                            pattern += 3;
                            partial_line += count;
                        }
                    }
                    else {
                        pattern += 3;
                        partial_line += count;
                    }
                }
            }
            //If there's a question mark after the character after the backslash
            else if(*(pattern + 2) == '?') {
                if(*(partial_line) == *(pattern + 1)) {
                    partial_line++;
                    pattern += 3; //Bypasses backslash, character and question mark
                }
                else {
                    pattern += 3;
                }
            }
            //If there's no wildcard two away from the backslash
            else {
                if(*(partial_line) == *(pattern + 1)) {
                    //Moves partial_line up one to keep checking from the next character and the pattern up two to bypass the character after the backslash
                    partial_line++;
                    pattern += 2; 
                }
                else
                    return 0;
            }
        }

        /*---------------------Period Wildcard------------------*/
        else if(*(pattern) == '.'){
            //If there's a plus after the period
            if(*(pattern + 1) == '+') {
                //Anything will work at this point, return 1
                return 1;
            }
            //If there's a question mark after the period
            else if(*(pattern + 1) == '?') {
                //If the next character in the pattern is the same as the one we're looking at
                if(*(pattern + 2) == *(partial_line)) {
                    pattern += 2;
                }
                else {
                    partial_line++;
                    pattern += 2; //Bypass the period and the question mark
                }
            }
            //There's no wildcard after the period
            else {
                partial_line++; //Any character will work
                pattern++;
            }
        }

        //If the next character in the pattern is some other character
        else {
            /*----------------Plus Wildcard-----------------*/
            if(*(pattern + 1) == '+') {
                //If there is a question mark after the plus
                if(*(pattern + 2) == '?') {
                    if(*(pattern) != *(partial_line)) {
                        pattern += 3;
                    }
                    else {
                        //The number of characters before the plus in the partial line must be counted so they can be bypassed
                        count = 0;
                        while(*(pattern) == *(partial_line + count)) {
                            count++;
                        }
                        //If the character in the pattern after the plus and question mark is the same as the one before the plus
                        if(*(pattern + 3) == *(pattern)) {
                            //There may be multiple so count them
                            count2 = 0;
                            while(*(pattern + 3 + count2) == *(pattern)) {
                                count2++;
                            }
                            //If the number of plus-characters in the partial line is less than the number of those characters after the plus (count2) plus 1, 
                            //there aren't enough of those plus-characters in the partial line
                            if(count < (count2 + 1)) {
                                return 0;
                            }
                            else {
                                count = count - count2;
                                pattern += 3;
                                partial_line += count;
                            }
                        }   
                        else {
                            pattern += 3;
                            partial_line += count;
                        }
                    }
                }
                //There is no wildcard after the plus
                else {
                    if(*(pattern) != *(partial_line)) {
                        return 0;
                    }
                    else {
                        //The number of characters before the plus in the partial line must be counted so they can be bypassed
                        count = 0;
                        while(*(pattern) == *(partial_line + count)) {
                            count++;
                        }
                        //If the character in the pattern after the plus is the same as the one before the plus
                        if(*(pattern + 2) == *(pattern)) {
                            //There may be multiple so count them
                            count2 = 0;
                            while(*(pattern + 2 + count2) == *(pattern)) {
                                count2++;
                            }
                            //If the number of plus-characters in the partial line is less than the number of those characters after the plus (count2) plus 1, 
                            //there aren't enough of those plus-characters in the partial line
                            if(count < (count2 + 1)) {
                                return 0;
                            }
                            else {
                                count = count - count2;
                                pattern += 2;
                                partial_line += count;
                            }
                        }   
                        else {
                            pattern += 2;
                            partial_line += count;
                        }
                    }
                }
            }
            /*-----------------Question Mark Wildcard-----------------*/
            else if(*(pattern + 1) == '?') {
                //If there's a plus after the question mark
                if(*(pattern + 2) == '+') {
                    if(*(pattern) != *(partial_line)) {
                        pattern += 3;
                    }
                    else {
                        //The number of characters before the plus in the partial line must be counted so they can be bypassed
                        count = 0;
                        while(*(pattern) == *(partial_line + count)) {
                            count++;
                        }
                        //If the character in the pattern after the question mark and plus is the same as the one before the question mark
                        if(*(pattern + 3) == *(pattern)) {
                            //There may be multiple so count them
                            count2 = 0;
                            while(*(pattern + 3 + count2) == *(pattern)) {
                                count2++;
                            }
                            //If the number of plus-characters in the partial line is less than the number of those characters after the plus (count2) plus 1, 
                            //there aren't enough of those plus-characters in the partial line
                            if(count < (count2 + 1)) {
                                return 0;
                            }
                            else {
                                count = count - count2;
                                pattern += 3;
                                partial_line += count;
                            }
                        }   
                        else {
                            pattern += 3;
                            partial_line += count;
                        }
                    }
                }
                //There's no wildcard after the question mark
                else {
                //If the character before the question mark is there, keep looking from the next part of partial line and move the pattern pointer up two
                if(*(partial_line) == *(pattern)) {
                    partial_line++;
                    pattern += 2; 
                }
                //If it's not there it's fine, just move the pattern pointer up two to keep looking for the next part of the pattern
                else
                    pattern += 2;
            }
            }
            /*-----------------No Wildcard (regular search) --------------*/
            else {
                if(*(partial_line) == *(pattern)) {
                    //Moves partial_line and pattern pointers up one so we can compare the next part of the pattern with the next part of the partial line
                    partial_line++;
                    pattern++; 
                }
                else
                    return 0;
            }
        }
    }
    //If we've reached the end of partial_line but the entire pattern hasn't been found yet, the pattern can't be in the line
    if(*(pattern) != '\0' && *(partial_line) == '\0') { 
        return 0;
    }
    
    //If the function hasn't returned 0 yet then the pattern must be there
    return 1;
        
}

/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
    int check;
    for(int i = 0; *(line+i) != '\0'; i++) {
        //If the first character in the pattern is a backslash, it looks for the first occurrence of the character after it
        if(*pattern == '\\') { 
            //If there is a question mark after the character after the backslash, look for the next character in the pattern that doesn't have a question mark
            //after it
            //if(*(pattern + 2) == '?') {
                
            if(*(line + i) == *(pattern+1)) {
                check = matches_leading((line + i), pattern);
                if(check == 1)
                    return 1;
            }
        }
        //If the first character in the pattern is a period, check every character
        else if(*(pattern) == '.') {
            check = matches_leading((line + i), pattern);
            if(check == 1)
                return 1;

        }
        //If the second character in the pattern is a question mark, the character doesn't necessarily need to be there
        else if(*(pattern + 1) == '?') {
            if(*(pattern + 2) == '+') {
                pattern += 3; //Just go past them so they don't have to be dealt with
            }
            else {
            //There may be multiple question marks, so keep looking until you find a character that doesn't have a question mark after it
            int j;
            for(j = 0; *(pattern + j) != '\0'; j+=2) {
                if(*(pattern + j + 1) != '?') {
                    break;
                }
            }
            //If pattern is NULL, there was nothing without a question mark after it, so everything will work
            if(*(pattern + j) == '\0') {
                return 1;
            }
            //If not check if the current character in the line is the same as the character without a plus before it
            if(*(line + i) == *(pattern + j)) {
                check = matches_leading((line + i), (pattern + j)); 
                if(check == 1)
                    return 1;
            } 
            }
        }
        //If the first character isn't a backslash or a period, look for the first occurrence of it in the line
        else {
            //If the first part of the pattern has a '+?' just move past it
            if(*(pattern + 1) == '+' && *(pattern + 2) == '?') { 
                pattern += 3;
            }
            else if(*(line + i) == *(pattern)) {
                check = matches_leading((line + i), pattern);
                if(check == 1)
                    return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
