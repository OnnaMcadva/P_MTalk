/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakaro <anmakaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:44 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/23 20:18:36 by anmakaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

static	void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd(S_SHUT, 1);
	exit(0);
}

static int	utf8_char_size(unsigned char c)
{
	if ((c & 0x80) == 0x00)
		return (1);
	else if ((c & 0xE0) == 0xC0)
		return (2);
	else if ((c & 0xF0) == 0xE0)
		return (3);
	else if ((c & 0xF8) == 0xF0)
		return (4);
	else
		return (0);
}

static void	process_byte(unsigned char *buf, int *byte_count, unsigned char c)
{
	static int	utf8_len = 0;

	buf[(*byte_count)++] = c;
	if (*byte_count == 1)
		utf8_len = utf8_char_size(buf[0]);
	if (*byte_count == utf8_len)
	{
		buf[utf8_len] = '\0';
		ft_putstr_fd((char *)buf, 1);
		*byte_count = 0;
		utf8_len = 0;
	}
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	buf[5];
	static int				bit_count = 0;
	static int				byte_count = 0;
	static unsigned char	c = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (!info->si_pid)
		return ;
	client_pid = info->si_pid;
	c |= (sig == SIGUSR1) << (7 - bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		bit_count = 0;
		process_byte(buf, &byte_count, c);
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
