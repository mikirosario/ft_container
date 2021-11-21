/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abintree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:13:06 by miki              #+#    #+#             */
/*   Updated: 2021/11/21 20:15:05 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ABINTREE_H
# define FT_ABINTREE_H

#include <cstring>

namespace ft
{
	template<typename T>
	class Abintree
	{
		public:
				typedef T		data_type;

				/*
				** For the single-value implementation of ft::bintree the data type
				** will be T.
				*/
				typedef struct	s_bstnode
				{
					/*
					** This enum field will define a node color as red or black.
					*/
					typedef enum	e_bstcolor
					{
						BLK = 0, RED
					}				t_bstcolor;
					struct s_bstnode				*parent;
					struct s_bstnode				*left;
					struct s_bstnode				*right;
					data_type						data;
					t_bstcolor						color;
				}				t_bstnode;
		protected:
			/* VARIABLES */
			t_bstnode *		_root;
			
			/* CONSTRUCTORS AND DESTRUCTOR */
			Abintree(void) : _root(NULL) {}

			/* COMMON RED-BLACK BINARY SEARCH TREE FUNCTIONS */
			
			/* DEPTH */
			/*
			** This recursive function finds the depth of a binary tree.
			** Might make this iterative in future.
			*/
			size_t			bintree_depth(t_bstnode *root) {
				size_t	left_depth;
				size_t	right_depth;

				if (root == NULL)
					return (0);
				else
				{
					left_depth = bintree_depth(root->left);
					right_depth = bintree_depth(root->right);
					if (left_depth > right_depth)
						return (left_depth + 1);
					else
						return (right_depth + 1);
				}	
			}

			/*
			** This function will perform a right rotation on the node passed as
			** root.
			*/
			void	right_rotation(t_bstnode **root, t_bstnode *node)
			{
				t_bstnode	*left;

				left = node->left;
				node->left = left->right;
				if (node->left)
					node->left->parent = node;
				left->parent = node->parent;
				if (!node->parent)
					*root = left;
				else if (node == node->parent->left)
					node->parent->left = left;
				else
					node->parent->right = left;
				left->right = node;
				node->parent = left;
			}

			/*
			** This function will perform a left rotation on the node passed as
			** root.
			*/
			void	left_rotation(t_bstnode **root, t_bstnode *node)
			{
				t_bstnode	*right;

				right = node->right;
				node->right = right->left;
				if (node->right)
					node->right->parent = node;
				right->parent = node->parent;
				if (node->parent == NULL)
					*root = right;
				else if (node == node->parent->left)
					node->parent->left = right;
				else
					node->parent->right = right;
				right->left = node;
				node->parent = right;
			}

			/*
			** This function handles red-black violation Cases 2 and 3 (uncle is
			** black) in which the violating node's parent is a LEFT child of
			** the grandparent.
			**
			** If the uncle is black and the node is a right child of the
			** parent, then a left rotation is applied on the parent. After the
			** left rotation, the parent becomes the node's left child, and the
			** node becomes its parent's parent.
			**
			** The node pointer is then changed to point to the parent.
			**
			** The new node is now a left child of the new parent (the old
			** node), which is also a left child of the grandparent (because it
			** switched places with the old parent, which was a left child). The
			** uncle is still black. So that puts us in Case 3. So we apply the
			** Case 3 correction.
			**
			** If the uncle is black and the node is a left child of the parent,
			** whether originally or because we applied a Case 2 rotation, then
			** we apply a right rotation on the grandparent and switch the
			** grandparent's colour with the parent's colour.
			**
			** The node pointer is then changed to point to the parent to check
			** its compliance with the red-black rules after the change. Note
			** that if a Case 2 rotation was applied, it will end up pointing to
			** the grandparent.
			**
			** -- RETURN VALUE --
			** The new_node's parent after the corrective rotations.
			*/
			t_bstnode	*left_case(t_bstnode *new_node, t_bstnode *parent, t_bstnode *granny, \
			t_bstnode **root)
			{
				typename t_bstnode::t_bstcolor	tmpc;

				if (new_node == parent->right)
				{
					left_rotation(root, parent);
					new_node = parent;
					parent = new_node->parent;
				}
				right_rotation(root, granny);
				tmpc = parent->color;
				parent->color = granny->color;
				granny->color = tmpc;
				new_node = parent;
				return (new_node);
			}

			/*
			** This function handles red-black violation Cases 2 and 3 (uncle is
			** black) in which the violating node's parent is a RIGHT child of
			** the grandparent.
			**
			** If the uncle is black and the node is a left child of the parent,
			** then a right rotation is applied on the parent. After the right
			** rotation, the parent becomes the node's right child, and the node
			** becomes its parent's parent.
			**
			** The node pointer is then changed to point to the parent.
			**
			** The new node is now a right child of the new parent (the old
			** node), which is also a right child of the grandparent (because it
			** switched places with the old parent, which was a right child).
			** The uncle is still black. So that puts us in Case 3. So we apply
			** the Case 3 correction.
			**
			** If the uncle is black and the node is a right child of the
			** parent, whether originally or because we applied a Case 2
			** rotation, then we apply a left rotation on the grandparent and
			** switch the grandparent's colour with the parent's colour.
			**
			** The node pointer is then changed to point to the parent to check
			** its compliance with the red-black rules after the change. Note
			** that if a Case 2 rotation was applied, it will end up pointing to
			** the grandparent.
			**
			** -- RETURN VALUE --
			** The new_node's parent after the corrective rotations.
			*/
			t_bstnode	*right_case(t_bstnode *new_node, t_bstnode *parent, t_bstnode *granny, \
			t_bstnode **root)
			{
				typename t_bstnode::t_bstcolor	tmpc;

				if (new_node == parent->left)
				{
					right_rotation(root, parent);
					new_node = parent;
					parent = new_node->parent;
				}
				left_rotation(root, granny);
				tmpc = parent->color;
				parent->color = granny->color;
				granny->color = tmpc;
				new_node = parent;
				return (new_node);
			}

			/*
			** This iterative balancer function will go up the red-black tree
			** passed as 'root' from the node passed as 'new_node' and perform
			** any operations as needed to correct violations of the red-black
			** requirements and balance the tree.
			**
			** -- RED-BLACK BINARY SEARCH TREE REQUIREMENTS --
			** 1. The red-black tree always has a black root.
			** 2. Other nodes may be black or red.
			** 3. All null nodes (also called 'leaves') are black.
			** 4. A red node may not have a red child.
			**
			** Thus, the outer loop excludes the possibility that the node may
			** be the root, or otherwise that the node may be black (if it is,
			** it doesn't matter if its parent is black or red), or otherwise
			** (if red) that its parent may be black (if it is, it's okay if the
			** node is red). If that check fails, we enter the correction
			** routine.
			**
			** Corrections may involve just changing the colours of the nodes,
			** or may require the nodes to be rotated left or right, or both.
			**
			** There are four different cases for correction, and two different
			** directions of rotation in case a rotation is needed.
			**
			** -- CORRECTION CASES --
			** The cases are, if the offending node's PARENT is a LEFT child:
			**
			** LEFT CASE:
			**
			** Case 0:	The node is the tree root.
			** Case 1:  The node's uncle is red.
			** Case 2:  The node's uncle is black, and the node is the parent's
			**			right child, so it forms a triangle with the parent and
			**			grandparent.
			** Case 3:  The node's uncle is black, and the node is the parent's
			**			left child, so it forms a line with the parent and
			**			grandparent.
			**
			** If the offending node's parent is a RIGHT child the cases are the same, but with left
			** and right switched:
			**
			** RIGHT CASE:
			**
			** Case 0:	The node is the tree root.
			** Case 1:  The node's uncle is red.
			** Case 2:  The node's uncle is black, and the node is the parent's
			**			left child, so it forms a triangle with the parent and
			**			grandparent.
			** Case 3:  The node's uncle is black, and the node is the parent's
			**			right child, so it forms a line with the parent and
			**			grandparent.
			**
			** RIGHT CASE 0 and 1 and LEFT CASE 0 and 1 are always the same, so
			** cases 0 and 1 are evaluated first.
			**
			** If a rotation is needed, it goes in the opposite direction of the
			** node's direction from the parent. That is, if the node is a right
			** child a left rotation would be needed, and if it is a left child
			** a right rotation would be needed. So we call separate functions:
			** left_case if the parent is a LEFT child, and right_case if the
			** parent is a RIGHT child.
			**
			** -- ALGORITHMIC PROCEDURE --
			** First we define the node's parent, grandparent and uncle.
			**
			** If the node's parent is the grandparent's LEFT child, that
			** determines that the uncle *must* be the grandparent's right
			** child. We call this "left_case".
			**
			** If the node's parent is the grandparent's RIGHT child, that
			** determines that the uncle *must* be the grandparent's left child.
			** We call this "right_case".
			**
			** If the uncle is red, it is Case 1.
			**
			** To correct a violation in Case 1, the node's parent, grandparent
			** and uncle are recoloured. The grandparent is coloured red, and
			** the parent and uncle black. The node pointer then moves up to the
			** grandparent to check the grandparent's compliance with red-black
			** rules after the change.
			**
			** If the uncle is black, it is either Case 2 or 3. Depending on
			** whether it is a left case or right case, we call the left_case
			** and right_case functions, respectively, to handle it.
			**
			** Lastly, if we have emerged from the while, we colour the tree
			** root black, as this is obligatory.
			*/
			void	bintree_balance(t_bstnode **root, t_bstnode *new_node)
			{
				t_bstnode	*granny;
				t_bstnode	*parent;
				t_bstnode	*uncle;
							//CASE 0
				while (new_node != *root && new_node->color == t_bstnode::RED && new_node->parent->color == t_bstnode::RED)
				{
					parent = new_node->parent;
					granny = new_node->parent->parent;
					if (parent == granny->left)
						uncle = granny->right;
					else
						uncle = granny->left;
					if (uncle != NULL && uncle->color == t_bstnode::RED) //CASE 1
					{
						granny->color = t_bstnode::RED;
						parent->color = t_bstnode::BLK;
						uncle->color = t_bstnode::BLK;
						new_node = granny;
					}
					else if (parent == granny->left) //PARENT IS LEFT CHILD
						new_node = left_case(new_node, parent, granny, root);
					else							//PARENT IS RIGHT CHILD
						new_node = right_case(new_node, parent, granny, root);
				}
				(*root)->color = t_bstnode::BLK;
			}
	};
}

#endif