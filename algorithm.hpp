/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/03 17:19:33 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_H
# define ALGORITHM_H

namespace ft
{
	// /*
	// ** Eh... C++ lexicographical_compare overload seemed like unnecessary code
	// ** duplication to me, so I made a single template that uses a default
	// ** comparison object if none is passed as a parameter, restricting the
	// ** comparable types expected by the comparison object in any case to the
	// ** ones specified by the Iterators.
	// **
	// ** I mean really, I went through all this trouble to make those Iterator
	// ** tags and you're telling me I don't even get to use them? Come on. :p
	// **
	// ** Also, it's a comparison, so I'm only interested in bool-returning
	// ** functions that take two values to compare. Reasonable, right?
	// **
	// ** FOILED AGAIN! Default template arguments for a function template are a
	// ** C++11 extension... BANNED by 42 syllabus. :p F.
	// **
	// ** Oh well, it was hideous anyway... my secret goal was actually to make you
	// ** shriek in horror. BEHOLD, my specialization-free version of
	// ** lexicographical_compare, ye mighty, and DESPAIR xD :
	// */
	//
	// template<typename T, typename U>
	// bool	compare(T const & a, U const & b)
	// {
	// 	return (a < b);
	// }
	//
	// template<typename InputIterator1, typename InputIterator2,
	// bool (*Comp)(typename InputIterator1::reference, typename InputIterator2::reference)
	// = ft::compare<typename InputIterator1::reference, typename InputIterator2::reference> >
	// bool	lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
	// 								InputIterator2 first2, InputIterator2 last2)
	// {
	// 	while(first1 != last1)
	// 	{
	// 		if (first2 == last2 || Comp(*first2, *first1))
	// 			return (false);
	// 		else if (Comp(*first1, *first2))
	// 			return (true);
	// 		++first1; ++first2;
	// 	}
	// 	return (first2 != last2);
	// }

	/*
	** STL-style lexicographical compare. Less nightmare-inducing than my
	** version (only because I try REALLY hard xD).
	*/

	template<typename InputIterator1, typename InputIterator2>
	bool	lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while(first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) //if second range is less than first, or
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1; ++first2;
		}
		return (first2 != last2); //if true, second range was shorter, if false equal? isn't that already checked in while?
	}
	
	/*
	** And... the specialization.
	**
	** It's just amazing HOW MUCH a type-obsessed language like C++ leaves
	** ambiguous in its templates. Those values could be the source code for
	** Cyperpunk 2077 for all we know, while the function might expect an exact
	** bitmap copy of the Mona Lisa. It's TOTAL ANARCHY. xD
	**
	** Even I found it too liberal, but my implementation (commented above) is
	** C++11-dependent, doesn't reflect STL, and, admittedly, it's ugly and
	** even more confusing than templates already are. xD
	**
	** At least it sets some logical type limits for the compare function,
	** though, I mean damn! xD
	*/

	template<typename InputIterator1, typename InputIterator2, typename Comp>
	bool	lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2, Comp comp)
	{
		while(first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1)) //if second range is less than first, or
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			++first1; ++first2;
		}
		return (first2 != last2); //if true, second range was shorter, if false equal? isn't that already checked in while?
	}
}

#endif
