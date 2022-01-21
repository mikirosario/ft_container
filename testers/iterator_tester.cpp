/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_tester.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:45:52 by miki              #+#    #+#             */
/*   Updated: 2022/01/21 07:05:13 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../testers.hpp"
#include "../vector.hpp"
#include <vector>

/*
** This early tester was used to test my vector iterators using a raw C-style
** array when the vector class was not yet completed. It is currently obsolete
** as the container testers all thoroughly test their respective iterators, so
** it is disabled, but I'll leave it in for reference, accessible via
** VECIT_STANDALONE argument.
*/
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
	ft::vector<int>::iterator ft_it(&a[0]); //For basic iterator
	ft::vector<int>::iterator ft_it2(&a[1]);
	PRINT	<< TXT_BYEL "CREATING IDENTICAL STD::VECTOR<INT>::ITERATORS:" << TXT_NL
			<< TXT_TAB << ALN << "std_it = &a[0]" << TXT_NL
			<< TXT_TAB << ALN << "std_it2 = &a[1]" << END;
	std::vector<int>::iterator std_it(std_vector.begin());
	std::vector<int>::iterator std_it2(std_vector.begin() + 1);
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
