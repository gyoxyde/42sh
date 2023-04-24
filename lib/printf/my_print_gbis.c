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

unsigned int exposantbis(double nbr)
{
    int i = 0, signe = 0;
    if (nbr < 0){
        nbr = -nbr;
    }
    for (; nbr < 1; i++, nbr *= 10, signe += 1);
    for (; nbr > 10; i++, nbr /= 10);
    return i;
}

unsigned int my_put_gbis(double nbr, int precision, struct mod modif)
{
    int k = exposantbis(nbr);
    if (k >= precision || k < -4)
        return my_printf("%.5E", nbr);
    return my_put_float_g(nbr, precision, modif);
}

unsigned int my_put_g_genbis(va_list ap, struct mod modif)
{
    double nbr = va_arg(ap, double);
    return my_put_gbis(nbr, modif.precision, modif);
}
