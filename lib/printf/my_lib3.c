/*
** EPITECH PROJECT, 2023
** PROJETS
** File description:
** my_lib3
*/

#include "my_printf.h"

char *its(char *dest, int nbr)
{
    if (nbr <= -10)
        dest = its(dest, nbr / 10);
    *dest++ = '0' - nbr % 10;
    return dest;
}

char *its_main(char *dest, int nbr)
{
    char *str = dest;
    *its(str, -nbr) = '\0';
    return dest;
}

int if_in(char *str, char *c)
{
    int i = 0;
    int len = my_strlen(c);
    while (str[i]){
        if (my_strncmp(str + i, c, len) == 0)
            return (1);
        i++;
    }
    return (0);
}

char *my_strndup(char *str, int len)
{
    char *dest = malloc(sizeof(char) * (len + 1));
    int i = 0;
    while (i < len){
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int is_letter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '/' ||
        c == '-' || c == '!' || c == '.' || ((c >= '1' && c <= '9') ||
        c == '0') || c == '_' || c == '=');
}
