/*
** EPITECH PROJECT, 2022
** printf
** File description:
** opti file
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include "my_printf.h"

struct mod detect_n(char const *str, va_list ap, struct mod modif)
{
    while (str[modif.i] == 43 || str[modif.i] == 35 || str[modif.i] == 32){
        for (; str[modif.i] == 43; modif.plus = 43, (modif.i)++);
        for (; str[modif.i] == 35; modif.hashtag = 35, (modif.i)++);
        for (; str[modif.i] == 32; modif.space = 32, (modif.i)++);
    }
    if (modif.plus == 43 && modif.space == 32)
        modif.space = 0;
    if (my_is_num(str[modif.i])){
        modif.padding = my_get_padding(str, modif.i, ap);
        for (; my_is_num(str[modif.i]) || str[modif.i] == 45 ||
            str[modif.i] != 43; (modif.i)++);
    }
    return modif;
}

struct mod detect_p(char const *str, va_list ap, struct mod modif)
{
    if (str[modif.i] == 46){
        modif.precision = my_get_precision(str, modif.i, ap);
        for (; !my_is_known_flag(str[modif.i]); (modif.i)++);
    }
    return modif;
}
