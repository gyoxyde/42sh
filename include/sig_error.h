/*
** EPITECH PROJECT, 2023
** PROJETS
** File description:
** sig_error
*/

#include "../include/my.h"

#pragma once

struct sig_struct{
    int signal;
    char *error_message;
    int return_value;
};
struct sig_struct sig_list[30] = {
    {SIGHUP, "Hangup", 129},
    {SIGINT, "\n", 1},
    {SIGQUIT, "Quit", 131},
    {SIGILL, "Illegal instruction", 132},
    {SIGTRAP, "Trace/BPT trap", 133},
    {SIGABRT, "Abort", 134},
    {SIGIOT, "Abort", 134},
    {SIGBUS, "Bus error", 135},
    {SIGFPE, "Floating exception", 136},
    {SIGKILL, "Killed", 137},
    {SIGUSR1, "User signal 1", 138},
    {SIGSEGV, "Segmentation fault", 139},
    {SIGUSR2, "User signal 2", 140},
    {SIGPIPE, "Broken pipe", 141},
    {SIGALRM, "Alarm clock", 142},
    {SIGTERM, "Terminated", 143},
    {SIGSTKFLT, "Stack limit exceeded", 144},
    {SIGSTOP, "\nSuspended (signal)", 1},
    {SIGTSTP, "\nSuspended", 1},
    {SIGTTIN, "\nSuspended (tty input)", 1},
    {SIGTTOU, "\nSuspended (tty output)", 1},
    {SIGXCPU, "Cputime limit exceeded", 152},
    {SIGXFSZ, "Filesize limit exceeded", 153},
    {SIGVTALRM, "Virtual time alarm", 154},
    {SIGPROF, "Profiling time alarm", 155},
    {SIGIO, "Pollable event occurred", 157},
    {SIGPOLL, "Pollable event occurred", 157},
    {SIGPWR, "Power failure", 158},
    {SIGSYS, "Bad system call", 159},
    {0, "", 0}
};
