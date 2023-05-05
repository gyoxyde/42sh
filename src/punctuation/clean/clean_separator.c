/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** clean_separator.c
*/
#include "shell.h"

int count_sepator(char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ';')
            count++;
    }
    return count;
}

char *clean_separator(char *str)
{
    int x = 0;
    int space = 0;
    char *dest =
    malloc(sizeof(char) * ((my_strlen(str) + count_sepator(str) * 2) + 1));
    int i = 0;
    for (; str[x] != '\0'; x++) {
        if (str[x] != ' ' && str[x] != ';')
            space ++;
        if (space != 0) {
            give_separator(str, x, dest, &i);
        }
    }
    dest[i] = '\0';
    return dest;
}

void give_separator(char *str, int x, char *dest, int *i)
{
    static bool alrdSep = false; int check = check_end_of_str_separator(str);
    if (str[x] != ' ' && str[x] != ';') {
        dest[(*i)] = str[x]; (*i)++; alrdSep = false;
    } else {
        if (x < check && str[x] == ' ' &&
            str[x + 1] == ';' && str[x + 2] == ' ' && alrdSep == false) {
            alrdSep = true; dest[(*i)] = ' '; (*i)++;
            dest[(*i)] = ';'; (*i)++; dest[(*i)] = ' '; (*i)++;
    } if (x < check && str[x] == ';' && str[x + 1] == ' ' && str[x - 1] != ' '
            && str[x - 1] != ';' && alrdSep == false) {
            alrdSep = true; dest[(*i)] = ' '; (*i)++;
            dest[(*i)] = ';'; (*i)++; dest[(*i)] = ' '; (*i)++;
    } if (x < check && str[x] == ' ' && str[x - 1] != ';' &&
        str[x + 1] != ' ' && str[x + 1] != ';' && alrdSep == false) {
            dest[(*i)] = ' '; (*i)++; return;
} if (x < check && str[x + 1] != ' ' && str[x + 1] != ';' && alrdSep == false) {
            dest[(*i)] = ' '; (*i)++;
            dest[(*i)] = ';'; (*i)++; dest[(*i)] = ' '; (*i)++;
        }
    }
}

int check_end_of_str_separator(char *str)
{
    int y = 0;

    for (; str[y] != '\0'; y++);
    y = y - 1;
    while (str[y] == ' ' || str[y] == ';') {
        y = y - 1;
    }
    return y;
}
