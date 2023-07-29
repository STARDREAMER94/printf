#include "main.h"

void buffer_print(char buffer[], int *buffer_index);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int k, printed = 0, ch_printed = 0;
	int flags, width, precision, size, buffer_index = 0;
	va_list ap;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(ap, format);

	for (k = 0; format && format[k] != '\0'; k++)
	{
		if (format[k] != '%')
		{
			buffer[buffer_index++] = format[k];
			if (buffer_index == BUFF_SIZE)
				buffer_print(buffer, &buffer_index);
			/* write(1, &format[k], 1);*/
			ch_printed++;
		}
		else
		{
			buffer_print(buffer, &buffer_index);
			flags = gets_flags(format, &k);
			width = gets_width(format, &k, ap);
			precision = gets_precision(format, &k, ap);
			size = gets_size(format, &k);
			++k;
			printed = printing_handler(format, &k, ap, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			ch_printed += printed;
		}
	}

	buffer_print(buffer, &buffer_index);

	va_end(ap);

	return (ch_printed);
}

/**
 * buffer_print - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buffer_index: Index at which to add next char, represents the length.
 */
void buffer_print(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}


