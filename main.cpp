/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/10/29 18:10:01 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.hpp"
#include <iostream>

int	main(void)
{
	int	a = 9;
	int b = 42;

	ft::vector<int>::Iterator it(&a);
	ft::vector<int>::Iterator it2(&b);

	//TODO ESTO PARA DECIR	(&a == &b) :_( :_(
	std::cout << std::boolalpha << (it == it2) << " " << (it != it2) << std::endl;
	
	return (0);
}