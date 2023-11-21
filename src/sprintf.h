#ifndef SRC_SPRINTF_H_
#define SRC_SPRINTF_H_

#include <stdarg.h>

#include "string.h"

typedef struct flags {
  int type;
  int minus;
  int plus;
  int space;
  int dot;
  int val_dot;
  int width;
  int negativ;
  int l;
  int h;
} t_flags;

int my_sprintf(char *str, const char *format, ...);

int read_str(const char *format, char *str, va_list args);

int s_write(char *str, char c, int res);

int s_fill_width(char *str, int width, int len, int res);

int sprintf_s(char *str, char *arg, t_flags flags, int res);

int int_to_length(va_list arg, t_flags flags);

char char_to_length(va_list arg, t_flags flags);

unsigned uns_to_length(va_list arg, t_flags flags);

int s_translator(char *str, int c, t_flags flags, va_list args, int res);

int sprintf_d(char *str, int arg, t_flags flags, int res);

void int_to_string(char *arg_str, int num);

void uns_to_string(char *arg_str, unsigned num);

int sprintf_c(char *str, char c, t_flags flags, int res);

int sprintf_f(char *str, double arg, t_flags flags, int res);

int sprintf_u(char *str, unsigned arg, t_flags flags, int res);

int put_d(char *str, char *arg_str, int tmp, t_flags flags, int res);

int put_u(char *str, char *arg_str, t_flags flags, int res);

int fill_d(char *str, char *arg_str, int tmp, t_flags flags, int len, int res);

int fill_u(char *str, char *arg_str, t_flags flags, int len, int res);

int write_str(char *str, char *str_put, int res);

t_flags s_init_flags(void);

int s_isdigit(int c);

int s_read_flags(const char *str, int i, t_flags *flags);

int s_type(int c);

int s_flag_dot(const char *str, int i, t_flags *flags);

t_flags s_flag_digit(char c, t_flags flags);

#endif // SRC_SPRINTF_H_
