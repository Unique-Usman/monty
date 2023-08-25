#include "monty.h"

int verify (int arg)
{
	if (arg != 2)
	{
		return (0);
	}
	return (1);
}

/*void execute_code(stack_t **head, char opcode[], int arg)
{

}*/
void opcode_push(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp, *new_stack;

	tmp = *stack;
	new_stack = malloc(sizeof(stack_t));
	if (!new_stack)
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
		new_stack->prev = NULL;
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

	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->prev;
	}
}

void interpret_code(string_t **string_stack)
{
	char buffer[1024];
	stack_t *head;
        char opcode[100];
	int i;
	unsigned int line_number;

	line_number = 1;
	instruction_t instruction_table[] = {
    		{"push", opcode_push},
    		{"pall", opcode_pall},
    		{NULL, NULL}
	};
        	if (sscanf(buffer, "%s %d", opcode, &arg) == 1)
		{
			if (strcmp(opcode, "push") == 0)
			{
				printf("L%d: usage: push integer", line_number);
				exit(EXIT_FAILURE);
			}
        	}

		printf("%s, %d", opcode, arg);
		for (i = 0; instruction_table[i].opcode != NULL; i++)
		{
			if (strcmp(instruction_table[i].opcode, opcode) == 0)
			{
				instruction_table[i].f(&head, line_number);
				break;
			}
		}
		line_number++;
}

void read_file(string_t **head, FILE *file)
{
	char buffer[1024];
	string_t *tmp;

	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		tmp = malloc(sizeof(string_t));
		if (!tmp)
		{
			printf("Error: malloc failed\n");
			exit(EXIT_FAILURE);
		}
		strcpy(tmp->content, buffer);
		tmp->next = NULL;
		tmp->prev = NULL;
		if (*head == NULL)
		{
			*head = tmp;
		}
		else
		{
			tmp->next = (*head);
			(*head)->prev = tmp;
			*head = tmp;
		}
	}
}
int main(int arg, char **args)
{
	FILE *file;
	char err[1024];

	string_t *head;

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
	read_file(&head, file);
	fclose(file);

	while (head != NULL)
	{
		printf("%s", head->content);
		head = head->next;
	}
	//interpret_code(&head);

	return (0);
}
