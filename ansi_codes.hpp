/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi_codes.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 07:10:32 by miki              #+#    #+#             */
/*   Updated: 2021/11/21 13:40:45 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSI_CODES_H
# define ANSI_CODES_H

/*
** Regular text
*/

# define TXT_BLK "\e[0;30m"
# define TXT_RED "\e[0;31m"
# define TXT_GRN "\e[0;32m"
# define TXT_YEL "\e[0;33m"
# define TXT_BLU "\e[0;34m"
# define TXT_MAG "\e[0;35m"
# define TXT_CYN "\e[0;36m"
# define TXT_WHT "\e[0;37m"

/*
** Regular bold text
*/

# define TXT_BBLK "\e[1;30m"
# define TXT_BRED "\e[1;31m"
# define TXT_BGRN "\e[1;32m"
# define TXT_BYEL "\e[1;33m"
# define TXT_BBLU "\e[1;34m"
# define TXT_BMAG "\e[1;35m"
# define TXT_BCYN "\e[1;36m"
# define TXT_BWHT "\e[1;37m"

/*
**Regular underlined text
*/

# define TXT_UBLK "\e[4;30m"
# define TXT_URED "\e[4;31m"
# define TXT_UGRN "\e[4;32m"
# define TXT_UYEL "\e[4;33m"
# define TXT_UBLU "\e[4;34m"
# define TXT_UMAG "\e[4;35m"
# define TXT_UCYN "\e[4;36m"
# define TXT_UWHT "\e[4;37m"

/*
** Regular background
*/

# define TXT_BLKB "\e[40m"
# define TXT_REDB "\e[41m"
# define TXT_GRNB "\e[42m"
# define TXT_YELB "\e[43m"
# define TXT_BLUB "\e[44m"
# define TXT_MAGB "\e[45m"
# define TXT_CYNB "\e[46m"
# define TXT_WHTB "\e[47m"

/*
** High intensity background 
*/

# define TXT_BLKHB "\e[0;100m"
# define TXT_REDHB "\e[0;101m"
# define TXT_GRNHB "\e[0;102m"
# define TXT_YELHB "\e[0;103m"
# define TXT_BLUHB "\e[0;104m"
# define TXT_MAGHB "\e[0;105m"
# define TXT_CYNHB "\e[0;106m"
# define TXT_WHTHB "\e[0;107m"

/*
** High intensity text
*/

# define TXT_HBLK "\e[0;90m"
# define TXT_HRED "\e[0;91m"
# define TXT_HGRN "\e[0;92m"
# define TXT_HYEL "\e[0;93m"
# define TXT_HBLU "\e[0;94m"
# define TXT_HMAG "\e[0;95m"
# define TXT_HCYN "\e[0;96m"
# define TXT_HWHT "\e[0;97m"

/*
** Bold high intensity text
*/

# define TXT_BHBLK "\e[1;90m"
# define TXT_BHRED "\e[1;91m"
# define TXT_BHGRN "\e[1;92m"
# define TXT_BHYEL "\e[1;93m"
# define TXT_BHBLU "\e[1;94m"
# define TXT_BHMAG "\e[1;95m"
# define TXT_BHCYN "\e[1;96m"
# define TXT_BHWHT "\e[1;97m"

/*
** Reset
*/

# define TXT_RST "\e[0m"
# define TXT_NL "\n"
# define TXT_TAB "\t"
# define TXT_SEP "-------------------------------------------------------------------------------------"

#endif