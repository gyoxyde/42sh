/*
** EPITECH PROJECT, 2023
** PROJETS
** File description:
** my_cd
*/

#include "../../include/my.h"

static int cd_dir(var_t m, char *target)
{
    char *CWD = malloc(sizeof(char) * 1024);
    int special = m->special_cd;

    m->special_cd = 0;
    getcwd(CWD, 1024);
    errno = 0;
    if (chdir(target) == -1){
        (special == 0) ? my_error(m->target) : my_error(target);
        my_error(my_strcatt(3, ": ", strerror(errno), ".\n"));
        return 1;
    }
    m->str_OLDPWD = my_strdup(CWD);
    getcwd(CWD, 1024);
    if (m->PWD <= -1){
        add_line(m, "PWD", CWD);
        return 0;
    }
    m->OLDPWD = 1;
    m->env[m->PWD] = my_strdup(my_strcat("PWD=", CWD));
    return 0;
}

static int cd_home(var_t m)
{
    if (m->HOME <= -1){
        my_error("cd: No home directory.\n");
        return 1;
    }

    m->special_cd = 1;
    return cd_dir(m, (m->env[m->HOME] + 5));
}

static int cd_old(var_t m)
{
    if (m->OLDPWD == -1){
        my_error(": No such file or directory.\n");
        return 1;
    }

    m->special_cd = 1;
    return cd_dir(m, m->str_OLDPWD);

}

static int special_cd(var_t m, char **args)
{
    if (args[0] == NULL || args[0][0] == '\0')
        return cd_home(m);

    if (my_tablen((void **)args) > 1){
        my_error("cd: Too many arguments.\n");
        return 1;
    }

    if (args[0][0] == '~')
        return cd_home(m);

    if (args[0][0] == '-')
        return cd_old(m);
    return 0;
}

int my_cd(char **args, var_t m)
{
    char *a = args[0];
    char *PWD;
    char *new_PWD;
    int len;
    errno = 0;

    if (a != NULL)
        len = my_tablen((void **)args);

    if (a == NULL || len > 1 || a[0] == '-' || a[0] == '~' || a[0] == '\0')
        return special_cd(m, args);

    PWD = malloc(sizeof(char) * 1024);
    getcwd(PWD, 1024);
    new_PWD = (args[0][0] != '/') ? my_strcatt(3, PWD, "/", a) : my_strdup(a);
    m->target = my_strdup(a);

    return cd_dir(m, new_PWD);
}
