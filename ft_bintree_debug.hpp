/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_debug.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:21:31 by miki              #+#    #+#             */
/*   Updated: 2021/11/21 21:19:00 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINTREE_DEBUG_H
# define FT_BINTREE_DEBUG_H

#include "ansi_codes.hpp"
#include <iostream>
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


namespace ft
{
	template<typename t_bstnode, typename Tonti = float>
	class bintree_printer
	{
		//DEBUG
		private:
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
		protected:
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
				std::cout << curpos << TXT_BHWHT << TXT_WHTB;
				// write(1, curpos, std::strlen(curpos));
				// write(1, TXT_BHWHT, 7);
				// write(1, TXT_WHTB, 5);
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
					std::cout << TXT_BHRED;
					//write(1, TXT_BHRED, 7);
				else
					std::cout << TXT_BHBLK;
					//write(1, TXT_BHBLK, 7);
				std::cout << root->data;
				std::cout << TXT_RST;
				//write(1, TXT_RST, 4);
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

				//write(1, TXT_BHWHT, 7);
				std::cout << TXT_BHWHT;
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
				std::cout << TXT_RST;
				// write(1, TXT_RST, 4);
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
			** of the tree it has been passed as root using the bintree_depth function.
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

				depth = bintree_depth(root);
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
	};

	template<typename t_bstnode>
	class bintree_printer<t_bstnode, int>
	{		//DEBUG
		private:
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
		protected:
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
				std::cout << curpos << TXT_BHWHT << TXT_WHTB;
				// write(1, curpos, std::strlen(curpos));
				// write(1, TXT_BHWHT, 7);
				// write(1, TXT_WHTB, 5);
				while (offset_left++ < var->hpos + offset)
					std::cout << " ";
					//write(1, " ", 1);
				n = root->data.second / 10;
				digits = 1;
				while (n && digits++)
					n /= 10;
				curpos = tgoto(p->tcaps.cur_mov, var->hpos - (digits / 2), p->var.vpos - 1);
				//write(1, curpos, std::strlen(curpos));
				std::cout << curpos;
				if (root->color)
					std::cout << TXT_BHRED;
					//write(1, TXT_BHRED, 7);
				else
					std::cout << TXT_BHBLK;
					//write(1, TXT_BHBLK, 7);
				std::cout << root->data.second;
				std::cout << TXT_RST;
				//write(1, TXT_RST, 4);
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

				//write(1, TXT_BHWHT, 7);
				std::cout << TXT_BHWHT;
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
				std::cout << TXT_RST;
				// write(1, TXT_RST, 4);
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
			** of the tree it has been passed as root using the bintree_depth function.
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

				depth = bintree_depth(root);
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
	};
};

#endif