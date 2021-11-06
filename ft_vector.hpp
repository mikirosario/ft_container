/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:15:40 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/06 23:52:03 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

#include <memory>
#include <algorithm>
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
				Iterator(void) : _m_ptr(NULL) {}
				explicit Iterator(typename Iterator::pointer ptr) : _m_ptr(ptr) {}
				Iterator(Iterator const & src) : _m_ptr(src._m_ptr) {}
				//Assignment Operator Overload
				Iterator &	operator=(Iterator const & rhs) {
					this->_m_ptr = rhs._m_ptr;
					return (*this);
				}
				//Relational Operator Overloads
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
				//Arithmetic Operator Overloads
				Iterator &							operator++(void) {
					++this->_m_ptr;
					return (*this);
				}
				Iterator							operator++(int) {
					Iterator	ret(this->_m_ptr);
					++this->_m_ptr;
					return (ret);
				}
				Iterator & 							operator--(void) {
					--this->_m_ptr;
					return (*this);
				}
				Iterator							operator--(int) {
					Iterator	ret(this->_m_ptr);
					--this->_m_ptr;
					return (ret);
				}
				Iterator &							operator+=(int inc) {
					this->_m_ptr += inc;
					return (*this);
				}
				Iterator &							operator-=(int dec) {
					this->_m_ptr -= dec;
					return (*this);
				}
				Iterator							operator+(int const & rhs) const {
					Iterator	sum(*this);
					return (sum += rhs);
				}
				Iterator							operator-(int const & rhs) const {
					Iterator	dif(*this);
					return (dif -= rhs);
				}
				typename Iterator::difference_type	operator-(Iterator const & rhs) const {
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
				typename Iterator::reference	operator[](typename Iterator::difference_type pos) const {
					return (*(this->_m_ptr + pos));
				}
				//aaaaah!!!! -> . ... claro!!!! :D
				typename Iterator::pointer		operator->(void) const {
					return (this->_m_ptr);
				}
				protected:
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
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			//Constructors
				//default
			explicit vector(const allocator_type & alloc = allocator_type()) : _size(0), _objc(0), _alloc(alloc), _arr(_alloc.allocate(0)) {}
				//fill
			explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
			: _size(n), _objc(0), _alloc(alloc), _arr(_alloc.allocate(_size)) {
				for ( ; _objc < n; ++_objc)
					this->_alloc.construct(_arr + _objc, val);
			}
			template<typename InputIt> //it's taking my int!!!! :O must do some enable_if is_iterator or something
			vector(InputIt first, InputIt last, const allocator_type & alloc = allocator_type()) :
			_size(last - first), _objc(0), _alloc(alloc), _arr(_alloc.allocate(_size)) {
				//std::copy<InputIt, iterator>(first, last, begin());
				(void)tmp;
				for ( ; _objc < _size; ++first, ++_objc)
				{
					this->_alloc.construct(_arr + _objc, *first);
				}
			}

			~vector(void) {
				this->_alloc.deallocate(this->_arr, _size);
			}
			iterator	begin(void) {
				return (iterator(_arr));
			}

			iterator	end(void)
			{
				return (iterator(_arr + _objc));
			}
		protected:
			const size_type				_size; //const?? allocator wants only the size reserved in the FIRST call to allocate?? what kind of shenanigan is THIS?? bring back malloc! xD
			size_type		_objc;
			allocator_type	_alloc;
			T	*_arr;

			

	};
};

#endif