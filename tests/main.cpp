/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:04:30 by tmatis            #+#    #+#             */
/*   Updated: 2021/09/02 13:25:16 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void module_head(std::string module_name)
{
	std::cout << ">>> " << module_name << std::endl;
}

void module_foot(void)
{
	std::cout << "<<<" << std::endl;
}

int main(void)
{
	module_test("witness test", 42);
	test_vector();
}
