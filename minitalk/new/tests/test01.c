/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakaro <anmakaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:39:21 by annavm            #+#    #+#             */
/*   Updated: 2025/05/23 19:18:49 by anmakaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	utf8_char_size(unsigned char c) {
	if ((c & 0x80) == 0x00) return 1;
	else if ((c & 0xE0) == 0xC0) return 2;
	else if ((c & 0xF0) == 0xE0) return 3;
	else if ((c & 0xF8) == 0xF0) return 4;
	else return 0;
}

int	main(void) {
	const char *str = "A Ю汉🙂 Жопа ";
	const unsigned char *p = (const unsigned char *)str;
	int count = 0;

	printf("Анализ строки: %s\n", str);
	while (*p) {
		int size = utf8_char_size(*p);
		printf("Символ: ");
		for (int i = 0; i < size; i++)
			printf("%c", p[i]);
		printf(" — занимает %d байт\n", size);

		p += size;
		count++;
	}

	printf("Всего символов: %d\n", count);
	return 0;
}
