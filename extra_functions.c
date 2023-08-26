#include "monty.h"
/**
 * verify - Check if argument equals 2.
 * @argc: Integer to be checked.
 * Return: 1 if arg is 2, else 0.
 */
int verify(int argc)
{
	if (argc != 2)
		return (0);
	return (1);
}

/**
 * read_file - Reads content from a file and stores in linked list.
 * @head: Double pointer to the head of the linked list.
 * @file: Pointer to the file to be read.
 *
 * Description: This function reads content from a file and stores it
 *              in a linked list.
 *
 * Return: Nothing.
 */

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
