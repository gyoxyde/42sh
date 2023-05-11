/*
** EPITECH PROJECT, 2023
** echo_function.c
** File description:
** echo_function
*/

#include "shell.h"

void print_word(int i, char **array)
{
    for (int j = 0; array[i][j] != '\0'; j++) {
        if (array[i][j] != 34 && array[i][j] != 39)
            my_printf("%c", array[i][j]);
    }
}

void echo_with_opt(char **array)
{
    int count = 0;
    for (int i = 2; array[i] != NULL; i++) count++;
    for (int i = 2; array[i] != NULL; i++) {
        print_word(i, array);
        if (i <= count)
            my_printf(" ");
    }
}

void echo_no_opt(char **array)
{
    int count = 0;
    for (int i = 1; array[i] != NULL; i++) count++;
    for (int i = 1; array[i] != NULL; i++) {
        print_word(i, array);
        if (i < count)
            my_printf(" ");
    }
    printf("\n");
}

void echo_function(char **array)
{
    if (!my_strcmp(array[1], "-n"))
        echo_with_opt(array);
    else
        echo_no_opt(array);
}
