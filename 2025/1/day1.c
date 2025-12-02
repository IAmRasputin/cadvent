#include <stdio.h>
#include <stdlib.h>

enum Direction {
	LEFT,
	RIGHT
};

struct cmd {
	enum Direction dir;
	int magnitude;
	struct cmd* next;
};

struct cmd* load_input() 
{
	FILE* input_file = fopen("input", "r");

	if (input_file == NULL) {
		return NULL;
	}

	struct cmd* first;
	struct cmd* inst = NULL;
	size_t size = sizeof(struct cmd);
	char line[8];

	while (fgets(line, 8, input_file) != NULL) {
		struct cmd* new_inst = (struct cmd*) malloc(sizeof(struct cmd));

		switch (line[0]) {
			case 'R':
				new_inst->dir = RIGHT;
				break;
			case 'L':
				new_inst->dir = LEFT;
				break;
			default:
				printf("input read error\n");
				return NULL;
		}

		new_inst->magnitude = atoi(line + sizeof(char));

		if (inst == NULL) {
			first = new_inst;
			inst = new_inst;
		} else {
			inst->next = new_inst;
			inst = new_inst;
		}
	}

	fclose(input_file);

	return first;
}

unsigned int turn_dial(unsigned int dial, enum Direction dir) 
{
	switch (dir) {
		case LEFT:
			if (dial == 0) {
				return 99;
			} else {
				return dial - 1;
			}
			break; // paranoid
		case RIGHT:
			if (dial == 99) {
				return 0;
			} else {
				return dial + 1;
			}
			break;
		default:
			printf("something is wrong here\n");
			exit(1);
	}
}

int main() 
{
	struct cmd* input = load_input();
	struct cmd* first = input;

	unsigned int dial = 50;
	unsigned int zero_count = 0;

	while (input != NULL) {
		for (int i = 0; i < input->magnitude; i++) {
			dial = turn_dial(dial, input->dir);
		}

		if (dial == 0) {
			zero_count++;
		}

		struct cmd* old = input;
		input = input->next;
	}

	printf("part 1: %d\n", zero_count);

	input = first; 
	dial = 50;
	zero_count = 0;

	while (input != NULL) {
		for (int i = 0; i < input->magnitude; i++) {
			dial = turn_dial(dial, input->dir);

			if (dial == 0) {
				zero_count++;
			}
		}

		struct cmd* old = input;
		input = input->next;
		free(old);
	}

	printf("part 2: %d\n", zero_count);
}
