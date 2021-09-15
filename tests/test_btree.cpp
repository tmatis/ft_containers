/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_btree.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:34:07 by tmatis            #+#    #+#             */
/*   Updated: 2021/09/15 20:33:37 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
#include <cassert>

void test_btree()
{
	ft::_rb_tree<int, std::less<int> > tree;

	for (int i = 0; i <= 10; i++)
	{
		std::cout << "insert " << i << std::endl;
		tree.insert(i);
		tree.print();
		std::cout << "----------------------" << std::endl; 
	}
	std::cout << "find:" << tree.find(5) << std::endl;
	std::cout << "find:" << tree.find(42) << std::endl; 
	for (int i = 0; i <= 10; i++)
	{
		std::cout << "erase " << i << std::endl;
		tree.remove(i);
		tree.print();
		std::cout << "----------------------" << std::endl;
	}
}
