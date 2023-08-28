#include "monty.h"

int arg = 0;


/**
 * interpret_code - This is main function the execute the code
 * @string_head: Pointer to code string
 */
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
		{"div", opcode_div},
		{"mod", opcode_mod},
		{"mul", opcode_mul},
		{"pchar", opcode_pchar},
		{"pstr", opcode_pstr},
		{"rotl", opcode_rotl},
		{"rotr", opcode_rotr},
		{NULL, NULL}
	};
	stack_t *stack;
	string_t *temp;
	char com;
	char opcode[100];
	int i, ret_scan, comment;
	unsigned int line_number;

	temp = *string_head;
	line_number = 0;
	stack = NULL;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	while (temp != NULL)
	{
		comment = sscanf(temp->content, "%c", &com);
		ret_scan = sscanf(temp->content, "%s %d", opcode, &arg);
		if (comment == 1 && com == '#')
		{
			temp = temp->prev;
			continue;
		}
		if (ret_scan == 1)
		{
			if (strcmp(opcode, "push") == 0)
			{
				fprintf(stderr, "L%d: usage: push integer", line_number);
				exit(EXIT_FAILURE);
			}
		}

		if (strcmp(opcode, "pchar") != 0)
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
	free_stack(stack);
}

/**
 * main - Entry point for Monty interpreter
 * @argc: Argument count
 * @args: Array of arguments
 *
 * Description: The main function serves as the entry point for
 * the Monty interpreter. It processes command line arguments and
 * executes instructions from the input source.
 *
 * Return: 0 on success, other values on error
 */
int main(int argc, char **args)
{
	FILE *file;
	char err[1024];
	string_t *head;


	if (!verify(argc))
	{
		fprintf(stderr, "%s", "USAGE: monty file");
		exit(EXIT_FAILURE);
	}
	file = fopen(args[1], "r");
	if (file == NULL)
	{
		strcpy(err, "Error: Can't open file ");
		strcat(err, args[1]);
		fprintf(stderr, "%s", err);
		exit(EXIT_FAILURE);
	}
	read_file(&head, file);
	fclose(file);

	interpret_code(&head);

	arg = arg;
	return (0);
}
