/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** input.c
*/

#include "shell.h"

int get_size_term(void)
{
    struct winsize w;
    ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int get_line_size(shell_t *shell)
{
    char prompt[PATH_MAX];
    int prompt_size = 0;
    if (getcwd(prompt, sizeof(prompt)) != NULL)
        prompt_size = strlen(prompt) + 2 + strlen(shell->i->input_str);
    return prompt_size;
}

void add_new_char(shell_t *shell, char c)
{
    putchar(c);
    shell->i->input_str = realloc(shell->i->input_str, shell->i->size + 1);
    shell->i->input_str[shell->i->current_char++] = c;
    shell->i->size++;
}

void receive_c(shell_t *shell, char c)
{
    if (shell->i->history_index > shell->i->history_length)
        shell->i->history_index = shell->i->history_length;
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
