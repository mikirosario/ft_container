/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:15:40 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/10 23:09:00 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

//precompiled header?
#include <memory>
#include <algorithm>
#include <exception>
//#include <stdexcept> //for length_error. Linux only, or Mac also?
#include <iostream>
//precompiled header?

#include "type_traits.hpp"
#include "iterator.hpp"

//DEBUG CODE
#include <vector>
//DEBUG CODE

#define RED "\e[1;31m"
#define RST "\e[0m"
#define PRNTERR std::cerr
#define NL "\n"
#define TAB "\t"
#define END RST << std::endl

#define GROWTH_FACTOR 2
/* This catch block is used after every call to reserve */
#define CATCH_RESERVE_EXCEPTIONS	catch (std::length_error & e) \
									{ \
										PRNTERR << RED << e.what() << END; \
									} \
									catch (std::bad_alloc & e) \
									{ \
										PRNTERR << RED << e.what() << END; \
									} \
									catch (std::exception & e) \
									{ \
										PRNTERR << RED << e.what() << END; \
									} \


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
			** It even beats my original ft_PRNTERRf and ft_itoa_base COMBINED.
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
			//									//should I shrink to fit here?
			// vector (const & vector src) : _capacity(src._capacity), _size(0), _alloc(src._alloc), _arr(_alloc.allocate(_capacity)) {
			// 	typename src.iterator first = src.begin();
			// 	typename src.iterator end = src.end();
			// 	for ( ; first != end; ++first)
			// 		this->_alloc.construct()
			// }
			~vector(void) {
				clear();
				this->_alloc.deallocate(this->_arr, _capacity);
			}

			// vector &	operator=(vector const & src) {
				
			// }

			template<typename InputIt>
			void				assign(InputIt first, InputIt last,
			typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type* = NULL) {
				size_type	new_size = last - first;

				try
				{
					reserve(new_size); 	//reserve will do nothing if new_size is not greater than capacity
					clear(); 			//reserve already calls clear if it had to reallocate, but there is no harm calling it
										//again, it will do nothing if the container is already clear.
					for ( ; first != last; ++first)
						push_back(*first);
				}
				CATCH_RESERVE_EXCEPTIONS
			}

			iterator			begin(void) {
				return (iterator(_arr));
			}
			//As Thor warns us, C++ is lying to you.
			//First argument of any void function is a pointer to the instance.
			//It appears as "this". If the instance is const, "this" points to
			//const, so it's a pointer to const - that's what this funky syntax
			//means. It's an overloaded begin for when 'this' is a pointer to
			//const, because the instance (the vector, in this case) is const.
			//In that case, since the vector is const, we return const_iterators
			//instead of normal iterators, as const_iterators are iterators to
			//const (but not const themselves, you can increment and decrement
			//them just fine).
			const_iterator		begin(void) const {
				return (const_iterator(_arr));
			}

			iterator			end(void) {
				return (iterator(_arr + _size));
			}

			const_iterator		end(void) const {
				return (const_iterator(_arr + _size));
			}
			
			reverse_iterator	rbegin(void) {
				return (ft::reverse_iterator<iterator>(iterator(_arr + _size)));
			}

			const_reverse_iterator	rbegin(void) const {
				return (ft::reverse_iterator<const_iterator>(const_iterator(_arr + _size)));
			}
			
			reverse_iterator	rend(void) {
				return (ft::reverse_iterator<iterator>(iterator(_arr)));
			}

			const_reverse_iterator	rend(void) const {
				return (ft::reverse_iterator<const_iterator>(const_iterator(_arr)));
			}

			/* Capacity */
			
			bool				empty(void) const {
				if (!size())
					return (true);
				return (false);
			}

			size_type			size(void) const {
				return (_size);
			}
			size_type			max_size(void) const {
				return (_alloc.max_size());
			}
			size_type			capacity(void) const {
				return (_capacity);
			}
			/*
			** This is an array, so any reallocation means copying over all the
			** contents of the prior array.
			**
			** If the new capacity is greater than max_size, length_error
			** exception is thrown. If _alloc throws an exception, we rethrow it
			** to the caller.
			**
			** If the new capacity is less than or equal to existing capacity,
			** the request is ignored.
			**
			** Otherwise, we attempt to allocate space for the new array. If it
			** fails, we handle the exceptions (bad_alloc should be thrown).
			**
			** If it succeeds, we copy the array over to the new location, clear
			** the old array (destroy all of its members), deallocate the old
			** array, pass the address of the new array to into the _arr
			** pointer, set the capacity to the new capacity, and reset the
			** size, because clear sets it to 0. Allocator must return a
			** deallocatable pointer, even if zero memory is allocated, so we
			** will always need to deallocate here, though we will never
			** dereference a pointer to an empty array, of course.
			**
			** That should do it.
			*/
			void				reserve(size_type new_cap) throw (std::length_error, std::bad_alloc, std::exception) {
				if (new_cap > this->max_size())
					throw std::length_error("So big, even Bjarne won't allocate it.");
				else if (new_cap > this->_capacity)
				{
					try
					{
						T *			new_arr = _alloc.allocate(new_cap);
						size_type	new_size = 0;
						for ( ; new_size < _size; ++new_size)
							new_arr[new_size] = _arr[new_size];
						clear();
						_alloc.deallocate(_arr, _capacity);
						this->_arr = new_arr;
						this->_capacity = new_cap;
						this->_size = new_size;
					}
					catch (std::bad_alloc & e)
					{
						throw ; //we rethrow bad_alloc
					}
					catch (std::exception & e)
					{
						throw ;
					}
				}
			}
			/*
			** This function destroys any objects constructed in the array in
			** reverse order, and then deallocates the memory occupied by the
			** array, using the provided allocator object. By default,
			** std::allocator. The allocator wants a raw pointer, not
			** iterator shenanigans, hence the dereferencing and referencing.
			**
			** The size is set to 0. Capacity is NOT affected.
			*/
			void				clear(void) {
				for (reverse_iterator rit = this->rbegin(), rend = this->rend(); rit != rend; ++rit)
					_alloc.destroy(&(*rit));
				this->_size = 0;
			}

			/*
			** This function pushes an element to the back and increments the
			** size count. If there is no room for the new element, the vector
			** reallocates more memory. Growth is exponential, and moderated by
			** the GROWTH_FACTOR.
			**
			** The reserve function may throw an exception, so we use a
			** try/catch block. The catch block is long and used every time I
			** call reserve, so I put it in a define. :p
			*/
			void				push_back(value_type const & val) {
				try
				{
					if (_size + 1 > _capacity)
						reserve(_capacity * GROWTH_FACTOR);
					_arr[_size++] = val;
				}
				CATCH_RESERVE_EXCEPTIONS
				// catch (std::length_error & e)
				// {
				// 	PRNTERR << RED << e.what() << END;
				// }
				// catch (std::bad_alloc & e)
				// {
				// 	PRNTERR << RED << e.what() << END;
				// }
				// catch (std::exception & e)
				// {
				// 	PRNTERR << RED << e.what() << END;
				// }
			}
			void				pop_back(void) {
				if (_size)
					_alloc.destroy(&(_arr[--_size]));
			}
			void				resize(size_type new_size, T value = T()) {
				if (new_size < _size)
					while (_size > new_size)
						pop_back();
				else if (new_size > _size)
					while (_size < new_size)
						push_back(value);
			}
			/*
			** This function destroys the element pointed to by pos and left
			** shifts all elements to its right, returning an iterator to the
			** following element at its new position. If the erased element is
			** the last element, the end iterator is returned.
			**
			** If invalid position is passed behaviour is "undefined", but I'm
			** nice, so I just return a NULL iterator. ;)
			*/
			iterator			erase(iterator pos) {
				iterator it = pos;
				iterator end = this->end();

				if (it >= end || it < begin())
					return (iterator(NULL));
				_alloc.destroy(&(*pos));
				for (iterator end = this->end(); it + 1 != end; ++it)
					*it = *(it + 1);
				pop_back();
				return (pos);
			}
			/*
			** This function destroys all the elements within the range and left
			** shifts all elements to the right of the destroyed elements by the
			** number of elements that were destroyed, returning an iterator to
			** the new position of the element after the last destroyed element.
			** If the last erased element was the last element, the end iterator
			** is returned.
			**
			** If invalid range is passed behaviour is "undefined", but I'm nice
			** so I just return a NULL iterator. ;)
			*/
			iterator			erase(iterator first, iterator last) {
				size_type	eraseCount;
				iterator	begin = this->begin();
				iterator	end = this->end();
				iterator	it;

				if (first < begin || last < begin || last > end || first > end || first > last)
					return (iterator(NULL));
				eraseCount = last - first;
				for (it = first; it != last; ++it)
					_alloc.destroy(&(*it));
				for (it = first; it + eraseCount != end; ++it)
					*it = *(it + eraseCount);
				for (size_type i = 0; i < eraseCount; ++i)
					pop_back();
				return  (last - eraseCount);
			}

		protected:
			size_type		_capacity;
			size_type		_size; //object count						
			allocator_type	_alloc;
			T	*_arr;
	};
};

#endif