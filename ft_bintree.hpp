/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:41:44 by miki              #+#    #+#             */
/*   Updated: 2021/11/29 16:19:28 by miki             ###   ########.fr       */
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
			typedef typename bintree::iterator					iterator;
			typedef typename bintree::const_iterator			const_iterator;
			typedef typename bintree::reverse_iterator			reverse_iterator;
			typedef typename bintree::const_reverse_iterator	const_reverse_iterator;
			/* STL-CONTAINER-STYLE TYPEDEFS */
			typedef Alloc										allocator_type;
			typedef T											key_type;
			typedef T											mapped_type;
			typedef data_type									value_type;
			typedef Compare										key_compare;


		protected:
			void	assign_key_value_pointers(t_bstnode * node) const {
				node->key = &node->data;
				node->value = &node->data;
			}

		private:
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
			** shenanigans? Or is it something more arcane still? :?
			**
			** Whatever the case, I am using the first solution for _root,
			** mainly so I have somewhere convenient to put this study note. :P
			**
			** I'll just make t_bstnode inherited from a parent class, he said.
			** IT'LL BE EASY, HE SAID! Two hours later...
			*/
			/* PRIVATE BASE CLASS VARIABLE REFERENCES */
			using Abintree<data_type, key_type, mapped_type, key_compare, allocator_type>::_root;

		public:
			/* CONSTRUCTORS AND DESTRUCTOR */
			bintree(void) : Abintree<T, T, T, Compare, Alloc>() {};
			~bintree(void) {
				this->bintree_free(_root); //<- Look, ma! No 'this->' on my _root! ;)
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
			
			ft::pair<iterator, bool> insert(data_type const & data) {
				size_type	old_size = this->size();
				t_bstnode *	new_node = this->bintree_add(_root, data, data);
				bool		return_status = this->size() > old_size ? true : false;
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
			iterator	insert(iterator hint, data_type const & data) {
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

			/* THIS IS A DEBUG FUNCTION; REMOVE */
			//DEBUG
			void		print(void) {
				this->ft_bintree_print(_root, 0);
			}
			//DEBUG
	};
};

#endif