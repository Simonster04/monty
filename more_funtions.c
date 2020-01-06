#include "monty.h"

/**
 * stack_add - adds the top two elements of the stack
 * @stack: array with the data
 * @line_number: line number
 */

void stack_add(stack_t **stack, unsigned int line_number)
{
	int add;

	if (!stack || !(*stack) || !((*stack)->next))
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	*stack = (*stack)->next;
	add = (*stack)->n + (*stack)->prev->n;
	(*stack)->n = add;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * stack_nop - nothing
 * @stack: array witn the data
 * @line_number: line number
 */

void stack_nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * new_malloc - allocates memory for a new node
 * @n: integer to be saved in the node
 * Return: the new allocated memory
 */

stack_t *new_malloc(int n)
{
	stack_t *new_node;

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->n = n;
	return (new_node);
}

/**
 * free_stack - free all nodes in a slack
 */

void free_stack(void)
{
	stack_t *aux;

	if (!head)
	{
		return;
	}

	while (head)
	{
		aux = head;
		head = head->next;
		free(aux);
	}
}

/**
 * queue_add - adds a node to the queue.
 * @new_node: Pointer to the new node.
 * @ln: Interger representing the line number of of the opcode.
 */
void queue_add(stack_t **queue, unsigned int line_number)
{
	stack_t *aux;

	(void)line_number;
	if (!queue || !(*queue))
		exit(EXIT_FAILURE);

	if (!head)
	{
		head = *queue;
		return;
	}
	aux = head;
	while (aux->next)
		aux = aux->next;

	aux->next = *queue;
	(*queue)->prev = aux;
}
