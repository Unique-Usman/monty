#include "monty.h"

/**
 * opcode_mod - Computes remainder of top two elements' division.
 * @stack: Pointer to stack's top.
 * @line_number: Current line number.
 */
void opcode_mod(stack_t **stack, unsigned int line_number)
{
	int count, tmp;
	stack_t *temp;

	temp = *stack;
	count = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
		if (count == 2)
			break;
	}

	if (count < 2)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	tmp = temp->n;

	if (tmp == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	tmp = temp->prev->n % tmp;

	temp->prev->n = tmp;
	opcode_pop(stack, line_number);
}

/**
 * opcode_pchar - Print char at top of stack
 * @stack: Double pointer to stack top
 * @line_number: Line number
 */
void opcode_pchar(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	if (tmp->n < 0 || tmp->n > 127)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", tmp->n);
}

/**
 * opcode_pstr - Print string from stack
 * @stack: Double pointer to stack top
 * @line_number: Line number
 */
void opcode_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	tmp = *stack;

	if (*stack == NULL)
	{
		printf("\n");
		return;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	while (tmp != NULL)
	{
		if (tmp->n < 0 || tmp->n > 127 || tmp->n == 0)
			return;
		printf("%c", tmp->n);
		tmp = tmp->prev;
	}
	printf("\n");
	line_number = line_number;
}

/**
 * opcode_rotl - Rotate stack left
 * @stack: Double pointer to stack top
 * @line_number: Line number
 */
void opcode_rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *temp2;

	temp2 = *stack;

	while (temp2->next != NULL)
	{
		temp2 = temp2->next;
	}

	temp2->next = (*stack);
	(*stack)->prev = temp2;
	temp2->prev->next = NULL;
	temp2->prev = NULL;
	*stack = temp2;

	line_number = line_number;
}

/**
 * opcode_rotr - Rotate stack right
 * @stack: Double pointer to stack top
 * @line_number: Line number
 */
void opcode_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp2, *temp;

	temp = *stack;

	while (temp2->next != NULL)
	{
		temp2 = temp2->next;
	}

	*stack = (*stack)->next;
	temp2->next = temp;
	temp2->next->prev = temp2;
	(*stack)->prev = NULL;
	line_number = line_number;
}
