#include "main.h"

/**
 * gets_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @k: take a parameter.
 * Return: Flags:
 */
int gets_flags(const char *format, int *k)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int n, curr_k;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_k = *k + 1; format[curr_k] != '\0'; curr_k++)
	{
		for (n = 0; FLAGS_CH[n] != '\0'; n++)
		{
			if (format[curr_k] == FLAGS_CH[n])
			{
				flags |= FLAGS_ARR[n];
				break;
			}
		}

		if (FLAGS_CH[n] == 0)
			break;
	}

	*k = curr_k - 1;

	return (flags);
}



