#include "monty.h"

/**
 * main - Start of program
 * @ac: Amount of arguments in command line
 * @av: Array with the entered arguments
 * Return: 0
 */

int main (int ac, char **av)
{
	if (ac == '\0' || ac != 2)
	{
		fprint(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	if (av[1] == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	return (0);
}
