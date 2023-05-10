/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** backspace_input.c
*/

#include "shell.h"

char *bs_mid_str(char *string, int j, shell_t *shell)
{
    char *copy = malloc(sizeof(char) * (shell->i->size - 1));
    int k = 0;
    for (int i = 0; i < (int) shell->i->size; i++) {
        if (i != j) {
            copy[k] = string[i];
            k++;
        }
    }
    return copy;
}

void backspace(shell_t *shell)
{
    if (shell->i->current_char < (int) shell->i->size
    && shell->i->current_char > 0) {
        shell->i->input_str =
        bs_mid_str(shell->i->input_str, shell->i->current_char - 1, shell);
        printf("\033[%iC", (int) shell->i->size - shell->i->current_char);
        for (int j = (int) shell->i->size - shell->i->current_char;
        j >= 0; j--) {
            printf("\b \b");
        }
        for (int l = shell->i->current_char - 1;
        l < (int) shell->i->size - 1; l++)
            printf("%c", shell->i->input_str[l]);
        printf("\033[%iD", (int) shell->i->size - shell->i->current_char);
        shell->i->current_char--;
        shell->i->size--;
    } else if (shell->i->current_char > 0) {
        printf("\b \b");
        shell->i->current_char--;
        shell->i->size--;
    }
}
