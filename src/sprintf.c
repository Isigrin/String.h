#include "sprintf.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

int my_sprintf(char *str, const char *format, ...) {
    va_list args;
    int res = 0;
    va_start(args, format);
    res = read_str(format, str, args);
    va_end(args);
    return res;
}

int read_str(const char *format, char *str, va_list args) {
    t_flags flags;
    int res = 0;
    int i = -1;
    while (format[++i]) {
        if (format[i] != '%') {
            res += s_write(str, format[i], res);
        } else if (format[i + 1]) {
            i++;
            flags = s_init_flags();
            i = s_read_flags(format, i, &flags);
            if (s_type(format[i])) {
                res += s_translator(str, (char)flags.type, flags, args, res);
            } else if (format[i] == '%') {
                res += s_write(str, format[i], res);
            }
        }
    }
    return (res);
}

int s_write(char *str, char c, int res) {
    str[res] = c;
    str[res + 1] = '\0';
    return 1;
}

int s_fill_width(char *str, int width, int len, int res) {
    int i = 0;

    while (width - len > 0) {
        s_write(str, ' ', res);
        res++;
        width--;
        i++;
    }
    return (i);
}

int sprintf_s(char *str, char *arg, t_flags flags, int res) {
    int len = 0, tmp, f = 0;
    if (flags.minus == 1) {
        int j = strlen(arg);
        if (j > flags.val_dot && flags.dot) j = flags.val_dot;
        for (int i = 0; i < j; i++) {
            s_write(str, arg[i], res);
            res++;
            len++;
        }
    }
    if ((int)strlen(arg) < flags.width) {
        tmp = s_fill_width(str, flags.width - strlen(arg), -flags.val_dot,
                           res);
        f = 1;
        res += tmp;
        len += tmp;
    }
    if (flags.val_dot < flags.width && !f) {
        tmp = s_fill_width(str, flags.width - flags.val_dot, 0, res);
        res += tmp;
        len += tmp;
    }
    if (flags.minus == 0) {
        int j = strlen(arg);
        if (j > flags.val_dot && flags.dot) j = flags.val_dot;
        for (int i = 0; i < j; i++) {
            s_write(str, arg[i], res);
            res++;
            len++;
        }
    }
    return len;
}

int int_to_length(va_list arg, t_flags flags) {
    int fast = 0;
    if (flags.l == 1) {
        fast = (long)fast;
        fast = va_arg(arg, long);
    } else if (flags.h == 1) {
        fast = (short)fast;
        fast = va_arg(arg, int);
    } else {
        fast = va_arg(arg, int);
    }
    return fast;
}

char char_to_length(va_list arg, t_flags flags) {
    char fast = 0;
    if (flags.l == 1) {
        fast = (wint_t)fast;
        fast = va_arg(arg, wint_t);
    } else {
        fast = va_arg(arg, int);
    }
    return fast;
}

unsigned uns_to_length(va_list arg, t_flags flags) {
    unsigned fast = 0;
    if (flags.l == 1) {
        fast = (long)fast;
        fast = va_arg(arg, long);
    } else if (flags.h == 1) {
        fast = (short)fast;
        fast = va_arg(arg, int);
    } else {
        fast = va_arg(arg, int);
    }
    return fast;
}

int s_translator(char *str, int c, t_flags flags, va_list args, int res) {
    int len = 0;

    if (c == 'c') {
        char arg_char = char_to_length(args, flags);
        len += sprintf_c(str, arg_char, flags, res);
    } else if (c == 'd' || c == 'i') {
        int arg_int = int_to_length(args, flags);
        len += sprintf_d(str, arg_int, flags, res);
    } else if (c == 's') {
        len += sprintf_s(str, va_arg(args, char *), flags, res);
    } else if (c == 'f') {
        len += sprintf_f(str, va_arg(args, double), flags, res);
    } else if (c == 'u') {
        unsigned arg_uns = uns_to_length(args, flags);
        len += sprintf_u(str, arg_uns, flags, res);
    }
    return len;
}

int sprintf_d(char *str, int arg, t_flags flags, int res) {
    char arg_str[100];
    int len = 0;
    if (arg < 0) flags.negativ = 1;
    int_to_string(arg_str, arg);
    len += put_d(str, arg_str, arg, flags, res);
    return len;
}

void int_to_string(char *arg_str, int num) {
    char buf[100];
    int k = 0;
    if (num < 0) num *= -1;
    while (num > 0) {
        buf[k++] = num % 10 + '0';
        num = num / 10;
    }
    int n = 0;
    for (int i = k - 1; i >= 0; i--) {
        arg_str[n++] = buf[i];
    }
    arg_str[n] = '\0';
}

void uns_to_string(char *arg_str, unsigned num) {
    char buf[100];
    int k = 0;
    while (num > 0) {
        buf[k++] = num % 10 + '0';
        num = num / 10;
    }
    int n = 0;
    for (int i = k - 1; i >= 0; i--) {
        arg_str[n++] = buf[i];
    }
    arg_str[n] = '\0';
}

int sprintf_f(char *str, double arg, t_flags flags, int res) {
    char arg_str1[100], arg_str2[100];
    int len = 0, f = 1;
    double i_part, f_part;

    if (arg < 0) flags.negativ = 1;
    if (flags.dot == 0) flags.val_dot = 6;
    int dote = flags.val_dot;
    arg *= pow(10, dote);
    arg = round(arg);
    arg /= pow(10, dote);

    f_part = modf(arg, &i_part);
    int_to_string(arg_str1, (int)i_part);
    f_part *= pow(10, dote);
    unsigned long long t = abs((int)round(f_part));
    int_to_string(arg_str2, t);

    if (flags.width < (int)(strlen(arg_str1) + strlen(arg_str2)))
        flags.width = 0;
    else
        flags.width -= (int)(strlen(arg_str2) + 1);
    if (flags.dot == 1 && flags.val_dot == 0) {
        f = 0;
        flags.width++;
    }

    flags.val_dot = 0;
    len += put_d(str, arg_str1, (int)i_part, flags, res);
    res += len;

    if (f) {
        res += s_write(str, '.', res);
        len++;

        flags.plus = 0;
        flags.width = 0;
        len += put_d(str, arg_str2, t, flags, res);
    }
    return len;
}

int sprintf_u(char *str, unsigned arg, t_flags flags, int res) {
    char arg_str[100];
    int len = 0;
    uns_to_string(arg_str, arg);
    len += put_u(str, arg_str, flags, res);

    return len;
}

int sprintf_c(char *str, char c, t_flags flags, int res) {
    int len = 0;
    if (flags.minus == 1) {
        s_write(str, c, res);
        res++;
    }
    len += s_fill_width(str, flags.width, 1, res);
    res += len;
    if (flags.minus == 0) {
        s_write(str, c, res);
    }
    return len + 1;
}

int put_d(char *str, char *arg_str, int tmp, t_flags flags, int res) {
    int len = strlen(arg_str);
    int l = 0, h;

    if (flags.plus == 1 && flags.negativ == 1) {
        flags.negativ = 0;
    }
    if (flags.val_dot > len && flags.width != 0) {
        flags.width -= flags.val_dot - len;
    }
    if (flags.space == 1 && flags.negativ == 0) {
        l += s_fill_width(str, 1, 0, res);
        res++;
    } else {
        flags.space = 0;
    }
    if (flags.minus == 1) {
        h = fill_d(str, arg_str, tmp, flags, len, res);
        l += h;
        res += h;
    }
    if (flags.width > flags.dot) {
        h = s_fill_width(str, flags.width,
                         len + flags.negativ + flags.plus + flags.space, res);
        l += h;
        res += h;
    }
    if (flags.minus == 0) {
        l += fill_d(str, arg_str, tmp, flags, len, res);
    }
    return l;
}

int put_u(char *str, char *arg_str, t_flags flags, int res) {
    int len = strlen(arg_str);
    int l = 0, h;

    if (flags.val_dot > len && flags.width != 0) {
        flags.width -= flags.val_dot - len;
    }

    if (flags.minus == 1) {
        h = fill_u(str, arg_str, flags, len, res);
        l += h;
        res += h;
    }
    if (flags.width > flags.dot) {
        h = s_fill_width(str, flags.width,
                         len + flags.negativ + flags.plus + flags.space, res);
        l += h;
        res += h;
    }
    if (flags.minus == 0) {
        l += fill_u(str, arg_str, flags, len, res);
    }
    return l;
}

int fill_d(char *str, char *arg_str, int tmp, t_flags flags, int len, int res) {
    int l = 0;
    if (tmp < 0) {
        res += s_write(str, '-', res);
        l++;
    }
    if (tmp >= 0 && flags.plus == 1) {
        res += s_write(str, '+', res);
        l++;
    }
    if (flags.val_dot < len) flags.val_dot = 0;
    if (flags.val_dot > 0) {
        while (flags.val_dot - len > 0) {
            res += s_write(str, '0', res);
            flags.val_dot--;
            l++;
        }
        l += write_str(str, arg_str, res);
    } else {
        l += write_str(str, arg_str, res);
    }
    return l;
}

int fill_u(char *str, char *arg_str, t_flags flags, int len, int res) {
    int l = 0;
    if (flags.val_dot < len) flags.val_dot = 0;
    if (flags.val_dot > 0) {
        while (flags.val_dot - len > 0) {
            res += s_write(str, '0', res);
            flags.val_dot--;
            l++;
        }
        l += write_str(str, arg_str, res);
    } else {
        l += write_str(str, arg_str, res);
    }
    return l;
}

int write_str(char *str, char *str_put, int res) {
    int i = 0;
    while (str_put[i]) {
        res += s_write(str, str_put[i++], res);
    }
    return i;
}

t_flags s_init_flags(void) {
    t_flags flags;

    flags.type = 0;
    flags.minus = 0;
    flags.plus = 0;
    flags.space = 0;
    flags.dot = 0;
    flags.val_dot = 0;
    flags.width = 0;
    flags.negativ = 0;
    flags.h = 0;
    flags.l = 0;
    return (flags);
}

int s_isdigit(int c) { return (c >= '0' && c <= '9'); }

int s_type(int c) {
    return ((c == 'c') || (c == 'd') || (c == 'i') || (c == 'f') ||
            (c == 's') || (c == 'u'));
}

int s_flag_dot(const char *str, int i, t_flags *flags) {
    while (s_isdigit(str[i])) {
        flags->val_dot = (flags->val_dot * 10) + (str[i++] - 48);
    }
    return i;
}

t_flags s_flag_digit(char c, t_flags flags) {
    flags.width = (flags.width * 10) + (c - 48);
    return (flags);
}

int s_read_flags(const char *str, int i, t_flags *flags) {
    while (str[i]) {
        if (!s_isdigit(str[i]) && !s_type(str[i]) && (str[i] != '-') &&
            (str[i] != '+') && (str[i] != ' ') && (str[i] != '.') &&
            (str[i] != 'h') && (str[i] != 'l')) {
            break;
        }
        if (str[i] == '+') {
            flags->plus = 1;
        }
        if (str[i] == ' ' && flags->plus == 0) {
            flags->space = 1;
        }
        if (str[i] == '-') {
            flags->minus = 1;
        }
        if (str[i] == '.') {
            flags->dot = 1;
            i = s_flag_dot(str, i + 1, flags);
        }
        if (s_isdigit(str[i]) && flags->dot == 0) {
            *flags = s_flag_digit(str[i], *flags);
        }
        if (str[i] == 'h') {
            flags->h = 1;
        }
        if (str[i] == 'l') {
            flags->l = 1;
        }
        if (s_type(str[i])) {
            flags->type = str[i];
            break;
        }
        i++;
    }
    return i;
}
