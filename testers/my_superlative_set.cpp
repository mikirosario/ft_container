/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_superlative_set.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:47:39 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/20 23:43:26 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../testers.hpp"
#include "../ft_set.hpp"

static void	make_seed_set(std::set<std::string> & seed_set)
{
	seed_set.insert("cuarenta y dos");
	seed_set.insert("ordenador");
	seed_set.insert("piscina");
	seed_set.insert("arbol binario de rojos y negros");
	seed_set.insert("tig");
	seed_set.insert("lista enlazada");
	seed_set.insert("array");
	seed_set.insert("marvin");
	seed_set.insert("norminette");
	seed_set.insert("cafe");
	seed_set.insert("agua");
	seed_set.insert("compilador");
}

/*
** This test compares my set with the STL set under the same conditions using
** std::string as key and value.
**
** Conditions are printed in yellow before each test and results are printed in
** red (if unequal) and green (if equal) after the test. The function returns
** true if all tests are passed and false otherwise.
**
** Certain execution operations are also timed. For timed operations, the timer
** results are printed in red if my set took more than 20 times what STL
** set took to perform the same operation, otherwise they are printed in
** green. Timed operations results also affect the final result.
**
** The max size comparison is done but doesn't affect the result. My max size is
** smaller than STL max size as my set is a bit less efficient and takes up more
** space per element. It is not required by the subject that they be equal and
** mine is still within the same order of magnitude (1e17 - 1e18, depending on
** machine).
**
** Reverse iterators are tested separately. Normal iterators are used throughout
** the test to print results on the screen and send them to the check functions
** for comparison and verification, so they are considered tested there.
**
** The double free test is only done on my version of the set. I trust STL
** developers that much. ;)
**
** The reverse iterator test is divided into a "Normal Person Reverse Iterator
** Test" and an "Insane Person Who Dereferences Reverse End Iterator Test
** (Consted and Non-Consted)". The latter only applies to school Macs, because
** there I imitate a really crazy implementation detail on Mac that causes end
** iterators to be dereferenceable without provoking a segmentation fault. :p
** The code is only meant to be uncommented on the 42 school Macs for
** evaluation purposes. Otherwise, it really makes no sense. I would prefer them
** to segfault.
*/
bool	my_superlative_set(void)
{
	std::set<std::string>	seed_set;
	char const *			color = TXT_BGRN;
	bool					ret = true;
	uint64_t				start;
	int64_t					ft_time;
	int64_t					stl_time;

	make_seed_set(seed_set);
	
	typedef ft::set<std::string>	ft_set;
	typedef std::set<std::string>	std_set;

	//DEFAULT CONSTRUCTOR
	PRINT	<< TXT_BYEL << "DEFAULT INSTANTIATION TEST" << END;
	ft_set		mi_set_default;
	std_set		su_set_default;
	print_set_comp(mi_set_default, su_set_default, color, ret);
	PRINT	<< ((isGreen(color) == true) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;

	PRINT	<< TXT_NL << TXT_BYEL << "RANGE CONSTRUCTION TESTS" << END;

	//RANGE CONSTRUCTOR
	start_timer(&start);
	ft_set		mi_set_range(seed_set.begin(), seed_set.end());
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std_set		su_set_range(seed_set.begin(), seed_set.end());
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	print_set_comp<ft_set, std_set >(mi_set_range, su_set_range, color, ret);

	//COPY CONSTRUCTOR
	PRINT	<< TXT_NL << TXT_BYEL << "COPY CONSTRUCTION TESTS" << END;
	start_timer(&start);
	ft_set		mi_set_copy(mi_set_range);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std_set		su_set_copy(su_set_range);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	print_set_comp<ft_set, std_set >(mi_set_copy, su_set_copy, color, ret);

	//ASSIGNMENT OVERLOAD
	PRINT	<< TXT_NL << TXT_BYEL << "ASSIGNMENT OVERLOAD TESTS" << END;
	start_timer(&start);
	mi_set_default = mi_set_copy;
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_default = su_set_copy;
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	print_set_comp<ft_set, std_set>(mi_set_default, su_set_default, color, ret);

	//REVERSE ITERATORS
	PRINT	<< TXT_NL << TXT_BYEL << "REVERSE ITERATOR TESTS" << END;
	PRINT	<< TXT_TAB << TXT_BYEL << "Normal Person Reverse Iterator Test" << END;
	print_set_rev_comp<ft_set, std_set>(mi_set_default, su_set_default, color, ret);
	PRINT	<< TXT_TAB << TXT_BYEL << "Insane Person Who Dereferences Reverse End Iterator Test (Consted and Non-Consted)" << END;
	//This just tests that the end iterator std::string is dereferenceable without segfault; there is no equality guarantee.
	//For whatever reason, STD seems to make this possible. :P
	//Update! It's not STD, it's fooking Mac!!!! This code crashed my Linux-compiled set, as it rightly should!!! xD
	ft_set::reverse_iterator mrend = mi_set_default.rend();
	ft_set::const_reverse_iterator cmrend = mi_set_default.rend();
	//std_set::reverse_iterator srend = su_set_default.rend();
	//std_set::const_reverse_iterator csrend = su_set_default.rend();
	PRINT	<< TXT_NL << *mrend << END;
	//PRINT	<< TXT_NL << srend->second << END;
	//PRINT	<< TXT_NL << csrend->second << END;
	PRINT	<< TXT_NL << *cmrend << END;
	PRINT	<< TXT_TAB << TXT_BGRN << "OK" << END;
	PRINT	<< TXT_NL << TXT_BYEL << "THE EVIL DOUBLE-FREE TEST" << END; //Ensure erasing and clearing doesn't lead to any double-free attempts.
	ft_set	mi_set_dblfree;
	mi_set_dblfree.insert("testing");
	mi_set_dblfree.erase("testing");
	mi_set_dblfree.clear();
	check(mi_set_dblfree.size() == 0 & mi_set_dblfree.empty() == true, color, ret);
	PRINT	<< TXT_TAB << color << (color == std::string(TXT_BGRN) ? "OK" : "KO") << END;

	//CAPACITY
	PRINT	<< TXT_NL << TXT_BYEL << "CAPACITY TESTS" << TXT_NL
			<< "Empty Test: " << TXT_NL
			<< "MY  " << TXT_TAB << "STD " << END;
	check(mi_set_default.empty() == su_set_default.empty(), color, ret);
	PRINT	<< color << std::boolalpha << mi_set_default.empty() << TXT_TAB << su_set_default.empty() << END;
	PRINT	<< TXT_BYEL << "Size Test: " << TXT_NL
			<< "MY  " << TXT_TAB << "STD " << END;
	check(mi_set_default.size() == su_set_default.size(), color, ret);
	PRINT	<< color << mi_set_default.size() << TXT_TAB << su_set_default.size() << END;
	PRINT	<< TXT_BYEL << "Max Size Test: " << TXT_NL
			<< "MY  " << TXT_TAB << TXT_TAB TXT_TAB << "STD " << END;
	PRINT	<< TXT_BWHT << mi_set_default.max_size() << TXT_TAB << su_set_default.max_size() << END;

	//OPERATIONS
	PRINT	<< TXT_NL << TXT_BYEL << "OPERATIONS TESTS" << TXT_NL
			<< TXT_TAB << "Find by std::string ('marvin')" << END;
	{
	//Start Exec Timer
	start_timer(&start);
	ft_set::iterator mit = mi_set_default.find("marvin");
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std_set::iterator sit = su_set_default.find("marvin");
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(*mit == *sit, color, ret);
	PRINT	<< color << *mit << TXT_NL
			<< *sit << END;
	}
	PRINT	<< TXT_TAB << TXT_BYEL << "Find by std::string Non-Existent ('marvine')" << END; //must return end()
	{
	//Start Exec Timer
	start_timer(&start);
	ft_set::iterator mit = mi_set_default.find("marvine");
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std_set::iterator sit = su_set_default.find("marvine");
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mit == mi_set_default.end() & sit == su_set_default.end(), color, ret);
	PRINT	<< ((isGreen(color) == true) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	}
	PRINT	<< TXT_BYEL << TXT_TAB << "Count Existent Element ('agua')" << TXT_NL;
	check(mi_set_default.count("agua") == su_set_default.count("agua"), color, ret);
	PRINT	<< "MY  " << TXT_TAB << "STD " << TXT_NL
			<< color << mi_set_default.count("agua") << TXT_TAB << su_set_default.count("agua") << END;
	PRINT	<< TXT_BYEL << TXT_TAB << "Count Non-Existent Element ('santana')" << TXT_NL;
	check(mi_set_default.count("santana") == su_set_default.count("santana"), color, ret);
	PRINT	<< "MY  " << TXT_TAB << "STD " << TXT_NL
			<< color << mi_set_default.count("santana") << TXT_TAB << su_set_default.count("santana") << END;
	{
	PRINT	<< TXT_BYEL << TXT_TAB << "Lower Bound Existent Element ('marvin')" << TXT_NL;
	ft_set::iterator mit = mi_set_default.lower_bound("marvin");
	std_set::iterator sit = su_set_default.lower_bound("marvin");
	check(*mit == *sit, color, ret);
	PRINT	<< color << *mit << TXT_NL << *sit << END;
	
	PRINT	<< TXT_BYEL << TXT_TAB << "Lower Bound Non-Existent Subsequent Element ('marvinovich')" << TXT_NL;
	mit = mi_set_default.lower_bound("marvinovich");
	sit = su_set_default.lower_bound("marvinovich");
	check(*mit == *sit, color, ret);
	PRINT	<< color << *mit << TXT_NL << *sit << END;
	
	PRINT	<< TXT_BYEL << TXT_TAB << "Lower Bound Non-Existent Min Element ('aaaa')" << TXT_NL;
	mit = mi_set_default.lower_bound("aaaa");
	sit = su_set_default.lower_bound("aaaa");
	check(*mit == *sit, color, ret);
	PRINT	<< color << *mit << TXT_NL << *sit << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Lower Bound Non-Existent Max Element ('zzzz')" << TXT_NL;
	mit = mi_set_default.lower_bound("zzzz");
	sit = su_set_default.lower_bound("zzzz");
	check(*(--mit) == *(--sit), color, ret);
	PRINT	<< color << (isGreen(color) == true ? "END()" : "NOT END()!") << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Upper Bound Existent Element ('cafe')" << TXT_NL;
	mit = mi_set_default.upper_bound("cafe");
	sit = su_set_default.upper_bound("cafe");
	check(*mit == *sit, color, ret);
	PRINT	<< color << *mit << TXT_NL << *sit << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Upper Bound Non-Existent Subsequent Element ('cafeteria')" << TXT_NL;
	mit = mi_set_default.upper_bound("cafeteria");
	sit = su_set_default.upper_bound("cafeteria");
	check(*mit == *sit, color, ret);
	PRINT	<< color << *mit << TXT_NL << *sit << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Upper Bound Non-Existent Min Element ('aaaa')" << TXT_NL;
	mit = mi_set_default.upper_bound("aaaa");
	sit = su_set_default.upper_bound("aaaa");
	check(*mit == *sit, color, ret);
	PRINT	<< color << *mit << TXT_NL << *sit << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Upper Bound Non-Existent Max Element ('zzzz')" << TXT_NL;
	mit = mi_set_default.upper_bound("zzzz");
	sit = su_set_default.upper_bound("zzzz");
	check(*(--mit) == *(--sit), color, ret);
	PRINT	<< color << (isGreen(color) == true ? "END()" : "NOT END()!") << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Equal Range Existent Element ('norminette')" << TXT_NL;
	ft::pair<ft_set::iterator, ft_set::iterator> mi_range = mi_set_default.equal_range("norminette");
	std::pair<std_set::iterator, std_set::iterator> su_range = su_set_default.equal_range("norminette");
	check(*mi_range.first == *su_range.first & *mi_range.second == *su_range.second, color, ret);
	PRINT	<< color << *mi_range.first << TXT_NL << *mi_range.second
			<< TXT_NL << *su_range.first << TXT_NL << *su_range.second << END;
	}

	//INSERT
	PRINT	<< TXT_NL << TXT_BYEL << "INSERT TESTS" << TXT_NL
			<< TXT_TAB << "Insert Single Element and Access by std::string Reference" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_set_default.insert("santana");
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_default.insert("santana");
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	check(*mi_set_default.find("santana") == *su_set_default.find("santana"), color, ret);
	PRINT	<< color << *mi_set_default.find("santana") << TXT_NL
			<< *su_set_default.find("santana") << END;
	
	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('alex') with GOOD Hint (aka. constant time insert, aka. DE GUAYS INSERT)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_set_default.insert(mi_set_default.lower_bound("alex"), "alex");
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_default.insert(su_set_default.lower_bound("alex"), "alex");
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(*mi_set_default.find("alex") == *su_set_default.find("alex"), color, ret);
	PRINT	<< color << *mi_set_default.find("alex") << TXT_NL
			<< *su_set_default.find("alex") << END;
	//print_set_comp(mi_set_default, su_set_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('a') with GOOD Hint (aka. constant time insert, aka. DE GUAYS INSERT)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_set_default.insert(mi_set_default.lower_bound("a"), "a");
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_default.insert(su_set_default.lower_bound("a"), "a");
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(*mi_set_default.find("a") == *su_set_default.find("a"), color, ret);
	PRINT	<< color << *mi_set_default.find("a") << TXT_NL
			<< *su_set_default.find("a") << END;
	//print_set_comp(mi_set_default, su_set_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('rorozco') with BAD Hint (aka. logarithmic time + correction time insert, aka. GILIPOLLAS INSERT)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_set_default.insert(mi_set_default.begin(), "rorozco");
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_default.insert(su_set_default.begin(), "rorozco");
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(*mi_set_default.find("rorozco") == *su_set_default.find("rorozco"), color, ret);
	PRINT	<< color << *mi_set_default.find("rorozco") << TXT_NL
			<< *su_set_default.find("rorozco") << END;
	
	PRINT	<< TXT_TAB << TXT_BYEL << "Insertion Result for set_default: " << END;
	print_set_comp(mi_set_default, su_set_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert by Range to set_copy (from agua to tig, including alex, santana and rorozco, excluding a)" << END; //insert range from agua to tig, including alex, santana and rorozco
	//Start Exec Timer
	start_timer(&start);
	mi_set_copy.insert(++mi_set_default.begin(), --mi_set_default.end());
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_copy.insert(++su_set_default.begin(), --su_set_default.end());
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_set_comp(mi_set_copy, su_set_copy, color, ret);

	//ERASE
	PRINT	<< TXT_NL << TXT_BYEL << "ERASE TESTS" << TXT_NL
			<< TXT_TAB << "Erase by Position (begin())" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_set_default.erase(mi_set_default.begin()); //should erase 'a'
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_default.erase(su_set_default.begin()); //should erase 'a'
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_set_comp(mi_set_default, su_set_default, color, ret);

	PRINT << TXT_BYEL << TXT_TAB << "Erase by std::string ('marvin')" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_set_default.erase("marvin"); //should erase 'marvin'
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_default.erase("marvin"); //should erase 'marvin'
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_set_comp(mi_set_default, su_set_default, color, ret);
	{
	PRINT << TXT_BYEL << TXT_TAB << "Erase by Range ('norminette' to 'santana')" << END;
	ft_set::iterator mit = mi_set_default.find("norminette");
	ft_set::iterator mend = mi_set_default.find("santana");
	std_set::iterator sit = su_set_default.find("norminette");
	std_set::iterator send = su_set_default.find("santana");
	//Start Exec Timer
	start_timer(&start);
	mi_set_default.erase(mit, mend);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_default.erase(sit, send);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//Stop Exec Timer
	print_set_comp(mi_set_default, su_set_default, color, ret);
	}

	//SWAP
	PRINT << TXT_NL << TXT_BYEL << "SWAP TEST (set_default <-> set_range)" << END;
	{
	//Start Exec Timer
	start_timer(&start);
	swap(mi_set_default, mi_set_range);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	swap(su_set_default, su_set_range);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_set_comp(mi_set_default, su_set_default, color, ret);
	}

	//CLEAR
	PRINT << TXT_NL << TXT_BYEL << "CLEAR TEST (set_range)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_set_range.clear();
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_set_range.clear();
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_set_comp(mi_set_range, su_set_range, color, ret);

	//COMPARISON OBJECT
	//Both mi_set_default and su_set_default value comps should return same
	//comparison result. Comparison by default checks if lhs is less than rhs,
	//returning true or false as appropriate.
	PRINT	<< TXT_NL << TXT_BYEL << "COMP OBJECT TESTS"
			<< TXT_NL << TXT_TAB << "value_comp(set_default.begin(), set_default.begin())" << END;
	{
	size_t	msg_offset;
	bool	my_res = mi_set_default.value_comp()(*mi_set_default.begin(), *mi_set_default.begin());
	bool	stl_res = su_set_default.value_comp()(*su_set_default.begin(), *su_set_default.begin());
	compare_log(my_res == stl_res, ret, "result", msg_offset);
	PRINT	<< std::boolalpha << std::setw(msg_offset) << my_res << TXT_TAB << std::setw(msg_offset) << stl_res << END;
	}
	{
	size_t	msg_offset;
	bool	my_res = mi_set_default.value_comp()(*mi_set_default.begin(), *++mi_set_default.begin());
	bool	stl_res = su_set_default.value_comp()(*su_set_default.begin(), *++su_set_default.begin());
	compare_log(my_res == stl_res, ret, "result", msg_offset);
	PRINT	<< std::boolalpha << std::setw(msg_offset) << my_res << TXT_TAB << std::setw(msg_offset) << stl_res << END;
	}

	//RELATIONAL OPERATORS
	PRINT << TXT_NL;
	comparison_operator_log<std::set< std::string>, ft::set<std::string> >(su_set_default, su_set_copy, mi_set_default, mi_set_copy, ret);

	return (ret);
}
