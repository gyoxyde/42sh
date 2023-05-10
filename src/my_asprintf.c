/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** my_asprintf
*/

#include "shell.h"
#include <stdarg.h>

int my_asprintf(char **strp, const char *format, ...)
{
    va_list args;
    int size;
    va_start(args, format);

    size = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);
    *strp = malloc(size);
    if (!*strp)
        return -1;
    va_start(args, format);
    vsnprintf(*strp, size, format, args);
    va_end(args);

    return size - 1;
}
