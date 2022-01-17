/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_magnificent_map.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:20:24 by miki              #+#    #+#             */
/*   Updated: 2022/01/17 19:17:04 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../testers.hpp"
#include "../map.hpp"

/*
** This test compares my map with the STL map under the same conditions using
** std::string as key and value.
**
** Conditions are printed in yellow before each test and results are printed in
** red (if unequal) and green (if equal) after the test. The function returns
** true if all tests are passed and false otherwise.
**
** Certain execution operations are also timed. For timed operations, the timer
** results are printed in red if my map took more than 20 times what STL
** map took to perform the same operation, otherwise they are printed in
** green. Timed operations results also affect the final result.
**
** The max size comparison is done but doesn't affect the result. My max size is
** smaller than STL max size as my map is a bit less efficient and takes up more
** space per element. It is not required by the subject that they be equal and
** mine is still within the same order of magnitude (1e17 - 1e18, depending on
** machine).
**
** Reverse iterators are tested separately. Normal iterators are used throughout
** the test to print results on the screen and send them to the check functions
** for comparison and verification, so they are considered tested there.
**
** The double free test is only done on my version of the map. I trust STL
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
bool	my_magnificent_map(std::map<std::string, std::string> const & seed_map)
{
	char const *	color = TXT_BGRN;
	bool			ret = true;
	uint64_t		start;
	int64_t			ft_time;
	int64_t			stl_time;

	typedef ft::map<std::string, std::string>	ft_map;
	typedef std::map<std::string, std::string>	std_map;

	//DEFAULT CONSTRUCTOR
	PRINT	<< TXT_BYEL << "DEFAULT INSTANTIATION TEST" << END;
	ft_map		mi_map_default;
	std_map		su_map_default;
	print_map_comp(mi_map_default, su_map_default, color, ret);
	PRINT	<< ((isGreen(color) == true) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;

	PRINT	<< TXT_NL << TXT_BYEL << "RANGE CONSTRUCTION TESTS" << END;

	//RANGE CONSTRUCTOR
	start_timer(&start);
	ft_map		mi_map_range(seed_map.begin(), seed_map.end());
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std_map		su_map_range(seed_map.begin(), seed_map.end());
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	print_map_comp<ft_map, std_map >(mi_map_range, su_map_range, color, ret);

	//COPY CONSTRUCTOR
	PRINT	<< TXT_NL << TXT_BYEL << "COPY CONSTRUCTION TESTS" << END;
	start_timer(&start);
	ft_map		mi_map_copy(mi_map_range);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std_map		su_map_copy(su_map_range);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	print_map_comp<ft_map, std_map >(mi_map_copy, su_map_copy, color, ret);

	//ASSIGNMENT OVERLOAD
	PRINT	<< TXT_NL << TXT_BYEL << "ASSIGNMENT OVERLOAD TESTS" << END;
	start_timer(&start);
	mi_map_default = mi_map_copy;
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default = su_map_copy;
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	print_map_comp<ft_map, std_map>(mi_map_default, su_map_default, color, ret);

	//REVERSE ITERATORS
	PRINT	<< TXT_NL << TXT_BYEL << "REVERSE ITERATOR TESTS" << END;
	PRINT	<< TXT_TAB << TXT_BYEL << "Normal Person Reverse Iterator Test" << END;
	print_map_rev_comp<ft_map, std_map>(mi_map_default, su_map_default, color, ret);
	PRINT	<< TXT_TAB << TXT_BYEL << "Insane Person Who Dereferences Reverse End Iterator Test (Consted and Non-Consted)" << END;
	//This just tests that the end iterator std::string is dereferenceable without segfault; there is no equality guarantee.
	//For whatever reason, STD seems to make this possible. :P
	//Update! It's not STD, it's fooking Mac!!!! This code crashed my Linux-compiled map, as it rightly should!!! xD
	ft_map::reverse_iterator mrend = mi_map_default.rend();
	ft_map::const_reverse_iterator cmrend = mi_map_default.rend();
	//std_map::reverse_iterator srend = su_map_default.rend();
	//std_map::const_reverse_iterator csrend = su_map_default.rend();
	PRINT	<< TXT_NL << mrend->second << END;
	//PRINT	<< TXT_NL << srend->second << END;
	//PRINT	<< TXT_NL << csrend->second << END;
	PRINT	<< TXT_NL << cmrend->second << END;
	PRINT	<< TXT_TAB << TXT_BGRN << "OK" << END;
	PRINT	<< TXT_NL << TXT_BYEL << "THE EVIL DOUBLE-FREE TEST" << END; //Ensure erasing and clearing doesn't lead to any double-free attempts.
	ft_map	mi_map_dblfree;
	mi_map_dblfree.insert(ft::make_pair("testing", "123"));
	mi_map_dblfree.erase("testing");
	mi_map_dblfree.clear();
	check(mi_map_dblfree.size() == 0 & mi_map_dblfree.empty() == true, color, ret);
	PRINT	<< TXT_TAB << color << (color == std::string(TXT_BGRN) ? "OK" : "KO") << END;

	//CAPACITY
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
	//ACCESS
	PRINT	<< TXT_NL << TXT_BYEL << "ACCESS ELEMENT BY std::string REFERENCE TEST" << TXT_NL
			<< TXT_TAB << "Find Reference to Existent Element ('norminette')" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default["norminette"];
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default["norminette"];
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mi_map_default["norminette"] == su_map_default["norminette"], color, ret);
	PRINT	<< color << mi_map_default["norminette"] << TXT_NL
			<< su_map_default["norminette"] << END;
	PRINT	<< TXT_BYEL << TXT_TAB << "Insert New std::string and Default-Instantiated std::string ('aguafiestas')" << TXT_NL;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default["aguafiestas"];
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default["aguafiestas"];
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mi_map_default["aguafiestas"] == su_map_default["aguafiestas"], color, ret);
			PRINT	<< (isGreen(color) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	PRINT	<< color << mi_map_default["aguafiestas"] << TXT_NL
			<< su_map_default["aguafiestas"] << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Insert std::string by std::string Reference ('miyamoto')" << TXT_NL;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default["miyamoto"] = "MIYAMOTO: \t\t\tEminencia de los videojuegos que descubrió que la constante gravitacional está más guapa como variable.";
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default["miyamoto"] = "MIYAMOTO: \t\t\tEminencia de los videojuegos que descubrió que la constante gravitacional está más guapa como variable.";
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mi_map_default["miyamoto"] == su_map_default["miyamoto"], color, ret);
	PRINT	<< (isGreen(color) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	PRINT	<< color << mi_map_default["miyamoto"] << TXT_NL
			<< su_map_default["miyamoto"] << END;

	PRINT	<< TXT_BYEL << TXT_TAB << "Replace std::string by std::string Reference ('aguafiestas')" << TXT_NL;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default["aguafiestas"] = "AGUAFIESTAS: \t\t\tSinónimo de Marvin (véase 'marvin').";
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default["aguafiestas"] = "AGUAFIESTAS: \t\t\tSinónimo de Marvin (véase 'marvin').";
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mi_map_default["aguafiestas"] == su_map_default["aguafiestas"], color, ret);
	PRINT	<< (isGreen(color) ? TXT_BGRN "OK" : TXT_BRED "KO") << END;
	PRINT	<< color << mi_map_default["aguafiestas"] << TXT_NL
			<< su_map_default["aguafiestas"] << END;
	
	PRINT	<< TXT_BYEL << TXT_TAB << "Result:" << END;
	print_map_comp(mi_map_default, su_map_default, color, ret);

	//OPERATIONS
	PRINT	<< TXT_NL << TXT_BYEL << "OPERATIONS TESTS" << TXT_NL
			<< TXT_TAB << "Find by std::string ('marvin')" << END;
	{
	//Start Exec Timer
	start_timer(&start);
	ft_map::iterator mit = mi_map_default.find("marvin");
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std_map::iterator sit = su_map_default.find("marvin");
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mit->first == sit->first & mit->second == sit->second, color, ret);
	PRINT	<< color << mit->second << TXT_NL
			<< sit->second << END;
	}
	PRINT	<< TXT_TAB << TXT_BYEL << "Find by std::string Non-Existent ('marvine')" << END; //must return end()
	{
	//Start Exec Timer
	start_timer(&start);
	ft_map::iterator mit = mi_map_default.find("marvine");
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	std_map::iterator sit = su_map_default.find("marvine");
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
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
	ft_map::iterator mit = mi_map_default.lower_bound("marvin");
	std_map::iterator sit = su_map_default.lower_bound("marvin");
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
	ft::pair<ft_map::iterator, ft_map::iterator> mi_range = mi_map_default.equal_range("norminette");
	std::pair<std_map::iterator, std_map::iterator> su_range = su_map_default.equal_range("norminette");
	check(mi_range.first->first == su_range.first->first
		& mi_range.first->second == su_range.first->second
		& mi_range.second->first == su_range.second->first
		& mi_range.second->second == su_range.second->second
		, color, ret);
	PRINT	<< color << mi_range.first->second << TXT_NL << mi_range.second->second
			<< TXT_NL << su_range.first->second << TXT_NL << su_range.second->second << END;
	}

	//INSERT
	PRINT	<< TXT_NL << TXT_BYEL << "INSERT TESTS" << TXT_NL
			<< TXT_TAB << "Insert Single Element and Access by std::string Reference" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default.insert(ft::pair<std::string const, std::string>("santana", "SANTANA: \t\t\t\tCanario estepario."));
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default.insert(std::pair<std::string const, std::string>("santana", "SANTANA: \t\t\t\tCanario estepario."));
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	check(mi_map_default["santana"] == su_map_default["santana"], color, ret);
	PRINT	<< color << mi_map_default["santana"] << TXT_NL
			<< su_map_default["santana"] << END;
	
	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('alex') with GOOD Hint (aka. constant time insert, aka. DE GUAYS INSERT)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default.insert(mi_map_default.lower_bound("alex"), ft::make_pair<std::string, std::string>("alex", "ALEX: \t\t\t\tCien por cien NO FAKE!"));
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default.insert(su_map_default.lower_bound("alex"), std::make_pair<std::string, std::string>("alex", "ALEX: \t\t\t\tCien por cien NO FAKE!"));
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mi_map_default["alex"] == su_map_default["alex"], color, ret);
	PRINT	<< color << mi_map_default["alex"] << TXT_NL
			<< su_map_default["alex"] << END;
	//print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('a') with GOOD Hint (aka. constant time insert, aka. DE GUAYS INSERT)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default.insert(mi_map_default.lower_bound("a"), ft::make_pair<std::string, std::string>("a", "A: \t\t\t\tPrimera letra del alafabeto latino."));
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default.insert(su_map_default.lower_bound("a"), std::make_pair<std::string, std::string>("a", "A: \t\t\t\tPrimera letra del alafabeto latino."));
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mi_map_default["a"] == su_map_default["a"], color, ret);
	PRINT	<< color << mi_map_default["a"] << TXT_NL
			<< su_map_default["a"] << END;
	//print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert Single Element ('rorozco') with BAD Hint (aka. logarithmic time + correction time insert, aka. GILIPOLLAS INSERT)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default.insert(mi_map_default.begin(), ft::make_pair<std::string, std::string>("rorozco", "ROROZCO: \t\t\t\tDueña de la Playstation 4."));
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default.insert(su_map_default.begin(), std::make_pair<std::string, std::string>("rorozco", "ROROZCO: \t\t\t\tDueña de la Playstation 4."));
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	check(mi_map_default["rorozco"] == su_map_default["rorozco"], color, ret);
	PRINT	<< color << mi_map_default["rorozco"] << TXT_NL
			<< su_map_default["rorozco"] << END;
	
	PRINT	<< TXT_TAB << TXT_BYEL << "Insertion Result for map_default: " << END;
	print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT	<< TXT_TAB << TXT_BYEL << "Insert by Range to map_copy (from agua to tig, including alex, santana and rorozco, excluding a)" << END; //insert range from agua to tig, including alex, santana and rorozco
	//Start Exec Timer
	start_timer(&start);
	mi_map_copy.insert(++mi_map_default.begin(), --mi_map_default.end());
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_copy.insert(++su_map_default.begin(), --su_map_default.end());
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_map_comp(mi_map_copy, su_map_copy, color, ret);

	//ERASE
	PRINT	<< TXT_NL << TXT_BYEL << "ERASE TESTS" << TXT_NL
			<< TXT_TAB << "Erase by Position (begin())" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default.erase(mi_map_default.begin()); //should erase 'a'
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default.erase(su_map_default.begin()); //should erase 'a'
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_map_comp(mi_map_default, su_map_default, color, ret);

	PRINT << TXT_BYEL << TXT_TAB << "Erase by std::string ('marvin')" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_map_default.erase("marvin"); //should erase 'marvin'
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default.erase("marvin"); //should erase 'marvin'
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_map_comp(mi_map_default, su_map_default, color, ret);
	{
	PRINT << TXT_BYEL << TXT_TAB << "Erase by Range ('norminette' to 'santana')" << END;
	ft_map::iterator mit = mi_map_default.find("norminette");
	ft_map::iterator mend = mi_map_default.find("santana");
	std_map::iterator sit = su_map_default.find("norminette");
	std_map::iterator send = su_map_default.find("santana");
	//Start Exec Timer
	start_timer(&start);
	mi_map_default.erase(mit, mend);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_default.erase(sit, send);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//Stop Exec Timer
	print_map_comp(mi_map_default, su_map_default, color, ret);
	}

	//SWAP
	PRINT << TXT_NL << TXT_BYEL << "SWAP TEST (map_default <-> map_range)" << END;
	{
	//Start Exec Timer
	start_timer(&start);
	swap(mi_map_default, mi_map_range);
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	swap(su_map_default, su_map_range);
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_map_comp(mi_map_default, su_map_default, color, ret);
	}

	//CLEAR
	PRINT << TXT_NL << TXT_BYEL << "CLEAR TEST (map_range)" << END;
	//Start Exec Timer
	start_timer(&start);
	mi_map_range.clear();
	ft_time = stop_timer_nanosec(&start);
	start_timer(&start);
	su_map_range.clear();
	stl_time = stop_timer_nanosec(&start);
	check_exec_time(ft_time, stl_time, ret);
	//End Exec Timer
	print_map_comp(mi_map_range, su_map_range, color, ret);

	//COMPARISON OBJECT
	//Both mi_map_default and su_map_default value comps should return same
	//comparison result. Comparison by default checks if lhs is less than rhs,
	//returning true or false as appropriate.
	PRINT	<< TXT_NL << TXT_BYEL << "COMP OBJECT TESTS"
			<< TXT_NL << TXT_TAB << "value_comp(map_default.begin(), map_default.begin())" << END;
	{
	size_t	msg_offset;
	bool	my_res = mi_map_default.value_comp()(*mi_map_default.begin(), *mi_map_default.begin());
	bool	stl_res = su_map_default.value_comp()(*su_map_default.begin(), *su_map_default.begin());
	compare_log(my_res == stl_res, ret, "result", msg_offset);
	PRINT	<< std::boolalpha << std::setw(msg_offset) << my_res << TXT_TAB << std::setw(msg_offset) << stl_res << END;
	}
	{
	size_t	msg_offset;
	bool	my_res = mi_map_default.value_comp()(*mi_map_default.begin(), *++mi_map_default.begin());
	bool	stl_res = su_map_default.value_comp()(*su_map_default.begin(), *++su_map_default.begin());
	compare_log(my_res == stl_res, ret, "result", msg_offset);
	PRINT	<< std::boolalpha << std::setw(msg_offset) << my_res << TXT_TAB << std::setw(msg_offset) << stl_res << END;
	}

	//RELATIONAL OPERATORS
	PRINT << TXT_NL;
	comparison_operator_log<std::map< std::string, std::string>, ft::map<std::string, std::string> >(su_map_default, su_map_copy, mi_map_default, mi_map_copy, ret);

	return (ret);
}