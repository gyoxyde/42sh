/*
** EPITECH PROJECT, 2022
** B-PSU-200-LIL-2-1-minishell2-henri.gey-bechalier
** File description:
** clean_double_and.c
*/
#include "shell.h"

int count_double_and(char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '&')
            count++;
    }
    return count;
}

char *clean_double_and(char *str)
{
    int x = 0; int space = 0;
    char *dest =
    malloc(sizeof(char) *
    ((my_strlen(str) + count_double_and(str) * 2) + 1)); int i = 0;
    for (; str[x] != '\0'; x++) {
        if (str[x] != ' ' && str[x] != '&')
            space ++;
        if (space != 0) {
            give_double_and(str, x, dest, &i);
        }
    }
    dest[i] = '\0';
    return dest;
}

void give_double_and(char *str, int x, char *dest, int *i)
{
    if (str[x] != '&') {
        dest[(*i)] = str[x]; (*i)++;
    } else {
        if (str[x - 1] == ' ' && str[x + 1] == '&') {
            dest[(*i)] = '&'; (*i)++; dest[(*i)] = '&'; (*i)++; return;
        } if (str[x - 1] != ' ' && str[x - 1] != '&' &&
        str[x + 1] == '&') {
            dest[(*i)] = ' '; (*i)++; dest[(*i)] = '&'; (*i)++;
            dest[(*i)] = '&'; (*i)++; return;
        } if (str[x - 1] != ' ' && str[x - 1] != '&' && str[x + 1] == ' ') {
            dest[(*i)] = ' '; (*i)++; dest[(*i)] = '&'; (*i)++;
            return;
        } if (str[x - 1] != ' ' && str[x - 1] != '&' && str[x + 1] != ' '
        && str[x + 1] != '&') {
            dest[(*i)] = ' '; (*i)++; dest[(*i)] = '&'; (*i)++;
            dest[(*i)] = ' '; (*i)++; return;
        }
        give_double_and_two(str, x, dest, i);
    }
}

void give_double_and_two(char *str, int x, char *dest, int *i)
{
    if (str[x - 1] == ' ' && str[x + 1] != '&' && str[x + 1] != ' ') {
        dest[(*i)] = '&'; (*i)++; dest[(*i)] = ' '; (*i)++;
        return;
    }
    if (str[x - 1] == '&' && str[x + 1] == ' ') {
        return;
    }
    if (str[x + 1] != ' ' && str[x + 1] != '&') {
        dest[(*i)] = ' '; (*i)++;
        return;
    }
    dest[(*i)] = str[x]; (*i)++;
    return;
}
