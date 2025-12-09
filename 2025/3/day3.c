#include <stdio.h>

#define BANK_LENGTH 102 // Including the newline and null

int digits_to_int(char first, char last)
{
	return ((first - '0') * 10) + (last - '0');
}


int max_joltage(char* in)
{
	int max = 0;

	for (int i = 0; i < BANK_LENGTH - 2; i++) {
		for (int j = i + 1; j < BANK_LENGTH - 1; j++) {
			int num = digits_to_int(in[i], in[j]);
			if (max < num) {
				max = num;
			}
		}
	}

	return max;
}

int main(void)
{
	FILE* input_file = fopen("input", "r"); 
	char bank[BANK_LENGTH];

	int sum;

	if (input_file == NULL) {
		printf("Failed to read input file\n");
		return 1;
	}


	while (fgets(bank, BANK_LENGTH, input_file) != NULL) {
		sum += max_joltage(bank);
	}

	printf("%d\n", sum);
	
	return 0;
}
