/*The following function should allocate space for a new string, copy the string from the passed argument into the new string, and convert every lower-case character in the new string into an upper-case character (do not modify the original string). Fill-in the blanks and the body of the for() loop:   */
#include <stdio.h>
#include <string.h>

char* upcase(char* str) { 
 	char* p;  	 		
    char* result; 
 	result = (char*) malloc(sizeof(char) * strlen(str)); 
   	strcpy(result, str); 
  	for(p = result; *p!='\0'; p++) {  
    /* Fill-in 'A' = 65, 'a' = 97, 'Z' = 90 , 'z' = 122 */ 
        int ip = (int) *p;
		if(ip >= 97 && ip <= 122) {
            ip = ip - 32;
            *p = (char) ip;
        }
 	 } 
 	 return result; 
 } 
int main() {
    char* str1;
    char* str2;
    while (1) {
        printf ("str1 = ");
        if (!gets (str1)) {
            return 0;
        };
        str2 = upcase(str1);
        printf ("The uppercase of str1 is %s.\n", str2);
    }
}
    
