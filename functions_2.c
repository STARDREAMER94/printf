#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * prints_unsigned - Prints an unsigned number
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int prints_unsigned(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(list, unsigned long int);

	num = convert_size_unsignd(num, size);

	if (num == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[k--] = (num % 10) + '0';
		num /= 10;
	}

	k++;

	return (writes_unsignd(0, k, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * prints_octal - Prints an unsigned number in octal notation
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prints_octal(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{

	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(list, unsigned long int);
	unsigned long int in_it_num = num;

	UNUSED(width);

	num = convert_size_unsignd(num, size);

	if (num == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[k--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && in_it_num != 0)
		buffer[k--] = '0';

	k++;

	return (writes_unsignd(0, k, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * prints_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prints_hexadecimal(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	return (prints_hex(list, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * prints_hex_upper - Prints an unsigned number in upper hexadecimal notation
 * @list: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int prints_hex_upper(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	return (prints_hex(list, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * prints_hex - Prints a hexadecimal number in lower or upper
 * @list: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int prints_hex(va_list list, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(list, unsigned long int);
	unsigned long int in_it_num = num;

	UNUSED(width);

	num = convert_size_unsignd(num, size);

	if (num == 0)
		buffer[k--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[k--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && in_it_num != 0)
	{
		buffer[k--] = flag_ch;
		buffer[k--] = '0';
	}

	k++;

	return (writes_unsignd(0, k, buffer, flags, width, precision, size));
}

