/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2022/01/21 07:08:47 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"

int	print_err(std::string const & msg)
{
	std::cerr << msg << std::endl;
	return (1);
}

size_t	get_arg_id(std::string const & arg)
{
	size_t			id = 0;
	std::string	valid_args[TEST_NUM] =	{"iterator",
										"vector",
										"map",
										"stack",
										"set",
										"treeprint"};
	for ( ; id < TEST_NUM && arg != valid_args[id]; ++id) {}
	return (id);
}

int main(int const argc, char const ** argv)
{	
	bool				res;
	size_t				arg_id;
	bool (*tester[])() =	{iterator_tests,		//0
							my_veritable_vector,	//1
							my_magnificent_map,		//2
							my_stupendous_stack,	//3
							my_superlative_set,		//4
							my_talkative_tree};		//5

	if (argc == 2 && (arg_id = get_arg_id(argv[1])) < TEST_NUM)
	{
		res = tester[arg_id]();
		if (res == true)
			PRINT << TXT_BGRN "OK" << END;
		else
			PRINT << TXT_BRED "KO" << END;
	}
	else
	{
		//system("leaks ft_container");
		return (print_err(TXT_BRED "Pass a single argument indicating the container to test (vector, map, set, stack)"));
	}
	//system("leaks ft_container");
	return (0);
}
