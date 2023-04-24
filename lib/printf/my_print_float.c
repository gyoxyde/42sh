/*
** EPITECH PROJECT, 2022
** printf
** File description:
** float printing functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include "my_printf.h"

unsigned int my_put_float(double nbr, int prec, struct mod modif)
{
    if (prec == 0)
        nbr += 0.5;
    int n = nbr, car = 0;
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
    car += my_printf(".");
    if (modif.hashtag == 35 && modif.precision == 0)
        return car;
    n = decim * my_compute_power_rec(10, prec);
    car += my_printf("%d", n % my_compute_power_rec(10, prec));
    return car;
}

unsigned int my_put_float_f(va_list ap, struct mod modif)
{
    double nbr = va_arg(ap, double);
    return my_put_float(nbr, modif.precision, modif);
}

unsigned int my_print_exposant(int i, char c, char c1)
{
    if (c1 == 0){
        if (i > 9)
            return my_printf("%c+%i", c, i);
        return my_printf("%c+0%i", c, i);
    }
    if (i > 9)
        return my_printf("%c%c%i", c, 45, i);
    return my_printf("%c%c0%i", c, 45, i);
}

unsigned int my_print_scient(va_list ap, struct mod modif)
{
    double nbr = va_arg(ap, double);
    int i = 0, car = 0, signe = 0;
    int comp = (modif.precision == 0) ? 1 : 10;
    if (nbr < 0){
        nbr = -nbr;
        my_printf("-");
    }
    car += print_space(modif, nbr);
    for (; nbr < 1; i++, nbr *= 10, signe += 1);
    for (; nbr > comp; i++, nbr /= 10);
    car += my_printf("%.*f", modif.precision, nbr);
    car += my_print_exposant(i, 101, signe);
    return car;
}

unsigned int my_print_scient_maj(va_list ap, struct mod modif)
{
    double nbr = va_arg(ap, double);
    int i = 0, car = 0, signe = 0;
    int comp = (modif.precision == 0) ? 1 : 10;
    if (nbr < 0){
        nbr = -nbr;
        my_printf("-");
    }
    car += print_space(modif, nbr);
    for (; nbr < 1; i++, nbr *= 10, signe += 1);
    for (; nbr > comp; i++, nbr /= 10);
    car += my_printf("%.*f", modif.precision, nbr);
    car += my_print_exposant(i, 69, signe);
    return car;
}
