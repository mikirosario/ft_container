/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_test.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 07:54:37 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/21 10:16:38 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_test.hpp"
#include "set_test.hpp"
#include "vector_test.hpp"
#include "stack_test.hpp"
#include "map.hpp"
#include "set.hpp"
#include "vector.hpp"
#include "stack.hpp"

int	main(void)
{
	map_test<ft::map<std::string, std::string> >();
	set_test<ft::set<std::string> >();
	vector_test<ft::vector<int> >();
	stack_test<ft::stack<int> >();

	return(0);
}
