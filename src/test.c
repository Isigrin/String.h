#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "sprintf.h"
#include "string.h"

START_TEST(memchr_test) {  // 1//
    char str1[] = "12345";
    char str2[] = " ";
    char str3[] = "    \0/";
    ck_assert_msg(my_memchr(str1, '3', 4) == memchr(str1, '3', 4), "Fail");
    ck_assert_msg(my_memchr(str2, ' ', 2) == memchr(str2, ' ', 2), "Fail");
    ck_assert_msg(my_memchr(str3, '/', 3) == memchr(str3, '/', 3), "Fail");
}
END_TEST

START_TEST(memcmp_test) {  // 2//
    unsigned char str1[] = "ABOBAthefirst";
    unsigned char str2[] = "ABOBAthesecond";
    unsigned char str3[] = "ABOBAthethird";
    ck_assert_msg(my_memcmp(str1, str2, 8) == memcmp(str1, str2, 8),
                  "failed on ABOBAthe");
    ck_assert_msg(my_memcmp(str1, str2, 13) == memcmp(str1, str2, 13),
                  "failed on first and second");
    ck_assert_msg(my_memcmp(str3, str1, 13) == memcmp(str3, str1, 13),
                  "failed on first and third");
}
END_TEST

START_TEST(memcpy_test) {  // 3//
    unsigned char str1[20] = "ABOBA";
    unsigned char str2[20] = "ABO";
    unsigned char dst1[6];
    unsigned char dst2[5];
    my_memcpy(dst1, str1, 6);
    ck_assert_int_eq(my_strcmp((char *)dst1, (char *)str1), strcmp((char *)dst1, (char *)str1));
    my_memcpy(dst2, str2, 5);
    ck_assert_int_eq(my_strcmp((char *)dst2, (char *)str2), strcmp((char *)dst2, (char *)str2));
}
END_TEST

START_TEST(memmove_test) {  // 4//
    unsigned char str1[] = "ABOBA";
    my_memmove(&str1[3], &str1[1], 2);
    ck_assert_msg(
        my_strcmp((char *)str1, "ABOBO") == strcmp((char *)str1, "ABOBO"),
        "failed on ABOBO");
    my_memmove(&str1[2], &str1[0], 3);
    ck_assert_msg(
        my_strcmp((char *)str1, "ABABA") == strcmp((char *)str1, "ABABA"),
        "failed on ABABA");
}
END_TEST

START_TEST(memset_test) {  // 5//
    char src[] = "ABOBA";
    my_memset(src, 'A', 5);
    ck_assert_msg(my_strcmp(src, "AAAAA\0") == strcmp(src, "AAAAA\0"),
                  "memset failed on ABOBA");
}
END_TEST

START_TEST(strcat_test) {  // 6//
    char app[] = "second ";
    char dst[] = "first";
    ck_assert_msg(my_strcat(dst, app) == dst, "strcat failed on pointer");
    ck_assert_msg(
        my_strcmp(dst, "firstsecond ") == strcmp(dst, "firstsecond "),
        "strcat failed on firstsecond");
}
END_TEST

START_TEST(strncat_test) {  // 7//
    char app[] = "third ";
    char dst[12] = "first";
    char dst2[12] = "first";
    ck_assert_msg(my_strncat(dst, app, 3) == dst,
                  "strncat failed on pointer 1");
    ck_assert_msg(my_strcmp(dst, "firstthi") == strcmp(dst, "firstthi"),
                  "strncat failed on firstsecond");
    ck_assert_msg(my_strncat(dst2, app, 6) == dst2,
                  "strncat failed on pointer 2");
    ck_assert_msg(
        my_strcmp(dst2, "firstthird ") == strcmp(dst2, "firstthird "),
        "strncat failed on firstthird");
}
END_TEST

START_TEST(strchr_test) {  // 8//
    char app[] = "third ";
    ck_assert_msg(my_strchr(app, 'h') == (app + 1),
                  "strchr failed on pointer");
    ck_assert_msg(my_strchr(app, 'q') == 0, "strcat failed on NULL");
}
END_TEST

START_TEST(strcmp_test) {  // 9//
    char str1[] = "test";
    char str2[] = "testovteste";
    char str3[] = "test1";
    char str4[] = "test12";
    char str5[] = "tes";
    char str6[] = "tes";
    char str7[] = "";
    char str8[] = "";
    char str9[] = "\0";
    ck_assert_msg((my_strcmp(str1, str2) < 0) && (strcmp(str1, str2) < 0),
                  "Fail");
    ck_assert_msg(my_strcmp(str4, str3) > 0 && strcmp(str4, str3) > 0, "Fail");
    ck_assert_msg(my_strcmp(str5, str6) == strcmp(str5, str6), "Fail");
    ck_assert_msg(my_strcmp(str7, str8) == strcmp(str7, str8), "Fail");
    ck_assert_msg(my_strcmp(str8, str9) == strcmp(str8, str9), "Fail");
}
END_TEST

START_TEST(strncmp_test) {  // 10//
    char str1[20] = "test";
    char str2[20] = "testovteste";
    char str3[20] = "test1";
    char str4[20] = "test12";
    char str5[20] = "tes";
    char str6[20] = "tes";
    char str7[20] = "";
    char str8[20] = "";
    char str9[20] = "\0";
    // test with back to back
    ck_assert_int_eq(my_strncmp(str1, str2, 11), strncmp(str1, str2, 11));
    ck_assert_int_eq(my_strncmp(str4, str3, 6), strncmp(str4, str3, 6));
    ck_assert_int_eq(my_strncmp(str5, str6, 3), strncmp(str5, str6, 3));
    ck_assert_int_eq(my_strncmp(str7, str8, 3), strncmp(str7, str8, 3));
    // test with 0
    ck_assert_int_eq(my_strncmp(str8, str9, 0), strncmp(str8, str9, 0));
    ck_assert_int_eq(my_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
    ck_assert_int_eq(my_strncmp(str4, str3, 0), strncmp(str4, str3, 0));
    ck_assert_int_eq(my_strncmp(str5, str6, 0), strncmp(str5, str6, 0));
    ck_assert_int_eq(my_strncmp(str7, str8, 0), strncmp(str7, str8, 0));
    ck_assert_int_eq(my_strncmp(str8, str9, 0), strncmp(str8, str9, 0));
    ck_assert_int_eq(my_strncmp(str1, str2, 15), strncmp(str1, str2, 15));
    // test with full
    ck_assert_int_eq(my_strncmp(str4, str3, 15), strncmp(str4, str3, 15));
    ck_assert_int_eq(my_strncmp(str5, str6, 15), strncmp(str5, str6, 15));
    ck_assert_int_eq(my_strncmp(str7, str8, 15), strncmp(str5, str6, 15));
    ck_assert_int_eq(my_strncmp(str8, str9, 15), strncmp(str5, str6, 15));
}
END_TEST

START_TEST(strcpy_test) {  // 11//
    char str1[] = "";
    char str2[10] = "testtest";
    char str3[10] = "testtest";
    char str4[6] = "hello";
    char dest[30];
    char dest2[20];
    char dest3[10] = "123";
    ck_assert_str_eq(strcpy(dest, str1), my_strcpy(dest, str1));
    ck_assert_str_eq(strcpy(dest, str2), my_strcpy(dest, str2));
    ck_assert_str_eq(strcpy(dest2, str3), my_strcpy(dest2, str3));
    ck_assert_str_eq(strcpy(dest3, str4), my_strcpy(dest3, str4));
}
END_TEST

START_TEST(strncpy_test) {  // 12//
    char str1[] = "";
    char str2[] = "testtest";
    char str3[] = "testtest";
    char str4[] = "hello";
    char dest[30];
    char dest2[20];
    char dest3[20] = "123";
    ck_assert_str_eq(strncpy(dest, str1, 15), my_strncpy(dest, str1, 15));
    ck_assert_str_eq(strncpy(dest, str2, 15), my_strncpy(dest, str2, 15));
    ck_assert_str_eq(strncpy(dest2, str3, 9), my_strncpy(dest2, str3, 9));
    ck_assert_str_eq(strncpy(dest3, str4, 10), my_strncpy(dest3, str4, 10));
}
END_TEST

START_TEST(strcspn_test) {  // 13//
    char str1[] = "ABOBA";
    char str2[] = "A";
    char str3[] = "O";
    ck_assert_uint_eq(my_strcspn(str1, str2), strcspn(str1, str2));
    ck_assert_uint_eq(my_strcspn(str1, str3), strcspn(str1, str3));
}
END_TEST

START_TEST(strerror_test) {  // 14 //
    char *ptr1 = my_strerror(107);
    char *ptr2 = strerror(107);
    ck_assert_str_eq(ptr1, ptr2);
    ptr1 = my_strerror(-100);
    ptr2 = strerror(-100);
    ck_assert_str_eq(ptr1, ptr2);
    ptr1 = my_strerror(0);
    ptr2 = strerror(0);
    ck_assert_str_eq(ptr1, ptr2);
}
END_TEST

START_TEST(strlen_test) {  // 15//
    ck_assert_msg(my_strlen("ABOBA\0") == strlen("ABOBA\0"),
                  "failed on ABOBA");
    ck_assert_msg(my_strlen("") == strlen(""), "failed on empty");
    ck_assert_msg(my_strlen("\0") == strlen("\0"), "failed on slash 0");
}
END_TEST

START_TEST(strpbrk_test) {  // 16//
    char str1[] = "ABOBA";
    char str2[] = "BOBA";
    char str3[] = "SCHOOL";
    ck_assert_msg(my_strcmp(my_strpbrk(str1, str2), "ABOBA") ==
                      strcmp(my_strpbrk(str1, str2), "ABOBA"),
                  "my_strpbrk failed on A in ABOBA");
    ck_assert_msg(my_strcmp(my_strpbrk(str3, str2), "OOL") ==
                      strcmp(my_strpbrk(str3, str2), "OOL"),
                  "my_strpbrk failed on A in zero");
}
END_TEST

START_TEST(strrchr_test) {  // 17//
    ck_assert_msg(my_strrchr("1234", '3') == strrchr("1234", '3'), "fail");
    ck_assert_msg(my_strrchr("qwerty", 'y') == strrchr("qwerty", 'y'), "fail");
    ck_assert_msg(my_strrchr("", '3') == strrchr("", '3'), "fail");
    ck_assert_msg(my_strrchr("\0", '3') == strrchr("\0", '3'), "fail");
}
END_TEST

START_TEST(strspn_test) {  // 18//
    char a[] = "";
    char a1[] = "";
    char b[] = "eda";
    char b1[] = "not_eda";
    char c[] = " ";
    char c1[] = " ";
    char d[] = "qwerty";
    char d1[] = "asdfg";
    ck_assert_msg(my_strspn(a, a1) == strspn(a, a1), "Fail");
    ck_assert_msg(my_strspn(b, b1) == strspn(b, b1), "Fail");
    ck_assert_msg(my_strspn(c, c1) == strspn(c, c1), "Fail");
    ck_assert_msg(my_strspn(d, d1) == strspn(d, d1), "Fail");
}
END_TEST

START_TEST(strstr_test) {  // 19//
    char str1[10] = "123";
    char str2[15] = "55551235558";
    char str6[10] = " ";
    char str7[10] = " ";
    ck_assert_str_eq(strstr(str6, str7), my_strstr(str6, str7));
    ck_assert_str_eq(strstr(str2, str1), my_strstr(str2, str1));
}
END_TEST

START_TEST(strtok_test) {  // 20//
    char str1[] = "buv";
    char str2[] = "u";
    char str4[] = "test1/test2";
    char str5[] = "/";
    ck_assert_str_eq(my_strtok(str1, str2), strtok(str1, str2));
    ck_assert_str_eq(my_strtok(str4, str5), strtok(str4, str5));
}
END_TEST

START_TEST(to_upper_test) {  // 1//
    char str1[] = "buv";
    char str2[] = "teSttEst";
    char str3[] = "/";
    char str4[] = "\0";
    void *to_upper_res = my_to_upper(str1);
    void *to_upper_res1 = my_to_upper(str2);
    void *to_upper_res2 = my_to_upper(str3);
    void *to_upper_res3 = my_to_upper(str4);
    ck_assert_str_eq(to_upper_res, "BUV");
    ck_assert_str_eq(to_upper_res1, "TESTTEST");
    ck_assert_str_eq(to_upper_res2, "/");
    ck_assert_str_eq(to_upper_res3, "\0");
    if (NULL != to_upper_res) free(to_upper_res);
    if (NULL != to_upper_res1) free(to_upper_res1);
    if (NULL != to_upper_res2) free(to_upper_res2);
    if (NULL != to_upper_res3) free(to_upper_res3);
}
END_TEST

START_TEST(to_lower_test) {  // 2//
    char str1[20] = "buv";
    char str2[20] = "teStTE3st";
    char str3[20] = "/";
    void *to_lower_res = my_to_lower(str1);
    void *to_lower_res1 = my_to_lower(str2);
    void *to_lower_res2 = my_to_lower(str3);
    ck_assert_str_eq(to_lower_res, "buv");
    ck_assert_str_eq(to_lower_res1, "testte3st");
    ck_assert_str_eq(to_lower_res2, "/");
    if (NULL != to_lower_res) free(to_lower_res);
    if (NULL != to_lower_res1) free(to_lower_res1);
    if (NULL != to_lower_res2) free(to_lower_res2);
}
END_TEST

START_TEST(insert_test) {  // 3//
    char str1[] = "hello";
    char str2[] = "12345";
    void *insert_res = my_insert(str1, str2, 0);
    ck_assert_str_eq(insert_res, "12345hello");
    if (NULL != insert_res) free(insert_res);
}
END_TEST

START_TEST(trim_test) {  // 4//
    char str1[20] = "hello";
    char str2[20] = "ho";
    char str3[20] = "//hello/";
    char str4[20] = "/";
    void *trim_res = my_trim(str1, str2);
    void *trim_res1 = my_trim(str3, str4);
    ck_assert_str_eq(trim_res, "ell");
    ck_assert_str_eq(trim_res1, "hello");
    if (NULL != trim_res) free(trim_res);
    if (NULL != trim_res1) free(trim_res1);
}
END_TEST

START_TEST(c_test) {
    char str1[100];
    char str2[100];

    sprintf(str1, "hello %-c %5c", 'a', '#');
    my_sprintf(str2, "hello %-c %5c", 'a', '#');
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%c %-6c", 'a', '#');
    my_sprintf(str2, "hi%c %-6c", 'a', '#');
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%%");
    my_sprintf(str2, "hi%%");
    ck_assert_str_eq(str1, str2);

    wint_t ch = '$';
    sprintf(str1, "hi%lc", ch);
    my_sprintf(str2, "hi%lc", ch);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s_test) {
    char str1[100];
    char str2[100];

    sprintf(str1, "hello %-s %7s", "hihi", "haha");
    my_sprintf(str2, "hello %-s %7s", "hihi", "haha");
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%.3s %-7s", "hihi", "haha");
    my_sprintf(str2, "hi%.3s %-7s", "hihi", "haha");
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%5.2s %-3.5s", "hihi", "haha");
    my_sprintf(str2, "hi%5.2s %-3.5s", "hihi", "haha");
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%.1s %.1s %1.0s", "ABOBA", "ABIBA", "ABUBA");
    my_sprintf(str2, "hi%.1s %.1s %1.0s", "ABOBA", "ABIBA", "ABUBA");
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(d_i_test) {
    char str1[100];
    char str2[100];

    sprintf(str1, "hello %+d %-7d", 396, -68);
    my_sprintf(str2, "hello %+d %-7d", 396, -68);
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%.3d % 2d", 48562, 9843);
    my_sprintf(str2, "hi%.3d % 2d", 48562, 9843);
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%+5.2d %-3.5d", -123, 56);
    my_sprintf(str2, "hi%+5.2d %-3.5d", -123, 56);
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%-+6.1d % .2d %3.0d", 487, -1234, 5);
    my_sprintf(str2, "hi%-+6.1d % .2d %3.0d", 487, -1234, 5);
    ck_assert_str_eq(str1, str2);

    long int num1 = 4876365;
    sprintf(str1, "hi%ld", num1);
    my_sprintf(str2, "hi%ld", num1);
    ck_assert_str_eq(str1, str2);

    short int num2 = 32767;
    sprintf(str1, "hi%hd", num2);
    my_sprintf(str2, "hi%hd", num2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(f_test) {
    char str1[100];
    char str2[100];

    sprintf(str1, "hello %+f %-7f", 396.5, -68.12);
    my_sprintf(str2, "hello %+f %-7f", 396.5, -68.12);
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%.3f %12f", 4.8562, 984.3);
    my_sprintf(str2, "hi%.3f %12f", 4.8562, 984.3);
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%+5.2f %-3.5f", -12.358, 56.4);
    my_sprintf(str2, "hi%+5.2f %-3.5f", -12.358, 56.4);
    ck_assert_str_eq(str1, str2);

    sprintf(str1, "hi%-+6.1f % .2f %3.0f", 487.49, -12.34, 5.1);
    my_sprintf(str2, "hi%-+6.1f % .2f %3.0f", 487.49, -12.34, 5.1);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(u_test) {
    char str1[100];
    char str2[100];

    unsigned int n1 = 396, n2 = 68;
    sprintf(str1, "hello %u %-7u", n1, n2);
    my_sprintf(str2, "hello %u %-7u", n1, n2);
    ck_assert_str_eq(str1, str2);

    n1 = 48562, n2 = 9843;
    sprintf(str1, "hi%.3u %2u", n1, n2);
    my_sprintf(str2, "hi%.3u %2u", n1, n2);
    ck_assert_str_eq(str1, str2);

    n1 = -123, n2 = 56;
    sprintf(str1, "hi%5.2u %-3.5u", n1, n2);
    my_sprintf(str2, "hi%5.2u %-3.5u", n1, n2);
    ck_assert_str_eq(str1, str2);

    n1 = 487, n2 = 1234;
    unsigned int n3 = 5;
    sprintf(str1, "hi%-6.1u %.2u %3.0u", n1, n2, n3);
    my_sprintf(str2, "hi%-6.1u %.2u %3.0u", n1, n2, n3);
    ck_assert_str_eq(str1, str2);

    long unsigned num1 = 100;
    sprintf(str1, "hello %lu", num1);
    my_sprintf(str2, "hello %lu", num1);
    ck_assert_str_eq(str1, str2);

    short unsigned num2 = 101;
    sprintf(str1, "hello %hu", num2);
    my_sprintf(str2, "hello %hu", num2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

int main() {
    Suite *s1 = suite_create("Tests");
    TCase *tc1 = tcase_create("Tests");
    SRunner *sr = srunner_create(s1);
    int nf;
    suite_add_tcase(s1, tc1);
    tcase_add_test(tc1, memchr_test);
    tcase_add_test(tc1, memcmp_test);
    tcase_add_test(tc1, memcpy_test);
    tcase_add_test(tc1, memmove_test);
    tcase_add_test(tc1, memset_test);
    tcase_add_test(tc1, strcat_test);
    tcase_add_test(tc1, strncat_test);
    tcase_add_test(tc1, strchr_test);
    tcase_add_test(tc1, strcmp_test);
    tcase_add_test(tc1, strncmp_test);
    tcase_add_test(tc1, strcpy_test);
    tcase_add_test(tc1, strncpy_test);
    tcase_add_test(tc1, strcspn_test);
    tcase_add_test(tc1, strerror_test);
    tcase_add_test(tc1, strlen_test);
    tcase_add_test(tc1, strpbrk_test);
    tcase_add_test(tc1, strrchr_test);
    tcase_add_test(tc1, strspn_test);
    tcase_add_test(tc1, strstr_test);
    tcase_add_test(tc1, strtok_test);
    tcase_add_test(tc1, to_upper_test);
    tcase_add_test(tc1, to_lower_test);
    tcase_add_test(tc1, insert_test);
    tcase_add_test(tc1, trim_test);
    tcase_add_test(tc1, c_test);
    tcase_add_test(tc1, s_test);
    tcase_add_test(tc1, d_i_test);
    tcase_add_test(tc1, f_test);
    tcase_add_test(tc1, u_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
