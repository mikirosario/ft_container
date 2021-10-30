/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 02:07:52 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/10/31 00:01:10 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template<typename T>
	struct iterator_traits
	{
		typedef std::random_access_iterator_tag			iterator_category;
		typedef std::ptrdiff_t							difference_type;
		typedef	T										value_type;
		typedef value_type *							pointer;
		typedef value_type &							reference;
	};

}
