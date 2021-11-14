/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:15:40 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/14 01:36:47 by miki             ###   ########.fr       */
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
//#include <type_traits>
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
					return (!operator>=(rhs));
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
				return (ft::reverse_iterator<iterator>(iterator(this->end())));
			}

			const_reverse_iterator	rbegin(void) const {
				return (ft::reverse_iterator<const_iterator>(const_iterator(this->end())));
			}
			
			reverse_iterator	rend(void) {
				return (ft::reverse_iterator<iterator>(iterator(this->begin())));
			}

			const_reverse_iterator	rend(void) const {
				return (ft::reverse_iterator<const_iterator>(const_iterator(this->begin())));
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

			/*
			** This function resizes the container by new_size elements. If the
			** new size is greater than the current size, the value passed as an
			** argument is pushed to the end of the object until the new size is
			** reached. If no value is passed, the value is value-initialized.
			** If the new size is less than the current size, elements are
			** popped off the end of the object until the new_size is reached.
			** If the new size is the same as the current size, nothing is done.
			** If size_type is defined as signed and a negative number is passed
			** behaviour is undef-- OK, let's be real, you're asking for a
			** segmentation fault. I made that type unsigned for a reason, you
			** know. :p
			*/
			void				resize(size_type new_size, T value = T()) {
				if (new_size < _size)
					while (_size > new_size)
						pop_back();
				else if (new_size > _size)
					while (_size < new_size)
						push_back(value);
			}

			/*
			** SINGLE ELEMENT ERASE
			**
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
				//protect?
				if (it >= end || it < begin())
					return (iterator(NULL));
				_alloc.destroy(&(*pos));
				for (iterator end = this->end(); it + 1 != end; ++it)
					*it = *(it + 1);
				pop_back();
				return (pos);
			}

			/*
			** RANGE ERASE
			**
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
				//protect?
				if (first < begin || last < begin || last > end || first > end)
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
			
			//can't use iterators here, they will be invalidated by realloc...
			//good thing we're not scared of "unsafe" stuff ;)
			//a single resize could cause a realloc that invalidates pos
			//so we need to translate it IMMEDIATELY to a relative position
			//value that will be address-indifferent.
			/*
			** SINGLE ELEMENT INSERT
			**
			** This function inserts the value passed as val at the position pos
			** BEFORE the element at that position.
			**
			** Because this may lead to a reallocation that would invalidate any
			** iterators or pointers, we take the position relative to the
			** beginning of the array before resizing.
			**
			** If the position is not within the vector range, nothing is done
			** and a NULL iterator is returned. Otherwise, the vector is resized
			** to one element greater than its current size.
			**
			** An iterator 'it', starting at end - 1, is used to shift all
			** elements in the array right by one, including the element at
			** begin + 'pos'. Thus, 'pos' is the position of the last element to
			** be shifted and the position of the newly inserted element after
			** it is assigned to 'pos'. If 'pos' is at begin, it will be 0, so
			** begin + 'pos' will be begin.
			**
			** End is always one element right of the last element in the
			** vector, and the shift iterator is always assigned to end - 1.
			** Thus, if the vector was empty at the start (begin == end), after
			** the resize 'it' will be equal to end - 1, while 'pos' will be
			** equal to begin + 0, so 'it' will already be equal to 'pos' and
			** nothing will be right-shifted, leaving val to be directly copied
			** to *it.
			**
			** We return an iterator to the inserted value, which should always
			** be the last element pointed to by it.
			**
			** IT MAKES SENSE IN MY HEAD, OKAY!? xD I'm open to simpler ways of
			** organizing this. xD
			*/						
			iterator			insert(iterator pos, value_type const & val) {
				iterator	begin(this->begin());
				// // protect?
				// if (pos < begin || pos > this->end())
				// 	return (iterator(NULL));
				size_type	pos_index = (pos - begin);
				this->resize(_size + 1); //iterators invalidated here
				//right shift all values after and including _arr[pos_index]
				iterator	it(this->end() - 1);
				for (iterator first(this->begin() + pos_index); it != first; --it)
					*it = *(it - 1);
				//copy value to pos
				*it = val;
				return (it);
			}

			/*
			** FILL INSERT
			**
			** This function inserts n copies of the value passed as val before
			** the position passed as pos.
			**
			** As with the SINGLE ELEMENT INSERT, this may need reallocation,
			** which invalidates all previous pointers/iterators, so first we
			** want to take the position relative to the first element so it's
			** invariant under that transformation.
			**
			** Then we resize to size n to get our new positions, which will
			** start out all the way to our right. The iterator 'it' starts at
			** end() - 1 and copies the value at it - n, counting down until
			** equal to pos + n - 1, the position before the last new position
			** that will receive a copy of an existing value. If n was zero then
			** there are no new positions and for any non-empty array (where
			** end > begin) it just leads to useless self-copying of all values
			** after pos to themselves. To avoid this I thought of using a n > 0
			** check, though I'd prefer a more efficient solution. Maybe
			** avoiding the self-copying isn't worth the overhead of the extra
			** check on all function calls? On the fence about this...
			**
			** Anyway, after the right shift, it is set to first (which is begin
			** + pos_index), and val is copied there and to all subsequent
			** addresses of the array until first + n. Pretty straightforward.
			**
			** 
			**
			**
			**   B E
			** - - -
			** - - -
			** - v -
			** - v v v v -
			** insert(B, 2, d);
			**	 B	 E
			** - v ? -
			**   B	   E
			** - v ? ? - //step 1
			**	 B		   E
			** - v1 v2 ? ? ? ? -
			*	 B
			** - ? ? ? ? v1 v2
			*/
		//returns void in C++98 version. Gotta love consistency. xD
			void				insert(iterator pos, size_type n, T const & val) {
				iterator	begin(this->begin());
				// protect?
				// if (pos < begin || pos > this->end())
				// 	return ;
				size_type	pos_index = (pos - begin);
				this->resize(_size + n); //iterators invalidated here
				iterator first(this->begin() + pos_index);
				//if (n > 0)	//stop self-copying when n == 0 and _size > 0, or not worth extra check ?
								//other ways of approaching the right shift ?
				//{
					//right shift all values after and including _arr[pos_index] by n
					for (iterator it(this->end() - 1); it != first + n - 1; --it)
					{
						// //DEBUG
						// if (n != 2)
						// 	PRNTERR << "wha?" << END;
						// //DEBUG
						*it = *(it - n);
					}
					//copy val to positions before shifted values
					for (iterator it(first); it != first + n; ++it)
						*it = val;
				//}
			}
			
			//c++98 isn't actually type-safe if InputIt is an integer, instead
			//it interprets the same thing as the last overload (first is 'n'
			// and last is 'val'). I can see why, I mean they are very similar,
			//but... do I REALLY have to implement that?? I WANT to type check
			//the thing!! It doesn't even really make much sense, T and
			// size_type are still probably different integers. :p I might get
			//annoyed enough to do a run-time type check and call insert2
			//overload, which is awful. Wait, that isn't what they originally
			//did, is it...? IS IT? O_O
			template<typename InputIt>
			void	insert(iterator pos, InputIt first, InputIt last,
			typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type * = NULL) {
				// //protect??
				// if (pos < this->begin() || pos > this->end())
				// 	return ;
				size_type	grow_by = last - first;
				size_type	pos_index = (pos - this->begin());
				this->resize(_size + grow_by); //iterators invalidated here
				//right shift all values after and including _arr[pos_index]
				iterator insert_pos(this->begin() + pos_index);
				for (iterator it(this->end() - 1); it != insert_pos + grow_by - 1; --it)
					*it = *(it - grow_by);
				for (iterator it(this->begin() + pos_index); first != last; ++first, ++it)
					*it = *first;
			}

			/*
			** This function does what it says on the tin.
			*/
			void	swap(vector<T, Alloc> & src) {
				T				*org_arr = this->_arr;
				size_type		org_size = this->_size;
				size_type 		org_cap = this->_capacity;
				allocator_type	org_alloc = this->_alloc;

				this->_alloc = src._alloc;
				src._alloc = org_alloc;
				this->_arr = src._arr;
				src._arr = org_arr;
				this->_size = src._size;
				src._size = org_size;
				this->_capacity = src._capacity;
				src._capacity = org_cap;
			}

		protected:
			size_type		_capacity;
			size_type		_size; //object count						
			allocator_type	_alloc;
			T	*_arr;
	};

	/*
	** This is an std::swap specialization for my ft::vector. I have no idea how
	** it finds this and knows what to do with it, it isn't even in the std
	** namespace and it doesn't even refer to std::swap. Apparently it has to do
	** with Argument-Dependent Lookup. It deduces the arguments of x and y and
	** sees their type is in ft::, so it concludes, "oh, then the programmer
	** probably wants that swap in ft:: that takes two parameters exactly like
	** these".
	**
	** At this point I'm starting to think the C++ compiler is magic gnomes.
	**
	** Anyway this diverts std::swap to the swap I define in my vector class,
	** and it's a good thing too - because whatever the default swap is doing,
	** my vector class does NOT like it and throws a double free error at the
	** end of it to make that clear. :p
	*/
	template<typename T>
	void	swap(ft::vector<T> & x, ft::vector<T> & y) {
		x.swap(y);
	}
};

#endif