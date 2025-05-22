/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakaro <anmakaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:28 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 12:45:34 by anmakaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

static volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void send_bit(int pid, unsigned char bit)
{
    int timeout;

	timeout = 100;
    g_ack_received = 0;
	if (bit)
	    kill(pid, SIGUSR1);
	else
 	   kill(pid, SIGUSR2);
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

// static void	send_bit(int pid, unsigned char bit)
// {
// 	g_ack_received = 0;
// 	if (bit)
// 		kill(pid, SIGUSR1);
// 	else
// 		kill(pid, SIGUSR2);
// 	while (!g_ack_received)  // Ждём подтверждения
// 		pause();
// }

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
    	send_bit(pid, (c >> i--) & 1);
	
	// i = 8;
	// while (i--)
	// 	send_bit(pid, (c >> i) & 1);
}



int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <PID> <STRING>\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	signal(SIGUSR1, ack_handler);  // Настраиваем обработчик подтверждения
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');  // Отправляем завершающий нуль-символ
	return (0);
}
