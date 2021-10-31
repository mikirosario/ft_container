/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 02:07:52 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/10/31 23:38:33 by mikiencolor      ###   ########.fr       */
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

	//reverse_iterator inherits from normal iterator (which inherits from iterator_traits)
	//a copy of the base constructor is stored as current, and retrievable via the base getter
	template<class Iter>
	struct reverse_iterator {
		reverse_iterator(void) : current(Iter::_m_ptr) {}
		reverse_iterator(Iter const & normal_iterator) : current(normal_iterator) {}
		reverse_iterator(reverse_iterator const & src) : current(src.current) {}
		reverse_iterator & operator=(reverse_iterator const & src) {
			current = src.current;
			return (*this);
		}
		Iter	base(void) const {
			return (this->current);
		}
		typename Iter::reference	operator*(void) const {
			return (*(this->current - 1));
			//return (*this->Iter::operator-(1)); //para qué hacer copias de current sin necesidad?? :P
		}
		typename Iter::pointer		operator->(void) const {
			return (&(*this->current - 1));
			//return (&(*this->Iter::operator-(1)));
		}
		typename Iter::reference	operator[](typename Iter::difference_type n) const {
			return (current[-n-1]); //!?
		}
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
		protected:
			Iter	current;
	};
};

#endif