/*
** EPITECH PROJECT, 2022
** my_ls
** File description:
** my
*/

#pragma once
#define _GNU_SOURCE
#include "garbage.h"
#define malloc my_malloc
#define free my_free
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "./my_printf.h"
#include <math.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

typedef struct my_variables{
    char **path;
    int variables_added;
    char **env;
    char **keys;
    char *str_OLDPWD;
    char *temp_PWD;
    char *target;
    int special_cd;
    int OLDPWD;
    int PWD;
    int HOME;
    int return_value;
    int *pipefd;
    int pipesave;
}my_var;
typedef my_var *var_t;

typedef struct my_pipes{
    int *fd;
    int *prev_fd;
    int old_stdin;
    int old_stdout;
    int i;
    int status;
}*pipes_t;

int my_cd(char **args, var_t m);
int my_setenv(char **args, var_t m);
int my_unsetenv(char **args, var_t m);
int my_env(char **args, var_t m);
int my_tablen(void **tab);
int my_execute(char **args, var_t m);
int my_other(char **args, var_t m);
int execute_command(char *command, var_t m);
void delete_tabline(int i, var_t m);
int get_path(var_t m);
int env_to_struct(char **env, var_t m);
int init_struct(var_t m, char **env);
int free_all(var_t m);
char **search_return_val(char **args, var_t m);
int analyse_arg(char *arg, char *command);
int error_execute(int return_value);
int change_pwd(var_t m, char *target);
void delete_line(int i, var_t m);
int add_line(var_t m, char *arg1, char *arg2);
int error_message(int return_value);
int command_not_found(int a, char *command);
int my_exit(char **args, var_t m);
int my_pipe(char **args, var_t m);
int my_redirection(char **args, var_t m);
int my_db_redirection(char **args, var_t m);
int my_input(char **args, var_t m);
int my_db_input(char **args, var_t m);
int dup_redirection(char **args, var_t m, int fd, int copy_fd);
int search_know_command(char **args, var_t m);
int parse_command(char *str, var_t m);
int get_string_index(char **args, char *str);
int dup_redirection(char **args, var_t m, int fd, int copy_fd);
int create_pipe(char *command, var_t m);
char *spaces_commands(char *str);
