/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakaro <anmakaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:15:12 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 11:37:19 by anmakaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

int         ft_atoi_v(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd_v(const char *s, int fd);
void	ft_putnbr_fd_v(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif