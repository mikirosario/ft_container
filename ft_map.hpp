/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:05:31 by miki              #+#    #+#             */
/*   Updated: 2021/12/05 17:37:32 by mikiencolor      ###   ########.fr       */
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

#include "ansi_codes.hpp"
#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "ft_bintree_pair.hpp"

//DEBUG CODE
#include <vector>
//#include <type_traits>
//DEBUG CODE

#define PRNTERR std::cerr
#define END TXT_RST << std::endl

#define GROWTH_FACTOR 2
/* This catch block is used to catch reserve exceptions */
#define CATCH_RESERVE_EXCEPTIONS	catch (std::length_error & e) \
									{ \
										PRNTERR << TXT_BRED << e.what() << END; \
									} \
									catch (std::bad_alloc & e) \
									{ \
										PRNTERR << TXT_BRED << e.what() << END; \
									} \
									catch (std::exception & e) \
									{ \
										PRNTERR << TXT_BRED << e.what() << END; \
									} \

namespace ft
{
	template<typename Key, typename Value, typename Compare = ft::less<Key>, typename Alloc = std::allocator< ft::pair<Key, Value> > >
	class map
	{
		private:

			template<typename iT, typename Category>
			struct Iterator : public ft::iterator_traits<iT, Category>
			{
				friend class ft::map<Key, Value, Compare, Alloc>;
				//Constructible
				Iterator(void) : _tree_it(NULL) {}
				Iterator(Iterator const & src) : _tree_it(src._tree_it) {}
				//Destructible
				~Iterator(void) {}
				//Assignment Operator Overload
				Iterator &	operator=(Iterator const & rhs) {
					this->_tree_it = rhs._tree_it;
					return (*this);
				}
				//Relational Operator Overloads
				bool	operator==(Iterator const & rhs) const {
					return (this->_tree_it == rhs._tree_it);
				}
				bool	operator!=(Iterator const & rhs) const {
					return (!operator==(rhs)); //a!=b == !(a==b)
				}
				//Arithmetic Operator Overloads
				Iterator &							operator++(void) {
					++this->_tree_it;
					return (*this);
				}
				Iterator							operator++(int) {
					Iterator	ret(this->_tree_it);
					++this->_tree_it;
					return (ret);
				}
				Iterator & 							operator--(void) {
					--this->_tree_it;
					return (*this);
				}
				Iterator							operator--(int) {
					Iterator	ret(this->_tree_it);
					--this->_tree_it;
					return (ret);
				}
				//Referencing Operators
				//The const references/pointers will be consted by the vector
				//instantiation for const_iterators, which uses a const T. 
				//The function is always consted, as it itself doesn't modify
				//any class member.
				typename Iterator::reference	operator*(void) const {
					return(*this->_tree_it->value);
				}
				//aaaaah!!!! -> . ... claro!!!! :D
				typename Iterator::pointer		operator->(void) const {
					return (this->_tree_it->value);
				}
				protected:
					typename ft::bintree_pair<Key, Value, Compare, Alloc>::iterator	_tree_it;
			};

		public:
			typedef Key															key_type;
			typedef Value														mapped_type;
			typedef typename ft::pair<const Key, Value>							value_type;
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
			typedef ft::bintree_pair<Key, Value, Compare, Alloc>				t_tree;

			/* ---- CONSTRUCTORS AND DESTRUCTOR ---- */

			/* DEFAULT CONSTRUCTOR */
			explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _tree(comp, alloc) {}
			
			/* RANGE CONSTRUCTOR */
			template<class InputIt>
			map(InputIt first, InputIt last, const key_compare & comp = key_compare(),
			const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type * = NULL) : _tree(first._tree_it, last._tree_it, comp, alloc) {} 
			
			/* COPY CONSTRUCTOR */
			map(map const & src) : _tree(src._tree), _size(_tree.size()) {}
			
			
			

		protected:
			//size_type		_capacity;
			size_type		_size; //object count
			t_tree			_tree;
	};

	// both of these methods seem to work for swap
	// except if it's not a free function i obviously can't use ft::swap.
	// maybe i'll free it. i don't know. maybe not. aren't some containers not
	// swappable? i wouldn't have to enable_if them, would I?? :O because I'm
	// leaving them as friends if THAT's the case.

	// /* SWAP TEMPLATE SPECIALIZATION */
	// /*
	// ** This is an std::swap specialization for my ft::vector. I have no idea how
	// ** it finds this and knows what to do with it, it isn't even in the std
	// ** namespace and it doesn't even refer to std::swap. Apparently it has to do
	// ** with Argument-Dependent Lookup (ADL).
	// **
	// ** If I've understood it correctly (which I may not have), in ADL mode it
	// ** deduces the arguments of x and y and sees their type is in ft::, so it
	// ** concludes, "oh, then the programmer probably wants that swap in ft:: that
	// ** takes two parameters exactly like these".
	// **
	// ** I can also do this inside the vector class itself by making the
	// ** specialization a 'friend', which makes it visible to std::swap. Somehow.
	// ** Even though I haven't specified who I'm friends with, because I'm not
	// ** allowed to actually SAY std:: anywhere.
	// **
	// ** But! There is a caveat. The compiler ONLY does ADL if you put "using
	// ** std::swap" before the call to swap. At least according to the Internets.
	// ** In my brief experience, if I put NOTHING before the call to swap, and
	// ** just call "swap", it also finds it just fine, so it must use ADL there
	// ** too?
	// **
	// ** If, however, I do the totally unreasonable thing of addressing std::swap
	// ** directly, you know, the template I'm allegedly trying to specialize, it
	// ** will totally ignore any specializations outside its namespace and not do
	// ** the ADL. Why?
	// **
	// ** My hypothesis is that the C++ compiler is run by magic gnomes who hate
	// ** humans and they're trying to use it to drive us all insane and I've
	// ** decided to dedicate my life to proving it true.
	// **
	// ** Anyway this diverts std::swap to the swap I define in my vector class,
	// ** and it's a good thing too - because whatever the default swap is doing,
	// ** my vector class does NOT like it and throws a double free error at the
	// ** end of it to make that clear. So... yay? :p
	// */
	// template<typename T, typename Alloc>
	// void	swap(ft::vector<T, Alloc> & x, ft::vector<T, Alloc> & y) {
	// 	x.swap(y);
	// }

	// /* ---- RELATIONAL OPERATOR OVERLOADS ---- */

	// template<typename T, typename Alloc>
	// bool	operator==(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	// 	if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
	// 		return (true);
	// 	return (false);
	// }

	// template<typename T, typename Alloc>
	// bool	operator!=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	// 	return(!operator==(lhs, rhs)); //a!=b == !a==b
	// }

	// template<typename T, typename Alloc>
	// bool	operator<(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	// 	return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	// }

	// template<typename T, typename Alloc>
	// bool	operator>(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	// 	return(operator<(rhs, lhs)); //a>b == b<a
	// }

	// template<typename T, typename Alloc>
	// bool	operator<=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	// 	return(!operator<(rhs, lhs)); //a<=b == !b<a
	// }
	
	// template<typename T, typename Alloc>
	// bool	operator>=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs) {
	// 	return(!operator<(lhs, rhs)); //a>=b == !a<b
	//}
};

#endif