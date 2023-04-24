/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** minishell_2
*/
#include "my.h"
#include "unistd.h"
#include "stdio.h"
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#ifndef mysh1_h
    #define mysh1_h

typedef struct shell_s {
    char **env;
    char **array;
    char *redirect_str;
    char *redirect_lstr;
    char *oldpwd;
    char *temp_oldpwd;
    int index_path_found;
    int index_array;
    int recurs_nb;
    int exit_code;
    int temp_exit_code;
    bool wasItCd;
    int number_av;
    int fd2;
    int fd;
    int index_redi;
    int index_simpleR;
    int index_simpleL;
    int index_doubleR;
    int index_doubleL;
    ////// For left redirection
    pid_t pid;
    bool isRightDupDone;
    bool isLeftDupDone;
    ////////////////////////////
} shell_t;

int shell_start(shell_t *shell);
int shell_loop(shell_t *shell, char *str);
char *my_getstr(shell_t *shell);
int count_av(char *str);
void signal_handler(void);
void ctrl_c_handler(int signum);
int get_correct_path_fct(char **array, shell_t *shell);
int prompt(shell_t *shell);
int check_segfault(int status);
void fill_exit_code(int status, shell_t *shell);
int change_oldpwd(shell_t *shell);
void check_errno(char **array);

// return NULL if there's no key in the env. Else, it returns the value str.
char *my_getenv(char **env, char *key);

// Print the segfault_str by taking the "wait" status.
int check_error_segfault(int status, shell_t *shell);

// Write on error output
void print_error(char *str);

// Check if we are executing a directory or a file without +x chmod permission.
int isitdir_exec_cmd(char **array, shell_t *shell, char *path);

// Execute command from mysh
int execute_cmd(char **array, shell_t *shell);
void built_in_function(char **array, shell_t *shell, int number_av);
int check_built_in_fct(char *str, char **array, int number_av);

// Check if it's a ./"str" file in the current directory before checking path
int check_curr_dir(char *str);
int fct_curr_dir(char **array, shell_t *shell);

// Let's do a built_in_fct
int cd_fct(shell_t *shell, char *filepath, int number_av);
int cd_no_av_fct(shell_t *shell, int number_av);
int cd_dash_fct(int number_av, shell_t *shell);
int exec_cd_dash(shell_t *shell, char *oldpwd);
int exit_fct(int number_av, shell_t *shell, char **array);
void print_env(char **env);
int setenv_fct(shell_t *shell, char **array, int number_av);
int change_setenv(shell_t *shell, char *key, char *value);
int unsetenv_fct(shell_t *shell, char **array, int number_av);
void unsetenv_loop(shell_t *shell, char **array, int i);
int check_key_str(char *key, shell_t *shell);
int check_number_exit(shell_t *shell, char **array);

int check_path(shell_t *shell, char **array);

// Clean separator
char *clean_separator(char *str);
void give_separator(char *str, int x, char *dest, int *i);
int check_end_of_str_separator(char *str);
int count_sepator(char *str);

// Clean right redirection
char *clean_right_redi(char *str);
void give_right_redi(char *str, int x, char *dest, int *i);
int check_end_of_str_right_redi(char *str);
int count_right_redi(char *str);
void give_left_redi_two(char *str, int x, char *dest, int *i);

// Clean left redirection
char *clean_left_redi(char *str);
void give_left_redi(char *str, int x, char *dest, int *i);
int check_end_of_str_left_redi(char *str);
int count_left_redi(char *str);
void give_right_redi_two(char *str, int x, char *dest, int *i);

// Loop execve for semicolon
bool fill_array(shell_t *shell, char **array);

bool check_redirection(shell_t *shell, char **array);
void take_redirection_str(shell_t *shell, char **array, int i, char *str);
void take_redirection_lstr(shell_t *shell, char **array, int i, char *str);

bool isitrightredirection(char **array);
bool isitdoublerightredirection(char **array);
bool isitleftredirection(char **array);
bool isitdoubleleftredirection(char **array);
bool check_error_redirection(shell_t *shell, char **array, bool *recurs);

void shell_redirection(shell_t *shell,
char **array, int number_av);
void shell_do_fct(shell_t *shell, char **array, int number_av);

int my_right_redirection(shell_t *shell, char ***array, int *fd);
int my_doubleright_redirection(shell_t *shell, char ***array, int *fd);
int count_redirections(char **array, int i, int *nb_right, int *nb_left);
int my_left_redirection(shell_t *shell, char ***array, int *fd);
int my_doubleleft_redirection(shell_t *shell, char ***array, int *fd);

int check_start_right_str(char *str, int x, char *dest, int *i);

void add_redright(shell_t *shell, char **array,
int *simple_redR, int *double_redR);
void add_redleft(shell_t *shell, char **array,
int *simple_redL, int *double_redL);
int check_second_redi(char **array, int i, int j);

int get_avnb(shell_t *shell, char **array, int *number_av);

int check_start_left_str(char *str, int x, char *dest, int *i);
int parthing_for_redirections(shell_t *shell, char **array, int number_av);


#endif /* !mysh1_h */
