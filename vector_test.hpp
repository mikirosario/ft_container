/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:23:58 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/21 10:23:53 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"
#include <vector>
#include "vector.hpp"

template <typename Vector_T>
void	vector_test(void)
{
	/* CONSTRUCTOR TESTS */
	//FILL CONSTRUCTOR TEST
	PRINT	<< "FILL CONSTRUCTOR TEST" << END;
	Vector_T	fill_cont(4, 42);

	//RANGE CONSTRUCTOR TEST
	PRINT	<< TXT_BYEL "RANGE CONSTRUCTOR TEST" << END;
	Vector_T	range_cont(fill_cont.begin(), fill_cont.end());

	//COPY CONSTRUCTOR TEST
	PRINT	<< TXT_BYEL "COPY CONSTRUCTOR TEST" << END;
	Vector_T	copied_cont(fill_cont);
	
	//ASSIGNMENT OVERLOAD COPY TEST
	PRINT	<< TXT_BYEL "ASSIGNMENT OVERLOAD COPY TEST" << END;
	Vector_T	assigned_cont = fill_cont;

	//ITERATORS
	PRINT	<< TXT_BYEL "ITERATOR PRINT TEST" << END;
	typename Vector_T::iterator it = fill_cont.begin();
	typename Vector_T::const_iterator end = fill_cont.end();
	for ( ; it != end; ++it)
		PRINT << *it << TXT_NL;

	//REVERSE ITERATOR PRINT TEST
	PRINT	<< TXT_BYEL "REVERSE ITERATOR PRINT TEST" << END;
	typename Vector_T::reverse_iterator rit = fill_cont.rbegin();
	typename Vector_T::const_reverse_iterator rend = fill_cont.rend();	
	for ( ; rit != rend; ++rit)
		PRINT << *rit << TXT_NL;

	//CAPACITY
	PRINT	<< TXT_BYEL "MAX SIZE" << END;
	PRINT	<< fill_cont.max_size() << TXT_NL;

	//CAPACITY EQUALITY CHECK, this should be equal if we follow the same
	//allocation strategy of multiplying by * 2. :p
	PRINT	<< TXT_BYEL "CAPACITY" << END;
	PRINT	<< fill_cont.capacity() << TXT_NL;

	//PUSH_BACK TEST
	PRINT	<< TXT_BYEL "PUSH BACK TESTS" << END;
	fill_cont.push_back(84);
	fill_cont.push_back(168);
	fill_cont.push_back(69);
	copied_cont.push_back(-42);
	copied_cont.push_back(-21);
	
	//RESERVE TEST
	PRINT	<< TXT_BYEL "RESERVE TEST" << END;
	fill_cont.reserve(20);
	
	//POP_BACK TEST
	PRINT	<< TXT_BYEL "POP BACK TEST" << END;
	fill_cont.pop_back();
	
	//RESIZE TEST
	//Size down
	PRINT	<< TXT_BYEL "RESIZE TESTS" << END;
	fill_cont.resize(2);
	//Size up
	fill_cont.resize(4);
	//Size up with caller-specified value
	fill_cont.resize(6, 21);
	
	//ERASE TESTS
	//ERASE BY POSITION
	PRINT	<< TXT_BYEL "ERASE TESTS" << END;
	{
		typename Vector_T::iterator	erase_res = fill_cont.erase(fill_cont.begin() + 2);
		PRINT	<< *erase_res << TXT_NL
				<< erase_res - fill_cont.begin() << TXT_NL;
	}
	{
		typename Vector_T::iterator erase_res = fill_cont.erase(fill_cont.end() - 1);
		PRINT	<< erase_res - fill_cont.begin() << TXT_NL;
	}
	//ERASE BY RANGE
		//THESE RETURN VOID IN C++98
		fill_cont.erase(fill_cont.begin() + 1, fill_cont.end());

	//INSERT TESTS
	//INSERT BY POSITION
	PRINT	<< TXT_BYEL "INSERT TESTS" << END;
	fill_cont.insert(fill_cont.begin(), 1984);
	//INSERT BY POSITION AND CLONE N TIMES
	fill_cont.insert(fill_cont.begin(), 2, 1970);
	//Create new containers for swap test
	Vector_T	swappable_cont(4, 1);
	swappable_cont.insert(swappable_cont.begin() + 1, 1, 9);
	
	//INSERT BY RANGE
	fill_cont.insert(fill_cont.begin(), swappable_cont.begin(), swappable_cont.end());
	assigned_cont.insert(assigned_cont.begin(), fill_cont.rbegin(), fill_cont.rend());
	
	//SWAP TEST
	//AS CLASS FUNCTION
	PRINT	<< TXT_BYEL "SWAP TESTS" << END;
	fill_cont.swap(swappable_cont);
	swap(fill_cont, swappable_cont);

	//GET ALLOCATOR TEST
	PRINT	<< TXT_BYEL "GET ALLOCATOR TEST" << END;
	typename Vector_T::allocator_type alloc = fill_cont.get_allocator();
	PRINT	<< alloc.max_size() << TXT_NL;

	//ASSIGN TESTS
	PRINT	<< TXT_BYEL "ASSIGN TEST" << END;
	fill_cont.assign(8, 42);
	fill_cont.assign(copied_cont.begin(), copied_cont.end());

	//REFERENCING TESTS
	//Referencing by []
	PRINT	<< TXT_BYEL "REFERENCING TESTS" << END;
	PRINT	<< fill_cont[4] << TXT_NL;
	typename Vector_T::value_type &		num1(fill_cont[4]);
	PRINT	<< num1;
	try
	{
		PRINT << fill_cont.at(5) << TXT_NL;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TXT_TAB << TXT_BRED << e.what() << END;
	}
	try
	{
		PRINT << fill_cont.at(6) << TXT_NL;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TXT_TAB << TXT_BBLU << e.what() << END;
	}
	try
	{
		Vector_T	vacio;
		PRINT << vacio.at(0) << TXT_NL;
	}
	catch(const std::out_of_range & e)
	{
		PRNTERR << TXT_TAB << TXT_BBLU << e.what() << END;
	}
	//CONST REFERENCING
	const Vector_T	c_copied_cont(copied_cont);
	PRINT << c_copied_cont[2] << TXT_NL;

	//FRONT AND BACK TESTS
	PRINT	<< TXT_BYEL "FRONT AND BACK CHECKS" << END;
	PRINT	<< fill_cont.front() << TXT_NL;
	PRINT	<< fill_cont.back() << TXT_NL;
	PRINT	<< c_copied_cont.front() << TXT_NL;
	PRINT	<< c_copied_cont.back() << TXT_NL;
	fill_cont.front() = 5;
	fill_cont.back() = 10;
}
