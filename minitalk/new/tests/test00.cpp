/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test00.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:39:08 by annavm            #+#    #+#             */
/*   Updated: 2025/05/22 19:39:09 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main() {
    std::string smile = "🙂";
    std::string cyrillic = "Ю";
    std::string chinese = "汉";

    std::cout << "Смайлик занимает: " << smile.size() << " байт\n";
    std::cout << "Русская буква занимает: " << cyrillic.size() << " байт\n";
    std::cout << "Китайская буква занимает: " << chinese.size() << " байт\n";

    return 0;
}
