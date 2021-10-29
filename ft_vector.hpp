/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:15:40 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/10/29 19:00:28 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

#include <memory>

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		private:

		public:
				typedef T											value_type;
				typedef Alloc										allocator_type;
				typedef std::size_t									size_type;
				typedef std::ptrdiff_t								difference_type;
				typedef value_type&									reference;
				typedef const value_type&							const_reference;
				typedef value_type*									pointer;
				typedef const value_type*							const_pointer;

				struct Iterator
				{
					//Iterator Tags
					typedef std::random_access_iterator_tag			iterator_category;
					typedef std::ptrdiff_t							difference_type;
					typedef	vector::value_type						value_type;
					typedef vector::pointer							pointer;
					typedef vector::reference						reference;
					//Constructible
					Iterator(pointer ptr) : _m_ptr(ptr) {};

					//Comparison Operator Overloads
					bool	operator==(const Iterator & rhs) const {
						return (this->_m_ptr == rhs._m_ptr);
					}

					bool	operator!=(const Iterator & rhs) const {
						return (!operator==(rhs));
					}

					bool	operator>(const Iterator & rhs) const {
						return (this->_m_ptr > rhs._m_ptr);
					}

					bool	operator<(const Iterator & rhs) const {
						return (!operator>(rhs));
					}

					bool	operator >=(const Iterator & rhs) const {
						return (operator>(rhs) | operator==(rhs));
					}

					bool	operator <=(const Iterator & rhs) const {
						return (operator<(rhs) | operator==(rhs));
					}

					private:
						pointer	_m_ptr;

				};
	};
};

#endif