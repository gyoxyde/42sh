/*
** EPITECH PROJECT, 2023
** current
** File description:
** dbinput
*/

#include "../../../include/my.h"

static char *llist_to_str(l_list list)
{
    char *str = my_strcat(list->data, "\n");
    l_list tmp = list->next;

    do {
        str = my_strcatt(3, str, tmp->data, "\n");
        tmp = tmp->next;
    } while (tmp != list);
    return str;
}

static char *get_heredoc(char *end_of_file, l_list list)
{
    size_t size = 0;
    ssize_t read;
    char *co = NULL;
    if (isatty(0))
        my_printf("? ");
    read = getline(&co, &size, stdin);
    while (read != -1) {
        co[my_strlen(co) - 1] = '\0';
        if (my_strcmp(co, end_of_file) == 1)
            break;
        list = insert_end(my_strdup(co), list);
        if (isatty(0))
            my_printf("? ");
        free(co);
        co = NULL;
        read = getline(&co, &size, stdin);
    }
    if (read == -1)
        list = delete_begin(list);
    return llist_to_str(list);
}

int my_db_input(char **args, var_t m)
{
    int i = get_string_index(args, "<");

    if (i == -1)
        return 1;
    char *end_of_file = args[i + 1];
    if (end_of_file == NULL)
        return 1;
    for (int j = i, len = my_tablen((void **)args); j + 1 != len; j++)
        args[j] = args[j + 2];
    l_list list = NULL;
    char *file = get_heredoc(end_of_file, list);
    int pipefd[2];
    if (pipe(pipefd) == -1)
        return 1;
    write(pipefd[1], file, my_strlen(file));
    close(pipefd[1]);
    return dup_redirection(args, m, pipefd[0], 0);
}
