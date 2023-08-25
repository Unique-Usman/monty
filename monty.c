#include "monty.h"

int arg = 0;
void interpret_code(string_t **string_head)
{
	instruction_t instruction_table[] = {
		{"push", opcode_push},
		{"pall", opcode_pall},
		{"pint", opcode_pint},
		{"pop", opcode_pop},
		{"swap", opcode_swap},
		{"add", opcode_add},
		{"sub", opcode_sub},
		{NULL, NULL}
	};
	stack_t *stack;
	string_t *temp;
	char opcode[100];
	int i, ret_scan;
	unsigned int line_number;
	temp = *string_head;
	line_number = 1;
	stack = NULL;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	while (temp != NULL)
	{
		ret_scan = sscanf(temp->content, "%s %d", opcode, &arg);
		if (ret_scan == 1)
		{
			if (strcmp(opcode, "push") == 0)
			{
				printf("L%d: usage: push integer", line_number);
				exit(EXIT_FAILURE);
			}
		}

		opcode[4] = '\0';
		for (i = 0; instruction_table[i].opcode != NULL; i++)
		{
			if (strcmp(instruction_table[i].opcode, opcode) == 0)
			{
				instruction_table[i].f(&stack, line_number);
				break;
			}
		}
		line_number++;
		temp = temp->prev;
	}
}

int main(int argc, char **args)
{
	FILE *file;
	char err[1024];

	string_t *head;

	if (!verify(argc))
	{
		printf("%s", "USAGE: monty file");
		exit(EXIT_FAILURE);
	}
	file = fopen(args[1], "r");
	if (file == NULL)
	{
		strcpy(err, "Error: Can't open file ");
		strcat(err, args[1]);
		printf("%s", err);
		exit(EXIT_FAILURE);
	}
	read_file(&head, file);
	fclose(file);

	interpret_code(&head);

	return (0);
}
