/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:41:44 by miki              #+#    #+#             */
/*   Updated: 2021/11/21 22:24:38 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINTREE_H
# define FT_BINTREE_H


//DEBUG
#include "ft_bintree_debug.hpp"
//DEBUG

#include "ft_abintree.hpp"
#include <iostream>


namespace ft
{
	template<typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<typename ft::Abintree<T>::t_bstnode> >
	class bintree : public ft::Abintree<T>, /*DEBUG*/public ft::bintree_printer< typename ft::Abintree<T>::t_bstnode/*DEBUG*/ >
	{
		// /* NEEDFUL TYPEDEFS */
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
			typedef typename bintree::data_type	data_type;
			typedef typename bintree::t_bstnode	t_bstnode;
			typedef Alloc						allocator_type;
			typedef Compare						key_compare;

		private:
			allocator_type	_alloc;
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
			using Abintree<T>::_root;
			using Abintree<T>::bintree_depth;
			using Abintree<T>::right_rotation;
			using Abintree<T>::left_rotation;
			using Abintree<T>::left_case;
			using Abintree<T>::right_case;
			using Abintree<T>::bintree_balance;
			
			/*
			** This function dynamically reserves memory in heap for a new node
			** in a binary tree and sets the data segment of that node to the
			** value of the argument. The left and right child pointers are
			** nulled. Each node is RED by default.
			**
			** -- RETURN VALUES --
			** A pointer to the new binary tree node is returned to the caller.
			** If the memory reservation fails, a NULL pointer is returned.
			*/
			t_bstnode	*create_new_node(t_bstnode *parent, data_type data)
			{
				t_bstnode	*node;

				node = _alloc.allocate(1);
				_alloc.construct(node, t_bstnode());
				if (node != NULL)
				{
					node->data = data;
					node->parent = parent;
					node->left = NULL;
					node->right = NULL;
					node->color = t_bstnode::RED;
				}
				return (node);
			}

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
			t_bstnode	*bintree_search(t_bstnode *root, data_type data)
			{
				if (root == NULL || root->data == data)
					return (root);
				else if (data <= root->data)
					return (bintree_search(root->left, data));
				else
					return (bintree_search(root->right, data));
			}

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
			*/
			t_bstnode	*bintree_insert(t_bstnode *parent, t_bstnode *root, \
			data_type data)
			{
				if (root == NULL)
					root = create_new_node(parent, data);
				else if (data <= root->data)
					root->left = bintree_insert(root, root->left, data);
				else
					root->right = bintree_insert(root, root->right, data);
				return (root);
			}

			t_bstnode	*bintree_add(t_bstnode *&root, data_type data)
			{
				t_bstnode	*new_node;

				root = bintree_insert(NULL, root, data);
				new_node = bintree_search(root, data);
				bintree_balance(&root, new_node);
				return (root);
			}

			t_bstnode	*node_delete(t_bstnode *node)
			{
				std::memset(node, 0, sizeof(t_bstnode));
				_alloc.destroy(node);
				_alloc.deallocate(node, sizeof(t_bstnode));
				//delete node;
				return (NULL);
			}

			t_bstnode	*root_canal(t_bstnode *root)
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
			t_bstnode	*bintree_free(t_bstnode *root)
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
			bintree(void) : Abintree<T>() {};
			~bintree(void) {
				//debug
				//std::cout << "freeeeedom" << std::endl;
				//debug
				bintree_free(_root);
			}
			void	push_back(data_type data){
				bintree_add(_root, data);
			}
			void	print(void) {
				this->ft_bintree_print(_root, 0);
			}
			t_bstnode *	getRootNode(void) const {
				return (_root);
			}

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
					t_bstnode const *	ascendent_node = node;
					ascendent_node = node->parent;													//DEBUG
					while (ascendent_node != NULL && ascendent_node->data < node->data) //replace with comp obj
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
					t_bstnode const *	ascendent_node = node;											//replace with comp obj
					while (ascendent_node != NULL && !(ascendent_node->data < node->data) ) //replace with comp obj
						ascendent_node = ascendent_node->parent;
					node = ascendent_node;
				}
				else
					node = NULL;
				return (const_cast<t_bstnode *>(node));
			}
	};
};

#endif