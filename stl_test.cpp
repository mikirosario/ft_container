/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:12:22 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/21 10:19:47 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_test.hpp"
#include "set_test.hpp"
#include "vector_test.hpp"
#include "stack_test.hpp"
#include <map>
#include <set>
#include <vector>
#include <stack>

int	main(void)
{
	map_test<std::map<std::string, std::string> >();
	set_test<std::set<std::string> >();
	vector_test<std::vector<int> >();
	stack_test<std::stack<int, std::vector<int> > >();
	return(0);
}
