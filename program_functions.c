#include "monty.h"

/**
 * opcode_push - Pushes an element onto the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the command in the script file.
 *
 * Description: This function pushes an element onto the stack.
 *
 * Return: Nothing.
 */

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
	line_number = line_number;
}

/**
 * opcode_pall - Prints all elements in the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the command in the script file.
 *
 * Description: This function prints all elements in the stack.
 *
 * Return: Nothing.
 */


void opcode_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	tmp = *stack;

	if (*stack == NULL)
		return;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->prev;
	}
	line_number = line_number;
}

/**
 * opcode_pint - Prints the value at the top of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the command in the script file.
 *
 * Description: This function prints the value at the top of the stack.
 *
 * Return: Nothing.
 */
void opcode_pint(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (*stack == NULL)
	{
		printf("%u: can't pint, stack empty", line_number);
		exit(EXIT_FAILURE);
	}

	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	printf("%d\n", tmp->n);
}

/**
 * opcode_pop - Removes the top element from the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the command in the script file.
 *
 * Description: This function removes the top element from the stack.
 *
 * Return: Nothing.
 */
void opcode_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (*stack == NULL)
	{
		printf("%u: can't pop, stack empty", line_number);
		exit(EXIT_FAILURE);
	}

	tmp = *stack;
	if ((*stack)->next == NULL)
	{
		*stack = NULL;
		free(tmp);
		return;
	}

	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->prev->next = NULL;
	free(tmp);
}
