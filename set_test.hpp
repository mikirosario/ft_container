/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:15:49 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/21 10:23:39 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"
#include <set>
#include "set.hpp"

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

template <typename Set_T>
void	set_test(void)
{
	typedef	typename Set_T::value_type	Pair;
	std::set<std::string>	seed_set;

	make_seed_set(seed_set);

	//DEFAULT CONSTRUCTOR
	PRINT	<< TXT_BYEL << "DEFAULT INSTANTIATION TEST" << END;
	Set_T		set_default;

	PRINT	<< TXT_NL << TXT_BYEL << "RANGE CONSTRUCTION TESTS" << END;
	//RANGE CONSTRUCTOR
	Set_T		set_range(seed_set.begin(), seed_set.end());

	//COPY CONSTRUCTOR
	PRINT	<< TXT_NL << TXT_BYEL << "COPY CONSTRUCTION TESTS" << END;
	Set_T		set_copy(set_range);

	//ASSIGNMENT OVERLOAD
	PRINT	<< TXT_NL << TXT_BYEL << "ASSIGNMENT OVERLOAD TESTS" << END;
	set_default = set_copy;

	//ITERATORS
	typename Set_T::iterator it = set_default.begin();
	typename Set_T::const_iterator end = set_default.end();
	for ( ; it != end; ++it)
		PRINT << *it << TXT_NL;

	//REVERSE ITERATORS
	PRINT	<< TXT_NL << TXT_BYEL << "REVERSE ITERATOR TESTS" << END;
	typename Set_T::reverse_iterator rit = set_default.rbegin();
	typename Set_T::const_reverse_iterator rend = set_default.rend();	
	for ( ; rit != rend; ++rit)
		PRINT << *rit << TXT_NL;

	//CAPACITY
	PRINT	<< TXT_NL << TXT_BYEL << "CAPACITY TESTS" << END;
	PRINT	<< set_default.empty() << TXT_NL;
	PRINT	<< set_default.size() << TXT_NL;

	//OPERATIONS
	PRINT	<< TXT_NL << TXT_BYEL << "OPERATIONS TESTS" << END;
	{
		typename Set_T::iterator mit = set_default.find("marvin");
		PRINT	<< *mit << TXT_NL;
	}
	{
		typename Set_T::iterator mit = set_default.find("marvine");
		PRINT	<< (mit == set_default.end()) << TXT_NL;
	}

	PRINT	<< set_default.count("agua") << TXT_NL;
	PRINT	<< set_default.count("santana") << TXT_NL;
	{

	typename Set_T::iterator mit = set_default.lower_bound("marvin");
	PRINT	<< *mit << TXT_NL;

	mit = set_default.lower_bound("marvinovich");
	PRINT	<< *mit << TXT_NL;

	mit = set_default.lower_bound("aaaa");
	PRINT	<< *mit << TXT_NL;

	mit = set_default.lower_bound("zzzz");
	PRINT	<< (mit == set_default.end()) << TXT_NL;

	mit = set_default.upper_bound("cafe");
	PRINT	<< *mit << TXT_NL;

	mit = set_default.upper_bound("cafeteria");
	PRINT	<< *mit << TXT_NL;

	mit = set_default.upper_bound("aaaa");
	PRINT	<< *mit << TXT_NL;

	mit = set_default.upper_bound("zzzz");
	PRINT	<< (mit == set_default.end()) << TXT_NL;

	PRINT	<< *set_default.equal_range("norminette").first << TXT_NL << *set_default.equal_range("norminette").second << TXT_NL;
	}

	//INSERT
	PRINT	<< TXT_NL << TXT_BYEL << "INSERT TESTS" << END;
	set_default.insert(Pair("santana", "SANTANA: \t\t\t\tCanario estepario."));
	set_default.insert(set_default.lower_bound("alex"), Pair("alex", "ALEX: \t\t\t\tCien por cien NO FAKE!"));
	set_default.insert(set_default.lower_bound("a"), Pair("a", "A: \t\t\t\tPrimera letra del alafabeto latino."));
	set_default.insert(set_default.begin(), Pair("rorozco", "ROROZCO: \t\t\t\tDueña de la Playstation 4."));
	set_copy.insert(++set_default.begin(), --set_default.end());

	//ERASE
	PRINT	<< TXT_NL << TXT_BYEL << "ERASE TESTS" << TXT_NL;
	set_default.erase(set_default.begin()); //should erase 'a'
	set_default.erase("marvin"); //should erase 'marvin'
	{
		typename Set_T::iterator mit = set_default.find("norminette");
		typename Set_T::iterator mend = set_default.find("santana");
		set_default.erase(mit, mend); //should erase everything from norminette to before santana
	}

	//SWAP
	PRINT << TXT_NL << TXT_BYEL << "SWAP TEST (set_default <-> set_range)" << END;
	swap(set_default, set_range);

	//CLEAR
	PRINT << TXT_NL << TXT_BYEL << "CLEAR TEST (set_range)" << END;
	set_range.clear();

	//COMPARISON OBJECT
	PRINT	<< TXT_NL << TXT_BYEL << "COMP OBJECT TESTS" << END;
	{
		bool	my_res = set_default.value_comp()(*set_default.begin(), *set_default.begin());
		PRINT	<< std::boolalpha << my_res << END;
	}
	{
		bool	my_res = set_default.value_comp()(*set_default.begin(), *++set_default.begin());
		PRINT	<< std::boolalpha << my_res << END;
	}
}
