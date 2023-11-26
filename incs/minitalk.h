



#ifndef MINITALK_H
#define MINITALK_H

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stddef.h>

#define S_WLC "\n\033[0;94mWelcome to the server!\033[0m"
#define S_PID "\033[0;96mServer PID: \033[0m"
#define S_END_TRANS "\033[0;90m\nА котик где?..\033[0m\n"

#define C_ERROR "\n\033[6;91mAchtung Achtung !\033[0m"
#define C_ARGS "\033[38;5;214mAdd the server PID and a string или котика:)))\033[0m"
#define C_EX_ARGS "\033[0;92mExample : ./client 4242 \"To write a message use double quotation marks\"\033[0m\n"


int ft_atoi_v(const char *str);
void ft_send_bit(int server_pid, char c);
void	ft_putendl_fd_v(const char *s, int fd);

void ft_handle_signal(int signal, siginfo_t *siginfo, void *cont);

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd_v(int n, int fd);


#endif