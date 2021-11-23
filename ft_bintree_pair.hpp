/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_pair.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:41:44 by miki              #+#    #+#             */
/*   Updated: 2021/11/23 12:47:07 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINTREE_PAIR_H
# define FT_BINTREE_PAIR_H

#include "utility.hpp"
#include "ft_abintree.hpp"

//DEBUG
#include "ft_bintree_debug.hpp"
//DEBUG
//#include <memory>


#include <iostream>
#include <cstring>

namespace ft
{
	template< typename T1, typename T2, typename Compare = ft::less<T1>,
	typename Alloc = std::allocator< typename ft::Abintree< ft::pair<T1, T2> >::t_bstnode > >
	class bintree_pair : public ft::Abintree< ft::pair<T1, T2> >, /*DEBUG*/public ft::bintree_printer< typename ft::Abintree< ft::pair<T1, T2> >::t_bstnode, int/*DEBUG*/ >
	{
		/* NEEDFUL TYPEDEFS */
		public:
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
			typedef typename bintree_pair::data_type	data_type;
			typedef typename bintree_pair::t_bstnode	t_bstnode;
			typedef typename bintree_pair::size_type	size_type;

			/* STL CONTAINER STYLE TYPEDEFS */
			typedef Alloc								allocator_type;
			typedef T1									key_type;
			typedef T2									mapped_type;
			typedef data_type							value_type;
			typedef Compare								key_compare;

		private:
			allocator_type	_alloc;
			key_compare		_is_less;

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
			using Abintree<data_type>::_root;
			using Abintree<data_type>::_min;
			using Abintree<data_type>::_max;
			using Abintree<data_type>::_size;
			using Abintree<data_type>::bintree_depth;
			using Abintree<data_type>::right_rotation;
			using Abintree<data_type>::left_rotation;
			using Abintree<data_type>::left_case;
			using Abintree<data_type>::right_case;
			using Abintree<data_type>::bintree_balance;
			using Abintree<data_type>::fix_double_black;

			/* BINTREE_PAIR ITERATOR */
			/* THEY POINT TO NODE */
			template<typename iT, typename Category>
			struct Iterator : public ft::iterator_traits<iT, Category>
			{
				//Constructible
				Iterator(void) : _m_ptr(NULL), _last_node(NULL) {}
				explicit Iterator(typename Iterator::pointer ptr) : _m_ptr(ptr), _last_node(NULL) {}
				Iterator(Iterator const & src) : _m_ptr(src._m_ptr), _last_node(src._last_node), _is_less(src._is_less) {}
				//Assignment Operator Overload
				Iterator &	operator=(Iterator const & rhs) {
					this->_m_ptr = rhs._m_ptr;
					this->_last_node = rhs._last_node;
					this->_is_less = rhs._is_less;
					return (*this);
				}
				//Relational Operator Overloads
				bool	operator==(Iterator const & rhs) const {
					return (this->_m_ptr == rhs._m_ptr); //si las direcciones son iguales las keys son iguales cauenlaleche
				}
				bool	operator!=(Iterator const & rhs) const {
					return (!operator==(rhs)); //a!=b == !(a==b)
				}
				bool	operator<(Iterator const & rhs) const {
					return (_is_less(this->_m_ptr->data.first, rhs._m_ptr->data.first));
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
					if (this->_m_ptr != NULL)
					{
						this->_last_node = this->_m_ptr;
						this->_m_ptr = getNextNode(this->_m_ptr);
					}
					else
					{
						this->_m_ptr = this->_last_node;
						this->_last_node = NULL;
					}
					return (*this);
				}
				Iterator							operator++(int) {
					Iterator	ret(this->_m_ptr);
					if (this->_m_ptr != NULL)
					{
						this->_last_node = this->_m_ptr;
						this->_m_ptr = getNextNode(this->_m_ptr);
					}
					else
					{
						this->_m_ptr = this->_last_node;
						this->_last_node = NULL;
					}
					return (ret);
				}
				Iterator & 							operator--(void) {
					if (this->_m_ptr != NULL)
					{
						this->_last_node = this->_m_ptr;
						this->_m_ptr = getPrevNode(this->_m_ptr);
					}
					else
					{
						this->_m_ptr = this->_last_node;
						this->_last_node = NULL;
					}
					return (*this);
				}
				Iterator							operator--(int) {
					Iterator	ret(this->_m_ptr);
					if (this->_m_ptr != NULL)
					{
						this->_last_node = this->_m_ptr;
						this->_m_ptr = getPrevNode(this->_m_ptr);
					}
					else
					{
						this->_m_ptr = this->_last_node;
						this->_last_node = NULL;
					}
					return (ret);
				}
				Iterator &							operator+=(int inc) {
					for (int i = 0; i < inc; ++i)
						operator++();
					return (*this);
				}
				Iterator &							operator-=(int dec) {
					for (int i = 0; i < dec; ++i)
						operator--();
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
				typename Iterator::difference_type	operator+(Iterator const & rhs) const {
					typename Iterator::difference_type	hops = 0;
					bintree_search(this->_m_ptr, rhs._m_ptr->data.first, hops);
					return (hops);
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
					return (*(*this + pos));
				}
				//aaaaah!!!! -> . ... claro!!!! :D
				typename Iterator::pointer		operator->(void) const {
					return (this->_m_ptr);
				}
				protected:
					typename Iterator::pointer	_m_ptr;
					typename Iterator::pointer	_last_node;
					key_compare					_is_less;

				/*
				** Esta función busca el MENOR de los nodos MAYORES que 'node'.
				**
				** Si el nodo a su derecha no es NULL, el MENOR de los nodos MAYORES
				** que 'node' será el de más a la izquierda del de su derecha.
				**
				** Si el nodo a su derecha es NULL, el MENOR de los nodos MAYORES
				** que 'node' será el primer nodo ascendiente mayor que él.
				**
				** Si en ninguno de los dos casos se encuentra un nodo mayor, o
				** si 'node' carece tanto de hijo derecho como de padre, entonces ya
				** es el mayor de los nodos.
				**
				** -- VALOR DE RETORNO --
				** Se devuelve un puntero al menor de los nodos mayores que 'node'.
				** Si 'node' ya es el mayor nodo, se devuelve NULL.
				**
				** This function searches for the LEAST of the nodes that are
				** GREATER than 'node'... eh... I hope that makes sense. I think it
				** makes more sense in Spanish, so I wrote it for myself in Spanish
				** for future reference. xD
				**
				** If the node to the right of 'node' is not NULL, then the LEAST
				** of the nodes GREATER than 'node' is the leftmost node from the
				** node to its right.
				**
				** If the node to the right of 'node' is NULL, then the LEAST of
				** the nodes GREATER than 'node' is the first ascendent node greater
				** than 'node'.
				**
				** If there is no greater node in either case, or if 'node' has no
				** right child and no parent, then 'node' is already the greatest
				** node.
				**
				** -- RETURN VALUE --
				** A pointer to the least of the nodes greater than 'node' is
				** returned. If 'node' is already the greatest, NULL is returned.
				*/
				t_bstnode *	getNextNode(t_bstnode const * node) const {
					if (node->right != NULL)
					{
						node = node->right;
						while (node->left != NULL)
							node = node->left;
					}
					else if (node->parent != NULL)
					{
						t_bstnode const *	ascendent_node = node->parent;
						while (ascendent_node != NULL && _is_less(ascendent_node->data.first, node->data.first))
							ascendent_node = ascendent_node->parent;
						node = ascendent_node;
					}
					else
						node = NULL;
					return (const_cast<t_bstnode *>(node));
				}

				/*
				** Esta función busca el MAYOR de los nodos MENORES que 'node'.
				**
				** Si el nodo a su izquierda no es NULL, el MAYOR de los nodos
				** MENORES que 'node' será el de más a la derecha del de su
				** izquierda.
				**
				** Si el nodo a su izquierda es NULL, el MAYOR de los nodos MENORES
				** que 'node' será el primer ascendiente menor que o igual a él.
				** Nótese que el 'igual a' no será relevante para ft::map, que
				** envuelve esta clase, ya que no admite duplicados.
				**
				** Si en ninguno de los dos casos se encuentra un nodo menor, o si
				** 'node' carece tanto de hijo izquierdo como de padre, entonces ya
				** es el menor de los nodos.
				**
				** -- VALOR DE RETORNO --
				** Se devuelve un puntero al mayor de los nodos menores que 'node'.
				** Si 'node' ya es el menor nodo, se devuelve NULL.
				**
				** This function searches for the greatest of the nodes that are
				** lesser than 'node'.
				**
				** If the node to the left of 'node' is not NULL, then the GREATEST
				** of the nodes that are LESSER than 'node' is the rightmost node
				** from the node to its left.
				**
				** If the node to the left of 'node' is NULL, then the GREATEST of
				** the nodes that are LESSER than 'node' is the first ascendent node
				** less than 'node'.
				**
				** If there is no lesser node in either case, or if 'node' has no
				** left child and no parent, then 'node' is already the least node.
				**
				** -- RETURN VALUE --
				** A pointer to the greatest of the nodes lesser than 'node' is
				** returned. If 'node' is already the least node, NULL is returned.
				*/
				t_bstnode * getPrevNode(t_bstnode const * node) const {
					if (node->left != NULL)
					{
						node = node->left;
						while (node->right != NULL)
							node = node->right;
					}
					else if (node->parent != NULL)
					{
						t_bstnode const *	ascendent_node = node->parent;
						while (ascendent_node != NULL && !_is_less(ascendent_node->data.first, node->data.first) )
							ascendent_node = ascendent_node->parent;
						node = ascendent_node;
					}
					else
						node = NULL;
					return (const_cast<t_bstnode *>(node));
				}
			};

			/* METHODS */

			/*
			** This function will search the binary tree whose 'root' is passed
			** as the first argument for the value passed as 'data' in the
			** second argument.
			**
			** If the root node pointer is not NULL and the data is not present
			** in that node, this function will recursively call itself, passing
			** the pointer to the left or right branches of that node, as the
			** data is less than, equal to or greater than the data within the
			** node, until either a NULL pointer or a node with matching data is
			** found.
			**
			** -- RETURN VALUES --
			** If the 'data' passed as the second argument is found in the tree,
			** a pointer to the node containing the data is returned. If it is
			** not present in the tree, a NULL pointer is returned.	
			*/
			t_bstnode	*bintree_search(t_bstnode * root, key_type const & key) const
			{
										//_is_less(root->data.first, key) is false & _is_less(key, root->data.first) is false
										//is just a way of saying if (root->data.first < key is false and key < root->data.first is also false)
										//which is just a way of saying "if they are equal"
										//this hideousness is required by the assignment, i'm so sorry. :P
				if (root == NULL || !_is_less(root->data.first, key) & !_is_less(key, root->data.first)) //if (root == NULL || root->data.first == key) :P
					return (root);
				else if (_is_less(key, root->data.first) || !_is_less(root->data.first, key)) // if (key <= root->data.first) :P truly sorry about this :P
					return (bintree_search(root->left, key));
				else
					return (bintree_search(root->right, key));
			}

			t_bstnode *	bintree_search(t_bstnode *root, key_type const & key, typename Iterator<t_bstnode, std::bidirectional_iterator_tag>::difference_type & hops) const
			{
				if (root == NULL || !_is_less(root->data.first, key) & !_is_less(key, root->data.first))
					return (root);
				else if (_is_less(key, root->data.first) || !_is_less(root->data.first, key))
					return (bintree_search(root->left, key, ++hops));
				else
					return (bintree_search(root->right, key, ++hops));
			}
			
			/* CREATE_NEW_NODE */
			/*
			** This function dynamically reserves memory in heap for a new node
			** in a binary tree and sets the data segment of that node to the
			** value of the argument. The left and right child pointers are
			** nulled. Each node is RED by default.
			**
			** -- RETURN VALUE / EXCEPTIONS --
			** A pointer to the new binary tree node is returned to the caller.
			** If the memory reservation fails, a NULL pointer is returned and
			** a bad_alloc exception is rethrown to the caller.
			*/
			t_bstnode *	create_new_node(t_bstnode * parent, data_type new_pair) throw (std::bad_alloc, std::exception)
			{
				t_bstnode *	node = NULL;

				try
				{
					node = _alloc.allocate(1);
					_alloc.construct(node, t_bstnode());
					node->data = new_pair;
					node->parent = parent;
					node->left = NULL;
					node->right = NULL;
					node->color = t_bstnode::RED;
				}
				catch (std::bad_alloc const & e)
				{
					throw ;
				}
				catch (std::exception const & e)
				{
					throw ;
				}
				return (node);
			}

			/* BINTREE_INSERT */
			/*
			** This function inserts a node into a binary tree. If passed a NULL
			** pointer, a root node will be created.
			**
			** In the binary tree all values less than or equal to any node
			** value will be stored to the 'left' of that node, and all values
			** greater than any node value will be stored to the 'right' of that
			** node (note, 'left' and 'right' here are abstractions, not literal
			** orientations). This makes it possible to zero in on a value
			** within a set of values more quickly when searching for it by
			** using an approximation depending on whether the value is greater
			** than or less than the node value being analysed at any given
			** juncture.
			**
			** To create new nodes in a tree, the function will recursively call
			** itself, seeking a path to the nearest value (in an existing node
			** in the tree) to the value to be inserted, and store the value in
			** relation to that node. That node's right or left pointer will
			** then be set to point to the new node. The rest of the recursively
			** called functions will then return the original unmodified values
			** of the pointer addresses through which they accessed the nodes in
			** the path.
			**
			** So, for insert(root, 220);
			**
			**								200
			**								 |
			**								/ \
			**							 100   300
			**							 / \   / \
			**							 X X 220 X
			**
			** Now, in a set of four numbers (200, 100, 300, 220), a match for
			** 220 can be found from root in just two comparisons (as 220 is
			** greater than 200, as 220 is less than 300), instead of
			** potentially as many as four in an array or list (as 220 is not
			** equal to 200, as 220 is not equal to 100, as 220 is not equal to
			** 300, as 220 is equal to 220).
			**
			** This makes the structure relatively less efficient than lists and
			** arrays for frequent insertions and deletions, but more efficient
			** for frequent searches, such as of ordered key values.
			**
			** -- RETURN VALUE / EXCEPTIONS --
			** This function returns a pointer to the root of the tree passed as
			** an argument. If memory allocation failed, a bad_alloc exception
			** is rethrown to the caller. If memory allocation succeeded, the
			** address of the newly created node is written to the new_node
			** pointer, a reference to which is passed as an argument.
			*/
			t_bstnode *	bintree_insert(t_bstnode * parent, t_bstnode *root, \
			data_type const & new_pair, t_bstnode *& new_node) throw (std::bad_alloc, std::exception)
			{
				if (root == NULL)
				{
					try
					{
						root = create_new_node(parent, new_pair);
						new_node = root;
					}
					catch (std::bad_alloc const & e)
					{
						throw ;
					}
					catch (std::exception const & e)
					{
						throw ;
					}
				}
				else if (_is_less(new_pair.first, root->data.first) || !_is_less(root->data.first, new_pair.first)) //if (new_pair.key <= root-data.key)
					root->left = bintree_insert(root, root->left, new_pair, new_node);
				else
					root->right = bintree_insert(root, root->right, new_pair, new_node);
				return (root);
			}

			/* BINTREE_ADD */
			/*
			** This function is an adaptation of my original red-black binary
			** tree insert node gateway function in C. The new public method in
			** the C++ class calls this function directly to push new data onto
			** the tree.
			**
			** This function allocates memory. The insert and create_new_node
			** functions, being dependent on memory allocation, now throw
			** exceptions if memory allocation is impossible. The exceptions are
			** safely caught and handled here before any part of the
			** pre-existing tree is modified.
			**
			** If allocation succeeds the function, balances the tree as needed,
			** updates the tree _size variable, and updates the _min and _max
			** pointers if needed. The new_node pointer is invalidated by
			** bintree_balance so its associated key must be searched for again
			** to get the final address.
			**
			** -- RETURN VALUE --
			** A pointer to the root of the tree is returned. If the root
			** changed due to balancing, this will be a pointer to the new root.
			*/
			t_bstnode	*bintree_add(t_bstnode *& root, data_type const & new_pair)
			{
				t_bstnode *		new_node;
				key_type const	new_key = new_pair.first; //I was worried it might not jive with a std::move instruction if I ever use one :p

				try
				{
					root = bintree_insert(NULL, root, new_pair, new_node);
					bintree_balance(&root, new_node);
					++_size;
					if (_min == NULL || _is_less(new_key, _min->data.first)) //if (_min == NULL || new_pair.key < _min->data.key)
						_min = bintree_search(root, new_key);
					if (_max == NULL || _is_less(_max->data.first, new_key)) //if (_max == NULL || new_pair.key > _max->data.key)
						_max = bintree_search(root, new_key);
				}
				catch(std::bad_alloc const & e)
				{
					std::cerr << e.what() << std::endl;
				}
				catch(std::exception const & e)
				{
					std::cerr << e.what() << std::endl;
				}
				return (root);
			}

			t_bstnode *	node_delete(t_bstnode * node)
			{
				std::memset(node, 0, sizeof(t_bstnode));
				_alloc.destroy(node);
				_alloc.deallocate(node, sizeof(t_bstnode));
				--_size;
				return (NULL);
			}

			/* BINTREE_DELETE */
			/*
			** Deletes a node from a binary tree. You have NO idea the HORROR,
			** the PAIN that this implies. It's much worse than mere insertion.
			** SO much worse. You monster.
			*/
			t_bstnode * bintree_delete(t_bstnode * node) {
				if (node == NULL)
					return (NULL);
				if (node == _min)
					_min = &(*(iterator(_min) + 1));
				if (node == _max)
					_max = &(*(iterator(_max) - 1));
				if (node->right == NULL && node->left == NULL) //it's a leaf/both children are NULL
				{
					if (node->parent != NULL)
					{
						if (node->parent->right == node)
							node->parent->right = NULL;
						else
							node->parent->left = NULL;
					}
					if (node->color == t_bstnode::RED) //NULLs are black, so if original node is RED
						node->color = t_bstnode::BLK; //replacement node is BLACK
					else // if both original node and replacement node are BLACK
						fix_double_black(node); //replacement node is... DOUBLE BLACK! of course! what you mean that's not a color??? xD
					node_delete(node);
				}
				else if (node->left == NULL) //has only right child
				{
					//node == v
					//node->right == u
					node->data = node->right->data; //copy child to node
					if (node->color == t_bstnode::RED || node->right->color == t_bstnode::RED) //if either original node or replacement node are RED...
						node->color = t_bstnode::BLK; //replacement node is BLACK
					else //if both original node and replacement node are BLACK...
						fix_double_black(node); //replacement node is... DOUBLE BLACK! of course! what you mean that's not a color??? xD
					node->right = node_delete(node->right); //delete the original child
				}
				else if (node->right == NULL) //has only left child
				{
					node->data = node->left->data; // copy child to node
					if (node->color == t_bstnode::RED || node->left->color == t_bstnode::RED)  //if either original node or replacement node are RED...
						node->color = t_bstnode::BLK; //replacement node is BLACK
					else //if both original node and replacement node are BLACK...
						fix_double_black(node); //replacement node is... DOUBLE BLACK! of course! what you mean that's not a color??? xD
					node->left = node_delete(node->left); //delete the original child
				}
				else //has two children
				{
					//get successor node, swap data with it, and delete the successor
					t_bstnode * successor = node->right;
					value_type	data;
					while (successor->left != NULL)
						successor = successor->left;
					data = node->data;
					node->data = successor->data;
					successor->data = node->data;
					bintree_delete(successor);
				}
				return (NULL);
			}

			t_bstnode	*root_canal(t_bstnode * root)
			{
				if (root != NULL)
					if (root->left == NULL && root->right == NULL)
						root = node_delete(root);
				return (NULL);
			}

			/*
			** This is an iterative function for freeing memory used by binary
			** trees. Memory is zeroed before freeing. This is CPU-intensive,
			** but memory-light. It can be used to free trees that would be too
			** big to free with a recursive function.
			**
			** The function searches for childless nodes with a bias for left
			** children. When a childless node is found its memory is zeored and
			** it is freed, and then the next childless node is searched for.
			**
			** The function works through infanticide. Parents kill their
			** childless children. Horrifying, but I couldn't think of a more
			** humane way to do this. That's the world of binary trees. -_-
			**
			** We iterate down the tree with a pointer, starting with left
			** children. If the parent finds a left child, it checks whether its
			** child has children. If the parent finds a grandchild, it becomes
			** the child, and then we check the child's children for children.
			**
			** If the child has no children of its own, the parent DELETES its
			** own child. :_( Then it comes back for another round to check its
			** other child for children...
			**
			** Once the parent is childless, it becomes its own parent, and the
			** grim cycle continues, until everyone is DEAD. The root_canal
			** performs the final suicide.
			**
			** I hope you're happy, Valgrind. :(
			*/
			t_bstnode	*bintree_free(t_bstnode * root)
			{
				t_bstnode	*parent;

				parent = root;
				while (parent != NULL)
				{
					while (parent->left != NULL || parent->right != NULL)
					{
						if (parent->left != NULL)
						{
							if (parent->left->left != NULL || parent->left->right != NULL)
								parent = parent->left;
							else
								parent->left = node_delete(parent->left);
						}
						else if (parent->right != NULL)
						{
							if (parent->right->left != NULL || parent->right->right != NULL)
								parent = parent->right;
							else
								parent->right = node_delete(parent->right);
						}
					}
					parent = parent->parent;
				}
				return (root_canal(root));
			}

		public:
			typedef Iterator<t_bstnode, std::bidirectional_iterator_tag>		iterator;
			typedef Iterator<const t_bstnode, std::bidirectional_iterator_tag>	const_iterator; //Iterator formed with const T, so its value_type, pointers to value_type, references to value_type, etc, also all refer to const value
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

			bintree_pair(void) : Abintree<data_type>() {};
			~bintree_pair(void) {
				//debug
				//std::cout << "freeeeedom" << std::endl;
				//debug
				bintree_free(_root);
			}
			void	insert(key_type const & key, mapped_type const & value) {
				bintree_add(_root, ft::make_pair(key, value));
			}
			void	erase(t_bstnode & node) {
				bintree_delete(&node);
			}
			//DEBUG
			void	print(void) {
				this->ft_bintree_print(_root, 0);
			}
			//DEBUG
			t_bstnode &	getRootNode(void) const {
				return (_root);
			}
			t_bstnode &	getNode(key_type const & key) const {
				return (*(bintree_search(_root, key)));
			}

			/* ---- ITERATORS ---- */

			/* BEGIN AND END METHODS */
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
			** functionality is implemented. Nevertheless, the inefficiency of
			** actually iterating on a binary tree is OFF THE CHARTS. Seriously.
			** Just don't do it. If you need to iterate, use another structure.
			** The tree is really meant for performing searches.
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
	};
};

#endif