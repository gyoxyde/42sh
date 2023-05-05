/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** clean_right_redi.c
*/
#include "shell.h"

int count_right_redi(char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '>')
            count++;
    }
    return count;
}

char *clean_right_redi(char *str)
{
    int x = 0; int space = 0;
    char *dest =
    malloc(sizeof(char) *
    ((my_strlen(str) + count_right_redi(str) * 2) + 1)); int i = 0;
    for (; str[x] != '\0'; x++) {
        if (str[0] != '>' || space != 0)
            give_right_redi(str, x, dest, &i);
        if (check_start_right_str(str, x, dest, &i) == 1)
            space++;
    }
    dest[i] = '\0';
    return dest;
}

void give_right_redi(char *str, int x, char *dest, int *i)
{
    if (str[x] != '>') {
        dest[(*i)] = str[x]; (*i)++;
    } else {
        if (str[x - 1] == ' ' && str[x + 1] == '>') {
            dest[(*i)] = '>'; (*i)++; dest[(*i)] = '>'; (*i)++; return;
        } if (str[x - 1] != ' ' && str[x - 1] != '>' &&
            str[x + 1] == '>') {
            dest[(*i)] = ' '; (*i)++; dest[(*i)] = '>'; (*i)++;
            dest[(*i)] = '>'; (*i)++; return;
        } if (str[x - 1] != ' ' && str[x - 1] != '>' && str[x + 1] == ' ') {
            dest[(*i)] = ' '; (*i)++; dest[(*i)] = '>'; (*i)++;
            return;
        } if (str[x - 1] != ' ' && str[x - 1] != '>' && str[x + 1] != ' '
            && str[x + 1] != '>') {
            dest[(*i)] = ' '; (*i)++; dest[(*i)] = '>'; (*i)++;
            dest[(*i)] = ' '; (*i)++; return;
        }
        give_right_redi_two(str, x, dest, i);
    }
}

void give_right_redi_two(char *str, int x, char *dest, int *i)
{
    if (str[x - 1] == ' ' && str[x + 1] != '>' && str[x + 1] != ' ') {
        dest[(*i)] = '>'; (*i)++; dest[(*i)] = ' '; (*i)++;
        return;
    }
    if (str[x - 1] == '>' && str[x + 1] == ' ') {
        return;
    }
    if (str[x + 1] != ' ' && str[x + 1] != '>') {
        dest[(*i)] = ' '; (*i)++;
        return;
    }
    dest[(*i)] = str[x]; (*i)++;
}

int check_start_right_str(char *str, int x, char *dest, int *i)
{
    int space = 0;
    if (x == 0 && str[0] == '>' && str[1] != '\0' && str[1] != ' '
        && str[1] != '>') {
        dest[(*i)] = str[x]; (*i)++; dest[(*i)] = ' '; (*i)++; space++;
    } if (x == 0 && str[0] == '>' && str[1] == ' ') {
        dest[(*i)] = str[x]; (*i)++; space ++;
    } if (x == 0 && str[0] == '>' && str[1] == '\0') {
        dest[(*i)] = str[x]; (*i)++; space ++;
    }
    if (x == 0 && str[0] == '>' && str[1] == '>' && str[2] != '\0'
        && str[2] != ' ' && str[2] != '>') {
        dest[(*i)] = str[x]; (*i)++; dest[(*i)] = str[x]; (*i)++;
        space++;
    } if (x == 0 && str[0] == '>' && str[1] == '>' && str[2] == ' ') {
        dest[(*i)] = str[x]; (*i)++; dest[(*i)] = str[x]; (*i)++; space ++;
    } if (x == 0 && str[0] == '>' && str[1] == '>' && str[2] == '\0') {
        dest[(*i)] = str[x]; (*i)++; dest[(*i)] = str[x]; (*i)++; space ++;
    }
    return (space != 0);
}
