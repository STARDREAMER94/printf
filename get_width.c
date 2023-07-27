#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @k: List of arguments to be printed.
 * @ap: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *k, va_list ap)
{
	int current;
	int width = 0;

	current = *k + 1;
	while (format[current] != '\0')
	{
		if (is_digit(format[current]))
		{
			width *= 10;
			width += format[current] - '0';
		}
		else if (format[current] == '*')
		{
			current++;
			width = va_arg(ap, int);
			break;
		}
		else
			break;

current++;
}

	*k = current - 1;

	return (width);
}

