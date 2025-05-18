/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:28 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/18 20:48:15 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"
#include <signal.h>
#include <unistd.h>

static volatile int g_ack_received = 0;

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

int	ft_atoi_v(const char *str)
{
	int	result = 0;

	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result);
}

void	ft_send_bit(int server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_ack_received = 0;
		if (c & (1 << bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (!g_ack_received)
			pause();
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;

	if (argc != 3)
	{
		write(1, "Usage: ./client <server_pid> <string>\n", 38);
		return (1);
	}

	server_pid = ft_atoi_v(argv[1]);
	if (server_pid <= 0)
	{
		write(1, "Invalid server PID\n", 19);
		return (1);
	}

	signal(SIGUSR1, ack_handler);

	i = 0;
	while (argv[2][i])
	{
		ft_send_bit(server_pid, argv[2][i]);
		i++;
	}
	ft_send_bit(server_pid, '\0');
	return (0);
}
