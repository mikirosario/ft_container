/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:05:31 by miki              #+#    #+#             */
/*   Updated: 2021/12/07 19:34:18 by miki             ###   ########.fr       */
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
	template<typename Key, typename Value, typename Compare = ft::less<Key>, typename Alloc = std::allocator<typename ft::bintree_pair<Key, Value>::t_bstnode> >
	class map
	{
		private:

			template<typename iT, typename Category, typename tiT>
			struct Iterator : public ft::iterator_traits<iT, Category>
			{
				friend class ft::map<Key, Value, Compare, Alloc>;
				//Constructible
				Iterator(void) : _tree_it(NULL) {}
				Iterator(Iterator const & src) : _tree_it(src._tree_it) {}
				//DEBUG POR QUÉ NO REF???
				Iterator(typename ft::bintree_pair<Key, Value, Compare, Alloc>::iterator tree_it) : _tree_it(tree_it) {}
				Iterator(typename ft::bintree_pair<Key, Value, Compare, Alloc>::const_iterator tree_it) : _tree_it(tree_it) {}
				//Destructible
				~Iterator(void) {}
				//Assignment Operator Overload
				Iterator &	operator=(Iterator const & rhs) {
					this->_tree_it = rhs._tree_it;
					return (*this);
				}
				// operator	bool(void) const {
				// 	return(true);
				// }

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
				typename Iterator::reference	operator*(void) {
					return(*this->_tree_it->value);
				}
				const iT &						operator*(void) const {
					return(*this->_tree_it->value);
				}
				//aaaaah!!!! -> . ... claro!!!! :D
				typename Iterator::pointer		operator->(void) const {
					return (&this->_tree_it->data);
				}
				protected:
					tiT	_tree_it;
			};

		public:
			typedef Key																	key_type;
			typedef Value																mapped_type;
			typedef typename ft::pair<Key const, Value>									value_type;
			typedef Compare																key_compare;
			typedef typename ft::bintree_pair<Key const, Value, Compare>::value_compare	value_compare;
			typedef Alloc																allocator_type;
			typedef std::size_t															size_type;
			typedef std::ptrdiff_t														difference_type;
			typedef value_type&															reference;
			typedef const value_type&													const_reference;
			typedef value_type*															pointer;
			typedef const value_type*													const_pointer;
			typedef Iterator<value_type, std::bidirectional_iterator_tag, typename ft::bintree_pair<Key, Value, Compare, Alloc>::iterator>				iterator;
			typedef Iterator<value_type const, std::bidirectional_iterator_tag, typename ft::bintree_pair<Key, Value, Compare, Alloc>::const_iterator>			const_iterator; //Iterator formed with const, so its value_type, pointers to value_type, references to value_type, etc, also all refer to const value
			typedef ft::reverse_iterator<iterator>										reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
			typedef ft::bintree_pair<Key, Value, Compare, Alloc>						t_tree;

			/* ---- CONSTRUCTORS AND DESTRUCTOR ---- */

			/* DEFAULT CONSTRUCTOR */
			explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _tree(comp, alloc) {}
			
			/* RANGE CONSTRUCTOR */
			template<class InputIt>
			map(InputIt first, InputIt last, const key_compare & comp = key_compare(),
			const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type * = NULL) : _tree(first._tree_it, last._tree_it, comp, alloc) {} 
			
			/* COPY CONSTRUCTOR */
			//map(map const & src) : _tree(src._tree) {}
			map(map & src) : _tree(src._tree) {}
			
			/* DESTRUCTOR */
			~map(void) {}
			
			/* ASSIGNMENT OPERATOR OVERLOAD */
			map const &	operator=(map const & src) {
					_tree = src._tree;
			}

			/* ---- Iterators ---- */

			iterator				begin(void) {
				return (iterator(_tree.begin()));
			}

			const_iterator			begin(void) const {
				return (const_iterator(_tree.begin()));
			}

			iterator				end(void) {
				return (iterator(_tree.end()));
			}

			const_iterator			end(void) const {
				return (const_iterator(_tree.end()));
			}

			reverse_iterator		rbegin(void) {
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin(void) const {
				return (const_reverse_iterator(end()));
			}

			reverse_iterator		rend(void) {
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend(void) const {
				return (const_reverse_iterator(begin()));
			}

			/* ---- CAPACITY ---- */
			
			bool		empty(void) const {
				return (_tree.empty());
			}

			size_type	size(void) const {
				return (_tree.size());
			}

			size_type	max_size(void) const {
				return (_tree.max_size());
			}

			/* ---- ELEMENT ACCESS ---- */

			mapped_type &	operator[](key_type const &	key) {
				return (_tree.operator[](key));
			}

			/* ---- MODIFIERS ---- */

			/* INSERT BY KEY-VALUE PAIR */
										//value_type == ft::pair
			ft::pair<iterator, bool> insert(value_type const & key_value_pair) {
				ft::pair<typename t_tree::iterator, bool> res = _tree.insert(key_value_pair);
				return (ft::pair<iterator, bool>(iterator(res.first), res.second));
			}

			/* INSERT BY KEY-VALUE PAIR WITH HINT */
			iterator				insert(iterator position, value_type const & key_value_pair) {
				return (iterator(_tree.insert(position._tree_it, key_value_pair)));
			}

			/* INSERT BY RANGE OF KEY-VALUE PAIRS */
			template<typename InputIt>
			void					insert(InputIt first, InputIt last,
									typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type * = NULL) {
				_tree.insert(first, last);
			}

			/* ERASE BY POSITION */
			void					erase(iterator position) {
				_tree.erase(position._tree_it);
			}

			/* ERASE BY KEY */
			size_type				erase(key_type const & key) {
				return (_tree.erase(key));
			}

			/* ERASE BY RANGE */
			void					erase(iterator first, iterator last) {
				_tree.erase(first._tree_it, last._tree_it);
			}

			/* SWAP */
			void					swap(map const & src) {
				ft::swap(_tree, src._tree);
			}

			/* CLEAR */
			void					clear(void) {
				_tree.clear();
			}

			/* ---- OBSERVERS ----- */

			key_compare		key_comp(void) const {
				return(_tree.key_comp());
			}

			value_compare	value_comp(void) const {
				return (_tree.value_comp());
			}

			/* ---- OPERATIONS ---- */
			
			/* FIND */
			iterator									find(key_type const & key) {
				return (iterator(_tree.find(key)));
			}

			const_iterator								find(key_type const & key) const {
				return (const_iterator(_tree.find(key)));
			}

			/* COUNT */
			size_type									count(key_type const & key) const {
				return (_tree.count(key));
			}

			/* LOWER BOUND */
			iterator									lower_bound(key_type const & key) {
				return (iterator(_tree.lower_bound(key)));
			}

			const_iterator								lower_bound(key_type const & key) const {
				return (const_iterator(_tree.lower_bound(key)));
			}

			/* UPPER BOUND */
			iterator									upper_bound(key_type const & key) {
				return (iterator(_tree.upper_bound(key)));
			}

			const_iterator								upper_bound(key_type const & key) const {
				return (const_iterator(_tree.upper_bound(key)));
			}

			/* EQUAL RANGE */
			ft::pair<iterator, iterator>				equal_range(key_type const & key) {
				typename ft::pair<typename ft::bintree_pair<Key const, Value>::iterator, typename ft::bintree_pair<Key, Value>::iterator>	bintree_range;

				bintree_range = _tree.equal_range(key);
				return (ft::pair<iterator, iterator>(bintree_range.first, bintree_range.second));
			}
			
			ft::pair<const_iterator, const_iterator>	equal_range(key_type const & key) const {
				typename ft::pair<typename ft::bintree_pair<Key const, Value>::const_iterator, typename ft::bintree_pair<Key, Value>::const_iterator>	bintree_range;

				bintree_range = _tree.equal_range(key);
				return (ft::pair<const_iterator, const_iterator>(bintree_range.first, bintree_range.second));
			}

			/* ALLOCATOR */
			allocator_type	get_allocator(void) const {
				return (_tree.get_allocator());
			}
			
		protected:
			//size_type		_capacity;
			//size_type		_size; //object count
			t_tree			_tree;
	};

	/* SWAP TEMPLATE SPECIALIZATION */
	/*
	** This is an std::swap specialization for my ft::bintree. I have no idea how
	** it finds this and knows what to do with it, it isn't even in the std
	** namespace and it doesn't even refer to std::swap. Apparently it has to do
	** with Argument-Dependent Lookup (ADL).
	**
	** If I've understood it correctly (which I may not have), in ADL mode it
	** deduces the arguments of x and y and sees their type is in ft::, so it
	** concludes, "oh, then the programmer probably wants that swap in ft:: that
	** takes two parameters exactly like these".
	*/
	template<typename Key, typename Value, typename Compare, typename Alloc>
	void	swap(ft::map<Key, Value, Compare, Alloc> & x, ft::map<Key, Value, Compare, Alloc> & y) {
		x.swap(y);
	}

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