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
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(*stack);
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
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		free_stack(*stack);
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
		fprintf(stderr, "L%d: can't pop, stack empty\n", line_number);
		free_stack(*stack);
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


/**
 * opcode_swap - Swaps top two elements of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number in script file.
 *
 * Description: Swaps top two stack elements.
 */
void opcode_swap(stack_t **stack, unsigned int line_number)
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
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	tmp = temp->n;
	temp->n = temp->prev->n;
	temp->prev->n = tmp;
}
