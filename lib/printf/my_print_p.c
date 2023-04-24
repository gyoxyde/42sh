/*
** EPITECH PROJECT, 2022
** printf pointer
** File description:
** others files of project printf
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include "my_printf.h"

unsigned int my_put_pointer(va_list ap,
__attribute__((unused)) struct mod modif)
{
    void *n = va_arg(ap, void *);
    my_putstr("0x");
    return my_put_base((long long) n, "0123456789abcdef");
}
