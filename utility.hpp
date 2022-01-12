/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:01:02 by mikiencolor       #+#    #+#             */
/*   Updated: 2022/01/12 01:42:39 by mrosario         ###   ########.fr       */
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

	/* REMOVE CONST */
	/*
	** This function uses type deduction and const_cast to remove the constness
	** of a pointer.
	**
	** The ft::set made this necessary for me to make it work with my bintree.
	** To have the value in my set's bintree consted, as required by set, I
	** explicitly const the type when defining the tree. This consts all the
	** typedefs in the tree that refer to the type and consts the type in the
	** tree node.
	**
	** Unfortunately, there is an exceptional case where we HAVE to violate the
	** constness: when erasing a node from a binary tree, sometimes we need to
	** rebalance the tree. Tree node addresses are fixed, so this means data
	** MUST be copied from one node to another to enable rebalancing. This only
	** happens at the implementation level, not at the user level.
	**
	** Exceptionally, to perform those copies, we need to ignore the constness.
	**
	** A const_cast from inside the tree won't work, because inside the tree the
	** type is const by definition, so we have no reference to the unconsted
	** type. However, by implicitly calling our remove_const here, I have the
	** compiler use type deduction to deduce the unconsted type of the pointer,
	** so now I can return an unconsted pointer to my rebalancing function. :)
	*/
	template <typename T>
	T *		remove_const(T const * value)
	{
		return (const_cast<T *>(value));
	}
};

#endif