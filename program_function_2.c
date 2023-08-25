#include "monty.h"
/**
 * opcode_add - Adds top two elements of stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number in script file.
 *
 * Description: Adds top two stack elements.
 */
void opcode_add(stack_t **stack, unsigned int line_number)
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
                printf("L%d:  can't add, stack too short", line_number);
                exit(EXIT_FAILURE);
        }

        temp = *stack;
        while (temp->next != NULL)
        {
                temp = temp->next;
        }

        tmp = temp->n;
	tmp = tmp + temp->prev->n;

	temp->prev->n = tmp;
	opcode_pop(stack, line_number);
}

/**
 * opcode_nop - No-operation command.
 * @stack: Double pointer to the stack.
 * @line_number: Line number in script file.
 *
 * Description: No-operation (nop) command, does nothing.
 */
void opcode_nop(stack_t **stack, unsigned int line_number)
{
	*stack = *stack;
	line_number = line_number;
}

/**
 * opcode_sub - Subtracts top two elements of stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number in script file.
 *
 * Description: Subtracts second element from the top element of the stack.
 */
void opcode_sub(stack_t **stack, unsigned int line_number)
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
                printf("L%d:  can't sub, stack too short", line_number);
                exit(EXIT_FAILURE);
        }

        temp = *stack;
        while (temp->next != NULL)
        {
                temp = temp->next;
        }

        tmp = temp->n;
        tmp = temp->prev->n - tmp;

        temp->prev->n = tmp;
        opcode_pop(stack, line_number);
}
