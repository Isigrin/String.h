#include "string.h"

#include <stdio.h>
#include <stdlib.h>

void *my_memchr(const void *str, int c, size_t n) {  // 1 
    void *t = NULL;
    if (n != 0) {
        const unsigned char *p = str;
        do {
            if (*p++ == c) {
                t = ((void *)(p - 1));
            }
        } while (--n != 0);
    }
    return t;
}

int my_memcmp(const void *str1, const void *str2, size_t n) {  // 2 
    if (!n) return (0);

    while (--n && *(char *)str1 == *(char *)str2) {
        str1 = (char *)str1 + 1;
        str2 = (char *)str2 + 1;
    }

    return (*((unsigned char *)str1) - *((unsigned char *)str2));
}

void *my_memcpy(void *dest, const void *src, size_t n) {  // 3
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;
    for (size_t i = 0; i < n - 1; ++i) {
        *cdest++ = *csrc++;
    }
    return dest;
}

void *my_memmove(void *dest, const void *src, size_t n) {  // 4
    unsigned char *s;
    unsigned char *d;

    d = (unsigned char *)dest;
    s = (unsigned char *)src;

    while (n--) {
        *(d++) = *(s++);
    }

    return d;
}

void *my_memset(void *str, int c, size_t n) {  // 5 
    if (str) {
        char *tmp_mem = (char *)str;
        while (n--) *tmp_mem++ = (char)c;
    }

    return str;
}

char *my_strcat(char *dest, const char *src) {  // 6
    int i = 0;
    int l = my_strlen(dest);
    while (src[i] != '\0') {
        dest[l + i] = src[i];
        i++;
    }
    dest[l + i] = '\0';
    return dest;
}

char *my_strncat(char *dest, const char *src, size_t n) {  // 7
    size_t dest_len = my_strlen(dest);
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';

    return dest;
}

char *my_strchr(const char *str, int c) {  // 8
    int flag = 1;
    char *tmp = (char *)str;
    while (*tmp != (char)c) {
        if (!*tmp++) {
            flag = 0;
            break;
        }
    }
    if (!flag) tmp = NULL;

    return tmp;
}

int my_strcmp(const char *str1, const char *str2) {  // 9
    int s1;
    int s2;
    do {
        s1 = *str1++;
        s2 = *str2++;
        if (s1 == 0) break;
    } while (s1 == s2);
    return (s1 < s2) ? -1 : (s1 > s2);
}

int my_strncmp(const char *s1, const char *s2, size_t n) {  // 10
    int t;
    while (n && *s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0) {
        t = 0;
    } else {
        t = (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
    return t;
}

char *my_strcpy(char *dest, const char *src) {  // 11
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strncpy(char *dest, const char *src, unsigned int n) {  // 12
    unsigned int i;

    i = 0;
    while (i < n && src[i]) {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}

size_t my_strcspn(const char *str1, const char *str2) {  // 13
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    int i = 0, a = -1, flag = 1;
    for (i = 0; i < len1 && flag == 1; i++)
        for (int j = 0; j < len2 && flag == 1; j++)
            if (str1[i] == str2[j]) {
                a = i;
                flag = 0;
            }
    if (a == -1) a = len1;
    return a;
}

#if defined(__APPLE__)  // Apple OSX and iOS (Darwin) //14
#include "errlist.h"
char *my_strerror(int errnum) {
    static char errortemp[100];
    if (errnum < 106 && errnum >= 0) {
        char *my_errlist[107];
        // MAC_ERRLIST;
        my_strcpy(errortemp, my_errlist[errnum]);
    } else if (errnum < 0) {
        my_strcpy(errortemp, "Unknown error: ");
        int l = 0;
        int k = 0;
        char buf[20];
        char temp[20];
        errnum = errnum * (-1);
        while (errnum > 0) {
            buf[k++] = errnum % 10 + '0';
            errnum = errnum / 10;
        }
        for (int i = k - 1; i >= 0; i--) {
            if (l == 0) {
                temp[l] = '-';
                l++;
                k++;
            }
            temp[l++] = buf[i];
            if (l == k) {
                temp[l] = '\0';
            }
        }
        my_strcat(errortemp, temp);
    } else {
        my_strcpy(errortemp, "Unknown error: ");
        int l = 0;
        int k = 0;
        char buf[20];
        char temp[20];
        while (errnum > 0) {
            buf[k++] = errnum % 10 + '0';
            errnum = errnum / 10;
        }
        for (int i = k - 1; i >= 0; i--) {
            temp[l++] = buf[i];
            if (l == k) {
                temp[l] = '\0';
            }
        }
        my_strcat(errortemp, temp);
    }
    return errortemp;
}
#elif defined(__linux__)
#include "errlist.h"
char *my_strerror(int errnum) {
    static char errortemp[100];
    if (errnum < 134 && errnum >= 0) {
        char *my_errlist[134];
        LIN_ERRLIST;
        my_strcpy(errortemp, my_errlist[errnum]);
    } else if (errnum < 0) {
        my_strcpy(errortemp, "Unknown error ");
        int l = 0;
        int k = 0;
        char buf[20];
        char temp[20];
        errnum = errnum * (-1);
        while (errnum > 0) {
            buf[k++] = errnum % 10 + '0';
            errnum = errnum / 10;
        }
        for (int i = k - 1; i >= 0; i--) {
            if (l == 0) {
                temp[l] = '-';
                l++;
                k++;
            }
            temp[l++] = buf[i];
            if (l == k) {
                temp[l] = '\0';
            }
        }
        my_strcat(errortemp, temp);
    } else {
        my_strcpy(errortemp, "Unknown error ");
        int l = 0;
        int k = 0;
        char buf[20];
        char temp[20];
        while (errnum > 0) {
            buf[k++] = errnum % 10 + '0';
            errnum = errnum / 10;
        }
        for (int i = k - 1; i >= 0; i--) {
            temp[l++] = buf[i];
            if (l == k) {
                temp[l] = '\0';
            }
        }
        my_strcat(errortemp, temp);
    }
    return errortemp;
}
#endif

size_t my_strlen(const char *str) {  // 15
    int l = 0;
    while (str[l] != '\0') {
        l++;
    }
    return l;
}

char *my_strpbrk(const char *s1, const char *s2) {  // 16
    int s1len = my_strlen(s1);
    int s2len = my_strlen(s2);
    char *t = NULL;
    int flag = 1;
    for (int i = 0; i < s1len && flag == 1; i++)
        for (int j = 0; j < s2len && flag == 1; j++)
            if (s1[i] == s2[j]) {
                flag = 0;
                t = (char *)&s1[i];
            }
    if (flag) t = NULL;
    return t;
}

char *my_strrchr(const char *str, int c) {  // 17
    int len = my_strlen(str);
    int i;
    char *t;
    for (i = len - 1; i >= 0; --i) {
        if (str[i] == c) {
            break;
        }
    }
    if (i < 0)
        t = NULL;
    else
        t = (char *)(str + i);

    return t;
}

size_t my_strspn(const char *str1, const char *str2) {  // 18
    size_t n;
    const char *p;
    for (n = 0; *str1; str1++, n++) {
        for (p = str2; *p && *p != *str1; p++) {
        }
        if (!*p) break;
    }
    return n;
}

char *my_strstr(const char *haystack, const char *needle) {  // 19
    int i = 0, len;
    const char *point = NULL, *buf = NULL;
    len = my_strlen(haystack);
    while (haystack[i] != '\0') {
        int f = 1;
        int j = 0;
        while (needle[j] != '\0') {
            if (i + j >= len) break;
            if (haystack[i + j] == needle[j] && f == 1) {
                buf = haystack + i + j;
                f = 2;
            } else if (f != 2) {
                f = 0;
            }
            j++;
        }
        if (f == 2) {
            point = buf;
            break;
        }
        i++;
    }
    return (char *)point;
}

char *my_strtok(char *str, char *delim) {  // 20
    static char *p = 0;
    if (str)
        p = str;
    else if (!p)
        return 0;
    str = p + my_strspn(p, delim);
    p = str + my_strcspn(str, delim);
    if (p == str) return p = 0;
    p = *p ? *p = 0, p + 1 : 0;
    return str;
}

void *my_to_upper(const char *str) {  // 1
    int i = 0, flag = 1;
    size_t len = my_strlen(str);
    void *t = NULL;
    char *str_cpy = malloc((my_strlen(str) + 1) * sizeof(char));
    while (str[i] != '\0' && flag) {
        if ((len != 0)) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                str_cpy[i] = str[i] - 32;
            } else {
                str_cpy[i] = str[i];
            }
        } else {
            flag = 0;
            break;
        }
        i++;
    }
    str_cpy[i] = '\0';
    if (flag) t = str_cpy;
    return t;
}

void *my_to_lower(const char *str) {  // 2
    size_t len = my_strlen(str);
    int i = 0;
    char *str_cpy = (char *)malloc(my_strlen(str) * sizeof(char));
    while (str[i] != '\0') {
        if ((len != 0)) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str_cpy[i] = str[i] + 32;
            } else {
                str_cpy[i] = str[i];
            }
        } else {
            return NULL;
        }
        i++;
    }
    str_cpy[i] = '\0';
    return str_cpy;
}

void *my_insert(const char *src, const char *str,
                 size_t start_index) {  // 3
    size_t len1 = my_strlen(src);
    size_t len2 = my_strlen(str);
    char *tmp = NULL;
    void *t = NULL;
    if (start_index < len1) {
        tmp = (char *)malloc((len1 + len2 + 1) * sizeof(char));
        size_t b = 0;
        for (size_t i = 0; i < len1 + len2; i++) {
            if (i == (start_index)) {
                for (size_t j = 0; j < len2; j++, i++) {
                    tmp[i] = str[j];
                }
            }
            tmp[i] = src[b];
            b++;
        }
        t = tmp;
    }
    return t;
}

void *my_trim(const char *src, const char *trim_chars) {  // 4
    size_t begin = 0;
    size_t end = my_strlen(src) - 1;

    while (begin <= end && chrstr(src[begin], trim_chars)) {
        begin++;
    }

    while (chrstr(src[end], trim_chars) && begin <= end) {
        end--;
    }
    size_t len = end - begin + 1;
    char *res = (char *)malloc((len + 1) * sizeof(char));
    for (size_t i = 0; i < len; i++) {
        res[i] = src[begin + i];
    }
    res[len] = '\0';
    return res;
}

int chrstr(const char chr, const char *str) {
    int flag = 0;
    for (int j = 0; str[j] != '\0'; j++) {
        if (chr == str[j]) {
            flag = 1;
            break;
        }
    }
    return flag;
}
