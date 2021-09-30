#include <stdio.h>
int main() {
	int num;
	printf("Enter the number of lines for the punishment: ");
	scanf("%d", &num);

	if(num <= 0) {
		printf("You entered an incorrect value for the number of lines!");
	}

	else {
		for(int i = 0; i < num; i++) {
			printf("C programming language is the best! ");
		}
	}
	printf("\n");
}
