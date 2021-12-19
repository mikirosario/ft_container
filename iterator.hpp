/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 02:07:52 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/12/19 01:51:19 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_H
# define ITERATOR_H

//DEBUG CODE
#include <iostream>
//DEBUG CODE

namespace ft
{
	template<typename T, typename Category>
	struct iterator_traits
	{
		//typedef std::random_access_iterator_tag			iterator_category;
		typedef Category								iterator_category;
		typedef std::ptrdiff_t							difference_type;
		typedef	T										value_type;
		typedef value_type *							pointer;
		typedef value_type &							reference;
	};
	//a copy of the base constructor is stored as current, and retrievable via the base getter
	template<class Iter>
	//could inherit from iterator_traits to define traits more locally??
	struct reverse_iterator {
		typedef typename Iter::iterator_category		iterator_category; //un poco cutre, pero... ;)
		//reverse_iterator(void) : current(Iter::_m_ptr) {}
		reverse_iterator(void) : current(Iter()) {}
		reverse_iterator(Iter const & normal_iterator) : current(normal_iterator) {}
		reverse_iterator(reverse_iterator const & src) : current(src.current) {}
		virtual ~reverse_iterator(void) {}

		//Conversion Overload, All Iterators Convertible to Const
		operator	reverse_iterator<typename Iter::const_it>() const {
			return (reverse_iterator<typename Iter::const_it>(current));
		}
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
			return (this->current.operator==(rhs.current));
		}
		bool	operator!=(reverse_iterator const & rhs) const {
			return (this->current.operator!=(rhs.current));
		}
		bool	operator<(reverse_iterator const & rhs) const {
			return (this->current.operator>(rhs.current));
		}
		bool	operator>(reverse_iterator const & rhs) const {
			return (this->current.operator<(rhs.current));
		}
		bool	operator<=(reverse_iterator const & rhs) const {
			return (this->current.operator>=(rhs.current));
		}
		bool	operator>=(reverse_iterator const & rhs) const {
			return (this->current.operator<=(rhs.current));
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
		//Reverse address subtraction
		typename Iter::difference_type		operator-(reverse_iterator const & rhs) const
		{
			return (rhs.base() - this->base());
		}
		//Referencing Operator Overloads
		typename Iter::reference	operator*(void) const {
			return (*(--Iter(this->current)));
		}
		typename Iter::pointer		operator->(void) const {
			return (&(*(--Iter(this->current))));
		}
		typename Iter::reference	operator[](typename Iter::difference_type const & n) const {
			return (current[-n-1]);
		}
		protected:
			Iter	current;
	};
};

#endif