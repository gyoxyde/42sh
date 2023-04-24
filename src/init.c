/*
** EPITECH PROJECT, 2023
** PROJETS
** File description:
** init
*/

#include "../include/my.h"

static int init_void_env(var_t m)
{
    errno = 0;
    m->env = malloc(sizeof(char *) * 128);
    m->keys = malloc(sizeof(char *) * 128);
    for (int i = 0; i < 128; i++){
        m->keys[i] = NULL;
        m->env[i] = NULL;
    }

    m->temp_PWD = malloc(sizeof(char) * 1024);
    if (getcwd(m->temp_PWD, 1024) == NULL)
        my_error(my_strcat(strerror(errno), ".\n"));

    m->path = malloc(sizeof(char *));
    m->path[0] = malloc(sizeof(char));
    m->path[0] = NULL;
    return 1;
}

int init_struct(var_t m, char **env)
{
    m->PWD = -1;
    m->HOME = -1;
    m->return_value = 0;
    m->special_cd = 0;
    m->OLDPWD = -1;
    m->str_OLDPWD = NULL;

    if (env[0] == NULL)
        return init_void_env(m);

    env_to_struct(env, m);
    get_path(m);
    return 1;
}

int env_to_struct(char **env, var_t m)
{
    int key_len;
    int i;

    m->env = malloc(sizeof(char *) * (my_tablen((void **)env) + 64));
    m->keys = malloc(sizeof(char *) * (my_tablen((void **)env) + 64));
    m->env[my_tablen((void **)env)] = NULL;
    m->keys[my_tablen((void**)env)] = NULL;

    for (i = 0; env[i]; i++){
        for (key_len = 0; env[i][key_len] != '='; key_len++);
        m->keys[i] = malloc(sizeof(char) * key_len + 1);
        m->keys[i] = my_strncpy(m->keys[i], env[i], key_len);
        m->keys[i][key_len] = '\0';
        m->env[i] = my_strdup(env[i]);
    }
    m->env[i] = NULL;
    m->keys[i] = NULL;
    return 1;
}

int get_path(var_t m)
{
    for (int i = 0; m->env[i]; i++){
        if (my_strcmp(m->keys[i], "PWD")){
            m->PWD = i;
            continue;
        }
        if (my_strcmp(m->keys[i], "PATH")){
            m->path = to_word_array(m->env[i], ':');
            continue;
        }
        if (my_strcmp(m->keys[i], "HOME")){
            m->HOME = i;
            continue;
        }
    }
    return 1;
}
