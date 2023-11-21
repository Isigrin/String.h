#ifndef SRC_STRING_H_
#define SRC_STRING_H_

typedef unsigned long size_t;
#define NULL (void *)0

void *memchr(const void *str, int c, size_t n); // 1

int memcmp(const void *str1, const void *str2, size_t n); // 2

void *memcpy(void *dest, const void *src, size_t n); // 3

void *memmove(void *dest, const void *src, size_t n); // 4

void *memset(void *str, int c, size_t n); // 5

char *strcat(char *dest, const char *src); // 6

char *strncat(char *dest, const char *src, size_t n); // 7

char *strchr(const char *str, int c); // 8

int strcmp(const char *str1, const char *str2); // 9

int strncmp(const char *s1, const char *s2, size_t n); // 10

char *strcpy(char *dest, const char *src); // 11

char *strncpy(char *dest, const char *src, unsigned int n); // 12

size_t strcspn(const char *str1, const char *str2); // 13

char *strerror(int errnum); // 14

size_t strlen(const char *str); // 15

char *strpbrk(const char *str1, const char *str2); // 16

char *strrchr(const char *str, int c); // 17

size_t strspn(const char *str1, const char *str2); // 18

char *strstr(const char *haystack, const char *needle); // 19

char *strtok(char *str, char *delim); // 20

void *to_upper(const char *str);

void *to_lower(const char *str);

void *insert(const char *src, const char *str, size_t start_index);

void *trim(const char *src, const char *trim_chars);

int chrstr(const char chr, const char *str);

size_t count_dist(const void *begin, const void *end);

#endif // SRC_STRING_H_
