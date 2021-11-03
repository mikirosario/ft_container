/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:01:02 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/03 21:41:34 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

namespace ft
{
	template<typename T1, typename T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;
		T1			first;
		T2			second;
		pair(void) : first(), second() {}
		pair(T1 const & first_src, T2 const & second_src) : first(first_src), second(second_src) {}
		template<typename U1, typename U2>
		pair(pair<U1, U2> const &	pair_src) : first(pair_src.first), second(pair_src.second) {}
	};

	template<typename T1, typename T2>
	pair<T1, T2>	make_pair(T1 x, T1 y)
	{
		return (pair<T1, T2>(x, y));
	}
};

#endif