/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:28 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/21 23:59:13 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

static volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	send_bit(int pid, unsigned char bit)
{
	g_ack_received = 0;
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	while (!g_ack_received)  // Ждём подтверждения
		pause();
}

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 8;
	while (i--)
		send_bit(pid, (c >> i) & 1);
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
    send_bit(pid, 0);
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');  // Отправляем завершающий нуль-символ
	return (0);
}


// #include "../incs/minitalk.h"

// static volatile sig_atomic_t g_ack_received = 0;

// static void ack_handler(int sig)
// {
//     (void)sig;
//     g_ack_received = 1;
// }

// static void send_bit(pid_t pid, int bit)
// {
//     int retries = 3;

//     while (retries--)
//     {
//         g_ack_received = 0;
//         if (bit)
//             kill(pid, SIGUSR1);
//         else
//             kill(pid, SIGUSR2);
        
//         usleep(500);
//         if (g_ack_received)
//             return;
//     }
//     ft_putstr_fd("Server not responding!\n", 2);
//     exit(1);
// }

// static void send_unicode_char(pid_t pid, int c)
// {
//     if (c > 127)
//     {
//         send_bit(pid, (0b11000000 | (c >> 6)));
//         send_bit(pid, (0b10000000 | (c & 0b00111111)));
//     }
//     else
//     {
//         send_bit(pid, c);
//     }
// }

// int main(int argc, char **argv)
// {
//     struct sigaction sa;
//     pid_t           pid;
//     char            *str;

//     if (argc != 3)
//     {
//         ft_putstr_fd("Usage: ./client_bonus <PID> <STRING>\n", 2);
//         return 1;
//     }

//     sa.sa_handler = ack_handler;
//     sa.sa_flags = 0;
//     sigemptyset(&sa.sa_mask);
//     sigaction(SIGUSR1, &sa, NULL);

//     pid = ft_atoi(argv[1]);
//     str = argv[2];

//     while (*str)
//     {
//         send_unicode_char(pid, *str);
//         str++;
//     }
//     send_bit(pid, '\0');
//     return 0;
// }