#include "main.h"
/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @k: takes a parameter.
 * Return: Flags
 */
int get_flags(const char *format, int *k)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int i, current;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	current = *k + 1;
	while (format[current] != '\0')
	{
		i = 0;
		while (FLAGS_CH[i] != '\0')
		{
			if (format[current] == FLAGS_CH[i])
			{
				flags |= FLAGS_ARR[i];
				break;
			}
			i++;
		}

		if (FLAGS_CH[i] == 0)
			break;
	current++;
	}

	*k = current - 1;

	return (flags);
}

