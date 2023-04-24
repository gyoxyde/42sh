/*
** EPITECH PROJECT, 2022
** printf
** File description:
** if functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
#include "my_printf.h"

unsigned int my_is_known_flag(char c)
{
    char *str = "%discuoxXpbSfeE";
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return 1;
    return 0;
}

unsigned int my_is_num(char c)
{
    if ((c <= '9' && c >= '0') || c == 45)
        return 1;
    return 0;
}

unsigned int my_is_flag_or_modifier(char c)
{
    char *str = "%discuoxXpbSfeE-+#123456789.*";
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return 1;
    return 0;
}

unsigned int print_space(struct mod modif, long double nbr)
{
    if (nbr > 0){
        if (modif.plus == 43)
            return my_printf("+");
        if (modif.space == 32)
            return my_printf(" ");
    }
    return 0;
}
