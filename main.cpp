/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/23 00:49:40 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ansi_codes.hpp"
#include "ft_vector.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "utility.hpp"
#include "ft_bintree.hpp"
#include "ft_bintree_pair.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#define PRINT std::cout
#define ALN std::left << std::setw(30)
#define END TXT_RST << std::endl
#define SET std::setw(9) << color
									//reference to pointer
void	check(bool result, char const *& color, bool & ret)
{
	//Return check
	if (result == true)
		color = TXT_BGRN;
	else
	{
		color = TXT_BRED;
		ret = false;
	}
}

//TODO ESTO PARA DECIR	(&a == &b) :_( :_(
bool iterator_tests(void)
{
	bool			ret = true;
	char const *	color;

	PRINT << TXT_BYEL "CREATING INT ARRAY a[3] = {9,42,84}" << END;
	int a[3] = {9, 42, 84};
	std::vector<int> std_vector;
	std_vector.push_back(9);
	std_vector.push_back(42);
	std_vector.push_back(84);
	PRINT	<< TXT_BYEL TXT_SEP << TXT_NL
			<< TXT_BYEL "CREATING FT::VECTOR<INT>::ITERATORS:" << TXT_NL
			<< TXT_TAB << ALN << "ft_it = &a[0]" << TXT_NL
			<< TXT_TAB << ALN << "ft_it2 = &a[1]" << END;
	ft::vector<int>::iterator ft_it(&a[0]);
	ft::vector<int>::iterator ft_it2(&a[1]);
	PRINT	<< TXT_BYEL "CREATING IDENTICAL STD::VECTOR<INT>::ITERATORS:" << TXT_NL
			<< TXT_TAB << ALN << "std_it = &a[0]" << TXT_NL
			<< TXT_TAB << ALN << "std_it2 = &a[1]" << END;
	std::vector<int>::iterator std_it(std_vector.begin()); //MAC COMPILER WILL NOT CREATE ITERATOR FROM POINTER!!???
	std::vector<int>::iterator std_it2(std_vector.begin() + 1); //GRRAAAAAARRRRRRRGH!!!! WHY!!!!?????
	PRINT	<< TXT_BYEL "CREATING FT::VECTOR<INT>::CONST_ITERATOR:" << TXT_NL
			<< TXT_TAB << ALN << "ft_cit = &a[0]" << END;
	ft::vector<int>::const_iterator ft_cit(&a[0]);
	PRINT	<< TXT_BYEL "CREATING IDENTICAL STD::VECTOR<INT>::CONST_ITERATOR:" << TXT_NL
			<< TXT_TAB << ALN << "std_cit = &a[0]" << END;
	std::vector<int>::const_iterator std_cit(std_vector.begin());

	//CONST CHECK
	PRINT	<< TXT_BYEL "CONST_ITERATOR VALUES ARE READ-ONLY; PRINTING IS OKAY:" << END;
	check((*ft_cit == *std_cit), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "My const_iterator:     " << SET << *ft_cit
			<< TXT_TAB << ALN << TXT_BYEL " STD const_iterator:     " << SET << *std_cit << END;
	check((*(ft_cit + 1) == *(std_cit + 1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "My const_iterator + 1: " << SET << *(ft_cit + 1)
			<< TXT_TAB << ALN << TXT_BYEL " STD const_iterator + 1: " << SET << *(std_cit + 1) << END;
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
	PRINT 	<< TXT_BYEL "RELATIONAL OPERATOR CHECKS:" << END;
	check (((ft_it == ft_it2) == (std_it == std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it == ft_it2: " << std::boolalpha << SET << (ft_it == ft_it2)
			<< TXT_TAB << ALN << TXT_BYEL "std_it == std_it2: " << std::boolalpha << SET << (std_it == std_it2) << END;
	check (((ft_it != ft_it2) == (std_it != std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it != ft_it2: " << std::boolalpha << SET << (ft_it != ft_it2)
			<< TXT_TAB << ALN << TXT_BYEL "std_it != std_it2: " << std::boolalpha << SET << (std_it != std_it2) << END;
	check (((ft_it > ft_it2) == (std_it > std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it > ft_it2:  " << std::boolalpha << SET << (ft_it > ft_it2)
			<< TXT_TAB << ALN << TXT_BYEL "std_it > std_it2:  " << std::boolalpha << SET << (std_it > std_it2) << END;
	check (((ft_it < ft_it2) == (std_it < std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it < ft_it2:  " << std::boolalpha << SET << (ft_it < ft_it2)
			<< TXT_TAB << ALN << TXT_BYEL "std_it < std_it2:  " << std::boolalpha << SET << (std_it < std_it2) << END;
	check (((ft_it >= ft_it2) == (std_it >= std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it >= ft_it2: " << std::boolalpha << SET << (ft_it >= ft_it2)
			<< TXT_TAB << ALN << TXT_BYEL "std_it >= std_it2: " << std::boolalpha << SET << (std_it >= std_it2) << END;
	check (((ft_it <= ft_it2) == (std_it <= std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it <= ft_it2: " << std::boolalpha << SET << (ft_it <= ft_it2)
			<< TXT_TAB << ALN << TXT_BYEL "std_it <= std_it2: " << std::boolalpha << SET << (std_it <= std_it2) << END;
	//REFERENCING OPERATOR CHECK
	PRINT	<< TXT_BYEL "REFERENCING OPERATOR CHECKS:" << END;
	check((*ft_it == *std_it), color, ret);	
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "*ft_it:   " << SET << *ft_it
			<< TXT_TAB << ALN << TXT_BYEL " *std_it:   " << SET << *std_it << END;
	check((ft_it[2] == std_it[2]), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it[2]: " << SET << ft_it[2]
			<< TXT_TAB << ALN << TXT_BYEL " std_it[2]: " << SET << std_it[2] << END;
	//ARITHMETIC OPERATOR CHECK
	PRINT	<< TXT_BYEL "ARITHMETIC OPERATOR CHECKS:" << END;
	check ((*(ft_it2 + 1) == *(std_it2 + 1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it2 + 1: " << SET << *(ft_it2 + 1)
			<< TXT_TAB << ALN << TXT_BYEL " std_it2 + 1: " << SET << *(std_it2 + 1) << END;
	check ((*(ft_it2 - 1) == *(std_it2 - 1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it2 - 1: " << SET << *(ft_it2 - 1)
			<< TXT_TAB << ALN << TXT_BYEL " std_it2 - 1: " << SET << *(std_it2 - 1) << END;
	check (((*ft_it2++ == *std_it2++) && (*ft_it2 == *std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it2++:   " << SET << *ft_it2
			<< TXT_TAB << ALN << TXT_BYEL " std_it2++:   " << SET << *std_it2 << END;
	check (((*ft_it2-- == *std_it2--) && (*ft_it2 == *std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it2--:   " << SET << *ft_it2
			<< TXT_TAB << ALN << TXT_BYEL " std_it2--:   " << SET << *std_it2 << END;
	check (((*++ft_it2 == *++std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "++ft_it2:   " << SET << *ft_it2
			<< TXT_TAB << ALN << TXT_BYEL " ++std_it2:   " << SET << *std_it2 << END;
	check (((*--ft_it2 == *--std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "--ft_it2:   " << SET << *ft_it2
			<< TXT_TAB << ALN << TXT_BYEL " --std_it2:   " << SET << *std_it2 << END;
	check (((*(ft_it += 2) == *(std_it += 2))), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it += 2: " << SET << *ft_it
			<< TXT_TAB << ALN << TXT_BYEL " std_it += 2: " << SET << *std_it << END;
	check (((*(ft_it -= 2) == *(std_it -= 2))), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it -= 2: " << SET << *ft_it
			<< TXT_TAB << ALN << TXT_BYEL " std_it -= 2: " << SET << *std_it << END;
	//ASSIGNMENT OPERATOR CHECK
	PRINT	<< TXT_BYEL "ASSIGNMENT OPERATOR CHECK:" << END;
	check ((*(ft_it = ft_it2) == *(std_it = std_it2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_it = ft_it2:   " << SET << *ft_it << " == " << *ft_it2 << TXT_NL
			<< TXT_TAB << ALN << TXT_BYEL "std_it = std_it2: " << SET << *std_it << " == " << *std_it2 << TXT_NL
			<< TXT_BYEL "-------------------------------------------------------------------------------------" << END;

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
	std_it = std::vector<int>::iterator(std_vector.begin() + 3);
	ft_it2 = ft::vector<int>::iterator(&a[1]);
	std_it2 = std::vector<int>::iterator(std_vector.begin() + 1);
	ft_cit = ft::vector<int>::const_iterator(a + 3);
	std_cit = std::vector<int>::const_iterator(std_vector.begin() + 3);
	// /\ Whereupon I EXPLICITLY do what the compiler was willing to do for me
	// implicitly. xD
	PRINT	<< TXT_BYEL "CREATING REVERSE FT::VECTOR<INT>::ITERATORS:" << TXT_NL
			<< TXT_TAB << ALN << "ft_rit = &a[2]" << TXT_NL
			<< TXT_TAB << ALN << "ft_rit2 = &a[1]" << END;
	ft::reverse_iterator<ft::vector<int>::iterator> ft_rit(ft_it);
	ft::reverse_iterator<ft::vector<int>::iterator> ft_rit2(ft_it2);
	PRINT	<< TXT_BYEL "CREATING IDENTICAL REVERSE STD::VECTOR<INT>::ITERATORS:" << TXT_NL
			<< TXT_TAB << ALN << "std_rit = &a[2]" << TXT_NL
			<< TXT_TAB << ALN << "std_rit2 = &a[1]" << END;
	std::reverse_iterator<std::vector<int>::iterator> std_rit(std_it);
	std::reverse_iterator<std::vector<int>::iterator> std_rit2(std_it2);
	PRINT	<< TXT_BYEL "CREATING REVERSE FT::VECTOR<INT>::CONST_ITERATOR:" << TXT_NL
			<< TXT_TAB << ALN << "ft_rcit = &a[2]" << END;
	ft::reverse_iterator<ft::vector<int>::const_iterator> ft_rcit(ft_cit);
	PRINT	<< TXT_BYEL "CREATING IDENTICAL REVERSE STD::VECTOR<INT>::CONST_ITERATOR:" << TXT_NL
			<< TXT_TAB << ALN << "std_cit = &a[0]" << END;
	std::reverse_iterator<std::vector<int>::const_iterator> std_rcit(std_cit);
	//CONST CHECK
	PRINT	<< TXT_BYEL "REVERSE CONST_ITERATOR VALUES ARE READ-ONLY; PRINTING IS OKAY:" << END;
	check((*ft_rcit == *std_rcit), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "My reverse const_iterator:     " << SET << *ft_rcit
			<< TXT_TAB << ALN << TXT_BYEL " STD reverse const_iterator:     " << SET << *std_rcit << END;
	check((*(ft_rcit + 1) == *(std_rcit + 1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "My reverse const_iterator + 1: " << SET << *(ft_rcit + 1)
			<< TXT_TAB << ALN << TXT_BYEL " STD reverse const_iterator + 1: " << SET << *(std_rcit + 1) << END;
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
	PRINT 	<< TXT_BYEL "REVERSE RELATIONAL OPERATOR CHECKS:" << END;
	check (((ft_rit == ft_rit2) == (std_rit == std_rit2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit == ft_rit2:" << std::boolalpha << SET << (ft_rit == ft_rit2)
			<< TXT_TAB << ALN << TXT_BYEL "std_rit == std_rit2:" << std::boolalpha << SET << (std_rit == std_rit2) << END;
	check (((ft_rit != ft_rit2) == (std_rit != std_rit2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit != ft_rit2:" << std::boolalpha << SET << (ft_rit != ft_rit2)
			<< TXT_TAB << ALN << TXT_BYEL "std_rit != std_rit2:" << std::boolalpha << SET << (std_rit != std_rit2) << END;
	check (((ft_rit > ft_rit2) == (std_rit > std_rit2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit > ft_rit2:" << std::boolalpha << SET << (ft_rit > ft_rit2)
			<< TXT_TAB << ALN << TXT_BYEL "std_rit > std_rit2:" << std::boolalpha << SET << (std_rit > std_rit2) << END;
	check (((ft_rit < ft_rit2) == (std_rit < std_rit2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit < ft_rit2:" << std::boolalpha << SET << (ft_rit < ft_rit2)
			<< TXT_TAB << ALN << TXT_BYEL "std_rit < std_rit2:" << std::boolalpha << SET << (std_rit < std_rit2) << END;
	check (((ft_rit >= ft_rit2) == (std_rit >= std_rit2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit >= ft_rit2:" << std::boolalpha << SET << (ft_rit >= ft_rit2)
			<< TXT_TAB << ALN << TXT_BYEL "std_rit >= std_rit2:" << std::boolalpha << SET << (std_rit >= std_rit2) << END;
	check (((ft_rit <= ft_rit2) == (std_rit <= std_rit2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit <= ft_rit2:" << std::boolalpha << SET << (ft_rit <= ft_rit2)
			<< TXT_TAB << ALN << TXT_BYEL "std_rit <= std_rit2:" << std::boolalpha << SET << (std_rit <= std_rit2) << END;
	//REFERENCING OPERATOR CHECK
	PRINT	<< TXT_BYEL "REVERSE REFERENCING OPERATOR CHECKS:" << END;
	check((*ft_rit == *std_rit), color, ret);	
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "*ft_rit:   " << SET << *ft_rit
			<< TXT_TAB << ALN << TXT_BYEL " *std_rit:   " << SET << *std_rit << END;
	check((ft_rit[2] == std_rit[2]), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit[2]: " << SET << ft_rit[2]
			<< TXT_TAB << ALN << TXT_BYEL " std_rit[2]: " << SET << std_rit[2] << END;
	//ARITHMETIC OPERATOR CHECK
	PRINT	<< TXT_BYEL "REVERSE ARITHMETIC OPERATOR CHECKS:" << END;
	check ((*(ft_rit + 1) == *(std_rit + 1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit + 1: " << SET << *(ft_rit + 1)
			<< TXT_TAB << ALN << TXT_BYEL " std_rit + 1: " << SET << *(std_rit + 1) << END;
	check ((*(ft_rit2 - 2) == *(std_rit2 - 2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit2 - 2:" << SET << *(ft_rit2 - 2)
			<< TXT_TAB << ALN << TXT_BYEL "std_rit2 - 2:" << SET << *(std_rit2 - 2) << END;
	check (((*ft_rit++ == *std_rit++) && (*ft_rit == *std_rit)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit++:   " << SET << *ft_rit
			<< TXT_TAB << ALN << TXT_BYEL "std_rit++:   " << SET << *std_rit << END;
	check (((*ft_rit-- == *std_rit--) && (*ft_rit == *std_rit)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit--:   " << SET << *ft_rit
			<< TXT_TAB << ALN << TXT_BYEL "std_rit--:   " << SET << *std_rit << END;
	check (((*++ft_rit == *++std_rit)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "++ft_rit:   " << SET << *ft_rit
			<< TXT_TAB << ALN << TXT_BYEL "++std_rit:   " << SET << *std_rit << END;
	check (((*--ft_rit == *--std_rit)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "--ft_rit:   " << SET << *ft_rit
			<< TXT_TAB << ALN << TXT_BYEL "--std_rit:   " << SET << *std_rit << END;
	check (((*(ft_rit += 2) == *(std_rit += 2))), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit += 2: " << SET << *ft_rit
			<< TXT_TAB << ALN << TXT_BYEL "std_rit += 2: " << SET << *std_rit << END;
	check (((*(ft_rit -= 2) == *(std_rit -= 2))), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit -= 2:" << SET << *ft_rit
			<< TXT_TAB << ALN << TXT_BYEL "std_rit -= 2:" << SET << *std_rit << END;
	//ASSIGNMENT OPERATOR CHECK
	PRINT	<< TXT_BYEL "REVERSE ASSIGNMENT OPERATOR CHECK:" << END;
	check ((*(ft_rit = ft_rit2) == *(std_rit = std_rit2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "ft_rit = ft_rit2:   " << SET << *ft_rit << " == " << *ft_rit2 << TXT_NL
			<< TXT_TAB << ALN << TXT_BYEL "std_rit = std_rit2: " << SET << *std_rit << " == " << *std_rit2 << END;
	
	return (ret);
}

/*
** This is the same as the == comparison operator overload for a container,
** except it compares two different container types: STD_Container and
** MY_Container. This is used as the predicate for the check function in my
** testing routine to confirm whether std:: and ft:: versions of the same
** container type behave equally under the same conditions. If sizes and
** ranges are equal, it returns true, otherwise it returns false.
*/
template<class STD_Container, class MY_Container>
static bool	operator==(STD_Container const & lhs, MY_Container const & rhs)
{
	return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

/*
** This is a modification of my original check function. Here the predicate for
** container checking is always the same (cont1 == cont2), I both do the
** check and print the results here in the appropriate colors. The global return
** value is set to false if any of these checks fail.
**
** If the check fails, container contents are printed in red, otherwise they are
** printed in green.
*/
template<class STD_Container, class MY_Container>
void	cont_check_log(STD_Container std_cont, MY_Container my_cont, bool & ret)
{
	char const *	color;

	if (std_cont == my_cont)
		color = TXT_BGRN;
	else
	{
		color = TXT_BRED;
		ret = false;
	}
	PRINT	<< TXT_TAB << TXT_BYEL "MY Container: " << END;
	for (typename MY_Container::iterator it = my_cont.begin(), end = my_cont.end(); it != end; ++it)
		PRINT << TXT_TAB << color << *it << END;
	PRINT	<< TXT_TAB << TXT_BYEL "STD Container: " << END;
	for (typename STD_Container::iterator it = std_cont.begin(), end = std_cont.end(); it != end; ++it)
		PRINT << TXT_TAB << color << *it << END;
}

/*
** This function compares the sizes of the std::container and my ft::container
** and prints out the element count of each. If they are equal, the counts are
** printed in green, otherwise they are printed in red. This is a complementary
** log for the container check log, indicating at a glance whether unequal
** containers have the same size (and thus necessarily different content).
*/
template<class STD_Container, class MY_Container>
void	elemc_compare_log(STD_Container const & lhs, MY_Container const & rhs)
{
	char const *	color;

	color = lhs.size() == rhs.size() ? TXT_BGRN : TXT_BRED;
	PRINT	<< TXT_TAB << TXT_BYEL "MY Element Count" << TXT_TAB << "STD Element Count" << TXT_NL
			<< TXT_TAB << color << std::setw(17) << rhs.size() << TXT_TAB << std::setw(17) << lhs.size() << END;
}

template<class STD_Container, class MY_Container>
void	comparison_operator_log(STD_Container const & su_cont1, STD_Container const & su_cont2,
								MY_Container const & mi_cont1, MY_Container const & mi_cont2, bool & ret)
{
	char const *	color;

	PRINT 	<< TXT_BYEL "RELATIONAL OPERATOR CHECKS:" << END;
	check (((mi_cont1 == mi_cont2) == (su_cont1 == su_cont2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 == mi_cont2: " << std::boolalpha << SET << (mi_cont1 == mi_cont2)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 == su_cont2: " << std::boolalpha << SET << (su_cont1 == su_cont2) << END;
	check (((mi_cont1 != mi_cont2) == (su_cont1 != su_cont2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 != mi_cont2: " << std::boolalpha << SET << (mi_cont1 != mi_cont2)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 != su_cont2: " << std::boolalpha << SET << (su_cont1 != su_cont2) << END;
	check (((mi_cont1 == mi_cont1) == (su_cont1 == su_cont1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 == mi_cont1: " << std::boolalpha << SET << (mi_cont1 == mi_cont1)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 == su_cont1: " << std::boolalpha << SET << (su_cont1 == su_cont1) << END;
	check (((mi_cont1 != mi_cont1) == (su_cont1 != su_cont1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 != mi_cont1: " << std::boolalpha << SET << (mi_cont1 != mi_cont1)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 != su_cont1: " << std::boolalpha << SET << (su_cont1 != su_cont1) << END;
	check (((mi_cont1 > mi_cont2) == (su_cont1 > su_cont2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 > mi_cont2:  " << std::boolalpha << SET << (mi_cont1 > mi_cont2)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 > su_cont2:  " << std::boolalpha << SET << (su_cont1 > su_cont2) << END;
	check (((mi_cont1 < mi_cont2) == (su_cont1 < su_cont2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 < mi_cont2:  " << std::boolalpha << SET << (mi_cont1 < mi_cont2)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 < su_cont2:  " << std::boolalpha << SET << (su_cont1 < su_cont2) << END;
	check (((mi_cont1 > mi_cont1) == (su_cont1 > su_cont1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 > mi_cont1:  " << std::boolalpha << SET << (mi_cont1 > mi_cont1)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 > su_cont1:  " << std::boolalpha << SET << (su_cont1 > su_cont1) << END;
	check (((mi_cont1 < mi_cont1) == (su_cont1 < su_cont1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 < mi_cont1:  " << std::boolalpha << SET << (mi_cont1 < mi_cont1)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 < su_cont1:  " << std::boolalpha << SET << (su_cont1 < su_cont1) << END;
	check (((mi_cont1 >= mi_cont2) == (su_cont1 >= su_cont2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 >= mi_cont2: " << std::boolalpha << SET << (mi_cont1 >= mi_cont2)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 >= su_cont2: " << std::boolalpha << SET << (su_cont1 >= su_cont2) << END;
	check (((mi_cont1 <= mi_cont2) == (su_cont1 <= su_cont2)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 <= mi_cont2: " << std::boolalpha << SET << (mi_cont1 <= mi_cont2)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 <= su_cont2: " << std::boolalpha << SET << (su_cont1 <= su_cont2) << END;
	check (((mi_cont1 >= mi_cont1) == (su_cont1 >= su_cont1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 >= mi_cont1: " << std::boolalpha << SET << (mi_cont1 >= mi_cont1)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 >= su_cont1: " << std::boolalpha << SET << (su_cont1 >= su_cont1) << END;
	check (((mi_cont1 <= mi_cont1) == (su_cont1 <= su_cont1)), color, ret);
	PRINT	<< TXT_TAB << ALN << TXT_BYEL "mi_cont1 <= mi_cont1: " << std::boolalpha << SET << (mi_cont1 <= mi_cont1)
			<< TXT_TAB << ALN << TXT_BYEL "su_cont1 <= su_cont1: " << std::boolalpha << SET << (su_cont1 <= su_cont1) << END;	
}

/*
** This function will take the result of any comparison as comp. If the result
** is true, the color is set to green. If it is false, the color is set to red
** and the global return value is set to false.
**
** The message passed as a parameter will be printed to in a left and right
** column in yellow with the prefix "MY " and "STD ", respectively. The
** msg_offset will be set to the width of the longest message (std_msg). You can
** optionally specify the column width as the last argument, otherwise they
** will be separated only by a TXT_TAB.
**
** The color will be set to green or red before the function exits. It will need
** to be reset by the caller, either with TXT_RST or END!
*/
void	compare_log(bool comp, bool & ret, std::string const & msg, size_t & msg_offset, size_t const & minw = 0)
{
	char const *		color;
	std::string	const	my_msg = "MY " + msg;
	std::string	const	std_msg = "STD " + msg;

	if (comp)
		color = TXT_BGRN;
	else
	{
		color = TXT_BRED;
		ret = false;
	}
	msg_offset = std_msg.size();
	PRINT	<< TXT_TAB << TXT_BYEL << std::setw(minw) << my_msg << TXT_TAB << std::setw(minw) << std_msg << TXT_NL
			<< TXT_TAB << color;
}

/*
** The idea behind this test is to be a templated function with common tests for
** all container types to save me a bajillion hours writing out the same tests
** over and over again. Thanks, compiler. ;) The tests all compare my version
** and STL version of the same container type under the same conditions.
** Conditions are printed in yellow before each test and results are printed in
** red and green after the test. The function returns true if all tests are
** passed and false otherwise.
*/
template<class MY_Container, class STD_Container>
bool	my_veritable_vector(void)
{
	bool			ret = true;
	size_t			msg_offset;

	/* CONSTRUCTOR TESTS */
	//FILL CONSTRUCTOR TEST
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << TXT_NL
			<< "CONSTRUCTOR CHECKS" << TXT_NL
			<< TXT_NL
			<< "FILL CONSTRUCTOR TESTS" << TXT_NL
			<< TXT_TAB << "Fill-constructing: " << TXT_NL
			<< TXT_TAB << "  ft::container mi_fill_cont(4, 42)" << TXT_NL
			<< TXT_TAB << "  std::container su_fill_cont(4, 42)" << END;
	MY_Container	mi_fill_cont(4, 42);
	STD_Container	su_fill_cont(4, 42);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);

	//RANGE CONSTRUCTOR TEST
	PRINT	<< TXT_NL
			<< TXT_BYEL "RANGE CONSTRUCTOR TESTS" << TXT_NL
			<< TXT_TAB << "Range-constructing: " << TXT_NL
			<< TXT_TAB << "  ft::container mi_range_cont(mi_fill_cont.begin(), mi_fill_cont.end())" << TXT_NL
			<< TXT_TAB << "  std::container su_range_cont(su_fill_cont.begin(), su_fill_cont.end())" << END;
			MY_Container	mi_range_cont(mi_fill_cont.begin(), mi_fill_cont.end());
			STD_Container 	su_range_cont(su_fill_cont.begin(), su_fill_cont.end());
	elemc_compare_log(su_range_cont, mi_range_cont);
	cont_check_log(su_range_cont, mi_range_cont, ret);

	//COPY CONSTRUCTOR TEST
	PRINT	<< TXT_NL
			<< TXT_BYEL "COPY CONSTRUCTOR TESTS" << TXT_NL
			<< TXT_TAB << "Copy-constructing: " << TXT_NL
			<< TXT_TAB << "  ft::container mi_copied_cont(mi_fill_cont)" << TXT_NL
			<< TXT_TAB << "  std::container su_copied_cont(su_fill_cont)" << END;
	MY_Container	mi_copied_cont(mi_fill_cont);
	STD_Container	su_copied_cont(su_fill_cont);
	elemc_compare_log(su_copied_cont, mi_copied_cont);
	cont_check_log(su_copied_cont, mi_copied_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//ASSIGNMENT OVERLOAD COPY TEST
	PRINT	<< TXT_BYEL "ASSIGNMENT OVERLOAD COPY TEST" << TXT_NL
			<< TXT_TAB << "Copying via assignment: " << TXT_NL
			<< TXT_TAB << "  ft::container(0) mi_assigned_cont = mi_fill_cont" << TXT_NL
			<< TXT_TAB << "  std::container(0) su_assigned_cont = su_fill_cont" << END;
	MY_Container	mi_assigned_cont = mi_fill_cont;
	STD_Container	su_assigned_cont = su_fill_cont;
	elemc_compare_log(su_assigned_cont, mi_assigned_cont);
	cont_check_log(su_assigned_cont, mi_assigned_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//REVERSE ITERATOR PRINT TEST
	//DEBUG
	// Change this to output to file and do a diff or something, and include it in the global ret checks and the like
	//DEBUG
	PRINT	<< TXT_BYEL "REVERSE ITERATOR PRINT TEST" << TXT_NL
			<< TXT_TAB << "Printing using reverse iterators: " << TXT_NL
			<< TXT_TAB << "  mi_fill_cont" << TXT_NL
			<< TXT_TAB << "  su_fill_cont" << END;

	PRINT	<< TXT_TAB << TXT_BYEL "MY Reverse Printed Container: " << END;
	for (typename MY_Container::reverse_iterator rit = mi_fill_cont.rbegin(), rend = mi_fill_cont.rend(); rit != rend; ++rit)
		PRINT << TXT_TAB << *rit << END;
	PRINT	<< TXT_TAB << TXT_BYEL "STD Reverse Printed Container: " << END;
	for (typename STD_Container::reverse_iterator rit = su_fill_cont.rbegin(), rend = su_fill_cont.rend(); rit != rend; ++rit)
		PRINT << TXT_TAB << *rit << END;
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//MAX SIZE EQUALITY CHECK... I take allocator's max_size, and depending on
	//implementation STL appears to do different things at different times. We
	//SEEM to do the same thing on school Mac, however. ;)
	PRINT	<< TXT_BYEL "MAX SIZE EQUALITY CHECK" << TXT_NL
			<< TXT_TAB << "Comparing : " << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.max_size()" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.max_size()" << END;
	compare_log(su_fill_cont.max_size() == mi_fill_cont.max_size(), ret, "Max Size", msg_offset, 20);
	PRINT	<< mi_fill_cont.max_size() << TXT_TAB << su_fill_cont.max_size() << END;
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//CAPACITY EQUALITY CHECK, this should be equal if we follow the same
	//allocation strategy of multiplying by * 2. :p
	PRINT	<< TXT_BYEL "CAPACITY EQUALITY CHECK" << TXT_NL
			<< TXT_TAB << "Comparing : " << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.capacity()" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.capacity()" << END;
	compare_log(su_fill_cont.capacity() == mi_fill_cont.capacity(), ret, "Capacity", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont.capacity() << TXT_TAB << std::setw(msg_offset) << su_fill_cont.capacity() << END;
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//PUSH_BACK CHECK
	PRINT	<< TXT_BYEL "PUSH BACK CHECKS" << TXT_NL
			<< TXT_TAB << "Adding 84, 168 and 69 via push_back to: " << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.push_back(84...)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.push_back(84...)" << END;
	mi_fill_cont.push_back(84);
	mi_fill_cont.push_back(168);
	mi_fill_cont.push_back(69);
	su_fill_cont.push_back(84);
	su_fill_cont.push_back(168);
	su_fill_cont.push_back(69);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Adding -42 and -21 via push_back to: " << TXT_NL
			<< TXT_TAB << "  mi_copied_cont.push_back(-42...)" << TXT_NL
			<< TXT_TAB << "  su_copied_cont.push_back(-42...)" << END;
	mi_copied_cont.push_back(-42);
	mi_copied_cont.push_back(-21);
	su_copied_cont.push_back(-42);
	su_copied_cont.push_back(-21);
	elemc_compare_log(su_copied_cont, mi_copied_cont);
	cont_check_log(su_copied_cont, mi_copied_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//RESERVE CHECK
	PRINT	<< TXT_BYEL "RESERVE CHECK" << TXT_NL
			<< TXT_TAB << "Reserving space for 20 elements: " << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.reserve(20)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.reserve(20)" << END;
	mi_fill_cont.reserve(20);
	su_fill_cont.reserve(20);
	//CAPACITY AFTER RESERVE COMPARISON
	compare_log(su_fill_cont.capacity() == mi_fill_cont.capacity(), ret, "Capacity After Reserve", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont.capacity() << TXT_TAB << std::setw(msg_offset) << su_fill_cont.capacity() << END;
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//POP_BACK CHECK
	PRINT	<< TXT_BYEL "POP BACK CHECK" << TXT_NL
			<< TXT_TAB << "Popping back last element: " << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.pop_back()" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.pop_back()" << END;
	mi_fill_cont.pop_back();
	su_fill_cont.pop_back();
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//RESIZE CHECKS
	//Size down
	PRINT	<< TXT_BYEL "RESIZE CHECKS" << TXT_NL
			<< TXT_TAB << "Sizing down:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.resize(2)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.resize(2)" << END;
	mi_fill_cont.resize(2);
	su_fill_cont.resize(2);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//Size up
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Sizing up:" << TXT_NL
			<< TXT_TAB << " mi_fill_cont.resize(4)" << TXT_NL
			<< TXT_TAB << " su_fill_cont.resize(4)" << END;
	mi_fill_cont.resize(4);
	su_fill_cont.resize(4);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//Size up with caller-specified value
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Sizing up with caller-specified value:" << TXT_NL
			<< TXT_TAB << " mi_fill_cont.resize(6, 21)" << TXT_NL
			<< TXT_TAB << " su_fill_cont.resize(6, 21)" << END;
	mi_fill_cont.resize(6, 21);
	su_fill_cont.resize(6, 21);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//ERASE CHECKS
	//ERASE BY POSITION
	PRINT	<< TXT_BYEL "ERASE CHECKS" << TXT_NL
			<< TXT_TAB << "Erasing by position:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.erase(mi_fill_cont.begin() + 2)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.erase(su_fill_cont.begin() + 2)" << END;
	{
		typename MY_Container::iterator mi_erase_res = mi_fill_cont.erase(mi_fill_cont.begin() + 2);
		typename STD_Container::iterator su_erase_res = su_fill_cont.erase(su_fill_cont.begin() + 2);
		size_t	mi_res_pos = mi_erase_res - mi_fill_cont.begin();
		size_t	su_res_pos = su_erase_res - su_fill_cont.begin();

		elemc_compare_log(su_fill_cont, mi_fill_cont);
		cont_check_log(su_fill_cont, mi_fill_cont, ret);
		//Should return an iterator to the value after the erased element.
		//Since we're dealing with two different memory blocks, we convert the
		//iterators to their positions relative to begin() and compare those.
		compare_log(mi_res_pos == su_res_pos, ret, "Return Iterator Position", msg_offset);
		PRINT	<< std::setw(msg_offset) << mi_res_pos << TXT_TAB << std::setw(msg_offset) << su_res_pos << END;
	}
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Erasing last element by position:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.erase(mi_fill_cont.end() - 1)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.erase(su_fill_cont.end() - 1)" << END;
	{
		typename MY_Container::iterator mi_erase_res = mi_fill_cont.erase(mi_fill_cont.end() - 1);
		typename STD_Container::iterator su_erase_res = su_fill_cont.erase(su_fill_cont.end() - 1);
		size_t	mi_res_pos = mi_erase_res - mi_fill_cont.begin();
		size_t	su_res_pos = su_erase_res - su_fill_cont.begin();
	
		elemc_compare_log(su_fill_cont, mi_fill_cont);
		cont_check_log(su_fill_cont, mi_fill_cont, ret);
		//Should return an iterator to the value after the erased element.
		//Since we're dealing with two different memory blocks, we convert the
		//iterators to their positions relative to begin() and compare those.
		//In this case we're erasing the last element, so it should be equal to
		//end() for both.
		compare_log(mi_res_pos == su_res_pos, ret, "Return Iterator Position", msg_offset);
		PRINT	<< std::setw(msg_offset) << mi_res_pos << TXT_TAB << std::setw(msg_offset) << su_res_pos << END;
	}
	//ERASE BY RANGE
		PRINT	<< TXT_NL
				<< TXT_TAB << TXT_BYEL "Erasing by range:" << TXT_NL
				<< TXT_TAB << "  mi_fill_cont.erase(mi_fill_cont.begin() + 1, mi_fill_cont.end())" << TXT_NL
				<< TXT_TAB << "  su_fill_cont.erase(su_fill_cont.begin() + 1, su_fill_cont.end())" << END;
		//THESE RETURN VOID IN C++98
		mi_fill_cont.erase(mi_fill_cont.begin() + 1, mi_fill_cont.end());
		su_fill_cont.erase(su_fill_cont.begin() + 1, su_fill_cont.end());
		elemc_compare_log(su_fill_cont, mi_fill_cont);
		cont_check_log(su_fill_cont, mi_fill_cont, ret);
		PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
				<< "-------------------------------------------------------------------------------------" << END;

	//INSERT CHECKS
	//INSERT BY POSITION
	PRINT	<< TXT_BYEL "INSERT CHECKS" << TXT_NL
			<< TXT_TAB << "Inserting by position:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.insert(mi_fill_cont.begin(), 1984)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.insert(su_fill_cont.begin(), 1984)" << END;
	mi_fill_cont.insert(mi_fill_cont.begin(), 1984);
	su_fill_cont.insert(su_fill_cont.begin(), 1984);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//INSERT BY POSITION AND CLONE N TIMES
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Inserting by position and cloning n times:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.insert(mi_fill_cont.begin(), 2, 1970)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.insert(su_fill_cont.begin(), 2, 1970)" << END;
	mi_fill_cont.insert(mi_fill_cont.begin(), 2, 1970);
	su_fill_cont.insert(su_fill_cont.begin(), 2, 1970);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//Creating new containers for swap test
	PRINT	<< TXT_TAB << TXT_BYEL "Fill-creating new containers:" << TXT_NL
			<< TXT_TAB << "  ft::container mi_swappable_cont(4, 1)" << TXT_NL
			<< TXT_TAB << "  std::container su_swappable_cont(4, 1)" << END;
	MY_Container	mi_swappable_cont(4, 1);
	STD_Container	su_swappable_cont(4, 1);
	PRINT	<< TXT_TAB << TXT_BYEL "Inserting by position and cloning n times:" << TXT_NL
			<< TXT_TAB << "  mi_swappable_cont.insert(mi_swappable_cont.begin() + 1, 1, 9)" << TXT_NL
			<< TXT_TAB << "  su_swappable_cont.insert(su_swappable_cont.begin() + 1, 1, 9)" << END;
	mi_swappable_cont.insert(mi_swappable_cont.begin() + 1, 1, 9);
	su_swappable_cont.insert(su_swappable_cont.begin() + 1, 1, 9);
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);
	
	//INSERT BY RANGE
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Inserting by range:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.insert(mi_fill_cont.begin(), mi_swappable_cont.begin(), mi_swappable_cont.end())" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.insert(su_fill_cont.begin(), su_swappable_cont.begin(), su_swappable_cont.end())" << END;
	mi_fill_cont.insert(mi_fill_cont.begin(), mi_swappable_cont.begin(), mi_swappable_cont.end());
	su_fill_cont.insert(su_fill_cont.begin(), su_swappable_cont.begin(), su_swappable_cont.end());
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);

	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Inserting by range with reverse iterators:" << TXT_NL
			<< TXT_TAB << "  mi_assigned_cont.insert(mi_assigned_cont.begin(), mi_fill_cont.rbegin(), mi_fill_cont.rend())" << TXT_NL
			<< TXT_TAB << "  su_assigned_cont.insert(su_assigned_cont.begin(), su_fill_cont.rbegin(), su_fill_cont.rend())" << END;
	mi_assigned_cont.insert(mi_assigned_cont.begin(), mi_fill_cont.rbegin(), mi_fill_cont.rend());
	su_assigned_cont.insert(su_assigned_cont.begin(), su_fill_cont.rbegin(), su_fill_cont.rend());
	elemc_compare_log(su_assigned_cont, mi_assigned_cont);
	cont_check_log(su_assigned_cont, mi_assigned_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//SWAP CHECKS; 4 WAYS TO SWAP!
	//AS CLASS FUNCTION
	PRINT	<< TXT_BYEL "SWAP CHECKS" << TXT_NL
			<< TXT_TAB << "Swapping with class function:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.swap(mi_swappable_cont)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.swap(su_swappable_cont)" << END;
	mi_fill_cont.swap(mi_swappable_cont);
	su_fill_cont.swap(su_swappable_cont);
	//fill_cont swapped with swappable_cont
	PRINT	<< TXT_TAB << TXT_BYEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_TAB << TXT_BYEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);

	//WITH DEFAULT STD::SWAP
	//THIS DOES A BYTE-FOR-BYTE SWAP OF THE INSTANCE USING THE COPY-CONSTRUCTOR TO CREATE A THIRD TEMPORARY INSTANCE
	//VERY INEFFICIENT! BUT... FOR SCIENCE! xD
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Swapping with default std::swap" << TXT_NL
			<< TXT_TAB << "  std::swap(mi_fill_cont, mi_swappable_cont)" << TXT_NL
			<< TXT_TAB << "  std::swap(su_fill_cont, su_swappable_cont)" << END;
	std::swap(mi_fill_cont, mi_swappable_cont);
	std::swap(su_fill_cont, su_swappable_cont);
	//fill_cont swapped with swappable_cont again!
	PRINT	<< TXT_TAB << TXT_BYEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_TAB << TXT_BYEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);

	//USING FT::SWAP FOR FT::CONTAINER AND STD::SWAP FOR STD::CONTAINER VIA ARGUMENT-DEPENDENT LOOKUP (ADL)
	//ADL LOOKS UP A MATCHING TEMPLATE SPECIALIZATION WITHIN THE SAME NAMESPACE AS THE ARGUMENTS
	//THIS DOES MAGIC TO FIND MY SPECIALIZED SWAP TEMPLATE IN FT:: NAMESPACE WHICH CALLS THE CLASS FUNCTION
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Swapping with class function via ADL:" << TXT_NL
			<< TXT_TAB << "  std::swap(mi_fill_cont, mi_swappable_cont)" << TXT_NL
			<< TXT_TAB << "  std::swap(su_fill_cont, su_swappable_cont)" << END;
	swap(mi_fill_cont, mi_swappable_cont); //why does this activate ADL? no feckin idea!
	swap(su_fill_cont, su_swappable_cont);
	//fill_cont swapped with swappable_cont yet again!
	PRINT	<< TXT_TAB << TXT_BYEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_TAB << TXT_BYEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);

	//USING DEFAULT STD::SWAP BUT STILL FINDING FT::SWAP VIA ARGUMENT-DEPENDENT LOOKUP (ADL) FOR SOME REASON
	//ADL LOOKS UP A MATCHING TEMPLATE SPECIALIZATION WITHIN THE SAME NAMESPACE AS THE ARGUMENTS
	//THIS DOES MAGIC TO FIND MY SPECIALIZED SWAP TEMPLATE IN FT:: NAMESPACE WHICH CALLS THE CLASS FUNCTION
	//SO BASICALLY THE SAME AS BEFORE... RIGHT? I THINK. I HOPE!
	//HONESTLY, WHO THE HELL KNOWS AT THIS POINT? ONLY SCOTT MEYERS AND THE COMMITTEE... ANYWAY, THEY SWAP!
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Swapping with class function via ADL:" << TXT_NL
			<< TXT_TAB << "  std::swap(mi_fill_cont, mi_swappable_cont)" << TXT_NL
			<< TXT_TAB << "  std::swap(su_fill_cont, su_swappable_cont)" << END;
	using std::swap; //why does this activate ADL too? no feckin idea!
	swap(mi_fill_cont, mi_swappable_cont);
	swap(su_fill_cont, su_swappable_cont);
	//fill_cont swapped with swappable_cont yet another time!
	PRINT	<< TXT_TAB << TXT_BYEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_TAB << TXT_BYEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//GET ALLOCATOR CHECK
	// // You could do this:
	// MY_Container::allocator_type		my_alloc = mi_fill_cont.get_allocator();
	// STD_Container::allocator_type	std_alloc = su_fill_cont.get_allocator();
	//
	// // But you can't do this:
	// mi_fill_cont.allocator_type	my_alloc = mi_fill_cont.get_allocator();
	// su_fill_cont.allocator_type	std_alloc = su_fill_cont.get_allocator();
	//
	// // Because... well, according to compiler, because you just CAN'T. So THERE.
	//
	// Aaaanyway... we'll get an allocator instance and use it to allocate more
	// memory on the heap, because that's ALWAYS fun! :)
	//
	// Stop looking at me like that... ¬¬
	PRINT	<< TXT_BYEL "GET ALLOCATOR CHECK" << TXT_NL
			<< TXT_TAB << "Allocating heap memory using returned allocator instance:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.get_allocator().allocate(4)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.get_allocator().allocate(4)" << END;
	mi_fill_cont.get_allocator().allocate(4); //allocators are stateful, and remember what type they are allocating
	su_fill_cont.get_allocator().allocate(4); //so this is NOT 4 bytes, but rather 4 * sizeof(SourceContainer::value_type)
	typename MY_Container::value_type * 	mi_allocated_array = mi_fill_cont.get_allocator().allocate(4);
	typename STD_Container::value_type *	su_allocated_array = su_fill_cont.get_allocator().allocate(4);
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Assigning values to each allocation using constructor of returned allocator instance:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.get_allocator().construct(arr, val)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.get_allocator().construct(arr, val)" << END;
	//We don't know what the value_type could be, so we'll just default-initialize whatever it is.
	for (size_t i = 0; i < 4; ++i)
		mi_fill_cont.get_allocator().construct(&mi_allocated_array[i], typename MY_Container::value_type());
	for (size_t i = 0; i < 4; ++i)
		su_fill_cont.get_allocator().construct(&su_allocated_array[i], typename STD_Container::value_type());
	//Errmm... I'll just do memcmp! ;)
	{
		int	result;
		//sorry for the hideousness.
		//memcmp returns 0 if equal, compare_log expects true if equal...
		//the allocator expects a multiple of the type as the size, memcmp expects the size in bytes...
		//you know how it is. xD
		compare_log(!(result = std::memcmp(su_allocated_array, mi_allocated_array, 4 * sizeof(typename MY_Container::value_type))), ret, "Heap Allocation", msg_offset);
		PRINT	<< "mi_allocated_array " << (!result ? " == " : " != ") << " su_allocated_array" << END;
	}
	// // we can assign to the arrays and print the results if we know the types and they have ostream overloads and such
	// for (size_t i = 0; i < 4; ++i)
	// 	PRINT << "Allocated Array: " << mi_allocated_array[i] << END;
	// for (size_t i = 0; i < 4; ++i)
	// 	PRINT << "Allocated Array: " << su_allocated_array[i] << END;
	
	//Of course we can't forget to free our memory. ;)
	//First we destroy... don't know what those instances might need to free, after all...
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Destroying each instance in the allocated array:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.get_allocator().destroy(&arr[i])" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.get_allocator().destroy(&arr[i])" << END;
	size_t i = 3;
	do {
		mi_fill_cont.get_allocator().destroy(&mi_allocated_array[i]);
		su_fill_cont.get_allocator().destroy(&su_allocated_array[i]);
	} while (i-- > 0);
	//And then we deallocate... be sure to remember how much we allocated! ;)
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Deallocating the allocated memory block:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.get_allocator().deallocate(arr, 4)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.get_allocator().deallocate(arr, 4)" << END;
	mi_fill_cont.get_allocator().deallocate(mi_allocated_array, 4); // C++ is just SO much simpler than C!
	su_fill_cont.get_allocator().deallocate(su_allocated_array, 4); // I am really feeling that high level abstraction right now! xD
	//Look ma, no leaks!
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//ASSIGN CHECK
	PRINT	<< TXT_BYEL "ASSIGN CHECK" << TXT_NL
			<< TXT_TAB << "Assigning by fill:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.assign(8, 42)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.assign(8, 42)" << END;
	mi_fill_cont.assign(8, 42);
	su_fill_cont.assign(8, 42);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Assigning by range:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.assign(mi_copied_cont.begin(), mi_copied_cont.end())" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.assign(su_copied_cont.begin(), su_copied_cont.end())" << END;
	mi_fill_cont.assign(mi_copied_cont.begin(), mi_copied_cont.end());
	su_fill_cont.assign(su_copied_cont.begin(), su_copied_cont.end());
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//REFERENCING CHECKS
	//Referencing by []
	PRINT	<< TXT_BYEL "REFERENCING CHECKS" << TXT_NL
			<< TXT_TAB << "Referencing by []:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont[4])" << TXT_NL
			<< TXT_TAB << "  su_fill_cont[4])" << END;
	compare_log(mi_fill_cont[4] == su_fill_cont[4], ret, "fill_cont[4]", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont[4] << std::setw(msg_offset) << su_fill_cont[4] << END;
	//Referencing by &alias via []
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Referencing by &alias via [] (same thing):" << TXT_NL
			<< TXT_TAB << "  &mi_num1(mi_fill_cont[4]))" << TXT_NL
			<< TXT_TAB << "  &su_num1(su_fill_cont[4]))" << END;
	typename MY_Container::value_type &		mi_num1(mi_fill_cont[4]);
	typename STD_Container::value_type &	su_num1(su_fill_cont[4]);
	compare_log(mi_num1 == su_num1, ret, "num1 ref", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_num1 << TXT_TAB << std::setw(msg_offset) << su_num1 << END;
	//Referencing by container.at() member function
	//at() throws exceptions for out-of-bounds references
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Referencing in-bounds by container.at():" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.at(5)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.at(5)" << END;
	try
	{
		compare_log(mi_fill_cont.at(5) == su_fill_cont.at(5), ret, "fill_cont.at(5)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_fill_cont.at(5) << TXT_TAB << std::setw(msg_offset) << su_fill_cont.at(5) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TXT_TAB << TXT_BRED << e.what() << END;
	}

	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Referencing out-of-bounds by container.at() (my message):" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.at(6)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.at(6)" << END;
	try
	{
		compare_log(mi_fill_cont.at(6) == su_fill_cont.at(6), ret, "fill_cont.at(6)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_fill_cont.at(6) << TXT_TAB << std::setw(msg_offset) << su_fill_cont.at(6) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TXT_TAB << TXT_BBLU << e.what() << END;
	}
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Referencing out-of-bounds by container.at() (STL message):" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.at(6)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.at(6)" << END;
	try
	{
		compare_log(su_fill_cont.at(6) == mi_fill_cont.at(6), ret, "fill_cont.at(6)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_fill_cont.at(6) << TXT_TAB << std::setw(msg_offset) << su_fill_cont.at(6) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TXT_TAB << TXT_BBLU << e.what() << END; // OK, so which is clearer, my message, or STL message? xD
	}
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Referencing empty container.at() (my message):" << TXT_NL
			<< TXT_TAB << "  mi_vacio.at(0)" << TXT_NL
			<< TXT_TAB << "  su_vacio.at(0)" << END;
	try
	{
		MY_Container	mi_vacio;
		STD_Container	su_vacio;
		
		compare_log(mi_vacio.at(0) == su_vacio.at(0), ret, "vacio.at(0)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_vacio.at(0) << TXT_TAB << std::setw(msg_offset) << su_vacio.at(0) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TXT_TAB << TXT_BBLU << e.what() << END;
	}
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Referencing empty container.at() (STL message):" << TXT_NL
			<< TXT_TAB << "  mi_vacio_cont.at(0)" << TXT_NL
			<< TXT_TAB << "  su_vacio_cont.at(0)" << END;
	try
	{
		MY_Container	mi_vacio;
		STD_Container	su_vacio;
		
		compare_log(su_vacio.at(0) == mi_vacio.at(0), ret, "vacio.at(0)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_vacio.at(0) << TXT_TAB << std::setw(msg_offset) << su_vacio.at(0) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TXT_TAB << TXT_BBLU << e.what() << END;
	}
	//CONST REFERENCING
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Copy-creating const containers:"
			<< TXT_TAB << "  c_mi_copied_cont(mi_copied_cont)" << TXT_NL
			<< TXT_TAB << "  c_su_copied_cont(mi_copied_cont)" << END;
			const MY_Container	c_mi_copied_cont(mi_copied_cont);
			const STD_Container	c_su_copied_cont(su_copied_cont);
	PRINT	<< TXT_TAB << TXT_BYEL "Referencing const containers (by []):" << TXT_NL
			<< TXT_TAB << "  c_mi_copied_cont[2]" << TXT_NL
			<< TXT_TAB << "  c_su_copied_cont[2]" << END;
		compare_log(c_mi_copied_cont[2] == c_su_copied_cont[2], ret, "const copied_cont[2]", msg_offset);
		PRINT << std::setw(msg_offset) << c_mi_copied_cont[2] << std::setw(msg_offset) << c_su_copied_cont[2] << END;
	//COMPILE-TIME TESTS
	{
		// Const int reference to const c_fill_cont type_value, this is fine.
		typename MY_Container::const_reference	c_mi_num(c_mi_copied_cont[2]);
		typename STD_Container::const_reference	c_su_num(c_su_copied_cont[2]);
		compare_log(c_mi_num == c_su_num, ret, "const num", msg_offset);
		PRINT << std::setw(msg_offset) << c_mi_copied_cont[2] << TXT_TAB << std::setw(msg_offset) << c_su_copied_cont[2] << END;
		// // Compiler will not allow this as c_fill_cont is const.
		// typename MY_Container::reference & mi_num(c_mi_copied_cont[2]);
		// typename STD_Container::reference & su_num(c_su_copied_cont[2]);

		// // Compiler will also not allow this as c_mi_copied_cont is const.
		//c_mi_copied_cont[0] = 8;
		//c_su_copied_cont[0] = 8;
	}
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//FRONT AND BACK CHECKS
	PRINT	<< TXT_BYEL "FRONT AND BACK CHECKS" << TXT_NL
			<< TXT_TAB << "Calling front():" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.front()" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.front()" << END;
	compare_log(mi_fill_cont.front() == su_fill_cont.front(), ret, "fill_cont.front()", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont.front() << TXT_TAB << std::setw(msg_offset) << su_fill_cont.front() << END;
			
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Calling back():" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.back()" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.back()" << END;
	compare_log(mi_fill_cont.back() == su_fill_cont.back(), ret, "fill_cont.back()", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont.back() << TXT_TAB << std::setw(msg_offset) << su_fill_cont.back() << END;

	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Calling front() const:" << TXT_NL
			<< TXT_TAB << "  c_mi_copied_cont.front()" << TXT_NL
			<< TXT_TAB << "  c_su_copied_cont.front()" << END;
	compare_log(c_mi_copied_cont.front() == c_su_copied_cont.front(), ret, "const copied_cont.front()", msg_offset);
	PRINT	<< std::setw(msg_offset) << c_mi_copied_cont.front() << TXT_TAB << std::setw(msg_offset) << c_su_copied_cont.front() << END;

	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Calling back() const:" << TXT_NL
			<< TXT_TAB << "  c_mi_copied_cont.back()" << TXT_NL
			<< TXT_TAB << "  c_su_copied_cont.back()" << END;
	compare_log(c_mi_copied_cont.back() == c_su_copied_cont.back(), ret, "const copied_cont.back()", msg_offset);
	PRINT	<< std::setw(msg_offset) << c_mi_copied_cont.back() << TXT_TAB << std::setw(msg_offset) << c_su_copied_cont.back() << END;
	//COMPILE-TIME TESTS
	{
		//This is fine
		mi_fill_cont.front() = 5;
		mi_fill_cont.back() = 10;
		su_fill_cont.front() = 5;
		su_fill_cont.back() = 10;

		// // Compiler should not allow this as c_copied_cont is const.
		// c_mi_copied_cont.front() = 5;
		// c_mi_copied_cont.back() = 10;
		// c_su_copied_cont.front() = 5;
		// c_su_copied_cont.back() = 10;
	}
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//COMPARISON CHECKS
	comparison_operator_log(su_fill_cont, su_assigned_cont, mi_fill_cont, mi_assigned_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	return (ret);
}

int main(void)
{	
	//size_t				i;
	ft::bintree<int>	ex1;
	ft::bintree<int>	ex2;

	typedef ft::bintree_pair<std::string, std::string>	Dictionary;
	
	Dictionary	test2;

	ex1.push_back(58);
	ex1.push_back(26);
	ex1.push_back(2);
	ex1.push_back(42);
	ex1.push_back(15);
	ex1.print();
		

	ex2.push_back(42);
	ex2.push_back(15);
	ex2.push_back(58);
	ex2.push_back(2);
	ex2.push_back(26);
	ex2.print();
	ft::bintree<int>::iterator del_this(ex2.begin());
	ex2.erase(&(del_this[3]));
	PRINT << "MIEDO" << END;
	ex2.print();


	test2.push_back("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo.");
	test2.push_back("ordenador", "ORDENADOR: \t\t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios.");
	test2.push_back("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes.");
	test2.push_back("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo.");
	test2.push_back("tig", "TIG: \t\t\t\t\tTrabajo de interés general.");
	test2.push_back("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados.");
	test2.push_back("array", "ARRAY: \t\t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados.");
	test2.push_back("marvin", "MARVIN: \t\t\t\tRobot cascarrabias.");
	test2.push_back("norminette", "NORMINETTE: \t\t\t\tGuía de estilo que asegura que nadie podrá entender tu código.");
	test2.push_back("cafe", "CAFÉ: \t\t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua.");
	test2.push_back("agua", "AGUA: \t\t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe).");
	test2.push_back("compilador", "COMPILADOR: \t\t\t\tÚnico profesor en activo de 42.");
	
	// test2.push_back("cuarenta y dos", 42);
	// test2.push_back("uno", 1);
	// test2.push_back("noventa y nueve", 99);
	// test2.push_back("veintisiete", 27);
	// test2.push_back("dos", 2);
	// test2.push_back("sesenta y ocho", 68);
	// test2.push_back("ochenta y tres", 83);
	// test2.push_back("treinta y cuatro", 34);
	// test2.print();

	// test2.push_back(42, 42);
	// test2.push_back(1, 1);
	// test2.push_back(99, 99);
	// test2.push_back(27, 27);
	// test2.push_back(2, 2);
	// test2.push_back(68, 68);
	// test2.push_back(83, 83);
	// test2.push_back(34, 34);
	// //test2.print();

	// ft::bintree<int>::iterator ex1end = ex1.end();	
	// (void)ex1end;

	for (ft::bintree<int>::iterator it = ex1.begin(), end = ex1.end(); it != end; ++it)
		PRINT << it->data << END;

	ft::bintree<int>::iterator reftest = ex1.begin();
	PRINT << "REFTEST: " << reftest[2].data << END;

	PRINT << TXT_NL;

	for (ft::bintree<int>::reverse_iterator it = ex1.rbegin(), end = ex1.rend(); it != end; ++it)
		PRINT << it->data << END;

	PRINT << TXT_NL;
	PRINT << "EX2 POST-DELETE" << END;

	for (ft::bintree<int>::iterator it = ex2.begin(), end = ex2.end(); it != end; ++it)
		PRINT << it->data << END;

	PRINT << TXT_NL;

	// ft::bintree<int>::iterator ex42 = *(ex1.getNode(42));
	// PRINT << (*ex42).data << END;
	// ++ex42;
	// if (ex42 == ex1.end())
	// 	PRINT << "bleh" << END;

	PRINT << "EL ABECEDARIO DE 42" << END;
	
	for (Dictionary::iterator it = test2.begin(), end = test2.end(); it != end; ++it)
		PRINT << it->data.second << END;
	
	PRINT << TXT_NL;
	
	for (Dictionary::iterator it = test2.end() - 1, end = test2.begin() - 1; it != end; --it)
		PRINT << it->data.second << END;

	PRINT << TXT_NL;
	
	for (Dictionary::reverse_iterator it = test2.rbegin(), end = test2.rend(); it != end; ++it)
		PRINT << it->data.second << END;

	

	// if (iterator_tests())
	// 	PRINT << TXT_BGRN "OK" << END;
	// else
	// 	PRINT << TXT_BRED "KO" << END;
	// if (my_veritable_vector<ft::vector<int>, std::vector<int> >())
	// 	PRINT << TXT_BGRN "OK" << END;
	// else
	// 	PRINT << TXT_BRED "KO" << END;

	//quick make_pair test
	// using ft::make_pair;
	// ft::pair<int, char> pair_chorra = make_pair(42, 42);
	// std::pair<int, char> std_pair_chorra = std::make_pair(42, 42);
	// std::cout << "STD PAIR CHORRA: " << std_pair_chorra.first << " " << std_pair_chorra.second << std::endl;
	// std::cout << "FT PAIR CHORRA: " << pair_chorra.first << " " << pair_chorra.second << std::endl;
	// ft::pair<int, char>	pair_chorra(42, 42);
	// std::pair<int, char> std_pair_chorra(42, 42);

	// PRINT << TXT_BYEL "MY PAIR_CHORRA: " TXT_BGRN << pair_chorra.first << TXT_BYEL ", " TXT_BGRN << pair_chorra.second << END;
	// PRINT << TXT_BYEL "STD PAIR_CHORRA: " TXT_BGRN << std_pair_chorra.first << TXT_BYEL ", " TXT_BGRN << std_pair_chorra.second << END;

	// //enable_if test
	// //Change to non-integral (double, float, etc.) to test. :)
	// PRINT << TXT_BYEL "ENABLE_IF TEST:" << TXT_NL;
	// int	i = 1;
	// PRINT << TXT_TAB << ALN << "i is odd: " << std::boolalpha << TXT_BGRN << ft::is_odd(i) << END;

	// std::string	test1 = "Apple";
	// std::string test2 = "honey";
	// std::string test3 = "honey";
	// bool std_ret;

	// std_ret = std::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());

	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

	// std_ret = ft::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());
	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

	// std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test3.begin());
	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

	// std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test1.begin());
	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;
	// // //DEBUG
	// // {
	// // 	PRINT << TXT_BYEL << "THE GREAT IS_INTEGRAL TEST!" << TXT_NL
	// // 	<< "Double Is Integral?" << std::boolalpha << " " << std::is_integral<double>::value << TXT_NL
	// // 	<< "Float Is Integral?" << std::boolalpha << " " << std::is_integral<float>::value << TXT_NL
	// // 	<< "Unsigned Int Is Integral?" << std::boolalpha << " " << std::is_integral<unsigned int>::value << END;
	// // }
	// // //DEBUG


	return (0);
}