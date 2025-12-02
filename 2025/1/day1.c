#include <stdio.h>
#include <stdlib.h>

typedef enum {
	LEFT,
	RIGHT
} Direction;

typedef struct instruction {
	Direction dir;
	int magnitude;
	struct instruction* next;
} cmd_t;

cmd_t* load_input() {
	FILE* input_file = fopen("input", "r");

	if (input_file == NULL) {
		return NULL;
	}

	cmd_t* first;
	cmd_t* inst = NULL;
	char line[8];

	while (fgets(line, 8, input_file) != NULL) {
		cmd_t* new_inst = (cmd_t*) malloc(sizeof(cmd_t));

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

	return first;
}

unsigned int turn_dial(unsigned int dial, Direction dir) {
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

int main() {
	cmd_t* input = load_input();

	unsigned int dial = 50;
	unsigned int zero_count = 0;

	while (input != NULL) {
		for (int i = 0; i < input->magnitude; i++) {
			dial = turn_dial(dial, input->dir);
		}

		if (dial == 0) {
			zero_count++;
		}

		cmd_t* old = input;
		input = input->next;
		free(old);
	}

	printf("%d\n", zero_count);
}
