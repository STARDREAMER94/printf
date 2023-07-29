#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

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
int printing_handler(const char *format, int *index, va_list ap,
char buffer[], int flags, int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Functions to print chars and strings */
int string_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int percent_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int char_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int int_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int binary_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int unsigned_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int octal_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int print_hex(va_list list, char map_to[], char buffer[],
	int flags, char flag_char, int width, int precision, int size);
int hexadec_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int hex_upper_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* Function to print non printable characters */
int non_printable_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int pointer_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to handle other specifiers */
int gets_flags(const char *format, int *k);
int gets_precision(const char *format, int *k, va_list ap);
int gets_size(const char *format, int *k);
int gets_width(const char *format, int *k, va_list ap);

/*Function to print string in reverse*/
int reverse_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int rot13_string_print(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int writes_chars(char ch, char buffer[],
	int flags, int width, int precision, int size);
int writes_nums(int index, char buffer[],
	int flags, int width, int precision,
	int length, char pad, char extra_char);
int write_number(int is_neg, int index, char buffer[],
	int flags, int width, int precision, int size);
int writes_unsignd(int is_neg, int index, char buffer[],
	int flags, int width, int precision, int size);
int writes_pointers(char buffer[], int index, int length,
	int width, int flags, char pad,
char extra_char, int start_pad);

/****************** UTILITIES ******************/
int is_printable(char ch);
int appends_hex_code(char ascii_code, char buffer[], int k);
int is_digit(char ch);
long int converts_size_num(long int num, int size);
long int converts_size_unsignd(unsigned long int num, int size);

#endif /* MAIN_H */

