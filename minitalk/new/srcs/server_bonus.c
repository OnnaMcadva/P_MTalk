/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:44 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 00:46:59 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nServer shutting down gracefully.\n", 34);
	exit(0);
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int				bit_itr = -1;
	static unsigned char	c;

	(void)context;
    if (!info->si_pid) // Проверяем валидность PID клиента
        return;
	if (bit_itr < 0)
		bit_itr = 7;
	if (sig == SIGUSR1)
		c |= (1 << bit_itr);
	bit_itr--;
	if (bit_itr < 0)
	{
		if (c == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(c, 1);
		c = 0;
        bit_itr = 7;
	}
	g_received_bit = 1;
	kill(info->si_pid, SIGUSR1);  // Отправляем подтверждение клиенту
}

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


// #include "../incs/minitalk.h"

// static void handle_signal(int sig, siginfo_t *info, void *context)
// {
//     static int      bit_count = 0;
//     static char     c = 0;
//     static pid_t    client_pid = 0;

//     (void)context;
//     if (!info->si_pid)
//         return;
    
//     // Обработка нового клиента
//     if (client_pid != info->si_pid)
//     {
//         client_pid = info->si_pid;
//         bit_count = 0;
//         c = 0;
//     }

//     if (sig == SIGUSR1)
//         c |= (1 << (7 - bit_count));
    
//     if (++bit_count == 8)
//     {
//         if (c == '\0')
//             ft_putstr_fd("\nMessage received!\n", 1);
//         else
//             write(1, &c, 1);
//         bit_count = 0;
//         c = 0;
//     }
    
//     // Отправка подтверждения
//     kill(client_pid, SIGUSR1);
// }