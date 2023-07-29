#include "main.h"

/****************** (p) - pointer conversion ******************/
/**
 * pointer_print - Prints the value of a pointer variable
 * @list: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int pointer_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_char = 0, pad = ' ';
	int index = BUFF_SIZE - 2, length = 2, start_pad = 1; /* length=2, for '0x' */
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(list, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[index--] = map_to[num_address % 16];
		num_address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		extra_char = '+', length++;
	else if (flags & F_SPACE)
		extra_char = ' ', length++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - k - 1));*/
	return (writes_pointers(buffer, index, length,
		width, flags, pad, extra_char, start_pad));
}

/************* (S) - non-printable conversion *************/
/**
 * non_printable_print - Prints ascii codes in hexa of non printable chars
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int non_printable_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[k] != '\0')
	{
		if (is_printable(str[k]))
			buffer[k + offset] = str[k];
		else
			offset += appends_hex_code(str[k], buffer, k + offset);

		k++;
	}

	buffer[k + offset] = '\0';

	return (write(1, buffer, k + offset));
}

/********* (r) - printing in reverse conversion **********/
/**
 * reverse_print - Prints reverse string.
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int reverse_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int k, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(list, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (k = 0; str[k]; k++)
		;

	for (k = k - 1; k >= 0; k--)
	{
		char p = str[k];

		write(1, &p, 1);
		counter++;
	}
	return (counter);
}

/************ (R)- printing a rot13 string ************/
/**
 * rot13_string_print - Print a string in rot13.
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int rot13_string_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char y;
	char *str;
	unsigned int k, n;
	int counter = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(list, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (k = 0; str[k]; k++)
	{
		for (n = 0; in[n]; n++)
		{
			if (in[n] == str[k])
			{
				y = out[n];
				write(1, &y, 1);
				counter++;
				break;
			}
		}
		if (!in[n])
		{
			y = str[k];
			write(1, &y, 1);
			counter++;
		}
	}
	return (counter);
}

