/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_veritable_vector.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:55:37 by miki              #+#    #+#             */
/*   Updated: 2022/01/21 07:05:13 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../testers.hpp"
#include "../vector.hpp"
#include <vector>
#include <cstring> //for memcmp

/*
** This test compares my vector with the STL vector under the same conditions
** using ints.
**
** Conditions are printed in yellow before each test and results are printed in
** red (if unequal) and green (if equal) after the test. The function returns
** true if all tests are passed and false otherwise.
**
** Certain execution operations are also timed. For timed operations, the timer
** results are printed in red if my vector took more than 20 times what STL
** vector took to perform the same operation, otherwise they are printed in
** green. Timed operations results also affect the final result.
**
** Reverse iterators are tested separately. Normal iterators are used throughout
** the test to print results on the screen and send them to the check functions
** for comparison and verification, so they are considered tested there.
*/
bool	my_veritable_vector(void)
{
	bool		ret = true;
	size_t		msg_offset;
	__uint64_t	start;
	__int64_t	ft_time;
	__int64_t	stl_time;

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
	//Start Exec Timer
	start_timer(&start);
	ft::vector<int>		mi_fill_cont(4, 42);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std::vector<int>	su_fill_cont(4, 42);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//Stop Exec Timer
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);

	//RANGE CONSTRUCTOR TEST
	PRINT	<< TXT_NL
			<< TXT_BYEL "RANGE CONSTRUCTOR TESTS" << TXT_NL
			<< TXT_TAB << "Range-constructing: " << TXT_NL
			<< TXT_TAB << "  ft::container mi_range_cont(mi_fill_cont.begin(), mi_fill_cont.end())" << TXT_NL
			<< TXT_TAB << "  std::container su_range_cont(su_fill_cont.begin(), su_fill_cont.end())" << END;
	//Start Exec Timer
	start_timer(&start);
	ft::vector<int>	mi_range_cont(mi_fill_cont.begin(), mi_fill_cont.end());
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std::vector<int> 	su_range_cont(su_fill_cont.begin(), su_fill_cont.end());
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//Stop Exec Timer
	elemc_compare_log(su_range_cont, mi_range_cont);
	cont_check_log(su_range_cont, mi_range_cont, ret);

	//COPY CONSTRUCTOR TEST
	PRINT	<< TXT_NL
			<< TXT_BYEL "COPY CONSTRUCTOR TESTS" << TXT_NL
			<< TXT_TAB << "Copy-constructing: " << TXT_NL
			<< TXT_TAB << "  ft::container mi_copied_cont(mi_fill_cont)" << TXT_NL
			<< TXT_TAB << "  std::container su_copied_cont(su_fill_cont)" << END;
	//Start Exec Timer
	start_timer(&start);
	ft::vector<int>	mi_copied_cont(mi_fill_cont);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std::vector<int>	su_copied_cont(su_fill_cont);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	elemc_compare_log(su_copied_cont, mi_copied_cont);
	cont_check_log(su_copied_cont, mi_copied_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;
	
	//ASSIGNMENT OVERLOAD COPY TEST
	PRINT	<< TXT_BYEL "ASSIGNMENT OVERLOAD COPY TEST" << TXT_NL
			<< TXT_TAB << "Copying via assignment: " << TXT_NL
			<< TXT_TAB << "  ft::container(0) mi_assigned_cont = mi_fill_cont" << TXT_NL
			<< TXT_TAB << "  std::container(0) su_assigned_cont = su_fill_cont" << END;
	//Start Exec Timer
	start_timer(&start);
	ft::vector<int>	mi_assigned_cont = mi_fill_cont;
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std::vector<int>	su_assigned_cont = su_fill_cont;
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	elemc_compare_log(su_assigned_cont, mi_assigned_cont);
	cont_check_log(su_assigned_cont, mi_assigned_cont, ret);
	PRINT	<< TXT_BYEL "-------------------------------------------------------------------------------------" << TXT_NL
			<< "-------------------------------------------------------------------------------------" << END;

	//REVERSE ITERATOR PRINT TEST
	PRINT	<< TXT_BYEL "REVERSE ITERATOR PRINT TEST" << TXT_NL
			<< TXT_TAB << "Printing using reverse iterators: " << TXT_NL
			<< TXT_TAB << "  mi_fill_cont" << TXT_NL
			<< TXT_TAB << "  su_fill_cont" << END;

	PRINT	<< TXT_TAB << TXT_BYEL "MY Reverse Printed Container Timed Check: " << END;
	//Start Exec Timer
	start_timer(&start);
	for (ft::vector<int>::reverse_iterator rit = mi_fill_cont.rbegin(), rend = mi_fill_cont.rend(); rit != rend; ++rit)
		PRINT << TXT_TAB << *rit << END;
	ft_time = stop_timer_nanosec(&start);
	PRINT	<< TXT_TAB << TXT_BYEL "STD Reverse Printed Container: Timed Check " << END;
	start_timer(&start);
	for (std::vector<int>::reverse_iterator rit = su_fill_cont.rbegin(), rend = su_fill_cont.rend(); rit != rend; ++rit)
		PRINT << TXT_TAB << *rit << END;
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_rev_comp(mi_fill_cont, su_fill_cont, ret);
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
	//Start Exec Timer
	start_timer(&start);
	mi_fill_cont.push_back(84);
	mi_fill_cont.push_back(168);
	mi_fill_cont.push_back(69);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_fill_cont.push_back(84);
	su_fill_cont.push_back(168);
	su_fill_cont.push_back(69);
	stl_time = stop_timer_nanosec(&start);
	//End Exec Timer
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Adding -42 and -21 via push_back to: " << TXT_NL
			<< TXT_TAB << "  mi_copied_cont.push_back(-42...)" << TXT_NL
			<< TXT_TAB << "  su_copied_cont.push_back(-42...)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_copied_cont.push_back(-42);
	mi_copied_cont.push_back(-21);
	ft_time += stop_timer_nanosec(&start);
	start_timer(&start);
	su_copied_cont.push_back(-42);
	su_copied_cont.push_back(-21);
	stl_time += stop_timer_nanosec(&start);
	//End Exec Timer
	elemc_compare_log(su_copied_cont, mi_copied_cont);
	cont_check_log(su_copied_cont, mi_copied_cont, ret);
	check_exec_time(ft_time, stl_time, ret);
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
	//Start Exec Timer
	start_timer(&start);
	mi_fill_cont.pop_back();
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_fill_cont.pop_back();
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
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
		//Start Exec Timer
		start_timer(&start);
		ft::vector<int>::iterator mi_erase_res = mi_fill_cont.erase(mi_fill_cont.begin() + 2);
		ft_time = stop_timer_nanosec(&start);
		start_timer(&start);
		std::vector<int>::iterator su_erase_res = su_fill_cont.erase(su_fill_cont.begin() + 2);
		stl_time = stop_timer_nanosec(&start);
		check_exec_time(ft_time, stl_time, ret);
		//End Exec Timer
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
		//Start Exec Timer
		start_timer(&start);
		ft::vector<int>::iterator mi_erase_res = mi_fill_cont.erase(mi_fill_cont.end() - 1);
		ft_time = stop_timer_nanosec(&start);
		start_timer(&start);
		std::vector<int>::iterator su_erase_res = su_fill_cont.erase(su_fill_cont.end() - 1);
		stl_time = stop_timer_nanosec(&start);
		check_exec_time(ft_time, stl_time, ret);
		//End Exec Timer
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
		//Start Exec Timer
		start_timer(&start);
		mi_fill_cont.erase(mi_fill_cont.begin() + 1, mi_fill_cont.end());
		ft_time = stop_timer_nanosec(&start);
		start_timer(&start);
		su_fill_cont.erase(su_fill_cont.begin() + 1, su_fill_cont.end());
		stl_time = stop_timer_nanosec(&start);
		check_exec_time(ft_time, stl_time, ret);
		//End Exec Timer
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
	//Start Exec Timer
	start_timer(&start);
	mi_fill_cont.insert(mi_fill_cont.begin(), 1984);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_fill_cont.insert(su_fill_cont.begin(), 1984);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//INSERT BY POSITION AND CLONE N TIMES
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Inserting by position and cloning n times:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.insert(mi_fill_cont.begin(), 2, 1970)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.insert(su_fill_cont.begin(), 2, 1970)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_fill_cont.insert(mi_fill_cont.begin(), 2, 1970);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_fill_cont.insert(su_fill_cont.begin(), 2, 1970);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	//Creating new containers for swap test
	PRINT	<< TXT_TAB << TXT_BYEL "Fill-creating new containers:" << TXT_NL
			<< TXT_TAB << "  ft::container mi_swappable_cont(4, 1)" << TXT_NL
			<< TXT_TAB << "  std::container su_swappable_cont(4, 1)" << END;
	//Start Exec Timer
	start_timer(&start);
	ft::vector<int>	mi_swappable_cont(4, 1);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std::vector<int>	su_swappable_cont(4, 1);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	PRINT	<< TXT_TAB << TXT_BYEL "Inserting by position and cloning n times:" << TXT_NL
			<< TXT_TAB << "  mi_swappable_cont.insert(mi_swappable_cont.begin() + 1, 1, 9)" << TXT_NL
			<< TXT_TAB << "  su_swappable_cont.insert(su_swappable_cont.begin() + 1, 1, 9)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_swappable_cont.insert(mi_swappable_cont.begin() + 1, 1, 9);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_swappable_cont.insert(su_swappable_cont.begin() + 1, 1, 9);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);
	
	//INSERT BY RANGE
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Inserting by range:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.insert(mi_fill_cont.begin(), mi_swappable_cont.begin(), mi_swappable_cont.end())" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.insert(su_fill_cont.begin(), su_swappable_cont.begin(), su_swappable_cont.end())" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_fill_cont.insert(mi_fill_cont.begin(), mi_swappable_cont.begin(), mi_swappable_cont.end());
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_fill_cont.insert(su_fill_cont.begin(), su_swappable_cont.begin(), su_swappable_cont.end());
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);

	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Inserting by range with reverse iterators:" << TXT_NL
			<< TXT_TAB << "  mi_assigned_cont.insert(mi_assigned_cont.begin(), mi_fill_cont.rbegin(), mi_fill_cont.rend())" << TXT_NL
			<< TXT_TAB << "  su_assigned_cont.insert(su_assigned_cont.begin(), su_fill_cont.rbegin(), su_fill_cont.rend())" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_assigned_cont.insert(mi_assigned_cont.begin(), mi_fill_cont.rbegin(), mi_fill_cont.rend());
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_assigned_cont.insert(su_assigned_cont.begin(), su_fill_cont.rbegin(), su_fill_cont.rend());
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
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
	//Start Exec Timer
	start_timer(&start);
	mi_fill_cont.swap(mi_swappable_cont);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_fill_cont.swap(su_swappable_cont);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	//fill_cont swapped with swappable_cont
	PRINT	<< TXT_TAB << TXT_BYEL "  fill_cont:" << END;
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_TAB << TXT_BYEL "  swappable_cont:" << END;
	elemc_compare_log(su_swappable_cont, mi_swappable_cont);
	cont_check_log(su_swappable_cont, mi_swappable_cont, ret);

	//WITH DEFAULT STD::SWAP ON FT::VECTOR
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
	//Start Exec Timer
	start_timer(&start);
	swap(mi_fill_cont, mi_swappable_cont); //why does this activate ADL? no feckin idea!
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	swap(su_fill_cont, su_swappable_cont);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
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
	//Start Exec Timer
	start_timer(&start);
	swap(mi_fill_cont, mi_swappable_cont);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	swap(su_fill_cont, su_swappable_cont);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
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
	// ft::vector<int>::allocator_type		my_alloc = mi_fill_cont.get_allocator();
	// std::vector<int>::allocator_type	std_alloc = su_fill_cont.get_allocator();
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
	ft::vector<int>::value_type * 	mi_allocated_array = mi_fill_cont.get_allocator().allocate(4); //allocators are stateful, and remember what type they are allocating
	std::vector<int>::value_type *	su_allocated_array = su_fill_cont.get_allocator().allocate(4); //so this is NOT 4 bytes, but rather 4 * sizeof(SourceContainer::value_type)
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Assigning values to each allocation using constructor of returned allocator instance:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.get_allocator().construct(arr, val)" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.get_allocator().construct(arr, val)" << END;
	//We don't know what the value_type could be, so we'll just default-initialize whatever it is.
	for (size_t i = 0; i < 4; ++i)
		mi_fill_cont.get_allocator().construct(&mi_allocated_array[i], ft::vector<int>::value_type());
	for (size_t i = 0; i < 4; ++i)
		su_fill_cont.get_allocator().construct(&su_allocated_array[i], std::vector<int>::value_type());
	//Errmm... I'll just do memcmp! ;)
	{
		int	result;
		//sorry for the hideousness.
		//memcmp returns 0 if equal, compare_log expects true if equal...
		//the allocator expects a multiple of the type as the size, memcmp expects the size in bytes...
		//you know how it is. xD
		compare_log(!(result = std::memcmp(su_allocated_array, mi_allocated_array, 4 * sizeof(ft::vector<int>::value_type))), ret, "Heap Allocation", msg_offset);
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
	//Start Exec Timer
	start_timer(&start);
	mi_fill_cont.assign(8, 42);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_fill_cont.assign(8, 42);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	elemc_compare_log(su_fill_cont, mi_fill_cont);
	cont_check_log(su_fill_cont, mi_fill_cont, ret);
	PRINT	<< TXT_NL
			<< TXT_TAB << TXT_BYEL "Assigning by range:" << TXT_NL
			<< TXT_TAB << "  mi_fill_cont.assign(mi_copied_cont.begin(), mi_copied_cont.end())" << TXT_NL
			<< TXT_TAB << "  su_fill_cont.assign(su_copied_cont.begin(), su_copied_cont.end())" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_fill_cont.assign(mi_copied_cont.begin(), mi_copied_cont.end());
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_fill_cont.assign(su_copied_cont.begin(), su_copied_cont.end());
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
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
	ft::vector<int>::value_type &		mi_num1(mi_fill_cont[4]);
	std::vector<int>::value_type &	su_num1(su_fill_cont[4]);
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
		ft::vector<int>	mi_vacio;
		std::vector<int>	su_vacio;
		
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
		ft::vector<int>	mi_vacio;
		std::vector<int>	su_vacio;
		
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
			const ft::vector<int>	c_mi_copied_cont(mi_copied_cont);
			const std::vector<int>	c_su_copied_cont(su_copied_cont);
	PRINT	<< TXT_TAB << TXT_BYEL "Referencing const containers (by []):" << TXT_NL
			<< TXT_TAB << "  c_mi_copied_cont[2]" << TXT_NL
			<< TXT_TAB << "  c_su_copied_cont[2]" << END;
		compare_log(c_mi_copied_cont[2] == c_su_copied_cont[2], ret, "const copied_cont[2]", msg_offset);
		PRINT << std::setw(msg_offset) << c_mi_copied_cont[2] << std::setw(msg_offset) << c_su_copied_cont[2] << END;
	//COMPILE-TIME TESTS
	{
		// Const int reference to const c_fill_cont type_value, this is fine.
		ft::vector<int>::const_reference	c_mi_num(c_mi_copied_cont[2]);
		std::vector<int>::const_reference	c_su_num(c_su_copied_cont[2]);
		compare_log(c_mi_num == c_su_num, ret, "const num", msg_offset);
		PRINT << std::setw(msg_offset) << c_mi_copied_cont[2] << TXT_TAB << std::setw(msg_offset) << c_su_copied_cont[2] << END;
		// // Compiler will not allow this as c_fill_cont is const.
		// ft::vector<int>::reference & mi_num(c_mi_copied_cont[2]);
		// std::vector<int>::reference & su_num(c_su_copied_cont[2]);

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
