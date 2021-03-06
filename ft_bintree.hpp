/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:41:44 by miki              #+#    #+#             */
/*   Updated: 2022/01/18 00:25:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINTREE_H
# define FT_BINTREE_H

//DEBUG
#include "ft_bintree_debug.hpp"
//DEBUG
#include "ft_abintree.hpp"

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
			typedef typename bintree::t_lstnode					t_lstnode;
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
			using Abintree<data_type, key_type, mapped_type, key_compare, allocator_type>::_end_lst;

		public:
			/* CONSTRUCTORS AND DESTRUCTOR */
			explicit bintree(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : Abintree<T, T, T, Compare, Alloc>(comp, alloc) {};
			/* RANGE CONSTRUCTOR */
			template<class InputIt>
			bintree(InputIt first, InputIt last, const key_compare & comp = key_compare(),
			const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<ft::has_iterator_category<InputIt>::value, InputIt>::type * = NULL) : Abintree<data_type, key_type, mapped_type, key_compare, allocator_type>(comp, alloc) {
				this->insert(first, last);
			}
			/* COPY CONSTRUCTOR */
			bintree(bintree const & src) : Abintree<data_type, key_type, mapped_type, key_compare, allocator_type>(src._is_less, src._alloc) {
				this->insert(src.begin(), src.end());
			}
			~bintree(void) {
				this->lst_clr(this->_list_head, this->_list_tail);
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

				return (((this->insert(key)).first)->data);
			}

			/* INSERT SINGLE ELEMENT */
			/*
			** This function tries to insert the value passed as data into the
			** tree.
			**
			** ---- RETURN VALUE ----
			** A pair will be returned. If insertion was successful, the pair
			** will contain an iterator pointing to the newly inserted value and
			** a boolean set to true. If unsuccessful because the key already
			** exists, the pair will contain an iterator pointing to the
			** existing value and a bool set to false. If unsuccessful due to
			** memory allocation failure, the pair will contain a NULL iterator
			** and a bool set to false.
			*/
			ft::pair<iterator, bool> insert(data_type const & data) {
				size_type	old_size = this->size();
				t_bstnode *	new_node = this->bintree_add(_root, data, data);
				bool		return_status = this->size() > old_size ? true : false;
				return (ft::make_pair(iterator(this->thread_search(new_node), _end_lst), return_status));
			}

			/* INSERT SINGLE ELEMENT WITH HINT */
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
			**
			** TL;DR NOTE: If the insertion point is the tree root, we reject it
			** even if valid and use the logarithmic insertion. This remains
			** compliant with the constant time requirement for this function
			** because, for a root node insertion, we know the logarithmic
			** look-up will behave as a constant time insertion anyway, since it
			** will always be in the best case scenario, one comparison, which
			** is O(1), constant time.
			**
			** LONG NOTE:
			**
			** So. Why do I do this, though?
			**
			** The node pointer passed by reference to bintree_add may be
			** updated if the tree is rebalanced in a way that changes the
			** identity of the node at that position. This does not normally
			** matter, because all the references to the tree nodes are internal
			** to the tree (present in other nodes) or to the _thread list, both
			** of which are updated by separate logic inside the bintree_add
			** function, mostly recently added logic.
			**
			** HOWEVER, the root node has an ADDITIONAL reference in the tree
			** instance, namely: _root. A relic from when this was a C struct
			** without iterators with a thousand levels of indirection and a
			** bazillion getters and setters, and you simply accessed the root
			** of the tree through the _root pointer. Ah, what simple days those
			** were! Simple and happy!
			**
			** This reference must also be updated if the root node identity
			** changes, or else the _root pointer will be invalidated. The
			** bintree_balance function, also originally C code, was coded to
			** take the address of a root node and automatically update it as
			** needed. So, if we pass bintree_add a reference to the _root
			** pointer, which is exactly what normal (non-hint) insert does,
			** _root will be passed to bintree_balance and appropriately
			** updated there. Otherwise, the local node pointer we create in
			** this function would be updated by bintree_balance instead, and
			** _root would become invalidated.
			**
			** In other words, I'd have to code new logic to update the _root
			** pointer as needed, which would be a pain in the arse.
			**
			** Considering that realizing this case theoretically should exist
			** (amazing what 10 hours of sleep will do for the mind! xD),
			** confirming my theory was correct, and coming up with a workaround
			** and confirming the workaround works has all been a pain in the
			** arse already, I've decided to give my poor arse a break.
			*/
			iterator	insert(iterator hint, data_type const & data) {
				if (hint == this->end()) //if lower bound of data is end(), data MUST be inserted as a right child of previous node in the sequence
					--hint;
				if (this->is_valid_position(hint, data))
				{
					// //DEBUG
					// std::cerr << "CONFIRMO DE GUAYS INSERT" << std::endl;
					// //DEBUG	
					t_bstnode * node = &(*hint);
					return (iterator(static_cast<t_lstnode *>((this->bintree_add(node, data, data))->assoc_lst_node), _end_lst)); //constant time insertion
				}
				// //DEBUG
				// std::cerr << "CONFIRMO GILIPOLLAS INSERT" << std::endl;
				// //DEBUG
				return (insert(data).first); //log time insertion (if the insertion point is _root, constant tme)
			}

			/* INSERT RANGE WITH CONTAINER ITERATORS */
			/*
			** This insert method inserts the range between first and last into
			** the tree.
			**
			** If invalid iterators are passed the computer explodes.
			*/
			void		insert(iterator first, iterator last)
			{
				for ( ; first != last; ++first)
					insert(first->data);
			}

			void		insert(const_iterator first, const_iterator last)
			{
				for ( ; first != last; ++first)
					insert(first->data);
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
					insert(*first);
			}

			/* THIS IS A DEBUG FUNCTION; MAYBE DON'T REMOVE? */
			//DEBUG
			void		print(void) {
				this->ft_bintree_print(_root, 0);
			}
			//DEBUG
	};
};

#endif
