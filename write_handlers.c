#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * writes_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int writes_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and note ind at buffer's right */
	int k = 0;
	char note = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		note = '0';

	buffer[k++] = c;
	buffer[k] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (k = 0; k < width - 1; k++)
			buffer[BUFF_SIZE - k - 2] = note;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - k - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - k - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * writes_number - Prints a string
 * @is_negative: List of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int writes_number(int is_negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char note = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		note = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (writes_num(index, buffer, flags, width, precision,
		length, note, extra_ch));
}

/**
 * writes_num - Write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @note: Pading char
 * @extra_ch: Extra char
 *
 * Return: Number of printed chars.
 */
int writes_num(int index, char buffer[],
	int flags, int width, int prec,
	int length, char note, char extra_ch)
{
	int k, note_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = note = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		note = ' ';
	while (prec > length)
		buffer[--index] = '0', length++;
	if (extra_ch != 0)
		length++;
	if (width > length)
	{
		for (k = 1; k < width - length + 1; k++)
			buffer[k] = note;
		buffer[k] = '\0';
		if (flags & F_MINUS && note == ' ')/* A sign extra char to left of buffer */
		{
			if (extra_ch)
				buffer[--index] = extra_ch;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], k - 1));
		}
		else if (!(flags & F_MINUS) && note == ' ')/* extra char to left of buff */
		{
			if (extra_ch)
				buffer[--index] = extra_ch;
			return (write(1, &buffer[1], k - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && note == '0')/* extra char to left of note */
		{
			if (extra_ch)
				buffer[--note_start] = extra_ch;
			return (write(1, &buffer[note_start], k - note_start) +
				write(1, &buffer[index], length - (1 - note_start)));
		}
	}
	if (extra_ch)
		buffer[--index] = extra_ch;
	return (write(1, &buffer[index], length));
}

/**
 * writes_unsignd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int writes_unsignd(int is_negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position i */
	int length = BUFF_SIZE - index - 1, k = 0;
	char note = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		note = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		note = '0';

	if (width > length)
	{
		for (k = 0; k < width - length; k++)
			buffer[k] = note;

		buffer[k] = '\0';

		if (flags & F_MINUS) /* A sign extra char to left of buffer [buffer>note]*/
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], k));
		}
		else /* A sign extra char to left of padding(note) [note>buffer]*/
		{
			return (write(1, &buffer[0], k) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * writes_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: width specifier
 * @flags: Flags specifier
 * @note: Char representing the padding
 * @extra_ch: Char representing extra char
 * @note_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int writes_pointer(char buffer[], int index, int length,
	int width, int flags, char note, char extra_ch, int note_start)
{
	int k;

	if (width > length)
	{
		for (k = 3; k < width - length + 3; k++)
			buffer[k] = note;
		buffer[k] = '\0';
		if (flags & F_MINUS && note == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_ch)
				buffer[--index] = extra_ch;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], k - 3));
		}
		else if (!(flags & F_MINUS) && note == ' ')/* extra char to left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_ch)
				buffer[--index] = extra_ch;
			return (write(1, &buffer[3], k - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && note == '0')/* extra char to left of note */
		{
			if (extra_ch)
				buffer[--note_start] = extra_ch;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[note_start], k - note_start) +
				write(1, &buffer[index], length - (1 - note_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_ch)
		buffer[--index] = extra_ch;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

