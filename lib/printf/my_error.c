/*
** EPITECH PROJECT, 2023
** PROJETS
** File description:
** my_error
*/

#include "my_printf.h"

int my_error(char *error_str)
{
    write(2, error_str, my_strlen(error_str));
    return 84;
}
