/*
** EPITECH PROJECT, 2022
** my_strlen
** File description:
** my_strlen
*/

#include <string.h>

unsigned int my_strlen(char const * str )
{
    unsigned int i = 0;
    for (; str[i] != '\0'; i++);
    return i;
}
