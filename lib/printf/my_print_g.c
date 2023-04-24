/*
** EPITECH PROJECT, 2022
** printf flag g
** File description:
** other file for flag
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include "my_printf.h"

unsigned int exposant(double nbr)
{
    int i = 0, signe = 0;
    if (nbr < 0){
        nbr = -nbr;
    }
    for (; nbr < 1; i++, nbr *= 10, signe += 1);
    for (; nbr > 10; i++, nbr /= 10);
    return i;
}

unsigned int my_put_float_g(double nbr, int prec, struct mod modif)
{
    int n = nbr, car = 0, k = 0;
    long double rounding = 0.5, decim = 0.0;
    for (int j = 0; j < prec; j++, rounding = rounding / 10);
    decim = (nbr - n) + rounding;
    if (decim - (decim * 10) > 5)
        n += 1;
    car += print_space(modif, nbr);
    if (nbr == n)
        return my_printf("%d", n);
    car += my_printf("%d", n);
    if (prec == 0 && modif.hashtag != 35)
        return car;
    my_printf(".");
    n = decim * my_compute_power_rec(10, prec);
    if (modif.hashtag != 35)
        for (; k < prec && n % 10 == 0; k++, n /= 10);
    else
        for (; k < prec && n % 10 == 0 && n / 10 % 10 == 0; k++, n /= 10);
    car += my_printf("%d", n % my_compute_power_rec(10, prec - k));
    return car;
}

unsigned int my_put_g(double nbr, int precision, struct mod modif)
{
    int k = exposant(nbr);
    if (k >= precision || k < -4)
        return my_printf("%.5e", nbr);
    return my_put_float_g(nbr, precision, modif);
}

unsigned int my_put_g_gen(va_list ap, struct mod modif)
{
    double nbr = va_arg(ap, double);
    return my_put_g(nbr, modif.precision, modif);
}
