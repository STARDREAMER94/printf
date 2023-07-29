#include "main.h"
/**
 * printing_handler - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @ap: List of arguments to be printed.
 * @index: index.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int printing_handler(const char *format, int *index, va_list ap,
char buffer[], int flags, int width, int precision, int size)
{
	int k, unknown_length = 0, printed_ch = -1;
	fmt_t format_list_types[] = {
		{'c', char_print}, {'s', string_print}, {'%', percent_print},
		{'i', int_print}, {'d', int_print}, {'b', binary_print},
		{'u', unsigned_print}, {'o', octal_print}, {'x', hexadec_print},
		{'X', hex_upper_print}, {'p', pointer_print}, {'S', non_printable_print},
		{'r', reverse_print}, {'R', rot13_string_print}, {'\0', NULL}
	};
	for (k = 0; format_list_types[k].fmt != '\0'; k++)
		if (fmt[*index] == format_list_types[k].fmt)
			return (format_list_types[k].fn(ap, buffer, flags, width, precision, size));

	if (format_list_types[k].fmt == '\0')
	{
		if (fmt[*index] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (fmt[*index - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmt[*index] != ' ' && fmt[*index] != '%')
				--(*index);
			if (fmt[*index] == ' ')
				--(*index);
			return (1);
		}
		unknown_length += write(1, &fmt[*index], 1);
		return (unknown_length);
	}
	return (printed_ch);
}


