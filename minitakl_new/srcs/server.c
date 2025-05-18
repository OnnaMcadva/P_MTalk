/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:44 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/18 20:44:53 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"
#include <signal.h>
#include <unistd.h>

typedef struct s_server_state
{
	pid_t client_pid;
	int bit_count;
	unsigned char current_char;
} t_server_state;

static t_server_state g_state = {0, 0, 0};

void	send_ack(pid_t pid)
{
	if (pid != 0)
		kill(pid, SIGUSR1);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;

	if (g_state.client_pid != info->si_pid)
	{
		g_state.client_pid = info->si_pid;
		g_state.bit_count = 0;
		g_state.current_char = 0;
	}

	if (sig == SIGUSR1)
		g_state.current_char |= (1 << g_state.bit_count);
	g_state.bit_count++;

	if (g_state.bit_count == 8)
	{
		if (g_state.current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &g_state.current_char, 1);
		g_state.bit_count = 0;
		g_state.current_char = 0;
	}
	send_ack(g_state.client_pid);
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	write(1, "Server PID: ", 12);
	ft_putnbr_fd_v(pid, 1);
	write(1, "\n", 1);

	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}
