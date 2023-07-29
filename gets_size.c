#include "main.h"

/**
 * gets_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @k: List of arguments to be printed.
 *
 * Return: Precision.
 */
int gets_size(const char *format, int *k)
{
	int curr_k = *k + 1;
	int size = 0;

	if (format[curr_k] == 'l')
		size = S_LONG;
	else if (format[curr_k] == 'h')
		size = S_SHORT;

	if (size == 0)
		*k = curr_k - 1;
	else
		*k = curr_k;

	return (size);
}

