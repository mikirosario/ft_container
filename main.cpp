/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/12/13 10:03:10 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ansi_codes.hpp"
#include "ft_vector.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "utility.hpp"
#include "ft_bintree.hpp"
#include "ft_bintree_pair.hpp"
#include "ft_map.hpp"
#include "ft_stack.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>


#include <map>

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

// void	print(ft::map<std::string, std::string> const & map) {
// 	for (ft::map<std::string, std::string>::iterator it = map.begin(), end = map.end(); it != end; ++map)
// 		PRINT << *it << END;
// }

template<typename T>
void	print_map(T const & map)
{
	for (typename T::const_iterator it = map.begin(), end = map.end(); it != end; ++it)
		PRINT << it->second << END;
}

template<typename MyMap, typename StdMap>
void	print_map_comp(MyMap const & my_map, StdMap const & std_map, char const *& color, bool & ret)
{
	typename MyMap::const_iterator mit;
	typename MyMap::const_iterator mend;
	typename StdMap::const_iterator sit;
	typename StdMap::const_iterator send;
	for (mit = my_map.begin(), mend = my_map.end(), sit = std_map.begin(), send = std_map.end(); sit != send; ++mit, ++sit)
		{
			check((mit->second == sit->second), color, ret);
			PRINT << color << "MY  > " << mit->second << TXT_NL << "STL > " << sit->second << END;
		}
}

template<typename MyMap, typename StdMap>
void	print_map_rev_comp(MyMap const & my_map, StdMap const & std_map, char const *& color, bool & ret)
{
	typename MyMap::const_reverse_iterator mit;
	typename MyMap::const_reverse_iterator mend;
	typename StdMap::const_reverse_iterator sit;
	typename StdMap::const_reverse_iterator send;

	for (mit = my_map.rbegin(), mend = my_map.rend(), sit = std_map.rbegin(), send = std_map.rend(); sit != send; ++mit, ++sit)
		{
			check((mit->second == sit->second), color, ret);
			PRINT << color << "MY  > " << mit->second << TXT_NL << "STL > " << sit->second << END;
		}
}

bool	isGreen(std::string const color) {
	return (color.compare(TXT_BGRN) == 0);
}

template<typename Key, typename Value>
bool	my_magnificent_map(std::map<Key, Value> const & seed_map)
{
	char const *	color = TXT_BGRN;
	bool	ret = true;
	typedef ft::map<Key, Value>		ft_map;
	typedef std::map<Key, Value>	std_map;
	//DEFAULT CONSTRUCTOR
	PRINT	<< TXT_BYEL << "DEFAULT INSTANTIATION TEST" << END;
	ft_map		mi_map_default;
	std_map		su_map_default;
	print_map_comp(mi_map_default, su_map_default, color, ret);
	PRINT	<< ((isGreen(color) == true) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	

	PRINT	<< TXT_NL << TXT_BYEL << "RANGE CONSTRUCTION TESTS" << END;
	//RANGE CONSTRUCTOR
	ft_map		mi_map_range(seed_map.begin(), seed_map.end());
	std_map		su_map_range(seed_map.begin(), seed_map.end());
	print_map_comp<ft_map, std_map >(mi_map_range, su_map_range, color, ret);

	PRINT	<< TXT_NL << TXT_BYEL << "COPY CONSTRUCTION TESTS" << END;
	ft_map		mi_map_copy(mi_map_range);
	std_map		su_map_copy(su_map_range);
	print_map_comp<ft_map, std_map >(mi_map_copy, su_map_copy, color, ret);

	PRINT	<< TXT_NL << TXT_BYEL << "ASSIGNMENT OVERLOAD TESTS" << END;
	mi_map_default = mi_map_copy;
	su_map_default = su_map_copy;
	print_map_comp<ft_map, std_map>(mi_map_default, su_map_default, color, ret);

	PRINT	<< TXT_NL << TXT_BYEL << "REVERSE ITERATOR TEST" << END;
	print_map_rev_comp<ft_map, std_map>(mi_map_default, su_map_default, color, ret);

	PRINT	<< TXT_NL << TXT_BYEL << "CAPACITY TESTS" << TXT_NL
			<< "Empty Test: " << TXT_NL
			<< "MY  " << TXT_TAB << "STD " << END;
	check(mi_map_default.empty() == su_map_default.empty(), color, ret);
	PRINT	<< color << std::boolalpha << mi_map_default.empty() << TXT_TAB << su_map_default.empty() << END;
	PRINT	<< TXT_BYEL << "Size Test: " << TXT_NL
			<< "MY  " << TXT_TAB << "STD " << END;
	check(mi_map_default.size() == su_map_default.size(), color, ret);
	PRINT	<< color << mi_map_default.size() << TXT_TAB << su_map_default.size() << END;
	PRINT	<< TXT_BYEL << "Max Size Test: " << TXT_NL
			<< "MY  " << TXT_TAB << TXT_TAB TXT_TAB << "STD " << END;
	PRINT	<< TXT_BWHT << mi_map_default.max_size() << TXT_TAB << su_map_default.max_size() << END;

	PRINT	<< TXT_NL << TXT_BYEL << "ACCESS ELEMENT BY KEY REFERENCE TEST" << TXT_NL
			<< TXT_TAB << "Find Reference to Existent Element ('norminette')" << END;
	check(mi_map_default["norminette"] == su_map_default["norminette"], color, ret);
	PRINT	<< color << mi_map_default["norminette"] << TXT_NL
			<< su_map_default["norminette"] << END;
	
	PRINT	<< TXT_BYEL << TXT_TAB << "Insert New Key and Default-Instantiated Value ('aguafiestas')" << TXT_NL;
	check(mi_map_default["aguafiestas"] == su_map_default["aguafiestas"], color, ret);
			PRINT	<< (isGreen(color) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	PRINT	<< color << mi_map_default["aguafiestas"] << TXT_NL
			<< su_map_default["aguafiestas"] << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Insert Value by Key Reference ('miyamoto')" << TXT_NL;
	mi_map_default["miyamoto"] = "MIYAMOTO: \t\t\tEminencia de los videojuegos que descubrió que la constante gravitacional está más guapa como variable.";
	su_map_default["miyamoto"] = "MIYAMOTO: \t\t\tEminencia de los videojuegos que descubrió que la constante gravitacional está más guapa como variable.";
	check(mi_map_default["miyamoto"] == su_map_default["miyamoto"], color, ret);
	PRINT	<< (isGreen(color) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	PRINT	<< color << mi_map_default["miyamoto"] << TXT_NL
			<< su_map_default["miyamoto"] << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Replace Value by Key Reference ('aguafiestas')" << TXT_NL;
	mi_map_default["aguafiestas"] = "AGUAFIESTAS: \t\t\tSinónimo de Marvin (véase 'marvin').";
	su_map_default["aguafiestas"] = "AGUAFIESTAS: \t\t\tSinónimo de Marvin (véase 'marvin').";
	check(mi_map_default["aguafiestas"] == su_map_default["aguafiestas"], color, ret);
	PRINT	<< (isGreen(color) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	PRINT	<< color << mi_map_default["aguafiestas"] << TXT_NL
			<< su_map_default["aguafiestas"] << END;
	
	PRINT	<< TXT_BYEL << TXT_TAB << "Result:" << END;
	print_map_comp(mi_map_default, su_map_default, color, ret);

	
	PRINT	<< TXT_NL << TXT_BYEL << "OPERATIONS TESTS" << TXT_NL
			<< TXT_TAB << "Find by Key ('marvin')" << END;
	{
	typename ft_map::iterator mit = mi_map_default.find("marvin");
	typename std_map::iterator sit = su_map_default.find("marvin");
	check(mit->first == sit->first & mit->second == sit->second, color, ret);
	PRINT	<< color << mit->second << TXT_NL
			<< sit->second << END;
	}
	PRINT	<< TXT_TAB << TXT_BYEL << "Find by Key Non-Existent ('marvine')" << END; //must return end()
	{
	typename ft_map::iterator mit = mi_map_default.find("marvine");
	typename std_map::iterator sit = su_map_default.find("marvine");
	check(mit == mi_map_default.end() & sit == su_map_default.end(), color, ret);
	PRINT	<< ((isGreen(color) == true) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	}
	PRINT	<< TXT_BYEL << TXT_TAB << "Count Existent Element ('agua')" << TXT_NL;
	check(mi_map_default.count("agua") == su_map_default.count("agua"), color, ret);
	PRINT	<< "MY  " << TXT_TAB << "STD " << TXT_NL
			<< color << mi_map_default.count("agua") << TXT_TAB << su_map_default.count("agua") << END;
	PRINT	<< TXT_BYEL << TXT_TAB << "Count Non-Existent Element ('santana')" << TXT_NL;
	check(mi_map_default.count("santana") == su_map_default.count("santana"), color, ret);
	PRINT	<< "MY  " << TXT_TAB << "STD " << TXT_NL
			<< color << mi_map_default.count("santana") << TXT_TAB << su_map_default.count("santana") << END;
	{
	PRINT	<< TXT_BYEL << TXT_TAB << "Lower Bound Existent Element ('marvin')" << TXT_NL;
	typename ft_map::iterator mit = mi_map_default.lower_bound("marvin");
	typename std_map::iterator sit = su_map_default.lower_bound("marvin");
	check(mit->first == sit->first & mit->second == sit->second, color, ret);
	PRINT	<< color << mit->second << TXT_NL << sit->second << END;
	
	PRINT	<< TXT_BYEL << TXT_TAB << "Lower Bound Non-Existent Subsequent Element ('marvinovich')" << TXT_NL;
	mit = mi_map_default.lower_bound("marvinovich");
	sit = su_map_default.lower_bound("marvinovich");
	check(mit->first == sit->first & mit->second == sit->second, color, ret);
	PRINT	<< color << mit->second << TXT_NL << sit->second << END;
	
	PRINT	<< TXT_BYEL << TXT_TAB << "Lower Bound Non-Existent Min Element ('aaaa')" << TXT_NL;
	mit = mi_map_default.lower_bound("aaaa");
	sit = su_map_default.lower_bound("aaaa");
	check(mit->first == sit->first & mit->second == sit->second, color, ret);
	PRINT	<< color << mit->second << TXT_NL << sit->second << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Lower Bound Non-Existent Max Element ('zzzz')" << TXT_NL;
	mit = mi_map_default.lower_bound("zzzz");
	sit = su_map_default.lower_bound("zzzz");
	check((--mit)->first == (--sit)->first & mit->second == sit->second, color, ret);
	PRINT	<< color << (isGreen(color) == true ? "END()" : "NOT END()!") << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Upper Bound Existent Element ('cafe')" << TXT_NL;
	mit = mi_map_default.upper_bound("cafe");
	sit = su_map_default.upper_bound("cafe");
	check(mit->first == sit->first & mit->second == sit->second, color, ret);
	PRINT	<< color << mit->second << TXT_NL << sit->second << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Upper Bound Non-Existent Subsequent Element ('cafeteria')" << TXT_NL;
	mit = mi_map_default.upper_bound("cafeteria");
	sit = su_map_default.upper_bound("cafeteria");
	check(mit->first == sit->first & mit->second == sit->second, color, ret);
	PRINT	<< color << mit->second << TXT_NL << sit->second << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Upper Bound Non-Existent Min Element ('aaaa')" << TXT_NL;
	mit = mi_map_default.upper_bound("aaaa");
	sit = su_map_default.upper_bound("aaaa");
	check(mit->first == sit->first & mit->second == sit->second, color, ret);
	PRINT	<< color << mit->second << TXT_NL << sit->second << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Upper Bound Non-Existent Max Element ('zzzz')" << TXT_NL;
	mit = mi_map_default.upper_bound("zzzz");
	sit = su_map_default.upper_bound("zzzz");
	check((--mit)->first == (--sit)->first & mit->second == sit->second, color, ret);
	PRINT	<< color << (isGreen(color) == true ? "END()" : "NOT END()!") << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Equal Range Existent Element ('norminette')" << TXT_NL;
	ft::pair<typename ft_map::iterator, typename ft_map::iterator> mi_range = mi_map_default.equal_range("norminette");
	std::pair<typename std_map::iterator, typename std_map::iterator> su_range = su_map_default.equal_range("norminette");
	check(mi_range.first->first == su_range.first->first
		& mi_range.first->second == su_range.first->second
		& mi_range.second->first == su_range.second->first
		& mi_range.second->second == su_range.second->second
		, color, ret);
	PRINT	<< color << mi_range.first->second << TXT_NL << mi_range.second->second
			<< TXT_NL << su_range.first->second << TXT_NL << su_range.second->second << END;
	}
	
	PRINT	<< TXT_NL << TXT_BYEL << "INSERT TESTS" << TXT_NL
			<< TXT_TAB << "Insert Single Element and Access by Key Reference" << END;
	mi_map_default.insert(ft::pair<std::string const, std::string>("santana", "SANTANA: \t\t\t\tCanario estepario."));
	su_map_default.insert(std::pair<std::string const, std::string>("santana", "SANTANA: \t\t\t\tCanario estepario."));
	check(mi_map_default["santana"] == su_map_default["santana"], color, ret);
	PRINT	<< color << mi_map_default["santana"] << TXT_NL
			<< su_map_default["santana"] << END;
	
	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('alex') with GOOD Hint (aka. constant time insert, aka. DE GUAYS INSERT)" << END;
	mi_map_default.insert(mi_map_default.lower_bound("alex"), ft::make_pair<std::string, std::string>("alex", "ALEX: \t\t\t\tCien por cien NO FAKE!"));
	su_map_default.insert(su_map_default.lower_bound("alex"), std::make_pair<std::string, std::string>("alex", "ALEX: \t\t\t\tCien por cien NO FAKE!"));
	check(mi_map_default["alex"] == su_map_default["alex"], color, ret);
	PRINT	<< color << mi_map_default["alex"] << TXT_NL
			<< su_map_default["alex"] << END;
	//print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('a') with GOOD Hint (aka. constant time insert, aka. DE GUAYS INSERT)" << END;
	mi_map_default.insert(mi_map_default.lower_bound("a"), ft::make_pair<std::string, std::string>("a", "A: \t\t\t\tPrimera letra del alafabeto latino."));
	su_map_default.insert(su_map_default.lower_bound("a"), std::make_pair<std::string, std::string>("a", "A: \t\t\t\tPrimera letra del alafabeto latino."));
	check(mi_map_default["a"] == su_map_default["a"], color, ret);
	PRINT	<< color << mi_map_default["a"] << TXT_NL
			<< su_map_default["a"] << END;
	//print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('rorozco') with BAD Hint (aka. logarithmic time + correction time insert, aka. GILIPOLLAS INSERT)" << END;
	mi_map_default.insert(mi_map_default.begin(), ft::make_pair<std::string, std::string>("rorozco", "ROROZCO: \t\t\t\tDueña de la Playstation 4."));
	su_map_default.insert(su_map_default.begin(), std::make_pair<std::string, std::string>("rorozco", "ROROZCO: \t\t\t\tDueña de la Playstation 4."));
	check(mi_map_default["rorozco"] == su_map_default["rorozco"], color, ret);
	PRINT	<< color << mi_map_default["rorozco"] << TXT_NL
			<< su_map_default["rorozco"] << END;
	
	PRINT	<< TXT_TAB << TXT_BYEL << "Insertion Result for map_default: " << END;
	print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert by Range to map_copy (from agua to tig, including alex, santana and rorozco, excluding a)" << END; //insert range from agua to tig, including alex, santana and rorozco
	mi_map_copy.insert(++mi_map_default.begin(), --mi_map_default.end());
	su_map_copy.insert(++su_map_default.begin(), --su_map_default.end());
	print_map_comp(mi_map_copy, su_map_copy, color, ret);
	
	PRINT	<< TXT_NL << TXT_BYEL << "ERASE TESTS" << TXT_NL
			<< TXT_TAB << "Erase by Position (begin())" << END;
	mi_map_default.erase(mi_map_default.begin()); //should erase 'a'
	su_map_default.erase(su_map_default.begin()); //should erase 'a'
	print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT << TXT_BYEL << TXT_TAB << "Erase by Key ('marvin')" << END;
	mi_map_default.erase("marvin"); //should erase 'marvin'
	su_map_default.erase("marvin"); //should erase 'marvin'
	print_map_comp(mi_map_default, su_map_default, color, ret);

	{
	PRINT << TXT_BYEL << TXT_TAB << "Erase by Range ('norminette' to 'santana')" << END;
	typename ft_map::iterator mit = mi_map_default.find("norminette");
	typename ft_map::iterator mend = mi_map_default.find("santana");
	typename std_map::iterator sit = su_map_default.find("norminette");
	typename std_map::iterator send = su_map_default.find("santana");
	mi_map_default.erase(mit, mend);
	su_map_default.erase(sit, send);
	print_map_comp(mi_map_default, su_map_default, color, ret);
	}


	PRINT << TXT_NL << TXT_BYEL << "SWAP TEST (map_default <-> map_range)" << END;
	swap(mi_map_default, mi_map_range);
	swap(su_map_default, su_map_range);
	print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT << TXT_NL << TXT_BYEL << "CLEAR TEST (map_range)" << END;
	mi_map_range.clear();
	su_map_range.clear();
	print_map_comp(mi_map_range, su_map_range, color, ret);

	PRINT	<< TXT_NL << TXT_BYEL << "COMP OBJECT TESTS" << END;
	PRINT	<< std::boolalpha << mi_map_default.value_comp()(*mi_map_default.begin(), *(++mi_map_default.begin())) << END;

	//PASS MY BEGIN AND END ITERATORS TO FT::LEXICOGRAPHICAL COMPARE FOR THIS NONSENSE
	PRINT	<< TXT_NL << TXT_BYEL << "RELATIONAL OPERATORS??" << END; //UNDOCUMENTED RELATIONAL OPERATORS? :P
	PRINT	<< std::boolalpha << (su_map_default > su_map_copy) << END;


	return (true);
}

int main(void)
{	
	std::map<std::string, std::string>	seed_map;
	seed_map.insert(std::make_pair("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo."));
	seed_map.insert(std::make_pair<std::string, std::string>("ordenador", "ORDENADOR: \t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios."));
	seed_map.insert(std::make_pair<std::string, std::string>("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes."));
	seed_map.insert(std::make_pair<std::string, std::string>("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo."));
	seed_map.insert(std::make_pair<std::string, std::string>("tig", "TIG: \t\t\t\tTrabajo de interés general."));
	seed_map.insert(std::make_pair<std::string, std::string>("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados."));
	seed_map.insert(std::make_pair<std::string, std::string>("array", "ARRAY: \t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados."));
	seed_map.insert(std::make_pair<std::string, std::string>("marvin", "MARVIN: \t\t\t\tRobot cascarrabias."));
	seed_map.insert(std::make_pair<std::string, std::string>("norminette", "NORMINETTE: \t\t\tGuía de estilo que asegura que nadie podrá entender tu código."));
	seed_map.insert(std::make_pair<std::string, std::string>("cafe", "CAFÉ: \t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua."));
	seed_map.insert(std::make_pair<std::string, std::string>("agua", "AGUA: \t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe)."));
	seed_map.insert(std::make_pair<std::string, std::string>("compilador", "COMPILADOR: \t\t\tÚnico profesor en activo de 42."));

	my_magnificent_map<std::string, std::string>(seed_map);
	
	/*****/
	
	
// 	//size_t				i;
// 	ft::bintree<int>	ex1;
// 	ft::bintree<int>	ex2;

// 	//Esto tiene que funcionar :P
// 	// std::vector<int>	pepe;
// 	// int kevin[] = {1,2,3,4,5};
// 	// pepe.assign(kevin, kevin + 5);


// 	// std::vector<int> k (kevin, kevin + 5);

// 	// std::vector<int> std_quick_test;
// 	ft::vector<int>	quick_test;
// 	for(ft::vector<int>::const_iterator it = quick_test.begin(), end = quick_test.end(); it != end; ++it) {}
// 	//for (std::vector<int>::const_iterator it = std_quick_test.begin(), end = std_quick_test.end(); it != end; ++it) {}
// 	//DEFAULT CONSTRUCTOR
// 	PRINT << "MAP INSERT BY PAIR" << END;
// 	ft::map<std::string, std::string>	my_dictionary_default;
	
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("ordenador", "ORDENADOR: \t\t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("tig", "TIG: \t\t\t\t\tTrabajo de interés general."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("array", "ARRAY: \t\t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("marvin", "MARVIN: \t\t\t\tRobot cascarrabias."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("norminette", "NORMINETTE: \t\t\t\tGuía de estilo que asegura que nadie podrá entender tu código."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("cafe", "CAFÉ: \t\t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("agua", "AGUA: \t\t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe)."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("compilador", "COMPILADOR: \t\t\t\tÚnico profesor en activo de 42."));
	
// 	for (ft::map<std::string, std::string>::iterator it = my_dictionary_default.begin(), end = my_dictionary_default.end(); it != end; ++it)
// 		PRINT << it->second << END;

// 	//COPY CONSTRUCTOR
// 	ft::map<std::string, std::string>	my_dictionary_copy(my_dictionary_default);
// 	for (ft::map<std::string, std::string>::const_iterator it = my_dictionary_copy.begin(), end = my_dictionary_copy.end(); it != end; ++it)
// 		PRINT << it->second << END;
// 	std::map<std::string, std::string>	std_dictionary;
// 	for (std::map<std::string, std::string>::const_iterator it = std_dictionary.begin(), end = std_dictionary.end(); it != end; ++it)
// 		PRINT << it->second << END;

// 	//RANGE CONSTRUCTOR
// 	ft::map<std::string, std::string>	my_dictionary_range(my_dictionary_default.begin(), my_dictionary_default.end());
// 	for (ft::map<std::string, std::string>::const_iterator it = my_dictionary_range.begin(), end = my_dictionary_range.end(); it != end; ++it)
// 		PRINT << it->second << END;
	
// 	//ASSIGN CONSTRUCTOR
// 	ft::map<std::string, std::string>	my_dictionary_assign;
// 	my_dictionary_assign = my_dictionary_default;
// 	for (ft::map<std::string, std::string>::const_iterator it = my_dictionary_assign.begin(), end = my_dictionary_assign.end(); it != end; ++it)
// 		PRINT << it->second << END;

// 	//CONST TEST
// 	// const ft::map<std::string, std::string>	my_dictionary_const(my_dictionary_default);
// 	// for (ft::map<std::string, std::string>::const_iterator it = my_dictionary_const.begin(), end = my_dictionary_const.end(); it != end; ++it)
// 	// 	PRINT << (it->second = "blah blah blah") << END;
// 	ft::map<std::string, std::string>	my_dictionary_no_const(my_dictionary_default);
// 	for (ft::map<std::string, std::string>::iterator it = my_dictionary_no_const.begin(), end = my_dictionary_no_const.end(); it != end; ++it)
// 		PRINT << (it->second = "blah blah blah") << END;
	



// 	// test2.insert("cuarenta y dos", 42);
// 	// test2.insert("uno", 1);
// 	// test2.insert("noventa y nueve
	
// 	// ft::map<std::string, std::string>	my_default_constructed_dictionary;
// 	// ft::map<std::string, std::string>	my_default_constructed_dictionary;
// 	// ft::map<std::string, std::string>	my_default_constructed_dictionary;
	

	

// 	typedef ft::bintree_pair<std::string, std::string>	Dictionary;
	
// 	Dictionary	test2;

// 	PRINT << std::boolalpha << "New bintree ex1 is empty: " << ex1.empty() << END;
// 	PRINT << "New bintree ex1 size: " << ex1.size() << END;

// 	ex1.insert(58);
// 	ex1.insert(26);
// 	ex1.insert(2);
// 	ex1.insert(42);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.print();

// 	PRINT << TXT_NL << "Count 15s: " << ex1.count(15) << TXT_NL << std::endl;
// 	PRINT << TXT_NL << "Count 32s: " << ex1.count(32) << TXT_NL << std::endl;

// 	PRINT << TXT_NL << "El gilipollas insert: " << TXT_NL;
// 	ex1.insert(ex1.end(), 3);
// 	ex1.insert(ex1.begin(), 50);
// 	PRINT << TXT_NL << "El de guays insert: " << TXT_NL;
// 	ex1.insert(ex1.end(), 90);
// 	ex1.insert((ex1.begin() + 2), 4);
// 	ex1.print();

// 	PRINT << std::boolalpha << "Bintree ex1 is empty: " << ex1.empty() << END;
// 	PRINT << "Bintree ex1 size: " << ex1.size() << END;

// 	PRINT 	<< TXT_NL << "Lower Bound: " << ex1.lower_bound(30)->data
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(43)->data
// 			<< TXT_NL << "Lower Bound: " << (ex1.lower_bound(59) == ex1.end() ? "END" : "ERROR")
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(1)->data 
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(4)->data 
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(16)->data
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(14)->data
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(25)->data
// 			<< END;

// 	PRINT 	<< TXT_NL << "Upper Bound: " << ex1.upper_bound(30)->data
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(43)->data
// 			<< TXT_NL << "Upper Bound: " << (ex1.upper_bound(59) == ex1.end() ? "END" : "ERROR")
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(1)->data 
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(4)->data 
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(16)->data
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(14)->data
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(25)->data
// 			<< END;

// 	ex1.insert(43);
// 	ex1.print();


// // 	/* DELETE */
// // 	PRINT	<< TXT_NL << "DELETE BY RANGE TEST" << END;
// // 	//ex1.erase(ex1.begin() + 1);
// // 	ft::bintree<int>::iterator dfirst = (ex1.begin() + 1);
// // 	ft::bintree<int>::iterator dlast = (ex1.end() - 2);
// // 	ex1.erase(dfirst, dlast);
// // 	ex1.print();
// // PRINT	<< TXT_NL << "/DELETE BY RANGE TEST" << END;
	
// 	ex2.insert(42);
// 	ex2.insert(15);
// 	ex2.insert(58);
// 	ex2.insert(2);
// 	ex2.insert(26);
// 	ex2.print();

// 	PRINT << TXT_NL << "Insert 27 " << END;

// 	ex2.insert(27);
// 	ex2.print();


// 	// ft::bintree<int>::iterator del_this(ex2.begin());
// 	// ex2.erase(del_this[3]);




// 	PRINT << "MIEDO" << END;
// 	ex2.print();



// 	test2.insert("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo.");
// 	test2.insert("ordenador", "ORDENADOR: \t\t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios.");
// 	test2.insert("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes.");
// 	test2.insert("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo.");
// 	test2.insert("tig", "TIG: \t\t\t\t\tTrabajo de interés general.");
// 	test2.insert("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados.");
// 	test2.insert("array", "ARRAY: \t\t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados.");
// 	test2.insert("marvin", "MARVIN: \t\t\t\tRobot cascarrabias.");
// 	test2.insert("norminette", "NORMINETTE: \t\t\t\tGuía de estilo que asegura que nadie podrá entender tu código.");
// 	test2.insert("cafe", "CAFÉ: \t\t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua.");
// 	test2.insert("agua", "AGUA: \t\t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe).");
// 	test2.insert("compilador", "COMPILADOR: \t\t\t\tÚnico profesor en activo de 42.");
	
// 	// test2.insert("cuarenta y dos", 42);
// 	// test2.insert("uno", 1);
// 	// test2.insert("noventa y nueve", 99);
// 	// test2.insert("veintisiete", 27);
// 	// test2.insert("dos", 2);
// 	// test2.insert("sesenta y ocho", 68);
// 	// test2.insert("ochenta y tres", 83);
// 	// test2.insert("treinta y cuatro", 34);
// 	// test2.print();

// 	// test2.insert(42, 42);
// 	// test2.insert(1, 1);
// 	// test2.insert(99, 99);
// 	// test2.insert(27, 27);
// 	// test2.insert(2, 2);
// 	// test2.insert(68, 68);
// 	// test2.insert(83, 83);
// 	// test2.insert(34, 34);
// 	// //test2.print();

// 	// ft::bintree<int>::iterator ex1end = ex1.end();	
// 	// (void)ex1end;

// 	PRINT << TXT_NL << "Tree size: " << ex1.size() << END;
// 	for (ft::bintree<int>::iterator it = ex1.begin(), end = ex1.end(); it != end; ++it)
// 		PRINT << it->data << END;

// 	ft::bintree<int>::iterator reftest = ex1.begin();
// 	PRINT << "REFTEST: " << reftest[2].data << END;

// 	PRINT << TXT_NL;

// 	for (ft::bintree<int>::reverse_iterator it = ex1.rbegin(), end = ex1.rend(); it != end; ++it)
// 		PRINT << it->data << END;

// 	PRINT << TXT_NL;
// 	// PRINT << "EX2 POST-DELETE" << END;

// 	// for (ft::bintree<int>::iterator it = ex2.begin(), end = ex2.end(); it != end; ++it)
// 	// 	PRINT << it->data << END;

// 	// ft::bintree<int>::iterator ex42 = *(ex1.getNode(42));
// 	// PRINT << (*ex42).data << END;
// 	// ++ex42;
// 	// if (ex42 == ex1.end())
// 	// 	PRINT << "bleh" << END;

// 	PRINT << "EL ABECEDARIO DE 42" << END;

// 	PRINT << TXT_NL << "Dictionary size: " << test2.size() << END;
	
// 	for (Dictionary::iterator it = test2.begin(), end = test2.end(); it != end; ++it)
// 		PRINT << it->data.second << END;

// 	PRINT 	<< TXT_NL << "Lower Bound 'cafeteria' : " << test2.lower_bound("cafeteria")->data.first
// 			<< TXT_NL << "Lower Bound 'marvinovich': " << test2.lower_bound("marvinovich")->data.first
// 			<< TXT_NL << "Lower Bound 'tigs': " << (test2.lower_bound("tigs") == test2.end() ? "END" : "ERROR")
// 			<< TXT_NL << "Lower Bound 'aguafiestas': " << test2.lower_bound("aguafiestas")->data.first
// 			<< TXT_NL << "Lower Bound 'agu': " << test2.lower_bound("agu")->data.first
// 			<< TXT_NL << "Lower Bound 'ordenador': " << test2.lower_bound("ordenador")->data.first
// 			<< TXT_NL << "Lower Bound: 'tif': " << test2.lower_bound("tif")->data.first
// 			<< END;

// 	PRINT 	<< TXT_NL << "Upper Bound 'cafeteria' : " << test2.upper_bound("cafeteria")->data.first
// 			<< TXT_NL << "Upper Bound 'marvinovich': " << test2.upper_bound("marvinovich")->data.first
// 			<< TXT_NL << "Upper Bound 'tigs': " << (test2.upper_bound("tigs") == test2.end() ? "END" : "ERROR")
// 			<< TXT_NL << "Upper Bound 'aguafiestas': " << test2.upper_bound("aguafiestas")->data.first
// 			<< TXT_NL << "Upper Bound 'agu': " << test2.upper_bound("agu")->data.first
// 			<< TXT_NL << "Upper Bound 'ordenador': " << test2.upper_bound("ordenador")->data.first
// 			<< TXT_NL << "Upper Bound: 'tif': " << test2.upper_bound("tif")->data.first
// 			<< END;

// 	ft::pair<Dictionary::iterator, Dictionary::iterator> ajoyagua(test2.equal_range("a"));
// 	PRINT 	<< TXT_NL << "Equal Range 'agua': " <<  ajoyagua.first->data.first << " " << ajoyagua.second->data.first
// 			<< END;

// 	PRINT	<< TXT_NL << "Print by Reference: " << TXT_NL << test2["arbol binario de rojos y negros"] << END;
// 	PRINT	<< TXT_NL << "Insert by Reference: " << TXT_NL << (test2["santana"] = "SANTANA: \t\t\t\tCanario estepario.") << END;
// 	PRINT	<< TXT_NL << "Print by Reference: " << TXT_NL << ex1[15] << END;
// 	PRINT	<< TXT_NL << "Insert by Reference: " << TXT_NL << ex1[89] << END;
// 	ex1.print();
	
// 	// PRINT << TXT_NL;
// 	// PRINT << "DELETE MARVIN'S ENTRY xD" TXT_NL;
// 	// test2.erase(test2.getNode("marvin"));
// 	// PRINT << TXT_NL;

// 	PRINT << TXT_NL << "Dictionary size: " << test2.size() << END;
// 	for (Dictionary::iterator it = test2.end() - 1, end = test2.begin() - 1; it != end; --it)
// 		PRINT << it->data.second << END;

// 	PRINT << TXT_NL;
	
// 	for (Dictionary::reverse_iterator it = test2.rbegin(), end = test2.rend(); it != end; ++it)
// 		PRINT << it->data.second << END;

// 	Dictionary	new_dictionary;

// 	 PRINT << TXT_NL << "RANGE INSERTED DICTIONARY" << TXT_NL << END;
	
// 	 new_dictionary.insert(test2.begin(), test2.end());

// 	 for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 	 	PRINT << it->data.second << END;

// 	// PRINT << TXT_NL "BAD RANGE DELETE (SHOULD BE IGNORED)" TXT_NL << END;
// 	// test2.erase(new_dictionary.begin(), new_dictionary.end());
// 	// for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 	// 	PRINT << it->data.second << END;

// 	// PRINT << TXT_NL "DELETE NORMINETTE'S ENTRY BY KEY " TXT_NL << END;
// 	// new_dictionary.erase("norminette");
// 	// for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 	// {
// 	// 	if (it->next == it->_end)
// 	// 		PRINT << "I point to end! " << *it->key << END;
// 	// 	else
// 	// 		PRINT << "I point to " << *it->next->key << "!" << END;
// 	// 	PRINT << it->data.second << END;
// 	// }
// 	// size_t haalp = 0;
// 	// for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(); haalp < 15; ++haalp, ++it)
// 	// 	std::cerr << "sollozo: " << it->key << *it->key << std::endl;

// 	PRINT << TXT_NL "SANTANA DELETE " TXT_NL << END;
// 	new_dictionary.erase("santana");
// 	for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 	{
// 		//PRINT << "AAAAAH" << END;
// 		if (it->next == NULL)
// 			PRINT << "I point to end! " << *it->key << END;
// 		else
// 			PRINT << "I point to " << *it->next->key << "!" << END;
// 		PRINT << it->data.second << END;
// 	}

// 	for (ft::bintree_pair<std::string, std::string>::reverse_iterator rit = new_dictionary.rbegin(), rend = new_dictionary.rend(); rit != rend; ++rit)
// 	{
// 		if (rit->next == NULL)
// 			PRINT << "I point to end! " << *rit->key << END;
// 		else
// 			PRINT << "I point to " << *rit->next->key << "!" << END;
// 		PRINT << rit->data.second << END;
// 	}

// 	ft::bintree_pair<std::string, std::string>::iterator	carmensandiego = (new_dictionary.end() - 1);
// 	PRINT << "Where in the world is TIG? " << *carmensandiego->value << END;


// 	//VALE. EL PLAN. SACAR EL HILO DE LOS NODOS!!!! UN VECTOR DE ENLACES EN LA CLASE!!!!
// 	//MUAAAAAAAAAJAJAJAJAJAJAJAAJAJAJAAAAAA!!!!!!!
// 	//MAYBE THREAD SHOULD BE STD::LIST????? HMMMMMMM
// 	PRINT << TXT_NL "GOOD RANGE DELETE" TXT_NL << END;
// 	PRINT << "<EL GRAN PLAN>" << END;
// 	PRINT << "DELETE FROM BEGIN TO END - 2" << TXT_NL << END;
// 	new_dictionary.erase(new_dictionary.begin(), new_dictionary.end() - 2);
// 	for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 		PRINT << it->data.second << END;
// 	PRINT << "New size: " << new_dictionary.size() << END;
// 	PRINT << "</EL GRAN PLAN>" << TXT_NL << END;

// 	PRINT << "SWAP TEST" << TXT_NL << END;
// 	ft::swap(test2, new_dictionary);
// 	PRINT << "TEST2" << END;
// 	for (ft::bintree_pair<std::string, std::string>::iterator it = test2.begin(), end = test2.end(); it != end; ++it)
// 		PRINT << it->data.second << END;
// 	PRINT << TXT_NL << "NEW_DICTIONARY" << END;
// 	for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 		PRINT << it->data.second << END;
// 	PRINT << END;

// 	ft::map<std::string, std::string> default_constructed_map;

// 	std::map<std::string, std::string>	comp_dict;
// 	comp_dict.insert(std::make_pair("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("ordenador", "ORDENADOR: \t\t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("tig", "TIG: \t\t\t\t\tTrabajo de interés general."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("array", "ARRAY: \t\t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("marvin", "MARVIN: \t\t\t\tRobot cascarrabias."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("norminette", "NORMINETTE: \t\t\t\tGuía de estilo que asegura que nadie podrá entender tu código."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("cafe", "CAFÉ: \t\t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("agua", "AGUA: \t\t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe)."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("compilador", "COMPILADOR: \t\t\t\tÚnico profesor en activo de 42."));

// 	std::map<std::string, std::string>::iterator compit = comp_dict.begin();
// 	std::map<std::string, std::string>::iterator compend = comp_dict.end();
// 	--compend;
// 	--compend;
// 	// HASTA ESTO FUNCIONA EN MAC, POR LOS GNOMOS MÁGICOS O_O
// 	// for ( ; compit != compend; ++compit)
// 	// 	comp_dict.erase(compit);
// 	for ( ; compit != compend; )
// 		comp_dict.erase(compit++);
// 	for (compit = comp_dict.begin(), compend = comp_dict.end(); compit != compend; ++compit)
// 		std::cout << compit->second << std::endl;
	

// 	std::map<std::string, std::string>	eqtest1;
// 	std::map<std::string, std::string>	eqtest2;

// 	eqtest1.insert(std::make_pair("1", "1"));
// 	eqtest1.insert(std::make_pair("2", "2"));
// 	eqtest2.insert(std::make_pair("0", "1"));
// 	eqtest2.insert(std::make_pair("1", "2"));

// 	PRINT << "Equal is key ?: " << TXT_NL << (eqtest1.begin() == eqtest2.begin()) << END;
// 	PRINT << "Equal is address ?: " << (eqtest1.begin() == eqtest1.begin()) << END;
// 	PRINT << "Ends are NULL ?: " << (eqtest1.end() == eqtest2.end()) << END;
// 	//PRINT << "End == Begin - 1 ?: " << ((--eqtest1.begin()) == eqtest2.end()) << END;

// 	PRINT << "MAP TIENE DOS COMPORTAMIENTOS DISTINTOS PARA END Y --BEGIN O_O" << END;


// 	// Implementación LINUX, piensa como yo! Implementación MAC, no piensa como yo.
// 	// PARA VARIAR!!! xD En MAC esto tira segfault, en Linux bucle infinito.
// 	// size_t i = 0;
// 	// for(std::map<std::string, std::string>::iterator it = eqtest1.begin(); i < 8; ++it, ++i)
// 	// 	{PRINT << "Iteration test STL: " << &(*it) << END;}

// 	// PRINT << "QUÉ LÍO" << END;
// 	// i = 0;
// 	// for(std::map<std::string, std::string>::iterator it = (--eqtest1.end()); i < 8; --it, ++i)
// 	// 	{PRINT << "Iteration test STL: " << &(*it) << END;}
// 	// PRINT << "QUÉ LÍO NO BAJA DE REND/BEGIN!? !? WHYYYYYY" << END;
// 	// i = 0;
// 	// for(std::map<std::string, std::string>::reverse_iterator rit = eqtest1.rbegin(); i < 8; ++rit, ++i)
// 	// 	{PRINT << (i == 2 ? "REND" : "Iteration test STL: ") << &(*rit) << END;}
	
// 	std::cout << "piim" << std::endl;
// 	// PRINT << "QUÉ LÍO" << END;
// 	// i = 0;
// 	// for(std::map<std::string, std::string>::reverse_iterator rit = (++eqtest1.rend()); i < 8; --rit, ++i)
// 	// 	{PRINT << "Iteration test STL: " << &(*rit) << END;}

// 	// if (iterator_tests())
// 	// 	PRINT << TXT_BGRN "OK" << END;
// 	// else
// 	// 	PRINT << TXT_BRED "KO" << END;
// 	// if (my_veritable_vector<ft::vector<int>, std::vector<int> >())
// 	// 	PRINT << TXT_BGRN "OK" << END;
// 	// else
// 	// 	PRINT << TXT_BRED "KO" << END;

// 	//quick make_pair test
// 	// using ft::make_pair;
// 	// ft::pair<int, char> pair_chorra = make_pair(42, 42);
// 	// std::pair<int, char> std_pair_chorra = std::make_pair(42, 42);
// 	// std::cout << "STD PAIR CHORRA: " << std_pair_chorra.first << " " << std_pair_chorra.second << std::endl;
// 	// std::cout << "FT PAIR CHORRA: " << pair_chorra.first << " " << pair_chorra.second << std::endl;
// 	// ft::pair<int, char>	pair_chorra(42, 42);
// 	// std::pair<int, char> std_pair_chorra(42, 42);

// 	// PRINT << TXT_BYEL "MY PAIR_CHORRA: " TXT_BGRN << pair_chorra.first << TXT_BYEL ", " TXT_BGRN << pair_chorra.second << END;
// 	// PRINT << TXT_BYEL "STD PAIR_CHORRA: " TXT_BGRN << std_pair_chorra.first << TXT_BYEL ", " TXT_BGRN << std_pair_chorra.second << END;

// 	// //enable_if test
// 	// //Change to non-integral (double, float, etc.) to test. :)
// 	// PRINT << TXT_BYEL "ENABLE_IF TEST:" << TXT_NL;
// 	// int	i = 1;
// 	// PRINT << TXT_TAB << ALN << "i is odd: " << std::boolalpha << TXT_BGRN << ft::is_odd(i) << END;

// 	// std::string	test1 = "Apple";
// 	// std::string test2 = "honey";
// 	// std::string test3 = "honey";
// 	// bool std_ret;

// 	// std_ret = std::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());

// 	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

// 	// std_ret = ft::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());
// 	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

// 	// std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test3.begin());
// 	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

// 	// std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test1.begin());
// 	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;
// 	// // //DEBUG
// 	// // {
// 	// // 	PRINT << TXT_BYEL << "THE GREAT IS_INTEGRAL TEST!" << TXT_NL
// 	// // 	<< "Double Is Integral?" << std::boolalpha << " " << std::is_integral<double>::value << TXT_NL
// 	// // 	<< "Float Is Integral?" << std::boolalpha << " " << std::is_integral<float>::value << TXT_NL
// 	// // 	<< "Unsigned Int Is Integral?" << std::boolalpha << " " << std::is_integral<unsigned int>::value << END;
// 	// // }
// 	// // //DEBUG


	return (0);
}