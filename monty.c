#include "monty.h"

int verify (int arg)
{
	if (arg != 2)
	{
		return (0);
	}
	return (1);
}

void execute_code(stack_t **head, char opcode[], int arg)
{

}
void opcode_push(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp, *new_stack;

	tmp = *stack;
	new_stack = malloc(sizeof(stack_t));
	if (!tmp)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_stack->n = arg;
	new_stack->next = NULL;
	new_stack->prev = NULL;

	if (*stack == NULL)
	{
		*stack = new_stack;
		new_stack->next = NULL;
		new_stack = NULL;
		return;
	}
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_stack;
		new_stack->prev = tmp;
	}
}

void opcode_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	tmp = *stack;

	while (tmp != NULL)
	{
		printf("%d", tmp->n);
		tmp = tmp->next;
	}
}

void interpret_code(FILE *file)
{
	char buffer[1024];
	char *opcode;
	stack_t **head;
	int i;
	unsigned int line_number;

	line_number = 1;
	instruction_t instruction_table[] = {
    		{"push", opcode_push},
    		{"pall", opcode_pall},
    		{NULL, NULL}
	};

	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
        	char opcode[100];
        	//int arg;
        	if (sscanf(buffer, "%s %d", opcode, &arg) == 1)
		{
            		arg = 0;
        	}

		for (i = 0; instruction_table[i].opcode != NULL; i++)
		{
			if (strcmp(instruction_table[i].opcode, opcode) == 0)
			{
				instruction_table[i].f(head, line_number);
				break;
			}
		}
	}
}

int main(int arg, char **args)
{
	FILE *file;
	char err[1024];

	if (!verify(arg))
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
	interpret_code(file);
	fclose(file);

	return (0);
}
