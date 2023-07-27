#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @k: List of arguments to be printed.
 * @ap: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *k, va_list ap)
{
	int current = *k + 1;
	int precision = -1;

	if (format[current] != '.')
		return (precision);

	precision = 0;

	current += 1;
	while (format[current] != '\0')
	{
		if (is_digit(format[current]))
		{
			precision *= 10;
			precision += format[current] - '0';
		}
		else if (format[current] == '*')
		{
			current++;
			precision = va_arg(ap, int);
			break;
		}
		else
			break;

		current++;
	}
	*k = current - 1;

	return (precision);
}

