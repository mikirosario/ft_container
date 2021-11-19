/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 07:58:04 by miki              #+#    #+#             */
/*   Updated: 2021/11/19 14:56:56 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bintree.hpp"
#include <unistd.h>
#include <stdio.h>

/*
** This function dynamically reserves memory in heap for a new node in a binary
** tree and sets the data segment of that node to the value of the argument. The
** left and right child pointers are nulled. A pointer to the new node is
** returned to the caller. If the reservation fails, a null pointer is returned.
*/

t_bstnode	*create_new_node(t_bstnode *parent, long int data)
{
	t_bstnode	*node;

	node = malloc(sizeof(t_bstnode));
	if (node)
	{
		node->data = data;
		node->parent = parent;
		node->left = NULL;
		node->right = NULL;
		node->color = 1;
	}
	return (node);
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
long int data)
{
	if (root == NULL)
		root = create_new_node(parent, data);
	else if (data <= root->data)
		root->left = ft_bintree_insert(root, root->left, data);
	else
		root->right = ft_bintree_insert(root, root->right, data);
	return (root);
}

t_bstnode	*ft_bintree_add(t_bstnode *root, long int data)
{
	t_bstnode	*new_node;

	if (data > BINTREE_MAX_DATA || data < BINTREE_MIN_DATA)
	{
		write(2, "\e[0;31m", 7);
		ft_putnbr_fd(data, 2);
		ft_putendl_fd(": exceeds binary tree data limit", 2);
		write(2, "\e[0m", 4);
		return (NULL);
	}
	root = ft_bintree_insert(NULL, root, data);
	new_node = ft_bintree_search(root, data);
	printf("Search Check %d\n", (int)new_node->data);
	ft_bintree_balance(&root, new_node);
	return (root);
}
