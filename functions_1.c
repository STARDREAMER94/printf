#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * prints_char - Prints a char
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prints_char(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char d = va_arg(list, int);

	return (writes_char(d, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * prints_string - Prints a string
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prints_string(va_list list, char buffer[],
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

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * prints_percent - Prints a percent sign
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prints_percent(va_list list, char buffer[],
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

/************************* PRINT INT *************************/
/**
 * prints_int - Print int
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prints_int(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(list, long int);
	unsigned long int num;

	m = convert_size_num(m, size);

	if (m == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)m;

	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[k--] = (num % 10) + '0';
		num /= 10;
	}

	k++;

	return (writes_number(is_negative, k, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * prints_binary - Prints an unsigned number
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int prints_binary(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int d, n, k, i, sum;
	unsigned int a[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	d = va_arg(list, unsigned int);
	n = 2147483648; /* (2 ^ 31) */
	a[0] = d / n;
	for (k = 1; k < 32; k++)
	{
		n /= 2;
		a[k] = (d / n) % 2;
	}
	for (i = 0, sum = 0, counter = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			counter++;
		}
	}
	return (counter);
}

