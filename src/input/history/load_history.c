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

void close_history_file(FILE *file, char *line)
{
    fclose(file);
    free(line);
}

void parse_history_line(shell_t *shell, char *line, int history_length)
{
    line[strcspn(line, "\r\n")] = '\0';
    int i;
    line_comp(shell, line, &i);
    if (i == shell->i->history_length) {
        navigate_history(shell, line);
    } else {
        free(line);
    }
    shell->i->history_index = history_length;
    shell->i->history[shell->i->history_length] = NULL;
}

void load_history(shell_t *shell)
{
    FILE *file = fopen(".history", "r");
    char *line = malloc(sizeof(char) * 1024);
    int history_length = 1;
    if (file == NULL) {
        shell->i->history[-1] = NULL;
        return;
    }
    if (fgets(line, 1024, file) == NULL) {
        close_history_file(file, line);
        shell->i->history[-1] = NULL;
        return;
    }
    parse_history_line(shell, line, history_length);
    while (fgets(line, 1024, file) != NULL) {
        parse_history_line(shell, line, ++history_length);
        line = malloc(sizeof(char) * 1024);
    }
    close_history_file(file, line);
}
