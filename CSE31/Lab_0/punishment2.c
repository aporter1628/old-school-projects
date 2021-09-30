#include <stdio.h>
int main() {
	int num;
	printf("Enter the number of lines for the punishment: ");
	scanf("%d", &num);

	if(num <= 0) {
		printf("You entered an incorrect value for the number of lines!");
	}

	else {
		int typo;
		printf("Enter the line for which we want to make a typo: ");
		scanf("%d", &typo);

		if(typo <= 0 || typo > num) {
			printf("You entered an incorrect value for the line typo!");
		}

		else {
			for(int i = 0; i < num; i++) {
				if(i ==(typo-1)) {
					printf("C programming is the bet! ");
				}
				else {
					printf("C programming langauge is the best! ");
				}
			}
		}
	}
	printf("\n");
}
