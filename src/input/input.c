/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** input.c
*/

#include "shell.h"


char *string_shift(char *string, shell_t *shell)
{
    for (int i = (int) shell->i->size; i > shell->i->current_char; i--) {
        string[i] = string[i - 1];
    }
    return string;
}

void add_new_char(shell_t *shell, char c)
{
    if (shell->i->current_char < (int) shell->i->size) {
        shell->i->input_str = string_shift(shell->i->input_str, shell);
        printf("\033[%iC", (int) shell->i->size - shell->i->current_char);
        for (int j = (int) shell->i->size; j > 0; j--) {
            printf("\b \b");
        }
    } else
        putchar(c);
    shell->i->input_str = realloc(shell->i->input_str, shell->i->size + 1);
    shell->i->input_str[shell->i->current_char++] = c;
    shell->i->size++;
    if (shell->i->current_char < (int) shell->i->size) {
        for (int i = 0; i < (int) shell->i->size; i++) {
            printf("%c", shell->i->input_str[i]);
        }
        printf("\033[%iD", (int) shell->i->size - shell->i->current_char);
    }
}

void receive_c(shell_t *shell, char c)
{
    if (c == 27) {
        arrow(shell);
    } else if (c == '\b' || c == 127) {
        backspace(shell);
    } else {
        add_new_char(shell, c);
    }
}

char *my_getstr(shell_t *shell)
{
    shell->i->input_str = malloc(sizeof(char) + 1);
    memset(shell->i->input_str, 0, 0);
    shell->i->size = 0;
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VEOF] = 4;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    int c;
    shell->i->current_char = 0;
    shell->i->history_index = shell->i->history_length;
    while ((c = getchar()) != '\n' && c != VEOF)
        receive_c(shell, c);
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    error_input(shell, c);
    putchar('\n');
    history_add(shell);
    return shell->i->input_str;
}
