/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakaro <anmakaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:28:28 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 11:45:57 by anmakaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

void	ft_send_bit(int server_pid, char c)
{
	int	index_bit;

	index_bit = 0;
	while (index_bit < 8)
	{
		if (c & (0x01 << index_bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(1000);
		index_bit++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	server_pid;

	i = 0;
	server_pid = ft_atoi_v(av[1]);
	if (ac == 3 && server_pid > 1)
	{
		while (av[2][i])
		{
			ft_send_bit(server_pid, av[2][i]);
			i++;
		}
		ft_send_bit(server_pid, '\n');
	}
	else
	{
		ft_putendl_fd_v(C_ARGS, 1);
		ft_putendl_fd_v(C_EX_ARGS, 1);
	}
	return (0);
}
