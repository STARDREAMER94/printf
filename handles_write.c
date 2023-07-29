#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * writes_chars - Prints a string
 * @ch: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int writes_chars(char ch, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and padding at buffer's right */
	int k = 0;
	char pad = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pad = '0';

	buffer[k++] = ch;
	buffer[k] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (k = 0; k < width - 1; k++)
			buffer[BUFF_SIZE - k - 2] = pad;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - k - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - k - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * writes_nums - Write a number using a buffer
 * @id: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @pcn: Precision specifier
 * @length: Number length
 * @pad: Padding char
 * @extra_char: Extra char
 *
 * Return: Number of printed chars.
 */
int writes_nums(int id, char buffer[], int flags, int width, int pcn,
	int length, char pad, char extra_char)
{
	int k, start_pad = 1;

	if (pcn == 0 && id == BUFF_SIZE - 2 && buffer[id] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (pcn == 0 && id == BUFF_SIZE - 2 && buffer[id] == '0')
		buffer[id] = pad = ' '; /* width is displayed with padding ' ' */
	if (pcn > 0 && pcn < length)
		pad = ' ';
	while (pcn > length)
		buffer[--id] = '0', length++;
	if (extra_char != 0)
		length++;
	if (width > length)
	{
		for (k = 1; k < width - length + 1; k++)
			buffer[k] = pad;
		buffer[k] = '\0';
		if (flags & F_MINUS && pad == ' ')/* Assign extra char to left of buffer */
		{
			if (extra_char)
				buffer[--id] = extra_char;
			return (write(1, &buffer[id], length) + write(1, &buffer[1], k - 1));
		}
		else if (!(flags & F_MINUS) && pad == ' ')/* extra char to left of buff */
		{
			if (extra_char)
				buffer[--id] = extra_char;
			return (write(1, &buffer[1], k - 1) + write(1, &buffer[id], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')/* extra char to left of pad */
		{
			if (extra_char)
				buffer[--start_pad] = extra_char;
			return (write(1, &buffer[start_pad], k - start_pad) +
				write(1, &buffer[id], length - (1 - start_pad)));
		}
	}
	if (extra_char)
		buffer[--id] = extra_char;
	return (write(1, &buffer[id], length));
}

/************************* WRITE NUMBER *************************/
/**
 * writes_numbers - Prints a string
 * @is_neg: Lista of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_neg, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char pad = ' ', extra_char = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_neg)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (writes_nums(index, buffer, flags, width, precision,
		length, pad, extra_char));
}

/**
 * writes_unsignd - Writes an unsigned number
 * @is_neg: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int writes_unsignd(int is_neg, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position k */
	int length = BUFF_SIZE - index - 1, k = 0;
	char pad = ' ';

	UNUSED(is_neg);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] ==
		'0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		pad = ' ';
	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > length)
	{
		for (k = 0; k < width - length; k++)
			buffer[k] = pad;

		buffer[k] = '\0';

		if (flags & F_MINUS) /* Assign extra char to left of buffer [buffer>pad]*/
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], k));
		}
		else /* Assign extra char to left of padding [pad>buffer]*/
		{
			return (write(1, &buffer[0], k) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * writes_pointers - Write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @pad: Char representing the padding
 * @extra_char: Char representing extra char
 * @start_pad: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int writes_pointers(char buffer[], int index, int length,
	int width, int flags, char pad, char extra_char, int start_pad)
{
	int k;

	if (width > length)
	{
		for (k = 3; k < width - length + 3; k++)
			buffer[k] = pad;
		buffer[k] = '\0';
		if (flags & F_MINUS && pad == ' ')/* Assign extra char to left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], k - 3));
		}
		else if (!(flags & F_MINUS) && pad == ' ')/* extra char to left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[3], k - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')/* extra char to left of pad */
		{
			if (extra_char)
				buffer[--start_pad] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[start_pad], k - start_pad) +
				write(1, &buffer[index], length - (1 - start_pad) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_char)
		buffer[--index] = extra_char;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

