/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakaro <anmakaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:44 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 12:58:30 by anmakaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nServer shutting down gracefully.\n", 34);
	exit(0);
}

static void handle_signal(int sig, siginfo_t *info, void *context)
{
    static int      bit_count = 0;
    static char     c = 0;
    static pid_t    client_pid = 0;

    (void)context;
    if (!info->si_pid)
        return;
    
    if (client_pid != info->si_pid)
    {
        client_pid = info->si_pid;
        bit_count = 0;
        c = 0;
    }

    if (sig == SIGUSR1)
        c |= (1 << (7 - bit_count));
    
    if (++bit_count == 8)
    {
        if (c == '\0')
            ft_putstr_fd("\nMessage received!\n", 1);
        else
            write(1, &c, 1);
        bit_count = 0;
        c = 0;
    }
    
    kill(client_pid, SIGUSR1);
}


// static void	handle_signal(int sig, siginfo_t *info, void *context)
// {
// 	static int				bit_itr = -1;
// 	static unsigned char	c;

// 	(void)context;
// 	if (bit_itr < 0)
// 		bit_itr = 7;
// 	if (sig == SIGUSR1)
// 		c |= (1 << bit_itr);
// 	bit_itr--;
// 	if (bit_itr < 0)
// 	{
// 		if (c == '\0')
// 			ft_putchar_fd('\n', 1);
// 		else
// 			ft_putchar_fd(c, 1);
// 		c = 0;
// 		bit_itr = 7;
// 	}
// 	kill(info->si_pid, SIGUSR1);
// }

int	main(void)
{
	struct sigaction	sa;
	struct sigaction	sa_int;

	printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	
	while (1)
		pause();
	return (0);
}


// void	ft_handle_signal(int signal, siginfo_t *siginfo, void *cont)
// {
// 	static int	bit = 0;
// 	static int	i = 0;

// 	(void)siginfo;
// 	(void)cont;
// 	if (signal == SIGUSR1)
// 		i |= (0x01 << bit);
// 	bit++;
// 	if (bit == 8)
// 	{
// 		ft_putchar_fd(i, 1);
// 		if (i == '\n')
// 			ft_putstr_fd(S_END_TRANS, 1);
// 		bit = 0;
// 		i = 0;
// 	}
// }

// int	main(void)
// {
// 	pid_t				pid;
// 	struct sigaction	sa;

// 	pid = getpid();
// 	ft_putendl_fd_v(S_WLC, 1);
// 	ft_putstr_fd(S_PID, 1);
// 	ft_putnbr_fd_v(pid, 1);
// 	ft_putstr_fd(S_END_TRANS, 1);
	
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = ft_handle_signal;
// 	sigemptyset(&sa.sa_mask);
// 	while (1)
// 	{
// 		sigaction(SIGUSR1, &sa, NULL);
// 		sigaction(SIGUSR2, &sa, NULL);
// 		pause();
// 	}
// 	return (0);
// }

