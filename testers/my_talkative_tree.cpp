/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_talkative_tree.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 05:53:55 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/21 06:12:52 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_set.hpp"
#include "../testers.hpp"

/*
** The red-black binary tree comes with a simple debugging tool that prints out
** numeric trees. This test just creates such an numeric tree and prints it for
** evaluation purposes, to help visualize the mechanics of a red-black tree
** during evaluation and how the trees are structured and balanced.
**
** I already had this tool programmed in C for my own testing from when I first
** programmed the red-black tree in C (as you can see, back when I was also big
** on studying termcaps xD). I felt I needed it to get a more intuitive sense of
** what I was programming and to make checking correctness easier at a glance.
**
** I've just done a quick adaptation of the original code to this project. I
** removed printfs and made it an inheritable class, basically.
**
** It's very rudimentary, but I think it helps a lot to see what we're dealing
** with. I find it much better to visualize the tree than a simple list of
** levels. Feel free to play around with it.
**
** This function returns a bool just so I can use it in the same array as the
** other function pointers. It always returns true. ;)
*/
bool	my_talkative_tree(void) {
	ft::set<int>	test;

	test.insert(42);
	test.insert(84);
	test.insert(21);
	test.insert(2);
	test.insert(-42);
	test.insert(0);
	test.insert(10924);
	test.insert(474);
	test.insert(89);
	test.insert(10925);
	test.print_underlying_rb_tree();
	return (true);
}
