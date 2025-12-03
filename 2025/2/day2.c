/*
 * Turns out linked lists are kinda useful for returning sequences of 
 * indeterminate length!
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct id {
	char value[64];
	struct id* next;
};

struct range {
	long start;
	long end;
};

struct id* load_input(void) 
{
	FILE* input = fopen("input", "r");

	if (input == NULL) {
		return NULL;
	}

	// Get file size for buffers
	fseek(input, 0, SEEK_END);
	long size = ftell(input);
	fseek(input, 0, SEEK_SET);

	char input_str[size];
	char policy_acc[size];
	
	struct id* id_ptr = NULL;
	struct id* head = NULL;
	
	int policy_idx = 0;

	fgets(input_str, size, input);
	fclose(input);

	for (int i = 0; i < size; i++) {
		if (input_str[i] == ',' || input_str[i] == '\0') {
			policy_acc[policy_idx++] = '\0';

			struct id* new = (struct id*) malloc(sizeof(struct id));
			new->next = NULL;
			
			strcpy(new->value, policy_acc); 

			if (id_ptr == NULL) {
				id_ptr = head = new;	
			} else {
				id_ptr->next = new;
				id_ptr = id_ptr->next;
			}

			memset(policy_acc, '\0', size);

			policy_idx = 0;
		} else {
			policy_acc[policy_idx++] = input_str[i];
		}
	}

	return head;
}

struct range* get_range(struct id* input)
{
	struct range* out = (struct range*) malloc(sizeof(struct range));

	char * low = strtok(input->value, "-");
	char * high = strtok(NULL, "-");

	out->start = atol(low);
	out->end = atol(high);

	return out;
}

char* to_string(long number)
{
	char* out = (char*) malloc(16);
	sprintf(out, "%ld", number);
	return out;
}

int is_valid(char* in)
{
	if (strlen(in) % 2 != 0) {
		return 1;
	} else {
		int half = strlen(in) / 2;
		for (int i = 0; i < half; i++) {
			if (in[i] != in[half + i]) {
				return 1;
			}
		}

		return 0;
	}
}

int repeats(char* in, int div)
{
	// TODO
	return 0;
}

int is_valid_2(char* in)
{
	size_t in_length = strlen(in);
	if (in_length > 1) {
		for (int i = 1; i <= in_length/2; i++) {
			if (in_length % i == 0 && repeats(in, i)) {
				return 0;
			}
		}
	} 

	return 1;
}
    

int main(void)
{
	struct id* input = load_input();
	struct id* backup = input;

	long sum_invalid = 0;

	while (input != NULL) {
		struct range* r = get_range(input);
		for (long i = r->start; i <= r->end; i++) {
			char* str = to_string(i);

			if (!is_valid(str)) {
				sum_invalid += i;
			}

			free(str);
		}


		struct id* old = input;
		input = input->next;
		free(r);
		//free(old);
	}

	printf("Part 1: %ld\n", sum_invalid);

	input = backup;




}
