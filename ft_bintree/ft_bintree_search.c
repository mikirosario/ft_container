/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 09:34:57 by miki              #+#    #+#             */
/*   Updated: 2021/11/19 14:56:56 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bintree.hpp"

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

t_bstnode	*ft_bintree_search(t_bstnode *root, long int data)
{
	if (root == NULL || root->data == data)
		return (root);
	else if (data <= root->data)
		return (ft_bintree_search(root->left, data));
	else
		return (ft_bintree_search(root->right, data));
}
