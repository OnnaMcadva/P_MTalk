/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_v.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:31:52 by annavm            #+#    #+#             */
/*   Updated: 2023/11/26 19:31:55 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minitalk.h"

void	ft_putnbr_fd_v(int n, int fd)
{
	long int	helpa;

	helpa = n;
	if (helpa >= 10)
	{
		ft_putnbr_fd_v(helpa / 10, fd);
		ft_putchar_fd(helpa % 10 + '0', fd);
	}
	else
		ft_putchar_fd(helpa + '0', fd);
}
