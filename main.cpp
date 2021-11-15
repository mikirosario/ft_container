/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/15 01:18:05 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "utility.hpp"
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

void	my_veritable_vector(void)
{
	ft::vector<int>	viktor(4, 42);
	std::vector<int> vector(4, 42);

	//RANGE CONSTRUCTOR TEST
	ft::vector<int> range(viktor.begin(), viktor.end());
	for (ft::vector<int>::iterator it = range.begin(), end = range.end(); it != end; ++it)
		PRINT << "no puede ser: " << *it << NL;

	//COPY CONSTRUCTOR TEST
	ft::vector<int> clone(viktor);
	for (ft::vector<int>::iterator it = clone.begin(), end = clone.end(); it != end; ++it)
		PRINT << "Clone: " << *it << NL;
	
	//ASSIGNMENT OVERLOAD COPY TEST
	ft::vector<int> assigned(0);
	assigned = viktor;
	for (ft::vector<int>::iterator it = assigned.begin(), end = assigned.end(); it != end; ++it)
		PRINT << "Assigned: " << *it << NL;

	//REVERSE ITERATOR PRINT TEST
	for (ft::vector<int>::reverse_iterator rit = viktor.rbegin(), rend = viktor.rend(); rit != rend; ++rit)
		PRINT << "reverse: " << *rit << END;

	//MAX_SIZE
		PRINT << "Max Size: " << viktor.max_size() << END;
		PRINT << "Max Size STD: " << vector.max_size() << END;

	//CAPACITY
		PRINT << "Capacity Before Push_Back: " << viktor.capacity() << END;

	//PUSH_BACK
	viktor.push_back(84);
	viktor.push_back(168);
	viktor.push_back(69);
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Vamooooos: " << *it << NL;
	//CAPACITY
		PRINT << "Capacity After Push_Back: " << viktor.capacity() << END;
	
	//RESERVE
	viktor.reserve(10);
	//CAPACITY
		PRINT << "Capacity After Reserve: " << viktor.capacity() << END;
	
	//POP_BACK
	viktor.pop_back();
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Popped back: " << *it << NL;
	
	//RESIZE
	viktor.resize(2);
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Size down: " << *it << NL;
	viktor.resize(4);
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Size up: " << *it << NL;
	viktor.resize(6, 21);
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Size up overload: " << *it << NL;

	//ERASE 1
	viktor.erase(viktor.begin() + 2);
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Erased elem 2: " << *it << NL;
	if (viktor.erase(viktor.end() - 1) == viktor.end())
		PRINT << "BIEN" << NL;
	else
		PRINT << "MALDAD" << NL;
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Erased elem end: " << *it << NL;
	//ERASE 2
	viktor.erase(viktor.begin() + 1, viktor.end());
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Erased range: " << *it << NL;

	//INSERT 1
	viktor.insert(viktor.begin(), 1984);
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "After insertion 1: " << *it << NL;
	//INSERT 2
	viktor.insert(viktor.begin(), 2, 1970);
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "After insertion 2: " << *it << NL;
	
	ft::vector<int> tryst(4, 1);
	tryst.insert(tryst.begin() + 1, 1, 9);
	for (ft::vector<int>::iterator it = tryst.begin(), end = tryst.end(); it != end; ++it)
		PRINT << "After insertion alt: " << *it << NL;
	//INSERT 3
	viktor.insert(viktor.begin(), tryst.begin(), tryst.end());
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "After insertion 3: " << *it << NL;
	
	//SWAP
	viktor.swap(tryst);
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "After swap: " << *it << NL;
	
	//STD SWAP WITH FT::VECTOR
	swap(viktor, tryst); //HOW!? I didn't give you any information!! :O
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "After swap 2: " << *it << NL;

	//GET ALLOCATOR
	// //You could do this:
	// ft::vector<int>::allocator_type alloc = viktor.get_allocator();
	//
	// //But you can't do this:
	// viktor.allocator_type alloc = viktor.get_allocator();
	//
	// //Because... well, according to compiler, because you just can't. So there.
	// Aaaanyway...
	int * allocated_array = viktor.get_allocator().allocate(4);
	for (size_t i = 0; i < 4; ++i)
		viktor.get_allocator().construct(&allocated_array[i], 42);
	for (size_t i = 0; i < 4; ++i)
		PRINT << "Allocated Array: " << allocated_array[i] << END;
	size_t i = 3;
	do {
		viktor.get_allocator().destroy(&allocated_array[i]);
	} while (i-- > 0);
	viktor.get_allocator().deallocate(allocated_array, 4); // Why would anyone do this though?

	//ASSIGN
	clone.push_back(-42);
	clone.push_back(-21);
	viktor.assign(clone.begin(), clone.end());
	for (ft::vector<int>::iterator it = viktor.begin(), end = viktor.end(); it != end; ++it)
		PRINT << "Assign...: " << *it << NL;

	//std::vector<int> clone(vector.begin(), vector.end());
	std::vector<std::vector<int>::iterator> test;
	ft::vector<int>::iterator ft_it(viktor.begin());
	std::vector<int>::iterator std_it(vector.begin());

	//REFERENCING
	const ft::vector<int>	c_viktor(3, 42);
	ft::vector<int>	vacio;
	int & num1(viktor[0]);
	
	PRINT << "Referenced by viktor[]: " << num1 << END;

	try
	{
		int & num2(viktor.at(5));
		PRINT << "Referenced by at(): " << num2 << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << e.what() << END;
	}

	try
	{
		int & num2(viktor.at(6));
		PRINT << "Referenced by at(): " << num2 << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << e.what() << END;
	}

	try
	{
		int & num2(vacio.at(0));
		PRINT << "Referenced by at(): " << num2 << END;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << e.what() << END;
	}
	
	//CONST REFERENCING
	// Const int reference to const vector int, this is fine.
	const int & c_num(c_viktor[5]);
	// // Compiler will not allow this as c_viktor is const.
	// int & num3(c_viktor[5]);

	// This is all fine, read-only
	PRINT << "Const Reference: " << c_num << END;

	// // Compiler will not allow this as c_viktor is const.
	//c_viktor[0] = 8;
	

	//FRONT AND BACK
	PRINT << "Front: " << viktor.front() << NL
	<< "Back: " << viktor.back() << NL
	<< "Const Front: " << c_viktor.front() << NL
	<< "Const Back: " << c_viktor.back() << END;

	//This is fine
	viktor.front() = 5;
	viktor.back() = 10;

	// // Compiler should not allow this as c_viktor is const.
	// c_viktor.front() = 5;
	// c_viktor.back() = 10;

	//COMPARISON TEST
	PRINT << "viktor == assigned?: " << std::boolalpha << (viktor == assigned) << END;
	PRINT << "viktor != assigned?: " << std::boolalpha << (viktor != assigned) << END;
	PRINT << "viktor == viktor?: " << std::boolalpha << (viktor == viktor) << END;
	PRINT << "viktor != viktor?: " << std::boolalpha << (viktor != viktor) << END;
	PRINT << "viktor < assigned?: " << std::boolalpha << (viktor < assigned) << END;
	PRINT << "viktor > assigned?: " << std::boolalpha << (viktor > assigned) << END;
	PRINT << "viktor < viktor?: " << std::boolalpha << (viktor < viktor) << END;
	PRINT << "viktor > viktor?: " << std::boolalpha << (viktor > viktor) << END;
	PRINT << "viktor <= assigned?: " << std::boolalpha << (viktor <= assigned) << END;
	PRINT << "viktor >= assigned?: " << std::boolalpha << (viktor >= assigned) << END;
	PRINT << "viktor <= viktor?: " << std::boolalpha << (viktor <= viktor) << END;
	PRINT << "viktor >= viktor?: " << std::boolalpha << (viktor >= viktor) << END;

	//DEBUG i know i know, my iterators aren't done yet ok? it will take up a thousand characters eventually i swear! xD
	for (size_t i = 0; i < 4; ++i)
		PRINT << *ft_it++ << END;
	for (size_t i = 0; i < 4; ++i)
		PRINT << *std_it++ << END;
}

int main(void)
{	
	if (iterator_tests())
		PRINT << GRN "OK" << END;
	else
		PRINT << RED "KO" << END;
	
	my_veritable_vector();	

	//quick make_pair test
	ft::pair<int, char>	pair_chorra(42, 42);
	std::pair<int, char> std_pair_chorra(42, 42);

	PRINT << YEL "MY PAIR_CHORRA: " GRN << pair_chorra.first << YEL ", " GRN << pair_chorra.second << END;
	PRINT << YEL "STD PAIR_CHORRA: " GRN << std_pair_chorra.first << YEL ", " GRN << std_pair_chorra.second << END;

	//enable_if test
	//Change to non-integral (double, float, etc.) to test. :)
	PRINT << YEL "ENABLE_IF TEST:" << NL;
	int	i = 1;
	PRINT << TAB << ALN << "i is odd: " << std::boolalpha << GRN << ft::is_odd(i) << END;

	std::string	test1 = "Apple";
	std::string test2 = "honey";
	std::string test3 = "honey";
	bool std_ret;

	std_ret = std::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());

	PRINT << GRN << std::boolalpha << std_ret << END;

	std_ret = ft::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());
	PRINT << GRN << std::boolalpha << std_ret << END;

	std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test3.begin());
	PRINT << GRN << std::boolalpha << std_ret << END;

	std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test1.begin());
	PRINT << GRN << std::boolalpha << std_ret << END;
	// //DEBUG
	// {
	// 	PRINT << YEL << "THE GREAT IS_INTEGRAL TEST!" << NL
	// 	<< "Double Is Integral?" << std::boolalpha << " " << std::is_integral<double>::value << NL
	// 	<< "Float Is Integral?" << std::boolalpha << " " << std::is_integral<float>::value << NL
	// 	<< "Unsigned Int Is Integral?" << std::boolalpha << " " << std::is_integral<unsigned int>::value << END;
	// }
	// //DEBUG


	return (0);
}