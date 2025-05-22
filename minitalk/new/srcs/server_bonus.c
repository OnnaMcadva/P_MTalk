/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:44 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 22:28:16 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

static	void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd(S_SHUT, 1);
	exit(0);
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int		bit_count = 0;
	static char		c = 0;
	static pid_t	client_pid = 0;

	(void)context;
	if (!info->si_pid)
		return ;
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
			ft_putendl_fd_v(S_END, 1);
		else
			write(1, &c, 1);
		bit_count = 0;
		c = 0;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	struct sigaction	sa_int;

	ft_putendl_fd_v(S_WLC, 1);
	ft_putstr_fd(S_PID, 1);
	ft_putnbr_fd_v(getpid(), 1);
	ft_putstr_fd(S_DOLF, 1);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
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
