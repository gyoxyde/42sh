/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** print unsigned numbers and arg my_put_nbr
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include "my_printf.h"

unsigned int my_put_nbr_arg(va_list ap, struct mod modif)
{
    int a = va_arg(ap, int);
    int car = print_space(modif, a);
    return my_put_nbr(a) + car;
}

unsigned int my_unsigned_intlen(unsigned int n)
{
    int c = 0;
    for (; n > 1; c++, n /= 10);
    return c;
}

unsigned int my_put_unsigned_int(unsigned int a)
{
    int len = my_unsigned_intlen(a);
    if (a > 9) {
        my_put_unsigned_int(a / 10);
    }
    my_putchar('0'+ (a % 10));
    return len;
}

unsigned int my_put_unsigned(va_list ap, struct mod modif)
{
    int a = va_arg(ap, int);
    int car;
    if (a < 0)
        return my_put_unsigned_int(a + my_compute_power_rec(2, 32));
    else
        car = print_space(modif, a);
    return my_put_unsigned_int(a) + car;
}
