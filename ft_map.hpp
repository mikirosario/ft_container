/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:05:31 by miki              #+#    #+#             */
/*   Updated: 2021/11/20 22:19:24 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DEVECTOR :P

#ifndef FT_MAP_H
# define FT_MAP_H

//precompiled header?
#include <memory>
#include <algorithm>
#include <exception>
//#include <stdexcept> //for length_error. Linux only, or Mac also?
#include <iostream>
//precompiled header?

#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

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
/* This catch block is used to catch reserve exceptions */
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
	template<typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<T> >
	class map
	{
		private:

			template<typename iT, typename Category>
			struct Iterator : public ft::iterator_traits<iT, Category>
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
					return (!operator==(rhs)); //a!=b == !(a==b)
				}
				bool	operator<(Iterator const & rhs) const {
					return (this->_m_ptr < rhs._m_ptr);
				}
				bool	operator>(Iterator const & rhs) const {
					return (rhs < *this); //a>b == b<a
				}
				bool	operator<=(Iterator const & rhs) const {
					return (!(rhs < *this)); //a<=b == !(b<a)
				}
				bool	operator>=(Iterator const & rhs) const {
					return (!(*this < rhs)); //a>=b == !(a<b)
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
					rb_tree_type_when_its_done_xD *	_m_ptr;
			};

		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef typename ft::pair<const Key, T>								value_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;
			typedef value_type&													reference;
			typedef const value_type&											const_reference;
			typedef value_type*													pointer;
			typedef const value_type*											const_pointer;
			typedef Iterator<value_type, std::bidirectional_iterator_tag>		iterator;
			typedef Iterator<const value_type, std::bidirectional_iterator_tag>	const_iterator; //Iterator formed with const, so its value_type, pointers to value_type, references to value_type, etc, also all refer to const value
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			
			

		protected:
			size_type			_capacity;
			size_type			_size; //object count
			allocator_type		_alloc;
			rb_tree_node_type_when_its_done_xD *			_tree_root;
	};

	// both of these methods seem to work for swap
	// except if it's not a free function i obviously can't use ft::swap.
	// maybe i'll free it. i don't know. maybe not. aren't some containers not
	// swappable? i wouldn't have to enable_if them, would I?? :O because I'm
	// leaving them as friends if THAT's the case.

	/* SWAP TEMPLATE SPECIALIZATION */
	/*
	** This is an std::swap specialization for my ft::vector. I have no idea how
	** it finds this and knows what to do with it, it isn't even in the std
	** namespace and it doesn't even refer to std::swap. Apparently it has to do
	** with Argument-Dependent Lookup (ADL).
	**
	** If I've understood it correctly (which I may not have), in ADL mode it
	** deduces the arguments of x and y and sees their type is in ft::, so it
	** concludes, "oh, then the programmer probably wants that swap in ft:: that
	** takes two parameters exactly like these".
	**
	** I can also do this inside the vector class itself by making the
	** specialization a 'friend', which makes it visible to std::swap. Somehow.
	** Even though I haven't specified who I'm friends with, because I'm not
	** allowed to actually SAY std:: anywhere.
	**
	** But! There is a caveat. The compiler ONLY does ADL if you put "using
	** std::swap" before the call to swap. At least according to the Internets.
	** In my brief experience, if I put NOTHING before the call to swap, and
	** just call "swap", it also finds it just fine, so it must use ADL there
	** too?
	**
	** If, however, I do the totally unreasonable thing of addressing std::swap
	** directly, you know, the template I'm allegedly trying to specialize, it
	** will totally ignore any specializations outside its namespace and not do
	** the ADL. Why?
	**
	** My hypothesis is that the C++ compiler is run by magic gnomes who hate
	** humans and they're trying to use it to drive us all insane and I've
	** decided to dedicate my life to proving it true.
	**
	** Anyway this diverts std::swap to the swap I define in my vector class,
	** and it's a good thing too - because whatever the default swap is doing,
	** my vector class does NOT like it and throws a double free error at the
	** end of it to make that clear. So... yay? :p
	*/
	template<typename T, typename Alloc>
	void	swap(ft::vector<T, Alloc> & x, ft::vector<T, Alloc> & y) {
		x.swap(y);
	}

	/* ---- RELATIONAL OPERATOR OVERLOADS ---- */

	template<typename T, typename Alloc>
	bool	operator==(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
		if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return (true);
		return (false);
	}

	template<typename T, typename Alloc>
	bool	operator!=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
		return(!operator==(lhs, rhs)); //a!=b == !a==b
	}

	template<typename T, typename Alloc>
	bool	operator<(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
		return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<typename T, typename Alloc>
	bool	operator>(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
		return(operator<(rhs, lhs)); //a>b == b<a
	}

	template<typename T, typename Alloc>
	bool	operator<=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
		return(!operator<(rhs, lhs)); //a<=b == !b<a
	}
	
	template<typename T, typename Alloc>
	bool	operator>=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
		return(!operator<(lhs, rhs)); //a>=b == !a<b
	}
};

#endif