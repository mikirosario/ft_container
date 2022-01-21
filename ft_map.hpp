/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:05:31 by miki              #+#    #+#             */
/*   Updated: 2022/01/21 04:44:02 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_H
# define FT_MAP_H

#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "ft_bintree_pair.hpp"

namespace ft
{
	template<typename Key, typename Value, typename Compare = ft::less<Key>, typename Alloc = std::allocator<typename ft::bintree_pair<Key, Value>::t_bstnode> >
	class map
	{
		private:

			template<typename iT, typename Category, typename tiT>
			struct Iterator : public ft::iterator_traits<iT, Category>
			{
				typedef typename ft::pair<Key const, Value> const								val_t;
				typedef typename ft::bintree_pair<Key, Value, Compare, Alloc>::const_iterator	const_tree_it;
				typedef Iterator<val_t, Category, const_tree_it>								const_it;
				//Constructible
				Iterator(void) {}
				Iterator(Iterator const & src) : _tree_it(src._tree_it) {}
				Iterator(typename ft::bintree_pair<Key, Value, Compare, Alloc>::iterator const & tree_it) : _tree_it(tree_it) {}
				Iterator(typename ft::bintree_pair<Key, Value, Compare, Alloc>::const_iterator const & tree_it) : _tree_it(tree_it) {}
				//Destructible
				~Iterator(void) {}
				//Assignment Operator Overload
				Iterator &	operator=(Iterator const & rhs) {
					this->_tree_it = rhs._tree_it;
					return (*this);
				}
				//Conversion Operator - Iterator is always convertible to const_iterator
				operator	Iterator<iT const, Category, typename ft::bintree_pair<Key, Value, Compare, Alloc>::const_iterator>() const {
					return(Iterator<iT const, Category, typename ft::bintree_pair<Key, Value, Compare, Alloc>::const_iterator>(this->_tree_it));
				}
				//Relational Operator Overloads
				bool	operator==(const_it const & rhs) const {
					return (this->_tree_it == rhs.base());
				}
				bool	operator!=(const_it const & rhs) const {
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
				typename Iterator::reference	operator*(void) {
					return(this->_tree_it->data);
				}
				const iT &						operator*(void) const {
					return(this->_tree_it->data);
				}
				typename Iterator::pointer		operator->(void) const {
					return (&this->_tree_it->data);
				}
				tiT	base(void) const {
					return (_tree_it);
				};
				protected:
					tiT	_tree_it;
			};

		public:
			typedef ft::bintree_pair<Key, Value, Compare, Alloc>													t_tree;
			typedef Key																								key_type;
			typedef Value																							mapped_type;
			typedef typename ft::pair<Key const, Value>																value_type;
			typedef Compare																							key_compare;
			typedef Alloc																							allocator_type;
			typedef std::size_t																						size_type;
			typedef std::ptrdiff_t																					difference_type;
			typedef value_type&																						reference;
			typedef const value_type&																				const_reference;
			typedef value_type*																						pointer;
			typedef const value_type*																				const_pointer;
			typedef Iterator<value_type, std::bidirectional_iterator_tag, typename t_tree::iterator>				iterator;
			typedef Iterator<value_type const, std::bidirectional_iterator_tag, typename t_tree::const_iterator>	const_iterator; //Iterator formed with const tree iterator, so tree iterator value_type, pointers to value_type, references to value_type, etc, also all refer to const value
			typedef ft::reverse_iterator<iterator>																	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>															const_reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class ft::map<Key, Value, Compare, Alloc>;
				protected:
					Compare	_comp;
					value_compare (Compare src) : _comp(src) {} //This is technically a comparison object containing an operator, but it IS still an operator overload, and it DOES follow the standard implementation.
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator()(value_type const & x, value_type const & y) const {
						return _comp(x.first, y.first);
					}
			};

			/* ---- CONSTRUCTORS AND DESTRUCTOR ---- */

			/* DEFAULT CONSTRUCTOR */
			explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _tree(comp, alloc) {}
			
			/* RANGE CONSTRUCTOR */
			template<class InputIt>
			map(InputIt first, InputIt last, const key_compare & comp = key_compare(),
			const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type * = NULL) : _tree(first, last, comp, alloc) {} 

			/* COPY CONSTRUCTOR */
			map(map const & src) : _tree(src._tree) {}
			
			/* DESTRUCTOR */
			~map(void) {}
			
			/* ASSIGNMENT OPERATOR OVERLOAD */
			map const &	operator=(map const & src) {
					_tree = src._tree;
					return (*this);
			}

			/* ---- ITERATORS ---- */

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
				return (iterator(_tree.insert(position.base(), key_value_pair)));
			}

			/* INSERT BY RANGE OF KEY-VALUE PAIRS */
			template<typename InputIt>
			void					insert(InputIt first, InputIt last,
									typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type * = NULL) {
				_tree.insert(first, last);
			}

			/* ERASE BY POSITION */
			void					erase(iterator position) {
				_tree.erase(position.base());
			}

			/* ERASE BY KEY */
			size_type				erase(key_type const & key) {
				return (_tree.erase(key));
			}

			/* ERASE BY RANGE */
			void					erase(iterator first, iterator last) {
				_tree.erase(first.base(), last.base());
			}

			/* SWAP */
			void					swap(map & src) {
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
				return (value_compare(_tree.key_comp()));
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
				typename ft::pair<typename t_tree::iterator, typename t_tree::iterator>	bintree_range;

				bintree_range = _tree.equal_range(key);
				return (ft::pair<iterator, iterator>(bintree_range.first, bintree_range.second));
			}
			
			ft::pair<const_iterator, const_iterator>	equal_range(key_type const & key) const {
				typename ft::pair<typename t_tree::const_iterator, typename t_tree::const_iterator>	bintree_range;

				bintree_range = _tree.equal_range(key);
				return (ft::pair<const_iterator, const_iterator>(bintree_range.first, bintree_range.second));
			}

			/* ALLOCATOR */
			allocator_type	get_allocator(void) const {
				return (_tree.get_allocator());
			}
			
		protected:
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
	void	swap(map<Key, Value, Compare, Alloc> & x, map<Key, Value, Compare, Alloc> & y) {
		x.swap(y);
	}

	/* ---- RELATIONAL OPERATOR OVERLOADS ---- */

	template<typename Key, typename Value, typename Compare, typename Alloc>
	bool	operator==(map<Key, Value, Compare, Alloc> const & lhs, map<Key, Value, Compare, Alloc> const & rhs) {
		if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return (true);
		return (false);
	}

	template<typename Key, typename Value, typename Compare, typename Alloc>
	bool	operator!=(map<Key, Value, Compare, Alloc> const & lhs, map<Key, Value, Compare, Alloc> const & rhs) {
		return(!operator==(lhs, rhs)); //a!=b == !a==b
	}

	template<typename Key, typename Value, typename Compare, typename Alloc>
	bool	operator<(map<Key, Value, Compare, Alloc> const & lhs, map<Key, Value, Compare, Alloc> const & rhs) {
		return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<typename Key, typename Value, typename Compare, typename Alloc>
	bool	operator>(map<Key, Value, Compare, Alloc> const & lhs, map<Key, Value, Compare, Alloc> const & rhs) {
		return(operator<(rhs, lhs)); //a>b == b<a
	}

	template<typename Key, typename Value, typename Compare, typename Alloc>
	bool	operator<=(map<Key, Value, Compare, Alloc> const & lhs, map<Key, Value, Compare, Alloc> const & rhs) {
		return(!operator<(rhs, lhs)); //a<=b == !b<a
	}
	
	template<typename Key, typename Value, typename Compare, typename Alloc>
	bool	operator>=(map<Key, Value, Compare, Alloc> const & lhs, map<Key, Value, Compare, Alloc> const & rhs) {
		return(!operator<(lhs, rhs)); //a>=b == !a<b
	}
};

#endif
