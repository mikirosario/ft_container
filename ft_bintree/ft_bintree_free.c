/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 09:47:22 by miki              #+#    #+#             */
/*   Updated: 2021/11/19 14:56:56 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bintree.hpp"

t_bstnode	*node_delete(t_bstnode *node)
{
	ft_bzero(node, sizeof(t_bstnode));
	free(node);
	return (NULL);
}

t_bstnode	*root_canal(t_bstnode *root)
{
	if (root)
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
	while (parent)
	{
		while (parent->left || parent->right)
		{
			if (parent->left)
			{
				if (parent->left->left || parent->left->right)
					parent = parent->left;
				else
					parent->left = node_delete(parent->left);
			}
			else if (parent->right)
			{
				if (parent->right->left || parent->right->right)
					parent = parent->right;
				else
					parent->right = node_delete(parent->right);
			}
		}
		parent = parent->parent;
	}
	return (root_canal(root));
}

// Recursive function to do this, without the bzero... didn't like the idea of
// a potential memory bomb. :P
		// if (root) //recursive
		// {
		// 	root->right = ft_binary_tree_free(root->right);
		// 	root->left = ft_binary_tree_free(root->left);
		// 	free(root);
		// }
