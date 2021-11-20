/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:41:44 by miki              #+#    #+#             */
/*   Updated: 2021/11/20 18:51:23 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINTREE_H
# define FT_BINTREE_H

//DEBUG
			#ifdef __linux__
			# include <termcap.h>
			#endif
			#include <curses.h>
			#include <term.h>
			#include <sys/ioctl.h>
			#include <unistd.h>
			#include <stdio.h>
			#include <unistd.h>
			#include <stdio.h>
//DEBUG


#include <iostream>
#include <cstring>

namespace ft
{
	template<typename T>
	class bintree
	{
		public:
			typedef T	data_type;
		private:
			/*
			** This enum field will define a node color as red or black.
			*/
			typedef enum	e_color
			{
				btBLK = 0, btRED
			}				t_color;

			/*
			** For the single-value implementation of ft::bintree the data type
			** will be T.
			*/
			typedef struct	s_bstnode
			{
				struct s_bstnode				*parent;
				struct s_bstnode				*left;
				struct s_bstnode				*right;
				data_type						data;
				t_color							color;
			}				t_bstnode;
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

			
			/*
			** This function dynamically reserves memory in heap for a new node
			** in a binary tree and sets the data segment of that node to the
			** value of the argument. The left and right child pointers are
			** nulled. Each node is BLACK by default.
			**
			** -- RETURN VALUES --
			** A pointer to the new binary tree node is returned to the caller.
			** If the memory reservation fails, a NULL pointer is returned.
			*/
			t_bstnode	*create_new_node(t_bstnode *parent, data_type data)
			{
				t_bstnode	*node;

				node = new t_bstnode;
				if (node != NULL)
				{
					node->data = data;
					node->parent = parent;
					node->left = NULL;
					node->right = NULL;
					node->color = btRED;
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
			t_bstnode	*ft_bintree_search(t_bstnode *root, data_type data)
			{
				if (root == NULL || root->data == data)
					return (root);
				else if (data <= root->data)
					return (ft_bintree_search(root->left, data));
				else
					return (ft_bintree_search(root->right, data));
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
			void	ft_bintree_balance(t_bstnode **root, t_bstnode *new_node)
			{
				t_bstnode	*granny;
				t_bstnode	*parent;
				t_bstnode	*uncle;
							//CASE 0
				while (new_node != *root && new_node->color == btRED && new_node->parent->color == btRED)
				{
					parent = new_node->parent;
					granny = new_node->parent->parent;
					if (parent == granny->left)
						uncle = granny->right;
					else
						uncle = granny->left;
					if (uncle != NULL && uncle->color == btRED) //CASE 1
					{
						granny->color = btRED;
						parent->color = btBLK;
						uncle->color = btBLK;
						new_node = granny;
					}
					else if (parent == granny->left) //PARENT IS LEFT CHILD
						new_node = left_case(new_node, parent, granny, root);
					else							//PARENT IS RIGHT CHILD
						new_node = right_case(new_node, parent, granny, root);
				}
				(*root)->color = btBLK;
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
			t_bstnode	*ft_bintree_insert(t_bstnode *parent, t_bstnode *root, \
			data_type data)
			{
				if (root == NULL)
					root = create_new_node(parent, data);
				else if (data <= root->data)
					root->left = ft_bintree_insert(root, root->left, data);
				else
					root->right = ft_bintree_insert(root, root->right, data);
				return (root);
			}

			t_bstnode	*ft_bintree_add(t_bstnode *&root, data_type data)
			{
				t_bstnode	*new_node;

				root = ft_bintree_insert(NULL, root, data);
				new_node = ft_bintree_search(root, data);
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

			//DEBUG

			/*
			** Regular bold text
			*/

			# define BBLK "\e[1;30m"
			# define BRED "\e[1;31m"
			# define BGRN "\e[1;32m"
			# define BYEL "\e[1;33m"
			# define BBLU "\e[1;34m"
			# define BMAG "\e[1;35m"
			# define BCYN "\e[1;36m"
			# define BWHT "\e[1;37m"

			/*
			**Regular underlined text
			*/

			# define UBLK "\e[4;30m"
			# define URED "\e[4;31m"
			# define UGRN "\e[4;32m"
			# define UYEL "\e[4;33m"
			# define UBLU "\e[4;34m"
			# define UMAG "\e[4;35m"
			# define UCYN "\e[4;36m"
			# define UWHT "\e[4;37m"

			/*
			** Regular background
			*/

			# define BLKB "\e[40m"
			# define REDB "\e[41m"
			# define GRNB "\e[42m"
			# define YELB "\e[43m"
			# define BLUB "\e[44m"
			# define MAGB "\e[45m"
			# define CYNB "\e[46m"
			# define WHTB "\e[47m"

			/*
			** High intensity background 
			*/

			# define BLKHB "\e[0;100m"
			# define REDHB "\e[0;101m"
			# define GRNHB "\e[0;102m"
			# define YELHB "\e[0;103m"
			# define BLUHB "\e[0;104m"
			# define MAGHB "\e[0;105m"
			# define CYNHB "\e[0;106m"
			# define WHTHB "\e[0;107m"

			/*
			** High intensity text
			*/

			# define HBLK "\e[0;90m"
			# define HRED "\e[0;91m"
			# define HGRN "\e[0;92m"
			# define HYEL "\e[0;93m"
			# define HBLU "\e[0;94m"
			# define HMAG "\e[0;95m"
			# define HCYN "\e[0;96m"
			# define HWHT "\e[0;97m"

			/*
			** Bold high intensity text
			*/

			# define BHBLK "\e[1;90m"
			# define BHRED "\e[1;91m"
			# define BHGRN "\e[1;92m"
			# define BHYEL "\e[1;93m"
			# define BHBLU "\e[1;94m"
			# define BHMAG "\e[1;95m"
			# define BHCYN "\e[1;96m"
			# define BHWHT "\e[1;97m"

			/*
			** Reset
			*/

			# define RESET "\e[0m"

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

			typedef struct s_bstprintvars
			{
				size_t			level;
				size_t			div;
				size_t			hpos;
				size_t			vpos;
			}				t_bstprintvars;

			typedef struct s_bstprint
			{
				t_bsttermcaps	tcaps;
				struct winsize	wsize;
				t_bstprintvars	var;
			}				t_bstprint;
			/*
			** This function uses the termcaps library to print a graphical representation
			** of a binary tree created using the t_bstnode type and the ft_bintree family
			** of functions. To do this first we need to get a couple of capabilities from
			** the termcaps library.
			**
			** The function termcaps_init currently uses getenv, which is probably banned in
			** any 42 project so at some point I need to move my own get_var function into
			** libft.:p
			*/

			int	ft_bintree_termcaps_init(t_bsttermcaps *tcaps)
			{
				char	*termtype;
				char	*capbuf;
				char	cm[3] = "cm";
				char	sf[3] = "sf";

				termtype = getenv("TERM");
				capbuf = &tcaps->capbuf[0];
				if (termtype && tgetent(tcaps->termbuf, termtype) > 0)
				{
					tcaps->cur_mov = tgetstr(cm, &capbuf);
					tcaps->scroll_up = tgetstr(sf, &capbuf);
					if (tcaps->cur_mov && tcaps->scroll_up)
						return (1);
				}
				std::cerr << "NO TERM DEFINED OR INVALID TERM TYPE" << std::endl;
				return (0);
			}

			/*
			** This function prints the node. :)
			**
			** The algorithm is as follows:
			**
			** 1. We determine the offset_left position by subtracting the offset from the
			**	  horizontal position.
			** 2. We move the cursor to offset_left.
			** 3. We activate the high-intensity bold white text colour.
			** 4. We activate the white background colour.
			** 5. We print spaces " " from offset_left to offset_right (hpos + offset). That
			**	  defines the space occupied by the node in the second to last row in the
			**	  window (vpos - 1). This is because we scroll up before launching the print
			**	  function and use the bottom row to print the connecting branches.
			** 6. We find the number of digits in the node data so that we know how to
			**    centre the number. (See below)
			** 7. We use the number of digits in the node data (digits) divided by 2 as an
			**	  offset to centre the number by moving the cursor to hpos - (digits \ 2)
			**	  before printing the number.
			** 8. Depending on the node's colour we change the text colour to high-intensity
			**	  bold red or black.
			** 9. We print the number using good old ft_putnbr. :)
			** 10. We reset the colours.
			**
			** About step 6, I know it's ridiculous. I know it should look like this:
			** n = root->data
			** digits = 1;
			**	while (n /= 10)
			**		digits++;
			**
			** 42 School has banned us from doing assignments in conditional statements and
			** limits us to 25 lines per function. So that's why we have to resort to this
			** hideous kind of stuff. I'm so sorry. :p
			*/

			void	print_node(t_bstprint *p, t_bstprintvars *var, size_t offset, \
			t_bstnode *root)
			{
				long long int	n;
				char			*curpos;
				size_t			offset_left;
				size_t			digits;

				offset_left = var->hpos - offset;
				curpos = tgoto(p->tcaps.cur_mov, offset_left, p->var.vpos - 1);
				std::cout << curpos << BHWHT << WHTB;
				// write(1, curpos, std::strlen(curpos));
				// write(1, BHWHT, 7);
				// write(1, WHTB, 5);
				while (offset_left++ < var->hpos + offset)
					std::cout << " ";
					//write(1, " ", 1);
				n = root->data / 10;
				digits = 1;
				while (n && digits++)
					n /= 10;
				curpos = tgoto(p->tcaps.cur_mov, var->hpos - (digits / 2), p->var.vpos - 1);
				//write(1, curpos, std::strlen(curpos));
				std::cout << curpos;
				if (root->color)
					std::cout << BHRED;
					//write(1, BHRED, 7);
				else
					std::cout << BHBLK;
					//write(1, BHBLK, 7);
				std::cout << root->data;
				std::cout << RESET;
				//write(1, RESET, 4);
			}

			/*
			** This function prints the left and right branches beneath a node if the node
			** has left or right children. The terms offset left and offset right refer,
			** respectively, to hpos - offset and hpos + offset.
			**
			** The algorithm is as follows:
			**
			** 1. We change the text colour to high-intensity bold white.
			** 2. We check whether there is a left child. If there is:
			**		 a) We move the cursor one column left of offset left and down to the
			**		    last row in the window (vpos).
			**		 b) We print a '/'. That's why we went one column left of offset left,
			**			so the right end of the '/' will appear to touch the corner of the
			**			white box on the upper row. :)
			** 3. We check whether there is a right child. If there is:
			**		 a) We move the cursor to offset right on the last row in the window
			**			(vpos).
			**		 b) We print a '\'.
			** 4. We reset the colours.
			*/

			void	print_branches(t_bstprint *p, t_bstprintvars *var, size_t offset, \
			t_bstnode *root)
			{
				char	*curpos;

				//write(1, BHWHT, 7);
				std::cout << BHWHT;
				if (root->left)
				{
					curpos = tgoto(p->tcaps.cur_mov, var->hpos - offset - 1, p->var.vpos);
					std::cout << curpos;
					std::cout << "/";
					// write(1, curpos, std::strlen(curpos));
					// write(1, "/", 1);
				}
				if (root->right)
				{
					curpos = tgoto(p->tcaps.cur_mov, var->hpos + offset, p->var.vpos);
					std::cout << curpos;
					std::cout << "\\";
					// write(1, curpos, std::strlen(curpos));
					// write(1, "\\", 1);
				}
				std::cout << RESET;
				// write(1, RESET, 4);
			}

			/*
			** This recursive function prints a row of tree nodes at the level specified by
			** the calling function by spawning clones of itself for each child node in the
			** tree until it reaches the originally specified depth, and then printing in
			** order from left to right.
			**
			** To achieve this the function has several sections.
			**
			** If it receives a null node as root, it simply returns without doing anything.
			**
			** //OFFSET\\
			** Otherwise, we calculate the offset. The offset is the relative distance in
			** columns from any node in the current row to its child nodes. For details on
			** how it is calculated, see the DEPTH LIMIT EQUATION section of the
			** btree_level_order_printer function description. The offset gives us the
			** horizontal position on the screen of left and right child nodes when we
			** subtract or add it to the current horizontal position (var.hpos). This also
			** corresponds to the space that will be occupied by the parent node in its row.
			**
			** The initial horizontal position is always the the screen width (ws_col) / 2,
			** and the hpos indicator is displaced left and right of that position by the
			** offset with each subsequent recursive call and level drop.
			**
			** For each level drop we decrement the var.level variable until it reaches 1,
			** at which point we will have dropped down to the level we want to print.
			**
			** Once we are at the level we want to print (var.level == 1), we print the node
			** and the branches below the node.
			**
			** If we haven't plumbed through the depths of the tree yet to get to the
			** level we want to print, we recursively call clones of our function for the
			** left and right children of our current node with the following modified
			** values:
			**
			** 1. The level - 1.
			** 2. The offset divisor + 1 (the offset divisor is essentially the inverse of
			**	  the level).
			** 3. For the left child, we pass hpos as left_offset (hpos - offset).
			** 4. For the right child, we pass hpos as right_offset. Since we changed hpos
			**	  to left_offset for the left child, this is now hpos + (offset * 2).
			**
			** Since the left is called first, and it will recursively call its left child
			** first, all left children finish printing first, then the right children are
			** printed. In any case, since the printing is done according to hpos, which is
			** passed always as an offset from the parent's hpos, and terminal doesn't seem
			** to mind being bombarded with lots of simultaneous write instructions (thanks
			** terminal!), we're all good regardless of the order. :)
			*/

			void	btree_print_level(t_bstprint *p, t_bstnode *root, t_bstprintvars var)
			{
				size_t	offset;

				if (root == NULL)
					return ;
				offset = (p->wsize.ws_col / var.div) - (p->wsize.ws_col / (var.div + 1));
				if (var.level == 1)
				{
					print_node(p, &var, offset, root);
					print_branches(p, &var, offset, root);
				}
				else if (var.level > 1)
				{
					var.level -= 1;
					var.div += 1;
					var.hpos -= offset;
					btree_print_level(p, root->left, var);
					var.hpos += (offset * 2);
					btree_print_level(p, root->right, var);
				}
			}

			/*
			** The level order section of the binary tree printer first determines the depth
			** of the tree it has been passed as root using the ft_bintree_depth function.
			** If the user-provided depth limit is 0 or greater than the total tree depth,
			** then the printer will try to print up to depth levels. Otherwise, it will try
			** to print up to depth_limit levels.
			**
			** //THE DEPTH LIMIT EQUATION\\
			** To determine the printable depth limit we divide the quotient of the total
			** column width of the screen by the row at the depth limit and subtract from
			** that the quotient of total column width of the screen divided by the row
			** after the row at the depth limit. This gives the distance between a node in
			** the upper row and a node in the bottom row. If the distance is less than 8
			** columns, we consider that there is not enough space between siblings for all
			** the children in the bottom row, so we decrement depth_limit by 1 and
			** calculate again, until we find a depth_limit that will accommodate all the
			** children in all the printed rows.
			**
			** The easiest way to understand the why of this equation is to imagine a row
			** of 100 columns and a tree of depth 2. So, let ws_row = 100 and depth = 2:
			**
			** ws_row / depth = 50
			** ws_row / (depth + 1) = 33
			** 50 - 33 = 17.
			**
			** So for a screen width of 100 columns, '17' is the offset between the node on
			** level 1 and its child nodes on level 2, like so:
			**
			** 0								50									100
			** ========================================================================
			**					 17-------------50+++++++++++++17
			** L1		 		 33				ROOT   		   67
			** L2				 LCHILD						   RCHILD
			**
			** So you can see that the space occupied by the parent is equal to the distance
			** between the children.
			**
			** That leaves 67 - 33 = 34 columns between the middle siblings on level 2.
			** If we divide the space evenly between them, they have 17 columns between each
			** other per child plus 33 more on the other side until the screen edge to
			** display their data. Roomy!
			**
			** So let's calculate this for a depth 3 tree. Let ws_row = 100 and depth = 3:
			**
			** ws_row / depth = 33
			** ws_row / (depth + 1) = 25
			** 33 - 25 = 8.
			**
			** So for a tree of depth 3, '8' is the offset between the nodes on level 2 and
			** their child nodes on level 3, like so:
			**
			** 0								50									100
			** ========================================================================
			**					 17-------------50+++++++++++++17
			** L1		 08------33++++++08		ROOT   08------67++++++08
			** L2		 25		 LCHILD	 41			   59	   RCHILD  75
			** L3		 LCHILD	  <16>   RCHILD	 <18>  LCHILD   <16>   RCHILD
			**
			** That leaves 59 - 41 = 18 columns betweeen cousins on level 3, and about
			** 41 - 25 = 16 columns between siblings. So dividing things up fairly, each
			** node gets about 8 columns on the left and 8 columns on the right to itself.
			**
			** Still enough room, but starting to get cramped, so we cut it off here. What
			** if we were to continue, though? Let ws_row = 100 and depth = 4:
			**
			** ws_row / depth = 25
			** ws_row / (depth + 1) = 20
			** 25 - 20 = 5.
			**
			** 0								50									100
			** ========================================================================
			**					 17-------------50+++++++++++++17
			** L1		 08------33++++++08		ROOT   08------67++++++08
			** L2	 05--25++05	 LC	 05--41++05    05--59++05  RC  05--75++05
			** L3	 20	 LC	 30		 36	 RC	 46	   54  LC  64	   70  RC  80
			** L4	 LC <10> RC	<06> LC	<10> RC<08>LC <10> RC <06> LC <10> RC

			** For a tree of depth 4 or greater with a total screen width of 100 columns,
			** the offset will be 5 (less than 8). That leaves just 10 columns between
			** siblings, 8 columns between second cousins, and a paltry 6 columns between
			** first cousins. Dividing that up fairly, each node will get about 3 - 5
			** columns on either side to display data. Many integers should actually still
			** fit in this case, but integers with more than 6 digits may be overwritten,
			** and things will start looking very messy. So that is why we stop printing
			** here. :)
			**
			** For user comfort we print out the total Tree Depth that we've found. We
			** initialize the level counter at 1, the horizontal position in the middle of
			** screen, and the divisor (used to calculate the offset of a given level in the
			** printing function) at 2 since the first level's offset is screen width / 2.
			**
			** For each level we want to print, first we scroll up one line to make space
			** for the branches we will draw on the line below. Then we fire up
			** btree_print_level to print each node in the level.
			**
			** When we are done printing the level we write a new line to move to the next
			** line and increment the level counter. We stop once we've reached depth_limit
			** levels of the tree.
			**
			** If we had to truncate because there wasn't enough screen space to print
			** everything the user wanted, we inform the user. If we truncated following the
			** user-provided depth limit, we indicate that.
			*/

			static int	ft_putchar(int chr)
			{
				if (write(STDOUT_FILENO, &chr, 1) == -1)
					return (EOF);
				return (chr);
			}

			void	btree_level_order_printer(t_bstnode *root, t_bstprint *p, \
			size_t depth_limit)
			{
				size_t	depth;
				size_t	user_depth_limit;

				depth = ft_bintree_depth(root);
				if (!depth_limit || depth_limit > depth)
					depth_limit = depth;
				user_depth_limit = depth_limit;
				while (((p->wsize.ws_col / depth_limit) - \
				p->wsize.ws_col / (depth_limit + 1)) < 8)
					depth_limit--;
				printf("Tree Depth: %zu\n", depth);
				p->var.level = 1;
				p->var.hpos = p->wsize.ws_col / 2;
				p->var.div = 2;
				while (p->var.level <= depth_limit)
				{
					tputs(p->tcaps.scroll_up, 1, ft_putchar);
					btree_print_level(p, root, p->var);
					//write(1, "\n", 1);
					std::cout << std::endl;
					p->var.level++;
				}
				if (depth_limit < user_depth_limit)
					printf("Stopped at Level %zu due to Lack of Space\n", depth_limit);
				else if (user_depth_limit < depth)
					printf("Stopped at User-Specified Depth Limit %zu\n", depth_limit);
			}

			/*
			** Thus function will save the column width and row height of the window in the
			** winsize struct. It returns 0 if unsuccessful and 1 if successful.
			**
			** Careful! Only use it in projects where ioctl is allowed. :)
			*/

			int	ft_get_window_size(struct winsize *wsize)
			{
				if (ioctl(STDOUT_FILENO, TIOCGWINSZ, wsize) == -1 \
				|| (wsize->ws_col == 0 || wsize->ws_row == 0))
					return (0);
				return (1);
			}

			/*
			** This function is one of my prides and joys. ;) It prints a graphical
			** representation of the binary tree passed as root, with all of the
			** parent-child relationships, up to the depth passed as depth_limit. If 0 or a
			** number greater than the total depth of the tree is passed as depth_limit,
			** then it will attempt to print the whole tree.
			**
			** The tree is printed placing the root at the centre of the screen, and each
			** subsequent level's nodes will be spaced at decreasing distances apart until
			** there is no more space on the screen to print new nodes without overwriting,
			** at which point the printing will stop and a Truncated Tree message will be
			** displayed below the tree. The printer will adapt to the screen size at the
			** moment of printing, so making the screen bigger or raising the screen
			** resolution will lead to more of the tree being printed.
			**
			** Any node of a tree can be passed as root and printed out to the depth-limit,
			** as long as there is space on the screen to accomodate it.
			**
			** This is one of the ft_bintree family of functions, so it works with t_bstnode
			** binary tree nodes. These are red-black tree nodes, so the printer will also
			** show the colour of each node by colouring the data either black or red. The
			** main purpose of the function was to help me debug my binary tree algorithms,
			** but, as I refined it, it turned into a sort of graphical miniproject. :)
			**
			** The printer uses level-order traversal to print the tree.
			**
			** NOTE: The reason I subtract one from the row count to get vpos (vertical
			** position) is that, while ANSI code starts counting rows and columns at 1, the
			** termcaps function tgoto that generates our ANSI code is origin-zero. So the
			** position of the cursor is one less than the number of the row on the screen.
			*/

			int	ft_bintree_print(t_bstnode *root, size_t depth_limit)
			{
				t_bstprint	p;
				int			winres;
				int			tcapsres;

				winres = ft_get_window_size(&p.wsize);
				p.var.vpos = p.wsize.ws_row - 1;
				tcapsres = ft_bintree_termcaps_init(&p.tcaps);
				if (!tcapsres)
				std::cerr << "termcaps_init failed" << std::endl;
				if (!winres)
					std::cerr << "get_window_size failed\n" << std::endl;
				if (!winres || !tcapsres)
					return (0);
				btree_level_order_printer(root, &p, depth_limit);
				return (1);
			}

			//DEBUG
			t_bstnode	*_root;
		public:
			bintree(void) : _root(NULL) {};
			~bintree(void) {
				//debug
				//std::cout << "freeeeedom" << std::endl;
				//debug
				ft_bintree_free(_root);
			}
			void	push_back(data_type data){
				ft_bintree_add(_root, data);
			}
			void	print(void) {
				ft_bintree_print(_root, 0);
			}
	};
};

#endif