/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 02:07:52 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/02 13:16:06 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_H
# define ITERATOR_H

//DEBUG CODE
#include <iostream>
//DEBUG CODE

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
	//a copy of the base constructor is stored as current, and retrievable via the base getter
	template<class Iter>
	//could inherit from iterator_traits to define traits more locally??
	struct reverse_iterator {
		reverse_iterator(void) : current(Iter::_m_ptr) {}
		reverse_iterator(Iter const & normal_iterator) : current(normal_iterator) {}
		reverse_iterator(reverse_iterator const & src) : current(src.current) {}
		//Base Iterator Getter
		Iter	base(void) const {
			return (this->current);
		}
		//Reverse Assignment Operator Overload
		reverse_iterator & operator=(reverse_iterator const & src) {
			current = src.current;
			return (*this);
		}
		//Relational Operator Overloads
		bool	operator==(reverse_iterator const & rhs) const {
			return (this->current.operator==(rhs.current - 1));
		}
		bool	operator!=(reverse_iterator const & rhs) const {
			return (this->current.operator!=(rhs.current - 1));
		}
		bool	operator<(reverse_iterator const & rhs) const {
			return (this->current.operator>(rhs.current - 1));
		}
		bool	operator>(reverse_iterator const & rhs) const {
			return (this->current.operator<(rhs.current - 1));
		}
		bool	operator<=(reverse_iterator const & rhs) const {
			return (this->current.operator>=(rhs.current - 1));
		}
		bool	operator>=(reverse_iterator const & rhs) const {
			return (this->current.operator<=(rhs.current - 1));
		}
		//Arithmetic Operator Overloads
		reverse_iterator &			operator++() {
			this->current.operator--();
			return (*this);
		}
		reverse_iterator			operator++(int) {
			reverse_iterator	ret(this->current);
			this->current.operator--();
			return (ret);
		}
		reverse_iterator &			operator--() {
			this->current.operator++();
			return (*this);
		}
		reverse_iterator			operator--(int) {
			reverse_iterator	ret(this->current);
			this->current.operator++();
			return (ret);
		}
		reverse_iterator			operator+(typename Iter::difference_type const n) const
		{
			return (reverse_iterator(this->current - n));
		}
		reverse_iterator			operator-(typename Iter::difference_type const n) const
		{
			return (reverse_iterator(this->current + n));
		}
		reverse_iterator &			operator+=(typename Iter::difference_type const n) {
			this->current.operator-=(n);
			return(*this);
		}
		reverse_iterator &			operator-=(typename Iter::difference_type const n) {
			this->current.operator+=(n);
			return(*this);
		}
		//Referencing Operator Overloads
		typename Iter::reference	operator*(void) const {
			return (*(this->current - 1));
		}
		typename Iter::pointer		operator->(void) const {
			return (&(*this->current - 1));
		}
		typename Iter::reference	operator[](typename Iter::difference_type const & n) const {
			return (current[-n-1]);
		}
		protected:
			Iter	current;
	};
};

#endif