/*
** EPITECH PROJECT, 2023
** current
** File description:
** search_in_str
*/

#include "my_printf.h"

int search_in_str(char *str, char *to_find)
{
    char *tmp = my_strdup(str);
    int count = 0;
    int len = my_strlen(to_find);
    while (tmp[0]){
        if (my_strncmp(tmp, to_find, len) == 0){
            count++;
            tmp += len;
        }
        if (tmp[0] && count != 0)
            count++;
        else
            break;
        tmp++;
    }
    return (count);
}
