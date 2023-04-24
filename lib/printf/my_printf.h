/*
** EPITECH PROJECT, 2022
** my.h
** File description:
** include all my functions of libmy.a
*/
#pragma once

#include "garbage.h"
#define malloc my_malloc
#define free my_free
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "./my_printf.h"
#include <math.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
struct mod {
    int padding;
    int precision;
    char pad;
    int nbr;
    int i;
    char plus;
    char hashtag;
    char space;
};
typedef struct linked_list{
    char *data;
    struct linked_list *next;
    struct linked_list *prev;
}llist;

typedef llist *l_list;
char *my_strcat(char const *dest, char const *src);
char *my_revstr(char *str);
unsigned int my_putchar(char c);
unsigned int my_intlen(long int c);
unsigned int my_put_nbr(int nb);
unsigned int my_putstr(char const *str);
unsigned int my_strlen(char const *str);
unsigned int my_compute_power_rec(int nbr, int p);
unsigned int my_printf(char const *str, ...);
unsigned int my_putchar_arg(va_list ap, struct mod modif);
unsigned int my_put_pourcent(va_list ap, struct mod modif);
unsigned int my_put_nbr_arg(va_list ap, struct mod modif);
unsigned int my_put_octal(va_list ap, struct mod modif);
unsigned int my_put_unsigned(va_list ap, struct mod modif);
unsigned int my_putstr_arg(va_list ap, struct mod modif);
unsigned int my_put_hexa(va_list ap, struct mod modif);
unsigned int my_put_hexa_maj(va_list ap, struct mod modif);
unsigned int my_put_pointer(va_list ap, struct mod modif);
unsigned int my_put_binary_unsigned(va_list ap,
__attribute__((unused)) struct mod modif);
unsigned int my_put_string_octal(va_list ap, struct mod modif);
unsigned int my_put_float_f(va_list ap, struct mod modif);
unsigned int my_print_scient(va_list ap, struct mod modif);
unsigned int my_print_scient_maj(va_list ap, struct mod modif);
unsigned int my_put_g_gen(va_list ap, struct mod modif);
struct mod detect_n(char const *str, va_list ap, struct mod modif);
struct mod detect_p(char const *str, va_list ap, struct mod modif);
unsigned int my_is_known_flag(char c);
unsigned int my_is_num(char c);
unsigned int my_put_g_genbis(va_list ap, struct mod modif);
unsigned int print_space(struct mod modif, long double nbr);
unsigned int my_put_float_g(double nbr, int prec, struct mod modif);
int my_get_padding(char const *str, int ind, va_list ap);
unsigned int my_get_precision(char const *str, int index, va_list ap);
unsigned int my_put_base(unsigned long long n, char const *base);
char *my_strncpy(char *dest, char const *src, unsigned int n);
char *my_strdup(char const *src);
int my_strncmp(char *a, char *b, int n);
l_list create(char *data);
l_list delete_begin(l_list list);
l_list insert_end(char *data, l_list list);
l_list insert_begin(char *data, l_list list);
int my_strisnum(char *str);
int get_nbr(char *str);
int my_error(char *error_str);
char **to_word_array(char *str, char c);
int my_tablen(void **tab);
int my_strcmp(char *a, char *b);
int my_isalpha(char *src);
char *my_cleanstr(char *src);
char *its(char *dest, int nbr);
char *its_main(char *dest, int nbr);
int my_strisnum(char *str);
char *my_strcatt(int nbr, ...);

int search_in_str(char *str, char *to_find);
int if_in(char *str, char *c);
char *my_strndup(char *str, int len);
int is_letter(char c);
