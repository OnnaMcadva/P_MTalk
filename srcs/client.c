/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:31:13 by annavm            #+#    #+#             */
/*   Updated: 2023/11/26 19:31:19 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

int	ft_atoi_v(const char *str)
{
	int	result;

	if (str == NULL)
	{
		return (0);
	}
	result = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
	{
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

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
		usleep(500);
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
		ft_putendl_fd_v(C_ERROR, 1);
		ft_putendl_fd_v(C_ARGS, 1);
		ft_putendl_fd_v(C_EX_ARGS, 1);
	}
	return (0);
}
