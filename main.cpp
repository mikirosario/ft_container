/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/19 16:11:31 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "utility.hpp"
#include "ft_bintree.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#define GRN "\e[1;32m"
#define RED "\e[1;31m"
#define YEL "\e[1;33m"
#define BLU "\e[1;36m"
#define RST "\e[0m"
#define PRINT std::cout
#define NL "\n"
#define TAB "\t"
#define ALN std::left << std::setw(30)
#define SEP "-------------------------------------------------------------------------------------"
#define END RST << std::endl
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
	std::vector<int> std_vector;
	std_vector.push_back(9);
	std_vector.push_back(42);
	std_vector.push_back(84);
	PRINT	<< YEL SEP << NL
			<< YEL "CREATING FT::VECTOR<INT>::ITERATORS:" << NL
			<< TAB << ALN << "ft_it = &a[0]" << NL
			<< TAB << ALN << "ft_it2 = &a[1]" << END;
	ft::vector<int>::iterator ft_it(&a[0]);
	ft::vector<int>::iterator ft_it2(&a[1]);
	PRINT	<< YEL "CREATING IDENTICAL STD::VECTOR<INT>::ITERATORS:" << NL
			<< TAB << ALN << "std_it = &a[0]" << NL
			<< TAB << ALN << "std_it2 = &a[1]" << END;
	std::vector<int>::iterator std_it(std_vector.begin()); //MAC COMPILER WILL NOT CREATE ITERATOR FROM POINTER!!???
	std::vector<int>::iterator std_it2(std_vector.begin() + 1); //GRRAAAAAARRRRRRRGH!!!! WHY!!!!?????
	PRINT	<< YEL "CREATING FT::VECTOR<INT>::CONST_ITERATOR:" << NL
			<< TAB << ALN << "ft_cit = &a[0]" << END;
	ft::vector<int>::const_iterator ft_cit(&a[0]);
	PRINT	<< YEL "CREATING IDENTICAL STD::VECTOR<INT>::CONST_ITERATOR:" << NL
			<< TAB << ALN << "std_cit = &a[0]" << END;
	std::vector<int>::const_iterator std_cit(std_vector.begin());

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
	std_it = std::vector<int>::iterator(std_vector.begin() + 3);
	ft_it2 = ft::vector<int>::iterator(&a[1]);
	std_it2 = std::vector<int>::iterator(std_vector.begin() + 1);
	ft_cit = ft::vector<int>::const_iterator(a + 3);
	std_cit = std::vector<int>::const_iterator(std_vector.begin() + 3);
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
		color = GRN;
	else
	{
		color = RED;
		ret = false;
	}
	PRINT	<< TAB << YEL "MY Container: " << END;
	for (typename MY_Container::iterator it = my_cont.begin(), end = my_cont.end(); it != end; ++it)
		PRINT << TAB << color << *it << END;
	PRINT	<< TAB << YEL "STD Container: " << END;
	for (typename STD_Container::iterator it = std_cont.begin(), end = std_cont.end(); it != end; ++it)
		PRINT << TAB << color << *it << END;
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

	color = lhs.size() == rhs.size() ? GRN : RED;
	PRINT	<< TAB << YEL "MY Element Count" << TAB << "STD Element Count" << NL
			<< TAB << color << std::setw(17) << rhs.size() << TAB << std::setw(17) << lhs.size() << END;
}

template<class STD_Container, class MY_Container>
void	comparison_operator_log(STD_Container const & su_cont1, STD_Container const & su_cont2,
								MY_Container const & mi_cont1, MY_Container const & mi_cont2, bool & ret)
{
	char const *	color;

	PRINT 	<< YEL "RELATIONAL OPERATOR CHECKS:" << END;
	check (((mi_cont1 == mi_cont2) == (su_cont1 == su_cont2)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 == mi_cont2: " << std::boolalpha << SET << (mi_cont1 == mi_cont2)
			<< TAB << ALN << YEL "su_cont1 == su_cont2: " << std::boolalpha << SET << (su_cont1 == su_cont2) << END;
	check (((mi_cont1 != mi_cont2) == (su_cont1 != su_cont2)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 != mi_cont2: " << std::boolalpha << SET << (mi_cont1 != mi_cont2)
			<< TAB << ALN << YEL "su_cont1 != su_cont2: " << std::boolalpha << SET << (su_cont1 != su_cont2) << END;
	check (((mi_cont1 == mi_cont1) == (su_cont1 == su_cont1)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 == mi_cont1: " << std::boolalpha << SET << (mi_cont1 == mi_cont1)
			<< TAB << ALN << YEL "su_cont1 == su_cont1: " << std::boolalpha << SET << (su_cont1 == su_cont1) << END;
	check (((mi_cont1 != mi_cont1) == (su_cont1 != su_cont1)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 != mi_cont1: " << std::boolalpha << SET << (mi_cont1 != mi_cont1)
			<< TAB << ALN << YEL "su_cont1 != su_cont1: " << std::boolalpha << SET << (su_cont1 != su_cont1) << END;
	check (((mi_cont1 > mi_cont2) == (su_cont1 > su_cont2)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 > mi_cont2:  " << std::boolalpha << SET << (mi_cont1 > mi_cont2)
			<< TAB << ALN << YEL "su_cont1 > su_cont2:  " << std::boolalpha << SET << (su_cont1 > su_cont2) << END;
	check (((mi_cont1 < mi_cont2) == (su_cont1 < su_cont2)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 < mi_cont2:  " << std::boolalpha << SET << (mi_cont1 < mi_cont2)
			<< TAB << ALN << YEL "su_cont1 < su_cont2:  " << std::boolalpha << SET << (su_cont1 < su_cont2) << END;
	check (((mi_cont1 > mi_cont1) == (su_cont1 > su_cont1)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 > mi_cont1:  " << std::boolalpha << SET << (mi_cont1 > mi_cont1)
			<< TAB << ALN << YEL "su_cont1 > su_cont1:  " << std::boolalpha << SET << (su_cont1 > su_cont1) << END;
	check (((mi_cont1 < mi_cont1) == (su_cont1 < su_cont1)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 < mi_cont1:  " << std::boolalpha << SET << (mi_cont1 < mi_cont1)
			<< TAB << ALN << YEL "su_cont1 < su_cont1:  " << std::boolalpha << SET << (su_cont1 < su_cont1) << END;
	check (((mi_cont1 >= mi_cont2) == (su_cont1 >= su_cont2)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 >= mi_cont2: " << std::boolalpha << SET << (mi_cont1 >= mi_cont2)
			<< TAB << ALN << YEL "su_cont1 >= su_cont2: " << std::boolalpha << SET << (su_cont1 >= su_cont2) << END;
	check (((mi_cont1 <= mi_cont2) == (su_cont1 <= su_cont2)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 <= mi_cont2: " << std::boolalpha << SET << (mi_cont1 <= mi_cont2)
			<< TAB << ALN << YEL "su_cont1 <= su_cont2: " << std::boolalpha << SET << (su_cont1 <= su_cont2) << END;
	check (((mi_cont1 >= mi_cont1) == (su_cont1 >= su_cont1)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 >= mi_cont1: " << std::boolalpha << SET << (mi_cont1 >= mi_cont1)
			<< TAB << ALN << YEL "su_cont1 >= su_cont1: " << std::boolalpha << SET << (su_cont1 >= su_cont1) << END;
	check (((mi_cont1 <= mi_cont1) == (su_cont1 <= su_cont1)), color, ret);
	PRINT	<< TAB << ALN << YEL "mi_cont1 <= mi_cont1: " << std::boolalpha << SET << (mi_cont1 <= mi_cont1)
			<< TAB << ALN << YEL "su_cont1 <= su_cont1: " << std::boolalpha << SET << (su_cont1 <= su_cont1) << END;	
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
** will be separated only by a TAB.
**
** The color will be set to green or red before the function exits. It will need
** to be reset by the caller, either with RST or END!
*/
void	compare_log(bool comp, bool & ret, std::string const & msg, size_t & msg_offset, size_t const & minw = 0)
{
	char const *		color;
	std::string	const	my_msg = "MY " + msg;
	std::string	const	std_msg = "STD " + msg;

	if (comp)
		color = GRN;
	else
	{
		color = RED;
		ret = false;
	}
	msg_offset = std_msg.size();
	PRINT	<< TAB << YEL << std::setw(minw) << my_msg << TAB << std::setw(minw) << std_msg << NL
			<< TAB << color;
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
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << NL
			<< "CONSTRUCTOR CHECKS" << NL
			<< NL
			<< "FILL CONSTRUCTOR TESTS" << NL
			<< TAB << "Fill-constructing: " << NL
			<< TAB << "  ft::container mi_fill_cont(4, 42)" << NL
			<< TAB << "  std::container su_fill_cont(4, 42)" << END;
	MY_Container	mi_fill_cont(4, 42);
	STD_Container	su_fill_cont(4, 42);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);

	//RANGE CONSTRUCTOR TEST
	PRINT	<< NL
			<< YEL "RANGE CONSTRUCTOR TESTS" << NL
			<< TAB << "Range-constructing: " << NL
			<< TAB << "  ft::container mi_range_cont(mi_fill_cont.begin(), mi_fill_cont.end())" << NL
			<< TAB << "  std::container su_range_cont(su_fill_cont.begin(), su_fill_cont.end())" << END;
			MY_Container	mi_range_cont(mi_fill_cont.begin(), mi_fill_cont.end());
			STD_Container 	su_range_cont(su_fill_cont.begin(), su_fill_cont.end());
	elemc_compare_log(su_range_cont, mi_range_cont);
	cont_check_log(su_range_cont, mi_range_cont, ret);

	//COPY CONSTRUCTOR TEST
	PRINT	<< NL
			<< YEL "COPY CONSTRUCTOR TESTS" << NL
			<< TAB << "Copy-constructing: " << NL
			<< TAB << "  ft::container mi_copied_cont(mi_fill_cont)" << NL
			<< TAB << "  std::container su_copied_cont(su_fill_cont)" << END;
	MY_Container	mi_copied_cont(mi_fill_cont);
	STD_Container	su_copied_cont(su_fill_cont);
	elemc_compare_log(su_copied_cont, mi_copied_cont);
	cont_check_log(su_copied_cont, mi_copied_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//ASSIGNMENT OVERLOAD COPY TEST
	PRINT	<< YEL "ASSIGNMENT OVERLOAD COPY TEST" << NL
			<< TAB << "Copying via assignment: " << NL
			<< TAB << "  ft::container(0) mi_assigned_cont = mi_fill_cont" << NL
			<< TAB << "  std::container(0) su_assigned_cont = su_fill_cont" << END;
	MY_Container	mi_assigned_cont = mi_fill_cont;
	STD_Container	su_assigned_cont = su_fill_cont;
	elemc_compare_log(su_assigned_cont, mi_assigned_cont);
	cont_check_log(su_assigned_cont, mi_assigned_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//REVERSE ITERATOR PRINT TEST
	//DEBUG
	// Change this to output to file and do a diff or something, and include it in the global ret checks and the like
	//DEBUG
	PRINT	<< YEL "REVERSE ITERATOR PRINT TEST" << NL
			<< TAB << "Printing using reverse iterators: " << NL
			<< TAB << "  mi_fill_cont" << NL
			<< TAB << "  su_fill_cont" << END;

	PRINT	<< TAB << YEL "MY Reverse Printed Container: " << END;
	for (typename MY_Container::reverse_iterator rit = mi_fill_cont.rbegin(), rend = mi_fill_cont.rend(); rit != rend; ++rit)
		PRINT << TAB << *rit << END;
	PRINT	<< TAB << YEL "STD Reverse Printed Container: " << END;
	for (typename STD_Container::reverse_iterator rit = su_fill_cont.rbegin(), rend = su_fill_cont.rend(); rit != rend; ++rit)
		PRINT << TAB << *rit << END;
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//MAX SIZE EQUALITY CHECK... I take allocator's max_size, and depending on
	//implementation STL appears to do different things at different times. We
	//SEEM to do the same thing on school Mac, however. ;)
	PRINT	<< YEL "MAX SIZE EQUALITY CHECK" << NL
			<< TAB << "Comparing : " << NL
			<< TAB << "  mi_fill_cont.max_size()" << NL
			<< TAB << "  su_fill_cont.max_size()" << END;
	compare_log(su_fill_cont.max_size() == mi_fill_cont.max_size(), ret, "Max Size", msg_offset, 20);
	PRINT	<< mi_fill_cont.max_size() << TAB << su_fill_cont.max_size() << END;
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//CAPACITY EQUALITY CHECK, this should be equal if we follow the same
	//allocation strategy of multiplying by * 2. :p
	PRINT	<< YEL "CAPACITY EQUALITY CHECK" << NL
			<< TAB << "Comparing : " << NL
			<< TAB << "  mi_fill_cont.capacity()" << NL
			<< TAB << "  su_fill_cont.capacity()" << END;
	compare_log(su_fill_cont.capacity() == mi_fill_cont.capacity(), ret, "Capacity", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont.capacity() << TAB << std::setw(msg_offset) << su_fill_cont.capacity() << END;
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//PUSH_BACK CHECK
	PRINT	<< YEL "PUSH BACK CHECKS" << NL
			<< TAB << "Adding 84, 168 and 69 via push_back to: " << NL
			<< TAB << "  mi_fill_cont.push_back(84...)" << NL
			<< TAB << "  su_fill_cont.push_back(84...)" << END;
	mi_fill_cont.push_back(84);
	mi_fill_cont.push_back(168);
	mi_fill_cont.push_back(69);
	su_fill_cont.push_back(84);
	su_fill_cont.push_back(168);
	su_fill_cont.push_back(69);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< NL
			<< TAB << YEL "Adding -42 and -21 via push_back to: " << NL
			<< TAB << "  mi_copied_cont.push_back(-42...)" << NL
			<< TAB << "  su_copied_cont.push_back(-42...)" << END;
	mi_copied_cont.push_back(-42);
	mi_copied_cont.push_back(-21);
	su_copied_cont.push_back(-42);
	su_copied_cont.push_back(-21);
	elemc_compare_log(su_copied_cont, mi_copied_cont);
	cont_check_log(su_copied_cont, mi_copied_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//RESERVE CHECK
	PRINT	<< YEL "RESERVE CHECK" << NL
			<< TAB << "Reserving space for 20 elements: " << NL
			<< TAB << "  mi_fill_cont.reserve(20)" << NL
			<< TAB << "  su_fill_cont.reserve(20)" << END;
	mi_fill_cont.reserve(20);
	su_fill_cont.reserve(20);
	//CAPACITY AFTER RESERVE COMPARISON
	compare_log(su_fill_cont.capacity() == mi_fill_cont.capacity(), ret, "Capacity After Reserve", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont.capacity() << TAB << std::setw(msg_offset) << su_fill_cont.capacity() << END;
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//POP_BACK CHECK
	PRINT	<< YEL "POP BACK CHECK" << NL
			<< TAB << "Popping back last element: " << NL
			<< TAB << "  mi_fill_cont.pop_back()" << NL
			<< TAB << "  su_fill_cont.pop_back()" << END;
	mi_fill_cont.pop_back();
	su_fill_cont.pop_back();
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//RESIZE CHECKS
	//Size down
	PRINT	<< YEL "RESIZE CHECKS" << NL
			<< TAB << "Sizing down:" << NL
			<< TAB << "  mi_fill_cont.resize(2)" << NL
			<< TAB << "  su_fill_cont.resize(2)" << END;
	mi_fill_cont.resize(2);
	su_fill_cont.resize(2);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//Size up
	PRINT	<< NL
			<< TAB << YEL "Sizing up:" << NL
			<< TAB << " mi_fill_cont.resize(4)" << NL
			<< TAB << " su_fill_cont.resize(4)" << END;
	mi_fill_cont.resize(4);
	su_fill_cont.resize(4);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//Size up with caller-specified value
	PRINT	<< NL
			<< TAB << YEL "Sizing up with caller-specified value:" << NL
			<< TAB << " mi_fill_cont.resize(6, 21)" << NL
			<< TAB << " su_fill_cont.resize(6, 21)" << END;
	mi_fill_cont.resize(6, 21);
	su_fill_cont.resize(6, 21);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//ERASE CHECKS
	//ERASE BY POSITION
	PRINT	<< YEL "ERASE CHECKS" << NL
			<< TAB << "Erasing by position:" << NL
			<< TAB << "  mi_fill_cont.erase(mi_fill_cont.begin() + 2)" << NL
			<< TAB << "  su_fill_cont.erase(su_fill_cont.begin() + 2)" << END;
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
		PRINT	<< std::setw(msg_offset) << mi_res_pos << TAB << std::setw(msg_offset) << su_res_pos << END;
	}
	PRINT	<< NL
			<< TAB << YEL "Erasing last element by position:" << NL
			<< TAB << "  mi_fill_cont.erase(mi_fill_cont.end() - 1)" << NL
			<< TAB << "  su_fill_cont.erase(su_fill_cont.end() - 1)" << END;
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
		PRINT	<< std::setw(msg_offset) << mi_res_pos << TAB << std::setw(msg_offset) << su_res_pos << END;
	}
	//ERASE BY RANGE
		PRINT	<< NL
				<< TAB << YEL "Erasing by range:" << NL
				<< TAB << "  mi_fill_cont.erase(mi_fill_cont.begin() + 1, mi_fill_cont.end())" << NL
				<< TAB << "  su_fill_cont.erase(su_fill_cont.begin() + 1, su_fill_cont.end())" << END;
		//THESE RETURN VOID IN C++98
		mi_fill_cont.erase(mi_fill_cont.begin() + 1, mi_fill_cont.end());
		su_fill_cont.erase(su_fill_cont.begin() + 1, su_fill_cont.end());
		elemc_compare_log(su_fill_cont, mi_fill_cont);
		cont_check_log(su_fill_cont, mi_fill_cont, ret);
		PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
				<< "-------------------------------------------------------------------------------------" << END;

	//INSERT CHECKS
	//INSERT BY POSITION
	PRINT	<< YEL "INSERT CHECKS" << NL
			<< TAB << "Inserting by position:" << NL
			<< TAB << "  mi_fill_cont.insert(mi_fill_cont.begin(), 1984)" << NL
			<< TAB << "  su_fill_cont.insert(su_fill_cont.begin(), 1984)" << END;
	mi_fill_cont.insert(mi_fill_cont.begin(), 1984);
	su_fill_cont.insert(su_fill_cont.begin(), 1984);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//INSERT BY POSITION AND CLONE N TIMES
	PRINT	<< NL
			<< TAB << YEL "Inserting by position and cloning n times:" << NL
			<< TAB << "  mi_fill_cont.insert(mi_fill_cont.begin(), 2, 1970)" << NL
			<< TAB << "  su_fill_cont.insert(su_fill_cont.begin(), 2, 1970)" << END;
	mi_fill_cont.insert(mi_fill_cont.begin(), 2, 1970);
	su_fill_cont.insert(su_fill_cont.begin(), 2, 1970);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//Creating new containers for swap test
	PRINT	<< TAB << YEL "Fill-creating new containers:" << NL
			<< TAB << "  ft::container mi_swappable_cont(4, 1)" << NL
			<< TAB << "  std::container su_swappable_cont(4, 1)" << END;
	MY_Container	mi_swappable_cont(4, 1);
	STD_Container	su_swappable_cont(4, 1);
	PRINT	<< TAB << YEL "Inserting by position and cloning n times:" << NL
			<< TAB << "  mi_swappable_cont.insert(mi_swappable_cont.begin() + 1, 1, 9)" << NL
			<< TAB << "  su_swappable_cont.insert(su_swappable_cont.begin() + 1, 1, 9)" << END;
	mi_swappable_cont.insert(mi_swappable_cont.begin() + 1, 1, 9);
	su_swappable_cont.insert(su_swappable_cont.begin() + 1, 1, 9);
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);
	
	//INSERT BY RANGE
	PRINT	<< NL
			<< TAB << YEL "Inserting by range:" << NL
			<< TAB << "  mi_fill_cont.insert(mi_fill_cont.begin(), mi_swappable_cont.begin(), mi_swappable_cont.end())" << NL
			<< TAB << "  su_fill_cont.insert(su_fill_cont.begin(), su_swappable_cont.begin(), su_swappable_cont.end())" << END;
	mi_fill_cont.insert(mi_fill_cont.begin(), mi_swappable_cont.begin(), mi_swappable_cont.end());
	su_fill_cont.insert(su_fill_cont.begin(), su_swappable_cont.begin(), su_swappable_cont.end());
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);

	PRINT	<< NL
			<< TAB << YEL "Inserting by range with reverse iterators:" << NL
			<< TAB << "  mi_assigned_cont.insert(mi_assigned_cont.begin(), mi_fill_cont.rbegin(), mi_fill_cont.rend())" << NL
			<< TAB << "  su_assigned_cont.insert(su_assigned_cont.begin(), su_fill_cont.rbegin(), su_fill_cont.rend())" << END;
	mi_assigned_cont.insert(mi_assigned_cont.begin(), mi_fill_cont.rbegin(), mi_fill_cont.rend());
	su_assigned_cont.insert(su_assigned_cont.begin(), su_fill_cont.rbegin(), su_fill_cont.rend());
	elemc_compare_log(su_assigned_cont, mi_assigned_cont);
	cont_check_log(su_assigned_cont, mi_assigned_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//SWAP CHECKS; 4 WAYS TO SWAP!
	//AS CLASS FUNCTION
	PRINT	<< YEL "SWAP CHECKS" << NL
			<< TAB << "Swapping with class function:" << NL
			<< TAB << "  mi_fill_cont.swap(mi_swappable_cont)" << NL
			<< TAB << "  su_fill_cont.swap(su_swappable_cont)" << END;
	mi_fill_cont.swap(mi_swappable_cont);
	su_fill_cont.swap(su_swappable_cont);
	//fill_cont swapped with swappable_cont
	PRINT	<< TAB << YEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TAB << YEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);

	//WITH DEFAULT STD::SWAP
	//THIS DOES A BYTE-FOR-BYTE SWAP OF THE INSTANCE USING THE COPY-CONSTRUCTOR TO CREATE A THIRD TEMPORARY INSTANCE
	//VERY INEFFICIENT! BUT... FOR SCIENCE! xD
	PRINT	<< NL
			<< TAB << YEL "Swapping with default std::swap" << NL
			<< TAB << "  std::swap(mi_fill_cont, mi_swappable_cont)" << NL
			<< TAB << "  std::swap(su_fill_cont, su_swappable_cont)" << END;
	std::swap(mi_fill_cont, mi_swappable_cont);
	std::swap(su_fill_cont, su_swappable_cont);
	//fill_cont swapped with swappable_cont again!
	PRINT	<< TAB << YEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TAB << YEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);

	//USING FT::SWAP FOR FT::CONTAINER AND STD::SWAP FOR STD::CONTAINER VIA ARGUMENT-DEPENDENT LOOKUP (ADL)
	//ADL LOOKS UP A MATCHING TEMPLATE SPECIALIZATION WITHIN THE SAME NAMESPACE AS THE ARGUMENTS
	//THIS DOES MAGIC TO FIND MY SPECIALIZED SWAP TEMPLATE IN FT:: NAMESPACE WHICH CALLS THE CLASS FUNCTION
	PRINT	<< NL
			<< TAB << YEL "Swapping with class function via ADL:" << NL
			<< TAB << "  std::swap(mi_fill_cont, mi_swappable_cont)" << NL
			<< TAB << "  std::swap(su_fill_cont, su_swappable_cont)" << END;
	swap(mi_fill_cont, mi_swappable_cont); //why does this activate ADL? no feckin idea!
	swap(su_fill_cont, su_swappable_cont);
	//fill_cont swapped with swappable_cont yet again!
	PRINT	<< TAB << YEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TAB << YEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);

	//USING DEFAULT STD::SWAP BUT STILL FINDING FT::SWAP VIA ARGUMENT-DEPENDENT LOOKUP (ADL) FOR SOME REASON
	//ADL LOOKS UP A MATCHING TEMPLATE SPECIALIZATION WITHIN THE SAME NAMESPACE AS THE ARGUMENTS
	//THIS DOES MAGIC TO FIND MY SPECIALIZED SWAP TEMPLATE IN FT:: NAMESPACE WHICH CALLS THE CLASS FUNCTION
	//SO BASICALLY THE SAME AS BEFORE... RIGHT? I THINK. I HOPE!
	//HONESTLY, WHO THE HELL KNOWS AT THIS POINT? ONLY SCOTT MEYERS AND THE COMMITTEE... ANYWAY, THEY SWAP!
	PRINT	<< NL
			<< TAB << YEL "Swapping with class function via ADL:" << NL
			<< TAB << "  std::swap(mi_fill_cont, mi_swappable_cont)" << NL
			<< TAB << "  std::swap(su_fill_cont, su_swappable_cont)" << END;
	using std::swap; //why does this activate ADL too? no feckin idea!
	swap(mi_fill_cont, mi_swappable_cont);
	swap(su_fill_cont, su_swappable_cont);
	//fill_cont swapped with swappable_cont yet another time!
	PRINT	<< TAB << YEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TAB << YEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
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
	PRINT	<< YEL "GET ALLOCATOR CHECK" << NL
			<< TAB << "Allocating heap memory using returned allocator instance:" << NL
			<< TAB << "  mi_fill_cont.get_allocator().allocate(4)" << NL
			<< TAB << "  su_fill_cont.get_allocator().allocate(4)" << END;
	mi_fill_cont.get_allocator().allocate(4); //allocators are stateful, and remember what type they are allocating
	su_fill_cont.get_allocator().allocate(4); //so this is NOT 4 bytes, but rather 4 * sizeof(SourceContainer::value_type)
	typename MY_Container::value_type * 	mi_allocated_array = mi_fill_cont.get_allocator().allocate(4);
	typename STD_Container::value_type *	su_allocated_array = su_fill_cont.get_allocator().allocate(4);
	PRINT	<< NL
			<< TAB << YEL "Assigning values to each allocation using constructor of returned allocator instance:" << NL
			<< TAB << "  mi_fill_cont.get_allocator().construct(arr, val)" << NL
			<< TAB << "  su_fill_cont.get_allocator().construct(arr, val)" << END;
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
	PRINT	<< NL
			<< TAB << YEL "Destroying each instance in the allocated array:" << NL
			<< TAB << "  mi_fill_cont.get_allocator().destroy(&arr[i])" << NL
			<< TAB << "  su_fill_cont.get_allocator().destroy(&arr[i])" << END;
	size_t i = 3;
	do {
		mi_fill_cont.get_allocator().destroy(&mi_allocated_array[i]);
		su_fill_cont.get_allocator().destroy(&su_allocated_array[i]);
	} while (i-- > 0);
	//And then we deallocate... be sure to remember how much we allocated! ;)
	PRINT	<< NL
			<< TAB << YEL "Deallocating the allocated memory block:" << NL
			<< TAB << "  mi_fill_cont.get_allocator().deallocate(arr, 4)" << NL
			<< TAB << "  su_fill_cont.get_allocator().deallocate(arr, 4)" << END;
	mi_fill_cont.get_allocator().deallocate(mi_allocated_array, 4); // C++ is just SO much simpler than C!
	su_fill_cont.get_allocator().deallocate(su_allocated_array, 4); // I am really feeling that high level abstraction right now! xD
	//Look ma, no leaks!
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//ASSIGN CHECK
	PRINT	<< YEL "ASSIGN CHECK" << NL
			<< TAB << "Assigning by fill:" << NL
			<< TAB << "  mi_fill_cont.assign(8, 42)" << NL
			<< TAB << "  su_fill_cont.assign(8, 42)" << END;
	mi_fill_cont.assign(8, 42);
	su_fill_cont.assign(8, 42);
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< NL
			<< TAB << YEL "Assigning by range:" << NL
			<< TAB << "  mi_fill_cont.assign(mi_copied_cont.begin(), mi_copied_cont.end())" << NL
			<< TAB << "  su_fill_cont.assign(su_copied_cont.begin(), su_copied_cont.end())" << END;
	mi_fill_cont.assign(mi_copied_cont.begin(), mi_copied_cont.end());
	su_fill_cont.assign(su_copied_cont.begin(), su_copied_cont.end());
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//REFERENCING CHECKS
	//Referencing by []
	PRINT	<< YEL "REFERENCING CHECKS" << NL
			<< TAB << "Referencing by []:" << NL
			<< TAB << "  mi_fill_cont[4])" << NL
			<< TAB << "  su_fill_cont[4])" << END;
	compare_log(mi_fill_cont[4] == su_fill_cont[4], ret, "fill_cont[4]", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont[4] << std::setw(msg_offset) << su_fill_cont[4] << END;
	//Referencing by &alias via []
	PRINT	<< NL
			<< TAB << YEL "Referencing by &alias via [] (same thing):" << NL
			<< TAB << "  &mi_num1(mi_fill_cont[4]))" << NL
			<< TAB << "  &su_num1(su_fill_cont[4]))" << END;
	typename MY_Container::value_type &		mi_num1(mi_fill_cont[4]);
	typename STD_Container::value_type &	su_num1(su_fill_cont[4]);
	compare_log(mi_num1 == su_num1, ret, "num1 ref", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_num1 << TAB << std::setw(msg_offset) << su_num1 << END;
	//Referencing by container.at() member function
	//at() throws exceptions for out-of-bounds references
	PRINT	<< NL
			<< TAB << YEL "Referencing in-bounds by container.at():" << NL
			<< TAB << "  mi_fill_cont.at(5)" << NL
			<< TAB << "  su_fill_cont.at(5)" << END;
	try
	{
		compare_log(mi_fill_cont.at(5) == su_fill_cont.at(5), ret, "fill_cont.at(5)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_fill_cont.at(5) << TAB << std::setw(msg_offset) << su_fill_cont.at(5) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TAB << RED << e.what() << END;
	}

	PRINT	<< NL
			<< TAB << YEL "Referencing out-of-bounds by container.at() (my message):" << NL
			<< TAB << "  mi_fill_cont.at(6)" << NL
			<< TAB << "  su_fill_cont.at(6)" << END;
	try
	{
		compare_log(mi_fill_cont.at(6) == su_fill_cont.at(6), ret, "fill_cont.at(6)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_fill_cont.at(6) << TAB << std::setw(msg_offset) << su_fill_cont.at(6) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TAB << BLU << e.what() << END;
	}
	PRINT	<< NL
			<< TAB << YEL "Referencing out-of-bounds by container.at() (STL message):" << NL
			<< TAB << "  mi_fill_cont.at(6)" << NL
			<< TAB << "  su_fill_cont.at(6)" << END;
	try
	{
		compare_log(su_fill_cont.at(6) == mi_fill_cont.at(6), ret, "fill_cont.at(6)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_fill_cont.at(6) << TAB << std::setw(msg_offset) << su_fill_cont.at(6) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TAB << BLU << e.what() << END; // OK, so which is clearer, my message, or STL message? xD
	}
	PRINT	<< NL
			<< TAB << YEL "Referencing empty container.at() (my message):" << NL
			<< TAB << "  mi_vacio.at(0)" << NL
			<< TAB << "  su_vacio.at(0)" << END;
	try
	{
		MY_Container	mi_vacio;
		STD_Container	su_vacio;
		
		compare_log(mi_vacio.at(0) == su_vacio.at(0), ret, "vacio.at(0)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_vacio.at(0) << TAB << std::setw(msg_offset) << su_vacio.at(0) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TAB << BLU << e.what() << END;
	}
	PRINT	<< NL
			<< TAB << YEL "Referencing empty container.at() (STL message):" << NL
			<< TAB << "  mi_vacio_cont.at(0)" << NL
			<< TAB << "  su_vacio_cont.at(0)" << END;
	try
	{
		MY_Container	mi_vacio;
		STD_Container	su_vacio;
		
		compare_log(su_vacio.at(0) == mi_vacio.at(0), ret, "vacio.at(0)", msg_offset);
		PRINT << std::setw(msg_offset) << mi_vacio.at(0) << TAB << std::setw(msg_offset) << su_vacio.at(0) << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TAB << BLU << e.what() << END;
	}
	//CONST REFERENCING
	PRINT	<< NL
			<< TAB << YEL "Copy-creating const containers:"
			<< TAB << "  c_mi_copied_cont(mi_copied_cont)" << NL
			<< TAB << "  c_su_copied_cont(mi_copied_cont)" << END;
			const MY_Container	c_mi_copied_cont(mi_copied_cont);
			const STD_Container	c_su_copied_cont(su_copied_cont);
	PRINT	<< TAB << YEL "Referencing const containers (by []):" << NL
			<< TAB << "  c_mi_copied_cont[2]" << NL
			<< TAB << "  c_su_copied_cont[2]" << END;
		compare_log(c_mi_copied_cont[2] == c_su_copied_cont[2], ret, "const copied_cont[2]", msg_offset);
		PRINT << std::setw(msg_offset) << c_mi_copied_cont[2] << std::setw(msg_offset) << c_su_copied_cont[2] << END;
	//COMPILE-TIME TESTS
	{
		// Const int reference to const c_fill_cont type_value, this is fine.
		typename MY_Container::const_reference	c_mi_num(c_mi_copied_cont[2]);
		typename STD_Container::const_reference	c_su_num(c_su_copied_cont[2]);
		compare_log(c_mi_num == c_su_num, ret, "const num", msg_offset);
		PRINT << std::setw(msg_offset) << c_mi_copied_cont[2] << TAB << std::setw(msg_offset) << c_su_copied_cont[2] << END;
		// // Compiler will not allow this as c_fill_cont is const.
		// typename MY_Container::reference & mi_num(c_mi_copied_cont[2]);
		// typename STD_Container::reference & su_num(c_su_copied_cont[2]);

		// // Compiler will also not allow this as c_mi_copied_cont is const.
		//c_mi_copied_cont[0] = 8;
		//c_su_copied_cont[0] = 8;
	}
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//FRONT AND BACK CHECKS
	PRINT	<< YEL "FRONT AND BACK CHECKS" << NL
			<< TAB << "Calling front():" << NL
			<< TAB << "  mi_fill_cont.front()" << NL
			<< TAB << "  su_fill_cont.front()" << END;
	compare_log(mi_fill_cont.front() == su_fill_cont.front(), ret, "fill_cont.front()", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont.front() << TAB << std::setw(msg_offset) << su_fill_cont.front() << END;
			
	PRINT	<< NL
			<< TAB << YEL "Calling back():" << NL
			<< TAB << "  mi_fill_cont.back()" << NL
			<< TAB << "  su_fill_cont.back()" << END;
	compare_log(mi_fill_cont.back() == su_fill_cont.back(), ret, "fill_cont.back()", msg_offset);
	PRINT	<< std::setw(msg_offset) << mi_fill_cont.back() << TAB << std::setw(msg_offset) << su_fill_cont.back() << END;

	PRINT	<< NL
			<< TAB << YEL "Calling front() const:" << NL
			<< TAB << "  c_mi_copied_cont.front()" << NL
			<< TAB << "  c_su_copied_cont.front()" << END;
	compare_log(c_mi_copied_cont.front() == c_su_copied_cont.front(), ret, "const copied_cont.front()", msg_offset);
	PRINT	<< std::setw(msg_offset) << c_mi_copied_cont.front() << TAB << std::setw(msg_offset) << c_su_copied_cont.front() << END;

	PRINT	<< NL
			<< TAB << YEL "Calling back() const:" << NL
			<< TAB << "  c_mi_copied_cont.back()" << NL
			<< TAB << "  c_su_copied_cont.back()" << END;
	compare_log(c_mi_copied_cont.back() == c_su_copied_cont.back(), ret, "const copied_cont.back()", msg_offset);
	PRINT	<< std::setw(msg_offset) << c_mi_copied_cont.back() << TAB << std::setw(msg_offset) << c_su_copied_cont.back() << END;
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
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	//COMPARISON CHECKS
	comparison_operator_log(su_fill_cont, su_assigned_cont, mi_fill_cont, mi_assigned_cont, ret);
	PRINT	<< YEL "-------------------------------------------------------------------------------------" << NL
			<< "-------------------------------------------------------------------------------------" << END;

	return (ret);
}

int main(void)
{	
	ft::bintree	test;

	test.push_back(3);
	test.push_back(8);
	test.push_back(2);
	test.push_back(4);


	// if (iterator_tests())
	// 	PRINT << GRN "OK" << END;
	// else
	// 	PRINT << RED "KO" << END;
	// if (my_veritable_vector<ft::vector<int>, std::vector<int> >())
	// 	PRINT << GRN "OK" << END;
	// else
	// 	PRINT << RED "KO" << END;

	// //quick make_pair test
	// ft::pair<int, char>	pair_chorra(42, 42);
	// std::pair<int, char> std_pair_chorra(42, 42);

	// PRINT << YEL "MY PAIR_CHORRA: " GRN << pair_chorra.first << YEL ", " GRN << pair_chorra.second << END;
	// PRINT << YEL "STD PAIR_CHORRA: " GRN << std_pair_chorra.first << YEL ", " GRN << std_pair_chorra.second << END;

	// //enable_if test
	// //Change to non-integral (double, float, etc.) to test. :)
	// PRINT << YEL "ENABLE_IF TEST:" << NL;
	// int	i = 1;
	// PRINT << TAB << ALN << "i is odd: " << std::boolalpha << GRN << ft::is_odd(i) << END;

	// std::string	test1 = "Apple";
	// std::string test2 = "honey";
	// std::string test3 = "honey";
	// bool std_ret;

	// std_ret = std::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());

	// PRINT << GRN << std::boolalpha << std_ret << END;

	// std_ret = ft::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());
	// PRINT << GRN << std::boolalpha << std_ret << END;

	// std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test3.begin());
	// PRINT << GRN << std::boolalpha << std_ret << END;

	// std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test1.begin());
	// PRINT << GRN << std::boolalpha << std_ret << END;
	// // //DEBUG
	// // {
	// // 	PRINT << YEL << "THE GREAT IS_INTEGRAL TEST!" << NL
	// // 	<< "Double Is Integral?" << std::boolalpha << " " << std::is_integral<double>::value << NL
	// // 	<< "Float Is Integral?" << std::boolalpha << " " << std::is_integral<float>::value << NL
	// // 	<< "Unsigned Int Is Integral?" << std::boolalpha << " " << std::is_integral<unsigned int>::value << END;
	// // }
	// // //DEBUG


	return (0);
}