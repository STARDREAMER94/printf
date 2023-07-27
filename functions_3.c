#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * prints_pointers - Prints the value of a pointer variable
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int prints_pointers(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_ch = 0, note = ' ';
	int j, index = BUFF_SIZE - 2, length = 2, note_start = 1;
	/* length=2, for '0x' */
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
		note = '0';
	if (flags & F_PLUS)
		extra_ch = '+', length++;
	else if (flags & F_SPACE)
		extra_ch = ' ', length++;

	index++;
	j = writes_pointers(buffer, index, length,
                width, flags, note, extra_ch, note_start);
	/*return (write(1, &buffer[k], BUFF_SIZE - k - 1));*/
	return (j);
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * prints_non_printable - Prints ascii codes in hexa of non printable chars
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prints_non_printable(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int k, offset = 0;
	char *str = va_arg(list, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	for (k = 0; str[k] != '\0'; k++)
	{
		if (is_printable(str[k]))
			buffer[k + offset] = str[k];
		else
			offset += append_hex_code(str[k], buffer, k + offset);

	}

	buffer[k + offset] = '\0';

	return (write(1, buffer, k + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * prints_reverse - Prints reverse string.
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int prints_reverse(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int k, i, counter = 0;

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

	for (i = k - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		counter++;
	}
	return (counter);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * prints_rot13string - Print a string in rot13.
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int prints_rot13string(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char v;
	char *str;
	unsigned int k, l;
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
		for (l = 0; in[l]; l++)
		{
			if (in[l] == str[k])
			{
				v = out[l];
				write(1, &v, 1);
				counter++;
				break;
			}
		}
		if (!in[l])
		{
			v = str[k];
			write(1, &v, 1);
			counter++;
		}
	}
	return (counter);
}

