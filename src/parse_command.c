/*
** EPITECH PROJECT, 2023
** current
** File description:
** parse_command
*/

#include "../include/my.h"

static int check_ambiguous(char **str, int i)
{
    if (str[i + 1] == NULL || str[i + 1][0] == '\0'){
        my_error("Missing name for redirect.\n");
        return 1;
    }
    if (my_strcmp(str[i], ">") == 1 && str[i + 2] != NULL &&
        my_strcmp(str[i + 2], ">") == 1){
        my_error("Ambiguous output redirect.\n");
        return 1;
    }
    if (my_strcmp(str[i], "<") == 1 && str[i + 2] != NULL &&
        my_strcmp(str[i + 2], "<") == 1){
        my_error("Ambiguous input redirect.\n");
        return 1;
    }
    return 0;
}

int check_error_redirection(char **str)
{
    for (int i = 0; str[i]; i++){
        if ((my_strcmp(str[i], ">") == 1 || my_strcmp(str[i], "<") == 1) &&
            check_ambiguous(str, i) == 1)
            return 1;
    }
    return 0;
}

char *tab_to_str(char **tab, char c)
{
    int len = 0;
    for (int i = 0; tab[i]; i++)
        len += my_strlen(tab[i]);
    char *str = malloc(sizeof(char) * (len + my_tablen((void **)tab) + 1));
    int j = 0;
    for (int i = 0; tab[i]; i++){
        for (int k = 0; tab[i][k]; k++)
            str[j++] = tab[i][k];
        if (str[j - 1] != '-')
            str[j++] = c;
    }
    str[j] = '\0';
    return str;
}

char **get_tab_command(char *str, int spaces)
{
    char **command = malloc(sizeof(char *) * (spaces + 2));
    command[spaces + 1] = NULL;
    int j = 0;
    for (int i = 0; str[0];){
        for (i = 0; str[i] && (is_letter(str[i]) || str[i] == '/'); i++);
        command[j] = my_strndup(str, i);
        str += i;
        if (!str[0])
            break;
        j++;
        i = 0;
        for (i = 0; str[i] && !is_letter(str[i]); i++);
        command[j] = my_strndup(str, i);
        str += i;
        if (!str[0])
            break;
        j++;
        i = 0;
    }
    return command;
}

char *spaces_commands(char *str)
{
    int spaces = 0;
    for (int i = 0; str[i];){
        for (; str[i] && (my_isalpha(&str[i]) || str[i] == '/'); i++);
        if (str[i])
            spaces++;
        for (; str[i] && !my_isalpha(&str[i]); i++);
        if (str[i])
            spaces++;
    }
    char **command = get_tab_command(str, spaces);
    return tab_to_str(command, ' ');
}
