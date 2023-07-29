#include "main.h"

/********************* (s)- string conversion *********************/
/**
 * string_print - Prints a string
 * @list: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int string_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, k;
	char *str = va_arg(list, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	/* va_end(list); */
	return (write(1, str, length));
}
/************* (%) - percentage identifier conversion *************/
/**
 * percent_print - Prints a percent sign
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int percent_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(list);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/******************(d)/(i) - integer conversion  *******************/
/**
 * int_print - Print int
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int int_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	int is_neg = 0;
	long int m = va_arg(list, long int);
	unsigned long int num;

	m = converts_size_num(m, size);

	if (m == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)m;

	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_neg = 1;
	}

	while (num > 0)
	{
		buffer[k--] = (num % 10) + '0';
		num /= 10;
	}

	k++;

	return (writes_numbers(is_neg, k, buffer, flags, width, precision, size));
}
/********************* (b) - binary conversion ********************/
/**
 * binary_print - Prints an unsigned number
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int binary_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int k, j, n, sum;
	unsigned int p[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	k = va_arg(list, unsigned int);
	j = 2147483648; /* (2 ^ 31) */
	p[0] = k / j;
	for (n = 1; n < 32; n++)
	{
		j /= 2;
		p[n] = (k / j) % 2;
	}
	for (n = 0, sum = 0, counter = 0; n < 32; n++)
	{
		sum += p[n];
		if (sum || n == 31)
		{
			char b = '0' + p[n];

			write(1, &b, 1);
			counter++;
		}
	}
	return (counter);
}
/********************** (c) - char conversion *********************/

/**
 * char_print - Prints a char
 * @list: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int char_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(list, int);

	return (writes_chars(c, buffer, flags, width, precision, size));
}



