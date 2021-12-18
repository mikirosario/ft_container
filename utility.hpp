/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:01:02 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/12/18 13:24:05 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

#include <functional>

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
		pair(pair<U1, U2> const & pair_src) : first(pair_src.first), second(pair_src.second) {}
	};

	template<typename T1, typename T2>
	pair<T1, T2>	make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template<typename T1, typename T2>
	bool	operator==(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
		return (lhs.first == rhs.first & lhs.second == rhs.second);
	}

	template<typename T1, typename T2>
	bool	operator!=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
		return (!operator==(lhs, rhs)); //a!=b == !a==b
	}

	template<typename T1, typename T2>
	bool	operator<(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
		bool ret;
		if (lhs.first < rhs.first)
			ret = true;
		else if (rhs.first < lhs.first)
			ret = false;
		else if (lhs.second < rhs.second)
			ret = true;
		else
			ret = false;
		return (ret);
	}

	template<typename T1, typename T2>
	bool	operator>(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
		return (operator<(rhs, lhs)); //a>b == b<a
	}

	template<typename T1, typename T2>
	bool	operator<=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
		return (!operator<(rhs, lhs)); //a<=b == !b<a
	}

	template<typename T1, typename T2>
	bool	operator>=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs) {
		return (!operator<(lhs, rhs)); //a>=b == !a<b
	}

	template<typename T>
	struct less
	{
		bool	operator()(T const & lhs, T const & rhs) const {
			return (lhs < rhs);
		}
	};
};

#endif