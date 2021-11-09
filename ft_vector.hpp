/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:15:40 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/09 22:03:37 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

#include <memory>
#include <algorithm>
#include "type_traits.hpp"
#include "iterator.hpp"

//DEBUG CODE
#include <cmath>
#include <vector>
#include <iostream>
//DEBUG CODE

//system bits == size of pointer (in bytes) * 8
#define SYSBITS (sizeof(void *) * 8)


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
			//Constructors //Need to take _max_size into account now...
				//default
			explicit vector(const allocator_type & alloc = allocator_type()) : _capacity(0), _size(0), _alloc(alloc), _arr(_alloc.allocate(0)) {}
				//fill
			explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
			: _capacity(n), _size(0), _alloc(alloc), _arr(_alloc.allocate(_capacity)) {
				for ( ; _size < n; ++_size)
					this->_alloc.construct(_arr + _size, val);
			}
				//range
			/*
			** THIS is now the single most hideous thing I have seen coded...
			** This... THING!!
			**
			** It beats the get_next_line written entirely in nested ternaries.
			**
			** It even beats my original ft_printf and ft_itoa_base COMBINED.
			**
			** I think 42 must hate C++ and the real point of these exercises
			** is to make us hate it as well. :p
			**
			** I can't believe this not only actually works, but is supposed to
			** be what passes for proper trait checking in C++98. WHAT EVEN IS
			** THIS!? IS THAT A FICTIONAL POINTER TO A TYPE I'M SETTING TO NULL?
			** WHAT THE HELL IS THIS EVEN DOING!? WHY, BJARNE, WHY!?
			**/
			template<typename InputIt> //it's taking my int!!!! :O must do some enable_if is_iterator or something
			vector(InputIt first, InputIt last, const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type* = NULL) :
			_capacity(last - first), _size(0), _alloc(alloc), _arr(_alloc.allocate(_capacity)) {
					for ( ; _size < _capacity; ++first, ++_size)
					{
						this->_alloc.construct(_arr + _size, *first);
					}
			}
			// /*
			// ** The !is_integral version. I don't get this either. What if it's
			// ** a vector of doubles? A vector of instantiated classes? But this
			// ** apparently was an official implementation?? O_O What is this
			// ** language!?
			// */
			// template<typename InputIt> //it's taking my int!!!! :O must do some enable_if is_iterator or something
			// vector(InputIt first, InputIt last, const allocator_type & alloc = allocator_type(),
			// typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) :
			// _capacity(last - first), _size(0), _alloc(alloc), _arr(_alloc.allocate(_capacity)) {
			// 		for ( ; _size < _capacity; ++first, ++_size)
			// 		{
			// 			this->_alloc.construct(_arr + _size, *first);
			// 		}
			// }
			// /*
			// ** The actual, official implementation from my own Linux library.
			// ** WTF is this!? Is this check performed at run-time inside the
			// ** _M_initialize_dispatch function? What does it do if it turns out
			// ** to be an integer, throw an exception? What is this MADNESS!? o_O
			// */
     		// template<typename _InputIterator>
			// vector(_InputIterator __first, _InputIterator __last,
			// const allocator_type& __a = allocator_type())
			// : _Base(__a)
			// {
			// 	// Check whether it's an integral type.  If so, it's not an iterator.
			// 	typedef typename std::__is_integer<_InputIterator>::__type _Integral;
			// 	_M_initialize_dispatch(__first, __last, _Integral());
			// }

			//copy
			//y si src.alloc es de otro tipo??
			//debería usar getters, para que sea standard
			// vector (const & vector src) : _capacity(src._capacity), _size(0), _alloc(src._alloc), _arr(_alloc.allocate(_capacity)) {
			// 	typename src.iterator first = src.begin();
			// 	typename src.iterator end = src.end();
			// 	for ( ; first != end; ++first)
			// 		this->_alloc.construct()
			// }
			~vector(void) {
				this->_alloc.deallocate(this->_arr, _capacity);
			}
			iterator			begin(void) {
				return (iterator(_arr));
			}

			iterator			end(void) {
				return (iterator(_arr + _size));
			}
			reverse_iterator	rbegin(void) {
				return (ft::reverse_iterator<iterator>(iterator(_arr + _size)));
			}
			reverse_iterator	rend(void) {
				return (ft::reverse_iterator<iterator>(iterator(_arr)));
			}
			size_type			size(void) {
				return (_size);
			}
			size_type			max_size(void){
				return (_alloc.max_size());
			}

		protected:
			const size_type	_capacity; //const?? allocator wants only the size reserved in the FIRST call to allocate?? what kind of shenanigan is THIS?? bring back malloc! xD
			size_type		_size; //object count						
			allocator_type	_alloc;
			T	*_arr;

			

	};
};

#endif