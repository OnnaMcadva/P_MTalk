/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:28 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 23:17:05 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

static volatile sig_atomic_t g_ack_received = 0;

static void ack_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	g_ack_received = 1;
}

static void handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("Client terminated\n", 2);
	exit(0);
}

static void send_bit(pid_t pid, int bit)
{
	int	timeout;

	timeout = 1000;
	g_ack_received = 0;
	if (bit)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_putstr_fd("Error: Invalid PID\n", 2);
			exit(1);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_putstr_fd("Error: Invalid PID\n", 2);
			exit(1);
		}
	}
	if (kill(pid, 0) == -1)
	{
		ft_putstr_fd("Error: Invalid PID\n", 2);
		exit(1);
	}
	while (!g_ack_received && timeout > 0)
	{
		usleep(100);
		timeout--;
	}
	if (!g_ack_received)
	{
		ft_putstr_fd("Error: Server not responding\n", 2);
		exit(1);
	}
}

static void send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
		send_bit(pid, (c >> i--) & 1);
}

static void send_unicode_char(pid_t pid, const char **str)
{
	unsigned char c = **str;

	if ((c & 0x80) == 0) // 1 байт (ASCII)
	{
		send_char(pid, c);
		(*str)++;
	}
	else if ((c & 0xE0) == 0xC0) // 2 байта
	{
		send_char(pid, c);
		(*str)++;
		if (**str)
			send_char(pid, (unsigned char)**str);
		(*str)++;
	}
	else if ((c & 0xF0) == 0xE0) // 3 байта
	{
		send_char(pid, c);
		(*str)++;
		if (**str)
			send_char(pid, (unsigned char)**str);
		(*str)++;
		if (**str)
			send_char(pid, (unsigned char)**str);
		(*str)++;
	}
	else if ((c & 0xF8) == 0xF0) // 4 байта (эмодзи)
	{
		send_char(pid, c);
		(*str)++;
		if (**str)
			send_char(pid, (unsigned char)**str);
		(*str)++;
		if (**str)
			send_char(pid, (unsigned char)**str);
		(*str)++;
		if (**str)
			send_char(pid, (unsigned char)**str);
		(*str)++;
	}
}

int main(int argc, char **argv)
{
	struct sigaction	sa;
	struct sigaction	sa_int;
	pid_t				pid;
	const char			*str;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client_bonus <PID> <STRING>\n", 2);
		return (1);
	}
	sa.sa_sigaction = ack_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error setting SIGUSR1 handler\n", 2);
		return (1);
	}
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		ft_putstr_fd("Error setting SIGINT handler\n", 2);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	while (*str)
		send_unicode_char(pid, &str);
	send_char(pid, '\0');
	return (0);
}