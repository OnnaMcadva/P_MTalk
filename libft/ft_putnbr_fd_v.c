/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_v.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakaro <anmakaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:08:49 by anmakaro          #+#    #+#             */
/*   Updated: 2023/12/05 13:16:56 by anmakaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
