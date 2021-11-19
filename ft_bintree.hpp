/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:41:44 by miki              #+#    #+#             */
/*   Updated: 2021/11/19 16:09:37 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINTREE_H
# define FT_BINTREE_H

# define BINTREE_MAX_DATA 4611686018427387903
# define BINTREE_MIN_DATA -4611686018427387904

#include <iostream>
#include <cstring>

namespace ft
{
	class bintree
	{
		private:
			typedef enum	e_color
			{
				R = 0, B
			}				t_color;

			/*
			** Although I use long long int for the data segment, I actually sequester a
			** single bit from it to store btree color data. So the storage limit is only
			** 4611686018427387903 in positive integers and 4611686018427387904 in
			** negatives. I still don't know how to say that number out loud, so should be
			** long enough for most purposes. ;) Since our struct is going to be padded in
			** 8-byte tranches anyway, because of the pointers, we might as well get as much
			** bang for our byte as we can. ;) BINTREE_MAX_DATA and BINTREE_MIN_DATA define
			** the respective maximum and minimum integers that can be held inside a binary
			** tree node. The binary tree add function uses them to police input.
			*/

			struct	s_bstnode
			{
				struct s_bstnode				*parent;
				struct s_bstnode				*left;
				struct s_bstnode				*right;
				int								data;
				t_color							color;
			};

			typedef struct s_bsttermcaps
			{
				char	termbuf[2048];
				char	capbuf[2048];
				char	*cur_mov;
				char	*scroll_up;
			}				t_bsttermcaps;

			/*
			** I'd REALLY rather do this by making tcaps and wsize globals in the
			** ft_bintree_print scope, and just passing level, div and hpos as unstructured
			** local variables, but 42 School Norm bans globals (and bans structs from being
			** declared in .c), so then I couldn't compile my lib for school projects. :( So
			** I did this instead.
			**
			** Since using the bstprint struct put me over the 4 argument limit for a
			** function, also per 42 School Norm, I made all the variables into a struct
			** too. They need their own struct, because I need to copy them from function to
			** function and operate on them independently, not just address a single
			** instance of them. I know it's more confusing than it has to be, I'm sorry.
			**
			** Don't judge me, norminette made me do it. xD
			*/

			// typedef struct s_bstprintvars
			// {
			// 	size_t			level;
			// 	size_t			div;
			// 	size_t			hpos;
			// 	size_t			vpos;
			// }				t_bstprintvars;

			// typedef struct s_bstprint
			// {
			// 	t_bsttermcaps	tcaps;
			// 	struct winsize	wsize;
			// 	t_bstprintvars	var;
			// }				t_bstprint;

			typedef struct s_bstnode	t_bstnode;
			/*
			** This recursive function finds the depth of a binary tree.
			** Might make this iterative in future.
			*/
			size_t			ft_bintree_depth(t_bstnode *root) {
				size_t	left_depth;
				size_t	right_depth;

				if (root == NULL)
					return (0);
				else
				{
					left_depth = ft_bintree_depth(root->left);
					right_depth = ft_bintree_depth(root->right);
					if (left_depth > right_depth)
						return (left_depth + 1);
					else
						return (right_depth + 1);
				}	
			}
			//Style 1
			
			/*
			** This function dynamically reserves memory in heap for a new node in a binary
			** tree and sets the data segment of that node to the value of the argument. The
			** left and right child pointers are nulled. A pointer to the new node is
			** returned to the caller. If the reservation fails, a null pointer is returned.
			*/

			t_bstnode	*create_new_node(t_bstnode *parent, int data)
			{
				t_bstnode	*node;

				node = new t_bstnode;
				if (node != NULL)
				{
					node->data = data;
					node->parent = parent;
					node->left = NULL;
					node->right = NULL;
					node->color = B;
				}
				return (node);
			}

			/*
			** This function will search the binary tree whose root is passed as the first
			** argument for the value passed as data in the second argument. If the data is
			** found in the tree, a pointer to the node containing the data is returned. If
			** it is not present in the tree, a NULL pointer is returned.
			**
			** If the root node pointer passed as an argument is not NULL and the data is
			** not present in that node, this function will recursively call itself passing
			** the pointer to the left or right branches of that node as the data is less
			** than, equal to or greater than the data within the node, until either a NULL
			** pointer or a node with matching data is found.
			*/

			t_bstnode	*ft_bintree_search(t_bstnode *root, int data)
			{
				if (root == NULL || root->data == data)
					return (root);
				else if (data <= root->data)
					return (ft_bintree_search(root->left, data));
				else
					return (ft_bintree_search(root->right, data));
			}

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
			** This function handles red-black violation cases 2 and 3 (uncle is black) in
			** which the violating node's parent is a LEFT child of the grandparent.
			**
			** If the uncle is black and the node is a right child of the parent, then a
			** left rotation is applied on the parent. After the left rotation, the parent
			** becomes the node's left child, and the node becomes its parent's parent.
			**
			** The node pointer is then changed to point to the parent.
			**
			** The new node is now a left child of the new parent (the old node), which is
			** also a left child of the grandparent (because it switched places with the old
			** parent, which was a left child). The uncle is still black. So that puts us in
			** Case 3. So we apply the Case 3 correction.
			**
			** If the uncle is black and the node is a left child of the parent, whether
			** originally or because we applied a Case 2 rotation, then we apply a right
			** rotation on the grandparent and switch the grandparent's colour with the
			** parent's colour.
			**
			** The node pointer is then changed to point to the parent to check its
			** compliance with the red-black rules after the change. Note that if a Case 2
			** rotation was applied, it will end up pointing to the grandparent.
			*/

			t_bstnode	*left_case(t_bstnode *new_node, t_bstnode *parent, t_bstnode *granny, \
			t_bstnode **root)
			{
				t_color	tmpc;

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
			** This function handles red-black violation cases 2 and 3 (uncle is black) in
			** which the violating node's parent is a RIGHT child of the grandparent.
			**
			** If the uncle is black and the node is a left child of the parent, then a
			** right rotation is applied on the parent. After the right rotation, the parent
			** becomes the node's right child, and the node becomes its parent's parent.
			**
			** The node pointer is then changed to point to the parent.
			**
			** The new node is now a right child of the new parent (the old node), which is
			** also a right child of the grandparent (because it switched places with the old
			** parent, which was a right child). The uncle is still black. So that puts us in
			** Case 3. So we apply the Case 3 correction.
			**
			** If the uncle is black and the node is a right child of the parent, whether
			** originally or because we applied a Case 2 rotation, then we apply a left
			** rotation on the grandparent and switch the grandparent's colour with the
			** parent's colour.
			**
			** The node pointer is then changed to point to the parent to check its
			** compliance with the red-black rules after the change. Note that if a Case 2
			** rotation was applied, it will end up pointing to the grandparent.
			*/

			t_bstnode	*right_case(t_bstnode *new_node, t_bstnode *parent, t_bstnode *granny, \
			t_bstnode **root)
			{
				t_color	tmpc;

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
			** This iterative balancer function will go up the red-black tree passed as root
			** from the node passed as new_node and perform any operations as needed to
			** correct violations of the red-black requirements and balance the tree.
			**
			** The red-black tree always has a black root. Other nodes may be black or red.
			** All null nodes (also called 'leaves') are black. A red node may not have a
			** red child.
			**
			** Thus, the while excludes the possibility that the node may be the root, or
			** otherwise that the node may be black (if it is, it doesn't matter if its
			** parent is black or red), or otherwise (if red) that it's parent may be black
			** (if it is, it's okay if the node is red). If that check fails, we enter the
			** correction while.
			**
			** Corrections may involve just changing the colours of the nodes, or may
			** require the nodes to be rotated left or right, or both.
			**
			** There are four different cases for correction, and two different directions
			** of rotation in case a rotation is needed.
			**
			** The cases are, if the node's parent is a left child:
			**
			** Case 0:	The node is the tree root.
			** Case 1:  The node's uncle is red.
			** Case 2:  The node's uncle is black, and the node is the parent's right child,
			**			so it forms a triangle with the parent and grandparent.
			** Case 3:  The node's uncle is black, and the node is the parent's left child,
			**			so it forms a line with the parent and grandparent.
			**
			** If the node's parent is a right child the cases are the same, but with left
			** and right switched.
			**
			** If a rotation is needed, it goes in the opposite direction of the the node's
			** direction from the parent. That is, if the node is a right child, a left
			** rotation would be needed, and if it is a left child, a right rotation would
			** be needed.
			**
			** First we define the node's parent, grandparent and uncle.
			**
			** If the node's parent is the grandparent's LEFT child, that determines that
			** the uncle *must* be the grandparent's right child. We call this "left_case".
			**
			** If the node's parent is the grandparent's RIGHT child, that determines that
			** the uncle *must* be the grandparent's left child. We call this "right case".
			**
			** If the uncle is red, it is Case 1.
			**
			** To correct a violation in Case 1, the node's parent, grandparent and uncle
			** are recoloured. The grandparent is coloured red, and the parent and uncle
			** black. The node pointer then moves up to the grandparent to check the
			** grandparent's compliance with red-black rules after the change.
			**
			** If the uncle is black, it is either Case 2 or 3. Depending on whether it is
			** a left case or right case, we call the left_case and right_case functions,
			** respectively, to handle it.
			**
			** Lastly, if we have emerged from the while, we colour the tree root black, as
			** this is obligatory.
			**
			** Why does this work? I'd by lying if I said I completely understood it. xD But
			** it does work, and applying it after an insertion gives you a nice, balanced
			** tree. So that's what I do! ;)
			*/

			void	ft_bintree_balance(t_bstnode **root, t_bstnode *new_node)
			{
				t_bstnode	*granny;
				t_bstnode	*parent;
				t_bstnode	*uncle;

				while (new_node != *root && new_node->color == B && new_node->parent->color == B)
				{
					parent = new_node->parent;
					granny = new_node->parent->parent;
					if (parent == granny->left)
						uncle = granny->right;
					else
						uncle = granny->left;
					if (uncle != NULL && uncle->color)
					{
						granny->color = B;
						parent->color = R;
						uncle->color = R;
						new_node = granny;
					}
					else if (parent == granny->left)
						new_node = left_case(new_node, parent, granny, root);
					else
						new_node = right_case(new_node, parent, granny, root);
				}
				(*root)->color = R;
			}


			/*
			** This function inserts a node into a binary tree. If passed a NULL pointer, a
			** root node will be created.
			**
			** In the binary tree all values less than or equal to any node value will be
			** stored to the 'left' of that node, and all values greater than any node value
			** will be stored to the 'right' of that node (note, 'left' and 'right' here are
			** abstractions, not literal orientations). This makes it possible to zero in on
			** a value within a set of values more quickly when searching for it by using an
			** approximation depending on whether the value is greater than or less than the
			** node value being analysed at any given juncture.
			**
			** To create new nodes in a tree, the function will recursively call itself,
			** seeking a path to the nearest value (in an existing node in the tree) to the
			** value to be inserted, and store the value in relation to that node. That
			** node's right or left pointer will then be set to point to the new node. The
			** rest of the recursively called functions will then return the original
			** unmodified values of the pointer addresses through which they accessed the
			** nodes in the path.
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
			** Now, in a set of four numbers (200, 100, 300, 220), a match for 220 can be
			** found from root in just two comparisons (as 220 is greater than 200, as 220
			** is less than 300), instead of potentially as many as four (as 220 is not
			** equal to 200, as 220 is not equal to 100, as 220 is not equal to 300, as 220
			** is equal to 220).
			**
			** This is more memory-intensive, but saves CPU cycles, which are at a premium
			** these days as thermal throttling became a limiting factor on CPU speed at
			** least 15 years before quantum uncertainty will become a limiting factor on
			** memory density. So as of 2021 we have increasingly memory-dense and
			** compute-poor computers. (*grumble grumble*)
			*/

			t_bstnode	*ft_bintree_insert(t_bstnode *parent, t_bstnode *root, \
			int data)
			{
				if (root == NULL)
					root = create_new_node(parent, data);
				else if (data <= root->data)
					root->left = ft_bintree_insert(root, root->left, data);
				else
					root->right = ft_bintree_insert(root, root->right, data);
				return (root);
			}

			t_bstnode	*ft_bintree_add(t_bstnode *root, int data)
			{
				t_bstnode	*new_node;

				root = ft_bintree_insert(NULL, root, data);
				new_node = ft_bintree_search(root, data);
				std::cout << "Search Check\n" << new_node->data << std::endl;
				ft_bintree_balance(&root, new_node);
				return (root);
			}

			t_bstnode	*node_delete(t_bstnode *node)
			{
				std::memset(node, 0, sizeof(t_bstnode));
				delete node;
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
			** This is an iterative function for freeing memory used by binary trees. Memory
			** is zeroed before freeing. This is CPU-intensive, but memory-light. It can be
			** used to free trees that may be too big to free with a recursive function.
			**
			** The function searches for childless nodes with a bias for left children. When
			** a childless node is found its memory is zeored and it is freed, and then the
			** next childless node is searched for.
			**
			** The function works through infanticide. Parents kill their childless
			** children. Horrifying, but I couldn't think of a more humane way to do this.
			** That's the world of binary trees. -_-
			**
			** We iterate down the tree with a pointer, starting with left children. If the
			** parent finds a left child, it checks whether its child has children. If the
			** parent finds a grandchild, it becomes the child, and then we check the
			** child's children for children. If the child has no children, the parent
			** DELETES its own child. :_( Then it comes back for another round to check its
			** other child for children...
			**
			** Once the parent is childless, it becomes its own parent, and the grim cycle
			** continues, until everyone is DEAD. The root_canal performs the final suicide.
			** I hope you're happy, Valgrind. :(
			*/

			t_bstnode	*ft_bintree_free(t_bstnode *root)
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

			// int				ft_bintree_print(t_bstnode *root, size_t depth_limit);
			// int				ft_bintree_termcaps_init(t_bsttermcaps *tcaps);
			t_bstnode *_root;
		public:
			bintree(void) : _root(NULL) {};
			~bintree(void) {
				ft_bintree_free(_root);
				std::cout << "freeeeedom" << std::endl;
			}
			void	push_back(int data){
				ft_bintree_add(_root, data);
			}
	};
};

#endif