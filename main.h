#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *k,
va_list ap, char buffer[], int flags, int width, int precision, int size);


/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int prints_char(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int prints_string(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int prints_percent(va_list list, char buffer[],
	int flags, int width, int precision, int size);


/* Functions to print numbers */
int prints_int(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int prints_binary(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int prints_unsigned(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int prints_octal(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int prints_hexadecimal(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int prints_hex_upper(va_list list, char buffer[],
	int flags, int width, int precision, int size);

int prints_hex(va_list list, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);


/* Function to print non printable characters */
int prints_non_printable(va_list list, char buffer[],
	int flags, int width, int precision, int size);


/* Funcion to print memory address */
int prints_pointers(va_list list, char buffer[],
	int flags, int width, int precision, int size);


/* Funciotns to handle other specifiers */
int get_flags(const char *format, int *k);
int get_width(const char *format, int *k, va_list ap);
int get_precision(const char *format, int *k, va_list ap);
int get_size(const char *format, int *k);


/*Function to print string in reverse*/
int prints_reverse(va_list list, char buffer[],
	int flags, int width, int precision, int size);


/*Function to print a string in rot 13*/
int prints_rot13string(va_list list, char buffer[],
	int flags, int width, int precision, int size);


/* width handler */
int writes_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int writes_number(int is_positive, int index, char buffer[],
	int flags, int width, int precision, int size);
int writes_num(int ind, char buffer[], int flags, int width, int precision,
	int length, char note, char extra_ch);
int writes_pointers(char buffer[], int index, int length,
	int width, int flags, char note, char extra_ch, int note_start);

int writes_unsignd(int is_negative, int index,
char buffer[],
	int flags, int width, int precision, int size);


/****************** UTILS ******************/
int is_printable(char);
int append_hex_code(char, char[], int);
int is_digit(char);

long int convert_size_num(long int num, int size);
long int convert_size_unsignd(unsigned long int num, int size);


#endif /* MAIN_H */
