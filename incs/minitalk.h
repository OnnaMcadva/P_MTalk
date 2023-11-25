

#ifndef MINITALK_H
#define MINITALK_H

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stddef.h>

#define S_WLC "Welcome to the server!"
#define S_PID "Server PID: %d\n"
#define S_CHEV "Received end of transmission\n"

# define C_ERROR "\n\033[0;91mAchtung Achtung !\033[0m"
# define C_ARGS "\033[38;5;214mAdd the server PID and a string или котика:)))\033[0m"
# define C_EX_ARGS "\033[0;92mExample : ./client 4242 \"To write a message use double quotation marks\"\033[0m\n"

int ft_atoi_v(const char *str);
void    ft_send_bit(int server_pid, wchar_t c);
void	ft_putendl_fd_v(const char *s, int fd);

void ft_handle_signal(int sig, siginfo_t *siginfo, void *context);
void ft_print_error(const char *error_message);
void ft_print_args_error(void);

void ft_send_message(int server_pid, char *message);

#endif
