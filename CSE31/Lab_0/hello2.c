#include <stdio.h>
int main() {
	char str1[20], str2[20];
	printf("Please enter your name: ");
	scanf("%[^\n]s", str1);

	printf("Welcome to CSE31, %s!\n", str1);
	return 0;
}

