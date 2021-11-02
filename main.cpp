/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/02 18:56:58 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.hpp"
#include "type_traits.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

#define GRN "\e[1;32m"
#define RED "\e[1;31m"
#define YEL "\e[1;33m"
#define RST "\e[0m"
#define PRINT std::cout
#define NL "\n"
#define TAB "\t"
#define ALN std::left << std::setw(30)
#define SEP "-------------------------------------------------------------------------------------"
#define END RST << NL
#define SET std::setw(9) << color
									//reference to pointer
void	check(bool result, char const *& color, bool & ret)
{
	//Return check
	if (result == true)
		color = GRN;
	else
	{
		color = RED;
		ret = false;
	}
}

//TODO ESTO PARA DECIR	(&a == &b) :_( :_(
bool iterator_tests(void)
{
	bool			ret = true;
	char const *	color;

	PRINT << YEL "CREATING INT ARRAY a[3] = {9,42,84}" << END;
	int a[3] = {9, 42, 84};
	PRINT	<< YEL SEP << NL
			<< YEL "CREATING FT::VECTOR<INT>::ITERATORS:" << NL
			<< TAB << ALN << "ft_it = &a[0]" << NL
			<< TAB << ALN << "ft_it2 = &a[1]" << END;
	ft::vector<int>::iterator ft_it(&a[0]);
	ft::vector<int>::iterator ft_it2(&a[1]);
	PRINT	<< YEL "CREATING IDENTICAL STD::VECTOR<INT>::ITERATORS:" << NL
			<< TAB << ALN << "std_it = &a[0]" << NL
			<< TAB << ALN << "std_it2 = &a[1]" << END;
	std::vector<int>::iterator std_it(&a[0]);
	std::vector<int>::iterator std_it2(&a[1]);
	PRINT	<< YEL "CREATING FT::VECTOR<INT>::CONST_ITERATOR:" << NL
			<< TAB << ALN << "ft_cit = &a[0]" << END;
	ft::vector<int>::const_iterator ft_cit(&a[0]);
	PRINT	<< YEL "CREATING IDENTICAL STD::VECTOR<INT>::CONST_ITERATOR:" << NL
			<< TAB << ALN << "std_cit = &a[0]" << END;
	std::vector<int>::const_iterator std_cit(&a[0]);

	//CONST CHECK
	PRINT	<< YEL "CONST_ITERATOR VALUES ARE READ-ONLY; PRINTING IS OKAY:" << END;
	check((*ft_cit == *std_cit), color, ret);
	PRINT	<< TAB << ALN << YEL "My const_iterator:     " << SET << *ft_cit
			<< TAB << ALN << YEL " STD const_iterator:     " << SET << *std_cit << END;
	check((*(ft_cit + 1) == *(std_cit + 1)), color, ret);
	PRINT	<< TAB << ALN << YEL "My const_iterator + 1: " << SET << *(ft_cit + 1)
			<< TAB << ALN << YEL " STD const_iterator + 1: " << SET << *(std_cit + 1) << END;
	// // const_iterator test, uncomment to test.
	// // Compiler will allow *ft_it = 0, but not *ft_cit = 0 :)
	// ft_it[0] = 8;
	// *ft_it = 0;
	// *ft_cit = 8;
	// ft_cit[0] = 0;
	// std_it[0] = 8;
	// *std_it = 0;
	// *std_cit = 8;
	// std_cit[0] = 0;

	
	//RELATIONAL OPERATOR CHECK
	PRINT 	<< YEL "RELATIONAL OPERATOR CHECKS:" << END;
	check (((ft_it == ft_it2) == (std_it == std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it == ft_it2: " << std::boolalpha << SET << (ft_it == ft_it2)
			<< TAB << ALN << YEL "std_it == std_it2: " << std::boolalpha << SET << (std_it == std_it2) << END;
	check (((ft_it != ft_it2) == (std_it != std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it != ft_it2: " << std::boolalpha << SET << (ft_it != ft_it2)
			<< TAB << ALN << YEL "std_it != std_it2: " << std::boolalpha << SET << (std_it != std_it2) << END;
	check (((ft_it > ft_it2) == (std_it > std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it > ft_it2:  " << std::boolalpha << SET << (ft_it > ft_it2)
			<< TAB << ALN << YEL "std_it > std_it2:  " << std::boolalpha << SET << (std_it > std_it2) << END;
	check (((ft_it < ft_it2) == (std_it < std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it < ft_it2:  " << std::boolalpha << SET << (ft_it < ft_it2)
			<< TAB << ALN << YEL "std_it < std_it2:  " << std::boolalpha << SET << (std_it < std_it2) << END;
	check (((ft_it >= ft_it2) == (std_it >= std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it >= ft_it2: " << std::boolalpha << SET << (ft_it >= ft_it2)
			<< TAB << ALN << YEL "std_it >= std_it2: " << std::boolalpha << SET << (std_it >= std_it2) << END;
	check (((ft_it <= ft_it2) == (std_it <= std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it <= ft_it2: " << std::boolalpha << SET << (ft_it <= ft_it2)
			<< TAB << ALN << YEL "std_it <= std_it2: " << std::boolalpha << SET << (std_it <= std_it2) << END;
	//REFERENCING OPERATOR CHECK
	PRINT	<< YEL "REFERENCING OPERATOR CHECKS:" << END;
	check((*ft_it == *std_it), color, ret);	
	PRINT	<< TAB << ALN << YEL "*ft_it:   " << SET << *ft_it
			<< TAB << ALN << YEL " *std_it:   " << SET << *std_it << END;
	check((ft_it[2] == std_it[2]), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it[2]: " << SET << ft_it[2]
			<< TAB << ALN << YEL " std_it[2]: " << SET << std_it[2] << END;
	//ARITHMETIC OPERATOR CHECK
	PRINT	<< YEL "ARITHMETIC OPERATOR CHECKS:" << END;
	check ((*(ft_it2 + 1) == *(std_it2 + 1)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it2 + 1: " << SET << *(ft_it2 + 1)
			<< TAB << ALN << YEL " std_it2 + 1: " << SET << *(std_it2 + 1) << END;
	check ((*(ft_it2 - 1) == *(std_it2 - 1)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it2 - 1: " << SET << *(ft_it2 - 1)
			<< TAB << ALN << YEL " std_it2 - 1: " << SET << *(std_it2 - 1) << END;
	check (((*ft_it2++ == *std_it2++) && (*ft_it2 == *std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it2++:   " << SET << *ft_it2
			<< TAB << ALN << YEL " std_it2++:   " << SET << *std_it2 << END;
	check (((*ft_it2-- == *std_it2--) && (*ft_it2 == *std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it2--:   " << SET << *ft_it2
			<< TAB << ALN << YEL " std_it2--:   " << SET << *std_it2 << END;
	check (((*++ft_it2 == *++std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "++ft_it2:   " << SET << *ft_it2
			<< TAB << ALN << YEL " ++std_it2:   " << SET << *std_it2 << END;
	check (((*--ft_it2 == *--std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "--ft_it2:   " << SET << *ft_it2
			<< TAB << ALN << YEL " --std_it2:   " << SET << *std_it2 << END;
	check (((*(ft_it += 2) == *(std_it += 2))), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it += 2: " << SET << *ft_it
			<< TAB << ALN << YEL " std_it += 2: " << SET << *std_it << END;
	check (((*(ft_it -= 2) == *(std_it -= 2))), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it -= 2: " << SET << *ft_it
			<< TAB << ALN << YEL " std_it -= 2: " << SET << *std_it << END;
	//ASSIGNMENT OPERATOR CHECK
	PRINT	<< YEL "ASSIGNMENT OPERATOR CHECK:" << END;
	check ((*(ft_it = ft_it2) == *(std_it = std_it2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_it = ft_it2:   " << SET << *ft_it << " == " << *ft_it2 << NL
			<< TAB << ALN << YEL "std_it = std_it2: " << SET << *std_it << " == " << *std_it2 << NL
			<< YEL "-------------------------------------------------------------------------------------" << END;

	//REVERSE ITERATOR CHECKS:
	// ft_it = (a + 3);
	// std_it = (a + 3);
	//
	// Uncomment the above and you'll find this doesn't work.
	// I'm guessing because the std::iterator copy constructors are declared as
	// explicit, so I've done likewise with mine to get the same behaviour,
	// otherwise the compiler had no problem with the expression and implicitly
	// used my copy constructor to convert to an ft_it.
	//
	// I was happy with it that way, but the subject DOES say try to implement
	// even the tiniest STL details... :).
	ft_it = ft::vector<int>::iterator(a + 3);
	std_it = std::vector<int>::iterator(a + 3);
	ft_it2 = ft::vector<int>::iterator(&a[1]);
	std_it2 = std::vector<int>::iterator(&a[1]);
	ft_cit = ft::vector<int>::const_iterator(a + 3);
	std_cit = std::vector<int>::const_iterator(a + 3);
	// /\ Whereupon I EXPLICITLY do what the compiler was willing to do for me
	// implicitly. xD
	PRINT	<< YEL "CREATING REVERSE FT::VECTOR<INT>::ITERATORS:" << NL
			<< TAB << ALN << "ft_rit = &a[2]" << NL
			<< TAB << ALN << "ft_rit2 = &a[1]" << END;
	ft::reverse_iterator<ft::vector<int>::iterator> ft_rit(ft_it);
	ft::reverse_iterator<ft::vector<int>::iterator> ft_rit2(ft_it2);
	PRINT	<< YEL "CREATING IDENTICAL REVERSE STD::VECTOR<INT>::ITERATORS:" << NL
			<< TAB << ALN << "std_rit = &a[2]" << NL
			<< TAB << ALN << "std_rit2 = &a[1]" << END;
	std::reverse_iterator<std::vector<int>::iterator> std_rit(std_it);
	std::reverse_iterator<std::vector<int>::iterator> std_rit2(std_it2);
	PRINT	<< YEL "CREATING REVERSE FT::VECTOR<INT>::CONST_ITERATOR:" << NL
			<< TAB << ALN << "ft_rcit = &a[2]" << END;
	ft::reverse_iterator<ft::vector<int>::const_iterator> ft_rcit(ft_cit);
	PRINT	<< YEL "CREATING IDENTICAL REVERSE STD::VECTOR<INT>::CONST_ITERATOR:" << NL
			<< TAB << ALN << "std_cit = &a[0]" << END;
	std::reverse_iterator<std::vector<int>::const_iterator> std_rcit(std_cit);
	//CONST CHECK
	PRINT	<< YEL "REVERSE CONST_ITERATOR VALUES ARE READ-ONLY; PRINTING IS OKAY:" << END;
	check((*ft_rcit == *std_rcit), color, ret);
	PRINT	<< TAB << ALN << YEL "My reverse const_iterator:     " << SET << *ft_rcit
			<< TAB << ALN << YEL " STD reverse const_iterator:     " << SET << *std_rcit << END;
	check((*(ft_rcit + 1) == *(std_rcit + 1)), color, ret);
	PRINT	<< TAB << ALN << YEL "My reverse const_iterator + 1: " << SET << *(ft_rcit + 1)
			<< TAB << ALN << YEL " STD reverse const_iterator + 1: " << SET << *(std_rcit + 1) << END;
	// // const_iterator test, uncomment to test.
	// // Compiler will allow *ft_rit = 0, but not *ft_rcit = 0 :)
	// ft_rit[0] = 8;
	// *ft_rit = 0;
	// *ft_rcit = 8;
	// ft_rcit[0] = 0;
	// std_rit[0] = 8;
	// *std_rit = 0;
	// *std_rcit = 8;
	// std_rcit[0] = 0;
	//RELATIONAL OPERATOR CHECK
	PRINT 	<< YEL "REVERSE RELATIONAL OPERATOR CHECKS:" << END;
	check (((ft_rit == ft_rit2) == (std_rit == std_rit2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit == ft_rit2:" << std::boolalpha << SET << (ft_rit == ft_rit2)
			<< TAB << ALN << YEL "std_rit == std_rit2:" << std::boolalpha << SET << (std_rit == std_rit2) << END;
	check (((ft_rit != ft_rit2) == (std_rit != std_rit2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit != ft_rit2:" << std::boolalpha << SET << (ft_rit != ft_rit2)
			<< TAB << ALN << YEL "std_rit != std_rit2:" << std::boolalpha << SET << (std_rit != std_rit2) << END;
	check (((ft_rit > ft_rit2) == (std_rit > std_rit2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit > ft_rit2:" << std::boolalpha << SET << (ft_rit > ft_rit2)
			<< TAB << ALN << YEL "std_rit > std_rit2:" << std::boolalpha << SET << (std_rit > std_rit2) << END;
	check (((ft_rit < ft_rit2) == (std_rit < std_rit2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit < ft_rit2:" << std::boolalpha << SET << (ft_rit < ft_rit2)
			<< TAB << ALN << YEL "std_rit < std_rit2:" << std::boolalpha << SET << (std_rit < std_rit2) << END;
	check (((ft_rit >= ft_rit2) == (std_rit >= std_rit2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit >= ft_rit2:" << std::boolalpha << SET << (ft_rit >= ft_rit2)
			<< TAB << ALN << YEL "std_rit >= std_rit2:" << std::boolalpha << SET << (std_rit >= std_rit2) << END;
	check (((ft_rit <= ft_rit2) == (std_rit <= std_rit2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit <= ft_rit2:" << std::boolalpha << SET << (ft_rit <= ft_rit2)
			<< TAB << ALN << YEL "std_rit <= std_rit2:" << std::boolalpha << SET << (std_rit <= std_rit2) << END;
	//REFERENCING OPERATOR CHECK
	PRINT	<< YEL "REVERSE REFERENCING OPERATOR CHECKS:" << END;
	check((*ft_rit == *std_rit), color, ret);	
	PRINT	<< TAB << ALN << YEL "*ft_rit:   " << SET << *ft_rit
			<< TAB << ALN << YEL " *std_rit:   " << SET << *std_rit << END;
	check((ft_rit[2] == std_rit[2]), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit[2]: " << SET << ft_rit[2]
			<< TAB << ALN << YEL " std_rit[2]: " << SET << std_rit[2] << END;
	//ARITHMETIC OPERATOR CHECK
	PRINT	<< YEL "REVERSE ARITHMETIC OPERATOR CHECKS:" << END;
	check ((*(ft_rit + 1) == *(std_rit + 1)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit + 1: " << SET << *(ft_rit + 1)
			<< TAB << ALN << YEL " std_rit + 1: " << SET << *(std_rit + 1) << END;
	check ((*(ft_rit2 - 2) == *(std_rit2 - 2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit2 - 2:" << SET << *(ft_rit2 - 2)
			<< TAB << ALN << YEL "std_rit2 - 2:" << SET << *(std_rit2 - 2) << END;
	check (((*ft_rit++ == *std_rit++) && (*ft_rit == *std_rit)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit++:   " << SET << *ft_rit
			<< TAB << ALN << YEL "std_rit++:   " << SET << *std_rit << END;
	check (((*ft_rit-- == *std_rit--) && (*ft_rit == *std_rit)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit--:   " << SET << *ft_rit
			<< TAB << ALN << YEL "std_rit--:   " << SET << *std_rit << END;
	check (((*++ft_rit == *++std_rit)), color, ret);
	PRINT	<< TAB << ALN << YEL "++ft_rit:   " << SET << *ft_rit
			<< TAB << ALN << YEL "++std_rit:   " << SET << *std_rit << END;
	check (((*--ft_rit == *--std_rit)), color, ret);
	PRINT	<< TAB << ALN << YEL "--ft_rit:   " << SET << *ft_rit
			<< TAB << ALN << YEL "--std_rit:   " << SET << *std_rit << END;
	check (((*(ft_rit += 2) == *(std_rit += 2))), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit += 2: " << SET << *ft_rit
			<< TAB << ALN << YEL "std_rit += 2: " << SET << *std_rit << END;
	check (((*(ft_rit -= 2) == *(std_rit -= 2))), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit -= 2:" << SET << *ft_rit
			<< TAB << ALN << YEL "std_rit -= 2:" << SET << *std_rit << END;
	//ASSIGNMENT OPERATOR CHECK
	PRINT	<< YEL "REVERSE ASSIGNMENT OPERATOR CHECK:" << END;
	check ((*(ft_rit = ft_rit2) == *(std_rit = std_rit2)), color, ret);
	PRINT	<< TAB << ALN << YEL "ft_rit = ft_rit2:   " << SET << *ft_rit << " == " << *ft_rit2 << NL
			<< TAB << ALN << YEL "std_rit = std_rit2: " << SET << *std_rit << " == " << *std_rit2 << END;
	
	return (ret);
}

int main(void)
{	
	if (iterator_tests())
		PRINT << GRN "OK" << END;
	else
		PRINT << RED "KO" << END;
	
	int	i = 1;
	//enable_if tests
	PRINT << "i is odd: " << std::boolalpha << ft::is_odd(i) << END;


	return (0);
}