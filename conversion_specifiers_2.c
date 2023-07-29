#include "main.h"

/************* (u) - unsigned number conversion *************/
/**
 * unsigned_print - Prints an unsigned number
 * @list: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int unsigned_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(list, unsigned long int);

	num = converts_size_unsignd(num, size);

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
/*********** (o) - unsigned num in octal conversion **************/
/**
 * octal_print - Prints an unsigned number in octal notation
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int octal_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{

	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(list, unsigned long int);
	unsigned long int in_it_num = num;

	UNUSED(width);

	num = converts_size_unsignd(num, size);

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

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hex - Prints a hexadecimal number in lower or upper
 * @list: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_char: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hex(va_list list, char map_to[], char buffer[],
	int flags, char flag_char, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	unsigned long int num = va_arg(list, unsigned long int);
	unsigned long int in_it_num = num;

	UNUSED(width);

	num = converts_size_unsignd(num, size);

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
		buffer[k--] = flag_char;
		buffer[k--] = '0';
	}

	k++;

	return (writes_unsignd(0, k, buffer, flags, width, precision, size));
}

/********* (x) - unsigned num in hexadecimal conversion *********/
/**
 * hexadec_print - Prints an unsigned number in hexadecimal notation
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int hexadec_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hex(list, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/****** (X) - unsigned num in upper hexadecimal conversion ******/
/**
 * hex_upper_print - Prints an unsigned number in upper hexadecimal notation
 * @list: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int hex_upper_print(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hex(list, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}


