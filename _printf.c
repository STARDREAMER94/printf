#include "main.h"

void prints_buffer(char buffer[], int *buff_index);

/**
 * _printf - Printf function
 * @format: format input.
 * Return: Printed_letters.
 */
int _printf(const char *format, ...)
{
	int k, printed = 0, printed_letters = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list ap;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(ap, format);

	k = 0;
	while (format && format[k] != '\0')
	{
		if (format[k] != '%')
		{
			buffer[(buff_index++)] = format[k];
			if (buff_index == BUFF_SIZE)
				/* buff_index = 1024(max) */
				prints_buffer(buffer, &buff_index);
			/* write(1, &format[k], 1);*/
			printed_letters++;
		}
		else
		{
			prints_buffer(buffer, &buff_index);
			flags = get_flags(format, &k);
			width = get_width(format, &k, ap);
			precision = get_precision(format, &k, ap);
			size = get_size(format, &k);
			++k;
			printed = handle_print(format, &k, ap, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_letters += printed;
		}
	k++;
	}

	prints_buffer(buffer, &buff_index);

	va_end(ap);

	return (printed_letters);
}

/**
 * prints_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_index: Index at which to add next char, represents the length.
 */
void prints_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);
/* basically a much more flexible putchar */
	*buff_index = 0;
}

