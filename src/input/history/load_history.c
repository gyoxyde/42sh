/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** load_history.c
*/

#include "shell.h"

void navigate_history(shell_t *shell, char *line)
{
    if (shell->i->history_length == HISTORY_SIZE) {
        free(shell->i->history[0]);
        for (int j = 0; j < HISTORY_SIZE - 1; j++) {
            shell->i->history[j] = shell->i->history[j + 1];
        }
        shell->i->history_length--;
    }
    shell->i->history[shell->i->history_length++] = strdup(line);
}

void line_comp(shell_t *shell, char *line, int *i)
{
    for (*i = 0; *i < shell->i->history_length; (*i)++) {
        if (strcmp(line, shell->i->history[*i]) == 0)
            break;
    }
}

void load_history(shell_t *shell)
{
    FILE *file = fopen(".history", "r");
    if (file == NULL)
        return;
    char *line = malloc(sizeof(char) * 1024);
    if (fgets(line, 1024, file) == NULL)
        shell->i->history[0] = NULL;
    while (fgets(line, 1024, file) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        int i;
        line_comp(shell, line, &i);
        if (i == shell->i->history_length) {
            navigate_history(shell, line);
        } else {
            free(line);
        }
        line = malloc(sizeof(char) * 1024);
    }
    fclose(file);
    free(line);
}
