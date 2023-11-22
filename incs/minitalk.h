

#ifndef MINITALK_H
#define MINITALK_H

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define S_WLC "Welcome to the server!"
#define S_PID "Server PID: %d\n"
#define S_CHEV "Received end of transmission\n"

void ft_handle_signal(int sig, siginfo_t *siginfo, void *context);
void ft_print_error(const char *error_message);
void ft_print_args_error(void);
void ft_send_bit(int pid, char c, int bit_delay);
void ft_send_message(int server_pid, char *message);
void ft_putendl_fd(const char *str, int fd);
int ft_is_str_digit(char *s);
int ft_atoi(const char *str);



#endif
