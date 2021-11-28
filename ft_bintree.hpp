/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:41:44 by miki              #+#    #+#             */
/*   Updated: 2021/11/28 03:33:31 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINTREE_H
# define FT_BINTREE_H


//DEBUG
#include "ft_bintree_debug.hpp"
//DEBUG

#include "ft_abintree.hpp"
#include <iostream>
#include <exception>

namespace ft
{
	template<typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator< typename ft::BintreeNode< T, T, T >::t_bstnode > >
	class bintree : public ft::Abintree<T, T, T, Compare, Alloc>, /*DEBUG*/public ft::bintree_printer< typename ft::Abintree<T, T, T, Compare, Alloc>::t_bstnode/*DEBUG*/ >
	{
		public:
			/* ---- NEEDFUL TYPEDEFS ---- */
			/*
			** Yet more C++ loveliness. These typedefs are defined in the base
			** class Abintree, but need to be re-typedeffed like this. Why?
			** Because the base class is templated, and you might create a
			** template specialization of the base class where your typedef
			** names are redefined as variables or functions. So, how is the
			** compiler supposed to be sure they are actually typenames you
			** naughty programmer expecting simple things to be simple?
			**
			** So you have to reassure it, "yes compiler, don't worry, it's a
			** typename, now go look it up."
			**
			** OMG, KILL ME NOW!! WHY, BJARNE, WHY!?
			*/
			typedef typename bintree::data_type					data_type;
			typedef typename bintree::t_bstnode					t_bstnode;
			typedef typename bintree::size_type					size_type;
			typedef typename bintree::C_key 					C_key;
			typedef typename bintree::iterator					iterator;
			typedef typename bintree::const_iterator			const_iterator;
			typedef typename bintree::reverse_iterator			reverse_iterator;
			typedef typename bintree::const_reverse_iterator	const_reverse_iterator;
			/* STL-CONTAINER-STYLE TYPEDEFS */
			typedef Alloc														allocator_type;
			typedef T															key_type;
			typedef T															mapped_type;
			typedef data_type													value_type;
			typedef Compare														key_compare;


		protected:
			void	assign_key_value_pointers(t_bstnode * node) const {
				node->key = &node->data;
				node->value = &node->data;
			}

		private:
			/* ---- VARIABLES ---- */
			//allocator_type	_alloc;

			/*
			** I died and went to C++ heaven after my problem with typedefs in
			** a templated parent class. This is what I found here: referencing
			** member variables from a templated parent class is also an ISSUE.
			**
			** Compile-time examination does not instantiate the template parent
			** class of a template class, so the compiler interprets that any
			** variables referenced in the derived class scope are independent,
			** and duly complains that it can't find where they are defined,
			** UNLESS you explicitly tell it that they are dependent on the
			** parent class...
			**
			** One way to do that is with 'using Parent<T>::var', meaning, "Hey,
			** compiler! When I say var, I mean the one Abintree<T> defines,
			** mmkay?"
			**
			** Another way is to use this->var everywhere. Does that mean the
			** 'this' pointer is of type Parent<T> * and it's using polymorphic
			** shenanigans? :?
			**
			** Whatever the case, I am using the first solution, mainly so I
			** have somewhere convenient to put this study note. :P
			**
			** I'll just make t_bstnode inherited from a parent class, he said.
			** Then I can pass it to the allocator via the parent class, he
			** said. IT'LL BE EASY, HE SAID! Two hours later...
			**
			** Anyway, all bintree functions that depend on Alloc or Comp for
			** their functionality will be defined in the derived class. All
			** other functions are defined in the parent class and used by the
			** derived class.
			*/
			/* PRIVATE BASE CLASS VARIABLE REFERENCES */
			using Abintree<data_type, key_type, mapped_type, key_compare, allocator_type>::_root;
			using Abintree<data_type, key_type, mapped_type, key_compare, allocator_type>::_min;
			using Abintree<data_type, key_type, mapped_type, key_compare, allocator_type>::_max;
			using Abintree<data_type, key_type, mapped_type, key_compare, allocator_type>::_size;
			/* PRIVATE BASE CLASS FUNCTION REFERENCES */

		public:
			/* CONSTRUCTORS AND DESTRUCTOR */
			bintree(void) : Abintree<T, T, T, Compare, Alloc>() {};
			~bintree(void) {
				//debug
				//std::cout << "freeeeedom" << std::endl;
				//debug
				this->bintree_free(_root);
			}

			/* ---- ITERATORS ---- */

			/* BEGIN AND END */
			/*
			** These functions respectively return iterators to the first
			** element of the container and the memory address after the last
			** element of the container. Const containers return
			** const_iterators, which are actually iterators TO const values
			** (the iterators themselves can be modified).
			**
			** In the binary tree, the address 'after' the last element and
			** 'before' the first element is virtualized to NULL, which is not
			** resolvable.
			**
			** Each iterator also stores its last resolvable address, so that if
			** incremented OR decremented from NULL it will return to its last
			** address.
			**
			** Note: If iterators are decremented or incremented past NULL, the
			** iterator will infinitely toggle between the last address and NULL
			** until the direction is reversed! So rather than the typical
			** segmentation fault for iterating out of bounds, you may also get
			** an infinite loop. Avoiding this behaviour would involve extra
			** overhead in the iterator and, frankly, I think the binary tree
			** has more than enough overhead as it is. ;)
			**
			** Note: While technically these are bidirectional iterators, full
			** functionality is implemented.
			*/
			iterator begin(void) {
				return (iterator(_min));
			}
			const_iterator begin(void) const {
				return (const_iterator(_min));
			}
			iterator end(void) {
				return (iterator(_max) + 1);
			}
			const_iterator end(void) const {
				return (const_iterator(_max) + 1);
			}

			iterator rbegin(void) {
				return (iterator(_max) + 1);
			}
			const_iterator rbegin(void) const {
				return (const_iterator(_max) + 1);
			}
			iterator rend(void) {
				return (iterator(_min));
			}
			const_iterator rend(void) const {
				return (const_iterator(_min));
			}

			/* ---- CAPACITY ---- */

			/* SIZE */
			/*
			** This method returns the number of ELEMENTS in the container, NOT
			** its allocated memory!
			*/
			size_type	size(void) const {
				return(_size);
			}

			/* EMPTY */
			/*
			** This method returns true if the container is empty. Otherwise it
			** returns false.
			*/
			bool		empty(void) const {
				return(_size == 0);
			}

			/* MAX_SIZE */
			/*
			** This method returns the container's maximum size, for which we
			** use its allocator's maximum size.
			*/
			size_type			max_size(void) const {
				return (this->_alloc.max_size());
			}
			
			/* ---- ELEMENT ACCESS ---- */

			/* OPERATOR[] */
			/*
			** This function will enable the following syntactic sugar:
			**
			** SYNTAX										RESOLUTION
			** my_bintree["existing_key"];					Reference to value pair of "existing_key".
			** my_bintree["existing_key"] = "new_value";	Replace value pair of "existing_key" with "new_value".
			** my_bintree["new_key"];						Insert new pair with "new_key" and default instantiated value.
			** my_bintree["new_key"] = "new_value";			Insert new pair with "new_key" and "new_value".
			**
			** When used to update values associated with existing keys, it is
			** an alias for find.
			**
			** When used to insert new keys, it is an alias for insert.
			**
			** So time complexity is O(log n) for each operation.
			**
			** Clever little invention, wish I'd thought of it instead of learnt
			** it from the STL. ;)
			*/
			mapped_type const &	operator[](key_type const & key) {

				return (((this->insert(key)).first)->data); // a reference to the mapped type of a pair(key, mapped_type()), or of an existing key if one already existed
			}

			/* INSERT SINGLE ELEMENT */
			
			ft::pair<iterator, bool> insert(value_type const & data) {
				size_type	old_size = size();
				t_bstnode *	new_node = this->bintree_add(_root, data, data);
				bool		return_status = size() > old_size ? true : false;
				return (ft::make_pair(iterator(new_node), return_status));
			}
			
			//DEBUG
			/* INSERT SINGLE ELEMENT WITH HINT */ //MAY NOW BE WORKING; NEEDS TESTING
			/*
			** The 'position' iterator serves as a hint, if you more or less
			** know where in the tree your data will be inserted.
			**
			** If the previous node in sequence from the hinted position is not
			** NULL and its key is greater than new key, or the next node in
			** sequence is not NULL and its key is less than the new key, the
			** hint is considered invalid and insertion is called on the tree
			** root instead. Otherwise insertion is called on the node pointed
			** to by the hint. If the hint is perfect, the new node will be
			** inserted in constant time. If it is rejected, it will be done in
			** logarithmic time, plus the time it took to check for validity.
			*/
			//DEBUG
			iterator	insert(iterator hint, value_type const & data) {
				if (this->is_valid_position(--hint, data))
				{
					t_bstnode * node = &(*hint);
					//DEBUG
					std::cerr << "CONFIRMO DE GUAYS INSERT" << std::endl;
					//DEBUG	
					return (iterator(this->bintree_add(node, data, data))); //constant time insertion
				}
				//DEBUG
				std::cerr << "CONFIRMO GILIPOLLAS INSERT" << std::endl;
				//DEBUG
				return (insert(data).first);
			}
			
			/* INSERT RANGE OF ELEMENTS */
			/*
			** This insert method inserts the range between first and last into
			** the tree.
			**
			** If invalid iterators are passed the computer explodes.
			*/
			template<typename InputIt>
			void		insert(InputIt first, InputIt last, typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type * = NULL)
			{
				for ( ; first != last; ++first)
					insert(first->data);
			}

			void	erase(t_bstnode & node) {
				this->bintree_delete(&node);
			}
			void		clear(void) {
				_root = this->bintree_free(this->_root);
			}
			/* THIS IS A DEBUG FUNCTION; REMOVE */
			//DEBUG
			void	print(void) {
				this->ft_bintree_print(_root, 0);
			}
			//DEBUG
			t_bstnode *	getRootNode(void) const {
				return (_root);
			}
			t_bstnode *	getNode(key_type const & key) const {
				return (this->bintree_search(_root, key));
			}

			/* LOWER BOUND */
			/*
			** This function first obtains the node containing an exact match to
			** 'key' (if one exists), or else the node that would be closest to
			** a node containing 'key', from the getNearestNode function, and
			** creates an iterator out of it. If the nearest_node key is less
			** than 'key', the iterator is incremented by one for the next
			** highest key. If the nearest_node key is greater than or equal to
			** 'key', then it is returned directly.
			**
			** -- RETURN VALUE --
			** The returned iterator points to the node considered to come AFTER
			** a node containing 'key', or to the first node EQUAL to 'key' if
			** one exists.
			*/
			iterator	lower_bound(key_type const & key) {
				t_bstnode *	nearest_node = this->getNearestNode(_root, NULL, key);
				iterator	ret(nearest_node);

				if (C_key(nearest_node->data) < C_key(key))
					++ret;
				return (ret);
			}

			const_iterator lower_bound(key_type const & key) const {
				t_bstnode *		nearest_node = this->getNearestNode(_root, NULL, key);
				const_iterator	ret(nearest_node);

				if (C_key(nearest_node->data) < C_key(key))
					++ret;
				return (ret);
			}

			/* UPPER BOUND */
			/*
			** This function first obtains the node containing an exact match to
			** 'key' (if one exists), or else the node that would be closest to
			** a node containing 'key', from the getNearestNode function, and
			** creates an iterator out of it. If the nearest_node key is less
			** than or equal to 'key', the iterator is incremented by one for
			** the next highest key. If the nearest_node key is greater than
			** 'key', then it is returned directly.
			**
			** -- RETURN VALUE --
			** The returned iterator points to the node considered to come AFTER
			** a node containing 'key'.
			*/
			iterator	upper_bound(key_type const & key) {
				t_bstnode * nearest_node = this->getNearestNode(_root, NULL, key);
				iterator	ret(nearest_node);

				if (C_key(nearest_node->data) <= C_key(key))
					++ret;
				return(ret);
			}
			
			const_iterator	upper_bound(key_type const & key) const {
				t_bstnode * 	nearest_node = this->getNearestNode(_root, NULL, key);
				const_iterator	ret(nearest_node);

				if (C_key(nearest_node->data) <= C_key(key))
					++ret;
				return(ret);
			}

			/* EQUAL RANGE */
			/*
			** This function returns the bounds of a range containing all nodes
			** with a key equal to 'key', wherein the first iterator points to
			** the beginning of the range and the second iterator points past
			** the end of the range. This tree implementation only admits unique
			** keys, so at most the range will consist of one node (the one
			** pointed to by the first iterator).
			**
			** If no match exists for 'key' then both iterators will point to
			** the node that would come after 'key'.
			**
			** The idea here is, imagine that you have a dictionary and one of
			** the keys is 'light', with multiple possible definitions. So you
			** have multiple 'lights' (not in a map, since it only admits unique
			** keys, but maybe in a multimap). For example:
			**
			** KEY		VAL
			** light	electromagnetic wave
			** light	elementary particle
			** light	luminous, bright
			** light	low in weight
			** lot		plot of land
			**
			** So, lower_bound("light") will return the first 'light',
			** upper_bound("light") will return 'lot', and now you can iterate
			** through the range, like so:
			**
			** for (it = lower_bound("light"), end = upper_bound("light"); it != end; ++it)
			**	do_stuff
			**
			** Or using for_each, if you're into that sort of thing, of course.
			** I happen to enjoy writing for loops. ;)
			**
			** In other words, you have a range of equal values - an
			** 'equal_range'.
			**
			** That's probably what you want the *_bound functions for, so the
			** equal_range function just directly retrieves that range for you
			** and sticks it in a pair with two iterators.
			**
			** This is all explained terribly in the reference manuals, because
			** C++ is all about making simple things simple. :p
			**
			** -- RETURN VALUE --
			** A pair of iterators, respectively the lower_bound and upper_bound
			** of the 'key' argument.
			*/
			ft::pair<iterator, iterator>				equal_range(key_type const & key) {
				return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(key_type const & key) const {
				return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}
			
			/* COUNT */
			/*
			** Returns the number of elements containing the key passed as key.
			** For this tree this will always be either 0 or 1 as duplicates are
			** not allowed, but a private recursive counting function is called
			** that will also work with multimap trees. If I ever make one. ;p
			**
			** -- RETURN VALUE --
			** The number of elements containing the 'key' passed as argument.
			*/
			size_type	count(key_type const & key) const {
				return (this->recursive_count(_root, key));
			}

			/* FIND */
			/*
			** -- RETURN VALUE --
			** Returns an iterator to the node with a key equal to the argument
			** passed as 'key'. If no such node exists, returns the end
			** iterator.
			*/
			iterator	find(key_type const & key) {
				t_bstnode *	node = this->bintree_search(_root, key);
				return (node == NULL ? end() : iterator(node));
			}
	};
};

#endif