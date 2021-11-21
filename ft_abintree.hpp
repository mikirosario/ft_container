/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abintree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:13:06 by miki              #+#    #+#             */
/*   Updated: 2021/11/21 17:27:27 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ABINTREE_H
# define FT_ABINTREE_H

namespace ft
{
	template<typename T>
	class Abintree
	{
		public:
				typedef T	data_type;

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
			t_bstnode *	_root;
			Abintree(void) : _root(NULL) {}
	};
}

#endif