/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test00.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakaro <anmakaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:39:08 by annavm            #+#    #+#             */
/*   Updated: 2025/05/23 13:03:33 by anmakaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main() {
    std::string smile = "🙂";
    std::string cyrillic = "Ю";
    std::string chinese = "汉";
    std::string japanese = "の";
    std::string czech = "ž";

    std::cout << "Smiley takes up: " << smile.size() << " bytes\n";
    std::cout << "Russian letter takes up: " << cyrillic.size() << " bytes\n";
    std::cout << "Chinese letter takes up: " << chinese.size() << " bytes\n";
    std::cout << "Japanese letter takes up: " << japanese.size() << " bytes\n";
    std::cout << "Czech letter takes up: " << czech.size() << " bytes\n";
    
    return 0;
}
