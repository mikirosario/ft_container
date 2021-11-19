/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_depth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:26:24 by miki              #+#    #+#             */
/*   Updated: 2021/11/19 14:56:56 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bintree.hpp"

size_t	ft_bintree_depth(t_bstnode *root)
{
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
