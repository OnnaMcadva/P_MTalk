/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:07:27 by anmakaro          #+#    #+#             */
/*   Updated: 2025/05/22 22:45:04 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define S_WLC "\n\033[0;94mWelcome to the server!\033[0m"
# define S_PID "\033[0;96mProcess ID: \033[0m"
# define S_DOLF "\n🐬\n"
# define S_END "\033[0;90m\n.. received ..\033[0m\n"
# define S_SHUT "\033[38;5;220m\nServer shutting down gracefully.\n\n\033[0m"

# define C_ERR_INV "\033[6;91mError: Invalid PID\n\033[0m"
# define C_ERR_RESP "\033[6;91mError: Server not responding\n\033[0m"
# define C_ARGS "\033[38;5;214mCopy/paste server PID and add a string\033[0m"
# define C_EX_ARGS "\033[0;92m./client 123 \"double quotation marks\"\033[0m"

#endif
