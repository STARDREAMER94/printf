#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @k: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *k)
{
	int current = *k + 1;
	int size = 0;

	if (format[current] == 'l')
		size = S_LONG;
	else if (format[current] == 'h')
		size = S_SHORT;

	if (size == 0)
		*k = current - 1;
	else
		*k = current;

	return (size);
}

