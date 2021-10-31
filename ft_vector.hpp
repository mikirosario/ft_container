/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:15:40 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/10/31 10:11:43 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

#include <memory>
#include "iterator.hpp"

//DEBUG CODE
#include <iostream>
//DEBUG CODE

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		private:
			template<typename iT>
			struct Iterator : public ft::iterator_traits<iT>
			{

				//Constructible
				Iterator(typename Iterator::pointer ptr) : _m_ptr(ptr) {};

				//Comparison Operator Overloads
				bool	operator==(Iterator const & rhs) const {
					return (this->_m_ptr == rhs._m_ptr);
				}
				bool	operator!=(Iterator const & rhs) const {
					return (!operator==(rhs));
				}
				bool	operator>(Iterator const & rhs) const {
					return (this->_m_ptr > rhs._m_ptr);
				}
				bool	operator<(Iterator const & rhs) const {
					return (!operator>(rhs));
				}
				bool	operator>=(Iterator const & rhs) const {
					return (operator>(rhs) | operator==(rhs));
				}
				bool	operator<=(Iterator const & rhs) const {
					return (operator<(rhs) | operator==(rhs));
				}
				//Assignment Operator Overload
				Iterator &	operator=(Iterator const & rhs) {
					this->_m_ptr = rhs->_m_ptr;
					return (*this);
				}
				//Arithmetic Operator Overloads
				Iterator &	operator++(void) {
					++this->_m_ptr;
					return (*this);
				}
				Iterator	operator++(int) {
					Iterator	ret(this->_m_ptr);
					++this->_m_ptr;
					return (ret);
				}
				Iterator & operator--(void) {
					--this->_m_ptr;
					return (*this);
				}
				Iterator	operator--(int) {
					Iterator	ret(this->_m_ptr);
					--this->_m_ptr;
					return (ret);
				}
				Iterator &	operator+=(int inc) {
					this->_m_ptr += inc;
					return (*this);
				}
				Iterator &	operator-=(int dec) {
					this->_m_ptr -= dec;
					return (*this);
				}
				Iterator	operator+(int const & rhs) const {
					Iterator	sum(*this);
					return (sum += rhs);
				}
				Iterator	operator-(int const & rhs) const {
					Iterator	dif(*this);
					return (dif -= rhs);
				}
				Iterator::difference_type	operator-(Iterator const & rhs) const {
					return (this->_m_ptr - rhs._m_ptr);
				}
				//Referencing Operators
				//The const references/pointers will be consted by the vector
				//instantiation for const_iterators, which uses a const T. 
				//The function is always consted, as it itself doesn't modify
				//any class member.
				typename Iterator::reference	operator*(void) const {
					return(*this->_m_ptr);
				}
				typename Iterator::reference	operator[](int pos) const {
					return (*(this->_m_ptr + pos));
				}
				typename Iterator::pointer		operator->(void) const {
					return (this->_m_ptr);
				}
				private:
					typename Iterator::pointer	_m_ptr;
			};

		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef value_type*									pointer;
			typedef const value_type*							const_pointer;
			typedef Iterator<T>									iterator;
			typedef Iterator<const T>							const_iterator; //Iterator formed with const T, so its value_type, pointers to value_type, references to value_type, etc, also all refer to const value

	};
};

#endif