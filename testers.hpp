/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:46:37 by miki              #+#    #+#             */
/*   Updated: 2022/01/17 21:46:43 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTERS_H
# define TESTERS_H

#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include "ansi_codes.hpp"
#include "type_traits.hpp"

#define PRINT std::cout
#define ALN std::left << std::setw(30)
#define END TXT_RST << std::endl
#define SET std::setw(9) << color
#define TEST_NUM 5

/* NANOSECOND EXECUTION TIMER */
void	start_timer(__uint64_t * start);
__int64_t	stop_timer_nanosec(__uint64_t * start);
void	check_exec_time(__int64_t & ft_time, __int64_t & stl_time, bool & ret);

/* COMPARES */
void	check(bool result, char const *& color, bool & ret);
void	compare_log(bool comp, bool & ret, std::string const & msg, size_t & msg_offset, size_t const & minw = 0);
bool	isGreen(std::string const color);

/* TEMPLATES */
/*
** 42 subject requires templates to be defined in their hpp, no include trickery
** to get around it. Sorry.
*/

/*
** This is the same as the == comparison operator overload for a container,
** except it compares two different container types: STD_Container and
** MY_Container. This is used as the predicate for the check function in my
** testing routine to confirm whether std:: and ft:: versions of the same
** container type behave equally under the same conditions. If sizes and
** ranges are equal, it returns true, otherwise it returns false.
**
** The MY_Container has_iterator thing is just a SFINAE trick to stop the
** compiler from sending non-iterable-container types in here where we clearly
** only want iterable containers. :P
**
*/
template<class STD_Container, class MY_Container >
typename ft::enable_if<ft::has_iterator<MY_Container>::value, bool>::type operator==(STD_Container const & lhs, MY_Container const & rhs)
{
	return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

/*
** This is a modification of my original check function. Here, the predicate for
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

/*
** This function compares all possible relational operator results for STD and
** FT containers of a given type and prints the results, setting the ret value
** to false if any check returns an unequal result. Note, relational operators
** were deprecated on std::map, but we are meant to imitate the C++98 version
** when they were still around, so...
*/
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
void	print_set_comp(MyMap const & my_map, StdMap const & std_map, char const *& color, bool & ret)
{
	typename MyMap::const_iterator mit;
	typename MyMap::const_iterator mend;
	typename StdMap::const_iterator sit;
	typename StdMap::const_iterator send;
	for (mit = my_map.begin(), mend = my_map.end(), sit = std_map.begin(), send = std_map.end(); sit != send; ++mit, ++sit)
		{
			check(*mit == *sit, color, ret);
			PRINT << color << "MY  > " << *mit << TXT_NL << "STL > " << *sit << END;
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

template<typename MyMap, typename StdMap>
void	print_set_rev_comp(MyMap const & my_map, StdMap const & std_map, char const *& color, bool & ret)
{
	typename MyMap::const_reverse_iterator mit;
	typename MyMap::const_reverse_iterator mend;
	typename StdMap::const_reverse_iterator sit;
	typename StdMap::const_reverse_iterator send;

	for (mit = my_map.rbegin(), mend = my_map.rend(), sit = std_map.rbegin(), send = std_map.rend(); sit != send; ++mit, ++sit)
		{
			check(*mit == *sit, color, ret);
			PRINT << color << "MY  > " << *mit << TXT_NL << "STL > " << *sit << END;
		}
}

/* TESTS */
bool 	iterator_tests(void);
bool	my_veritable_vector(void);
bool	my_magnificent_map(void);
bool	my_stupendous_stack(void);
bool	my_superlative_set(void);

#endif
