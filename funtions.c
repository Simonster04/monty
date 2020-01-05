#include "monty.h"

/**
 * stack_concat - adds new values to stack
 * @stack: new node added
 * @line_number: line number
 *
 */

void stack_concat(stack_t **stack, unsigned int line_number)
{
	stack_t *aux;

	(void)line_number;
	if (!stack || !(*stack))
	{
		exit(EXIT_FAILURE);
	}

	if (!head)
	{
		head = *stack;
		return;
	}

	aux = head;
	head = *stack;
	head->next = aux;
	aux->prev = head;
}

/**
 * stack_print - prints the value at the top of the stack
 * @stack: node to be printed
 * @line_number: line number
 *
 */

void stack_print(stack_t **stack, unsigned int line_number)
{
	stack_t *aux;

	(void)line_number;
	if (!stack)
	{
		exit(EXIT_FAILURE);
	}
	aux = *stack;
	while (aux)
	{
		printf("%d\n", aux->n);
		aux = aux->next;
	}
}

/**
 * stack_printtop - prints the value at the top of the stack
 * @stack: array with the data
 * @line_number: line number
 *
 */

void stack_printtop(stack_t **stack, unsigned int line_number)
{
	if (!stack || !(*stack))
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * stack_pop - removes the top element of the stack
 * @stack: array with the data
 * @line_number: line number
 *
 */

void stack_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *aux;

	if (!stack || !(*stack))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	aux = *stack;
	*stack = aux->next;
	if (*stack)
		(*stack)->prev = NULL;
	free(aux);
}

/**
 * stack_swap - swaps the top two elements of the stack
 * @stack: array with the data
 * @line_number: line number
 */

void stack_swap(stack_t **stack, unsigned int line_number)
{
	stack_t *aux;

	if (!stack || !(*stack) || !((*stack)->next))
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	aux = (*stack)->next;
	(*stack)->next = aux->next;
	if (!(aux->next))
		aux->next->prev = *stack;
	aux->next = *stack;
	(*stack)->prev = aux;
	aux->prev = NULL;
	*stack = aux;
}
