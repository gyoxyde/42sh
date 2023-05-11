/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** 42sh
*/

#ifndef mysh1_h
    #define mysh1_h
    #define HISTORY_SIZE 100
    #include "my.h"
    #include "unistd.h"
    #include <stdio.h>
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
    #include <termios.h>
    #include <termio.h>

typedef struct alias_s {
    char *pathfile;
    int number_letter;
    char *contenu;
    char **file;
    int count;
    int save_temp;
    int save_file;
    char *str_alias;
} alias_t;

typedef struct input_s {
    char *input_str;
    size_t size;
    int current_char;
    /////HISTORY
    char **history;
    int history_index;
    int history_length;
} input_t;

typedef struct pipes_s {
    int *fd;
    int *prev_fd;
    int old_stdin;
    int old_stdout;
    int i;
    int status;
} pipes_t;

typedef struct shell_s {
    pipes_t *p;
    alias_t *a;
    input_t *i;
    char **env;
    char **local;
    char **array;
    char **array_pipe;
    char *redirect_str;
    char *redirect_lstr;
    char *oldpwd;
    char *temp_oldpwd;
    char *str;
    int index_path_found;
    int index_array;
    int index_array_pipe;
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
    bool recurs_pipe;
    bool hasBeenPiped;
    bool islocal;
} shell_t;

enum cd_errors_type {
    TOO_MANY,
    NO_FILE,
    NOT_DIR,
    PERM_DENIED,
    NO_HOME,
    NO_HOME_VAR,
    CHDIR,
    NO_HOME2,
    NO_NAME,
    INVALID_CMD,
    NO_DUP2,
    AMBIGUOUS_INPUT,
    AMBIGUOUS_OUTPUT,
    RIGHT_REDI,
    LEFT_REDI
};

enum builtin_type {
    NOT_BUILT_IN,
    CD,
    SETENV,
    UNSETENV,
    ENV,
    EXIT,
    CD_NO_AV,
    CD_DASH,
    EXECUTE,
    EXECUTE_CURR_DIR,
    CD_WAVE,
    SET,
    UNSET,
    AL_NO_AV,
    AL,
    AL_ONE_AV,
    UA,
    UA_NO_AV,
    EC
};

enum set_errors_enum {
    BEGIN_LETTER,
    ALPHANUM_CHAR,
    PARENTHESIS_LEFT,
    PARENTHESIS_RIGHT,
    QUOTES
};

typedef struct special_variable_s {
    char **env;
    char **local;
    int exit_code;
} *special_var_t;


int shell_start(shell_t *shell);
void shell_loop(shell_t *shell, char **temp_array);
char *my_getstr(shell_t *shell);
char *intty_or_not(shell_t *shell);
int count_av(char *str);
void signal_handler(void);
void ctrl_c_handler(int signum);
int get_correct_path_fct(char **array, shell_t *shell);
int prompt(shell_t *shell);
int check_segfault(int status);
void fill_exit_code(int status, shell_t *shell);
int change_oldpwd(shell_t *shell);
void check_errno(char **array);
int my_asprintf(char **str, const char *format, ...);

// return NULL if there's no key in the env. Else, it returns the value str.
void signal_handler(void);
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
void alias_no_av_fct(shell_t *shell);
void alias_fct(shell_t *shell);
int check_alias_exist(shell_t *shell);
void alias_one_av(shell_t *shell);
void unalias_function(shell_t *shell);
void echo_function(char **array);

int check_path(shell_t *shell, char **array);
int check_built_in_fct2(char *str);

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

char *clean_pipe(char *str);
void give_pipe(char *str, int x, char *dest, int *i);
int check_start_pipe_str(char *str, int x, char *dest, int *i);
int count_pipe(char *str);
void give_pipe_two(char *str, int x, char *dest, int *i);

// Loop execve for semicolon
bool fill_array(shell_t *shell, char **array);

// Loop execve for pipe
bool fill_array_pipe(shell_t *shell, char **array);

bool check_redirection(shell_t *shell, char **array);
void take_redirection_str(shell_t *shell, char **array, int i, char *str);
void take_redirection_lstr(shell_t *shell, char **array, int i, char *str);

bool isitrightredirection(char **array);
bool isitdoublerightredirection(char **array);
bool isitleftredirection(char **array);
bool isitdoubleleftredirection(char **array);
bool check_error_redirection(shell_t *shell, char **array, bool *recurs);

int shell_redirection(shell_t *shell, char **array, int number_av);
void shell_do_fct(shell_t *shell, char **array, int number_av);

int my_right_redirection(shell_t *shell, char ***array, int *fd);
int my_doubleright_redirection(shell_t *shell, char ***array, int *fd);
int count_redirections(shell_t *shell, char **array, bool *recurs);
int my_left_redirection(shell_t *shell, char ***array, int *fd);
int my_doubleleft_redirection(shell_t *shell, char ***array);

int check_start_right_str(char *str, int x, char *dest, int *i);

void add_redright(shell_t *shell, char **array,
int *simple_redR, int *double_redR);
void add_redleft(shell_t *shell, char **array,
int *simple_redL, int *double_redL);
int check_second_redi(char **array, int i, int j);

int get_avnb(shell_t *shell, char **array, int *number_av);

int check_start_left_str(char *str, int x, char *dest, int *i);
int parthing_for_redirections(shell_t *shell, char **array, int number_av);

// pipe.c
int create_pipe(shell_t *shell);
int pipe_loop(char **array, shell_t *shell);
int close_all(shell_t *shell);
void pipe_fork(char **array, shell_t *shell);
void pipe_parent(shell_t *shell);
void pipe_child(shell_t *shell);

void close_all_fd(shell_t *shell, char **array, int number_av);

//clean_separator2.c
char *clean_double_and(char *str);
int count_double_and(char *str);
void give_double_and(char *str, int x, char *dest, int *i);
void give_double_and_two(char *str, int x, char *dest, int *i);

void init_all(shell_t *shell);
void init_loop(shell_t *shell);
void get_cleaned_str(shell_t *shell);

//error_command.c
bool check_error_recursive(shell_t *shell, char **array);
int dup_redirection(char **args, shell_t *shell, int fd, int copy_fd);

int redi_error_message(int type, shell_t *shell, char *str);

int close_right_fd(shell_t *shell);
int write_double_left_pipe(shell_t *shell, int *pipefd, char *file);
char *get_heredoc(char *end_of_file, shell_t *shell);

int check_for_ambiguous(shell_t *shell, char **array, bool *recurs);
int ambiguous_error(shell_t *shell, int type, bool *recurs);

void exec_parent_process(shell_t *shell, char **array);
void exec_child_process(shell_t *shell, char **array, char *path);

int check_exec_cmd(char **array, shell_t *shell, char **path);


//    BUILTIN SET / UNSET

char *my_getlocal(shell_t *shell, char *key);
char **get_keys(char **user_input, shell_t *shell);
char **get_values(char **user_input, shell_t *shell);
int get_local_index(char **local);
void order_local(char **keys, char **values, int len);
char *set_errors(int type, shell_t *shell);
char **get_flat_input(char **user_input, shell_t *shell);
int my_set_display(shell_t *shell);
int my_unset(shell_t *shell, char **array);
int my_setlocal(shell_t *shell, char **array);
int check_if_fct_is_here(char **path_array, char **array, int index);
void init_local(shell_t *shell);

char **search_special_var(char **args, shell_t *shell);
char **change_globbings(char **array, shell_t *shell);
int check_globbings_env(shell_t *shell, char **array);
//

//input/is_input_tty.c
char *intty_or_not(shell_t *shell);

//input/backspace_input.c
void backspace(shell_t *shell);

//input/arrow_input.c
void arrow(shell_t *shell);

//input/error_input.c
void error_input(shell_t *shell, char c);

//input/history/
void history_up(shell_t *shell);
void history_down(shell_t *shell);
void history_add(shell_t *shell);

//Check alias type
int check_which_alias(int number_av, char *str);

//Define array to execute
char **def_temp_array(shell_t *shell);

//Find alias position
void find_cor(char **temp_array, shell_t *shell);

//create new_array
char **create_new_array(shell_t *shell, char **temp_array, char **take_com,
                        int count_space);
char **create_tab_alias(char *str, char **alias_tab);

int check_pipe_redirection(shell_t *shell, char **array,
char *redirection, int type_error);

#endif /* !mysh1_h */
