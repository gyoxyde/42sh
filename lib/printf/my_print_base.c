/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** configurer une base
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include "my_printf.h"

unsigned int my_put_base(unsigned long long n, char const *base)
{
    int b = my_strlen(base), i;
    char str[64];
    for (i = 0; n != 0; n /= b, i++)
        str[i] = base[n % b];
    str[i] = '\0';
    return my_printf("%s", my_revstr(str));
}

unsigned int my_put_octal(va_list ap, struct mod modif)
{
    int n = va_arg(ap, int);
    unsigned int n1 = n;
    if (n < 0)
        n1 += my_compute_power_rec(2, 32);
    if (modif.hashtag == 35)
        my_printf("0");
    return my_put_base(n1, "01234567") + 1;
}

unsigned int my_put_hexa(va_list ap, struct mod modif)
{
    int n = va_arg(ap, int);
    unsigned int n1 = n;
    if (n < 0)
        n1 += my_compute_power_rec(2, 32);
    if (modif.hashtag == 35)
        my_printf("0x");
    return (my_put_base(n1, "0123456789abcdef"));
}

unsigned int my_put_hexa_maj(va_list ap, struct mod modif)
{
    int n = va_arg(ap, int);
    unsigned int n1 = n;
    if (n < 0)
        n1 += my_compute_power_rec(2, 32);
    if (modif.hashtag == 35)
        my_printf("0X");
    return (my_put_base(n1, "0123456789ABCDEF")) + 2;
}

unsigned int my_put_binary_unsigned(va_list ap,
__attribute__((unused)) struct mod modif)
{
    int n = va_arg(ap, int);
    if (n < 0)
        n += my_compute_power_rec(2, 32);
    return my_put_base(n, "01");
}
