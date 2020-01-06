#include "monty.h"

stack_t *head = NULL;

/**
 * main - Start of program
 * @ac: Amount of arguments in command line
 * @av: Array with the entered arguments
 * Return: 0
 */

int main(int ac, char **av)
{
	FILE *demo;

	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	if (!av[1])
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	if (access(av[1], R_OK) < 0)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	demo = fopen(av[1], "r");
	if (!demo)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	open_file(demo);
	fclose(demo);
	free_stack();
	return (0);
}

/**
 * open_file - Open the content of a file
 * @demo: pointer to the file
 *
 */

void open_file(FILE *demo)
{
	int line = 1;
	char *line_ptr = NULL;
	char *opcode, *val;
	size_t size = 0;

	while (getline(&line_ptr, &size, demo) != EOF)
	{
		if (!line_ptr)
		{
			fprintf(stderr, "Error: malloc failed");
			exit(EXIT_FAILURE);
		}

		opcode = strtok(line_ptr, "\n ");
		if (!opcode)
			break;
		val = strtok(NULL, "\n ");

		call_instruct(opcode, val, line);

		line++;
	}
	free(line_ptr);
}

/**
 * call_instruct - find the correct instruction
 * @opcode: given istruction
 * @val: given value to apply the instruction
 * @line: line number of opcode
 */

void call_instruct(char *opcode, char *val, int line)
{
	int i = 0, aux = 1;

	instruction_t func_list[] = {
		{"push", stack_concat},
		{"pall", stack_print},
		{"pint", stack_printtop},
		{"pop", stack_pop},
		{"swap", stack_swap},
		{"add", stack_add},
		{"nop", stack_nop},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	while (func_list[i].opcode)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			exec_line(func_list[i].f, opcode, val, line);
			aux = 0;
		}
		i++;
	}
	if (aux == 1)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line, opcode);
		exit(EXIT_FAILURE);
	}
}

/**
 * exec_line - executes the function
 * @f: pointer to the function
 * @opcode: opcode
 * @val: value
 * @line: line number
 */

void exec_line(op_func f, char *opcode, char *val, int line)
{
	int i = 0, aux = 1;
	stack_t *new_stack = NULL;

	if (strcmp(opcode, "push") == 0)
	{
		if (val && val[0] == '-')
		{
			val = val + 1;
			aux = -1;
		}
		if (!val)
		{
			fprintf(stderr, "L%d: usage: push integer\n", line);
			exit(EXIT_FAILURE);
		}
		while (val[i])
		{

			if (isdigit(val[i]) == 0)
			{
				fprintf(stderr, "L%d: usage: push integer\n", line);
				exit(EXIT_FAILURE);
			}
			i++;
		}
		new_stack = new_malloc(atoi(val) * aux);
		f(&new_stack, line);
	}
	else
		f(&head, line);
}
