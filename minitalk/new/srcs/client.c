/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:28 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 23:23:59 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

static volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	g_ack_received = 1;
}

static void	send_bit(int pid, unsigned char bit)
{
	int	timeout;

	timeout = 1000;
	g_ack_received = 0;
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	if (kill(pid, 0) == -1)
	{
		ft_putstr_fd(C_ERR_INV, 2);
		exit(1);
	}
	while (!g_ack_received && timeout > 0)
	{
		usleep(100);
		timeout--;
	}
	if (!g_ack_received)
	{
		ft_putstr_fd(C_ERR_RESP, 2);
		exit(1);
	}
}

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
		send_bit(pid, (c >> i--) & 1);
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*str;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_putendl_fd_v(C_ARGS, 1);
		ft_putendl_fd_v(C_EX_ARGS, 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	sa.sa_sigaction = ack_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
	return (0);
}
