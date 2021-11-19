/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_termcaps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:39:52 by miki              #+#    #+#             */
/*   Updated: 2021/11/19 14:56:56 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bintree.hpp"

#ifdef __linux__
# include <termcap.h>
#endif
#include <curses.h>
#include <term.h>

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

	termtype = getenv("TERM");
	capbuf = &tcaps->capbuf[0];
	if (termtype && tgetent(tcaps->termbuf, termtype) > 0)
	{
		tcaps->cur_mov = tgetstr("cm", &capbuf);
		tcaps->scroll_up = tgetstr("sf", &capbuf);
		if (tcaps->cur_mov && tcaps->scroll_up)
			return (1);
	}
	ft_putendl_fd("NO TERM DEFINED OR INVALID TERM TYPE\n", 2);
	return (0);
}
