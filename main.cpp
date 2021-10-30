/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/10/31 00:46:18 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.hpp"
#include <iostream>

int	main(void)
{

	int a[2] = {9,42};

	ft::vector<int>::iterator it(&a[0]);
	ft::vector<int>::iterator it2(&a[1]);

	// //const_iterator test, uncomment to test.
	// //Compiler will allow *it = 0, but not *cit = 0 :)
	// ft::vector<int>::const_iterator cit(&a[0]);
	// *it = 0;
	// *cit = 0;

	//TODO ESTO PARA DECIR	(&a == &b) :_( :_(
	std::cout << std::boolalpha << (it == it2) << " " << (it != it2) << std::endl;
	std::cout << std::boolalpha << (it > it2) << " " << (it < it2) << std::endl;
	std::cout << std::boolalpha << (it >= it) << " " << (it >= it2) << std::endl;
	std::cout << std::boolalpha << (it <= it) << " " << (it <= it2) << std::endl;
	std::cout << std::boolalpha << (it++ == it) << " " << (it == it2) << std::endl;
	--it;
	std::cout << std::boolalpha << ((it + 1) == it2) << " " << (it == it2) << std::endl;
	std::cout << std::boolalpha << ((it2 - 1) == it) << " " << (it == it2) << std::endl;

	std::cout << *it << "," << *(it + 1) << std::endl;
	std::cout << it[1] << "," << it[0] << std::endl;

	return (0);
}