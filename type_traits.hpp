/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:20:31 by mikiencolor       #+#    #+#             */
/*   Updated: 2022/01/21 04:28:26 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_H
# define TYPE_TRAITS_H

#include <clocale> //for NULL

/*
** This is hands down the most demented, twisted, evil thing I have seen in
** programming to date. O_O
**
** So, per Substitution Failure is Not an Error (SFINAE), if the enable_if
** struct has a type, is_odd returns that type, and the enable_if only has a
** type defined if it receives a true bool as first template parameter, and it
** only receives a true bool if is_integral<T>::value is true.
**
** Otherwise, the non-specialized first enable_if template is used, which does
** not define a member type for enable_if, therefore the substitution of the
** return type fails, and therefore the compiler can no longer find a valid
** function that will return the desired type and will, seemingly almost
** accidentally, print out a coherent compile-time error message explaining
** that the reason is the true condition for the first template parameter of the
** only function that does define a type member could not be met with the
** provided typename T.
**
** I feel like hiding under my blanket with some nice, harmless AT&T-syntax
** Assembly until the monsters go away. :_(
*/
namespace ft
{
	template<bool C, typename T = void>
	struct enable_if
	{
	};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T type;
		int tonti;
	};

	template<typename T, T val>
	struct integral_constant
	{
		typedef integral_constant<T,val>	type;
		typedef T							value_type;
		static const T						value = val;
		operator	value_type(void) {
			return (this->value);
		}
	};

	//Most longwinded way of saying const bool IN HISTORY
	//Should be banned by law
	struct true_type : public ft::integral_constant<bool,true>
	{
		typedef true_type	type;
	};

	struct false_type : public ft::integral_constant<bool,false>
	{
		typedef false_type	type;
	};

	//is_integral implementation
	//any instantiation with the listed types inherits true_type.
	//otherwise, the default instantiation inherits false_type.
	template<typename T>
	struct is_integral : public false_type {};
	//Specializations
	template <>
	struct is_integral<bool> : public true_type {};
	template <>
	struct is_integral<char> : public true_type {};
	template <>
	struct is_integral<wchar_t> : public true_type {};
	template <>
	struct is_integral<signed char> : public true_type {};
	template <>
	struct is_integral<short int> : public true_type {};
	template <>
	struct is_integral<int> : public true_type {};
	template <>
	struct is_integral<long int> : public true_type {};
	template <>
	struct is_integral<long long int> : public true_type {};
	template <>
	struct is_integral<unsigned char> : public true_type {};
	template <>
	struct is_integral<unsigned short int> : public true_type {};
	template <>
	struct is_integral<unsigned int> : public true_type {};
	template <>
	struct is_integral<unsigned long int> : public true_type {};
	template <>
	struct is_integral<unsigned long long int> : public true_type {};

	/*
	** This struct does a has_iterator_category check.
	**
	** OMG. This obscene struct receives a type T. It defines a yes of size 1
	** byte and a no of size 2 bytes.
	**
	** Then it declares a function test that does nothing but receive a
	** C::iterator_category *. What the hell is C::iterator_category *, you ask?
	** Why, it's a pointer to C::iterator_category, of course! Who cares that
	** C::iterator_category isn't even a real constructible object? It's valid.
	** You do you, C::iterator_category!
	**
	** So test receives a pointer to C::iterator category. If it receives such a
	** pointer it does nothing with it and returns a reference to our yes.
	** Normally the compiler complains about doing nothing with the variables we
	** receive, but somehow it doesn't here - I have no idea why. Then again,
	** normally functions have actual function bodies and definitions, so fuck
	** me.
	**
	** Then our demented struct declares another function test that takes
	** anything but a C::iterator_category, does nothing with it, and returns a
	** reference to no.
	**
	** Then we define a value to be the result of a comparison between yes and
	** the result of test<T>(NULL), where test is initialized with type T and we
	** just pass it a null pointer (*trollface*). Actually it's not even
	** supposed to be NULL, apparently even that is just too straightforward for
	** C++. No, it defines its own 'nullptr' somewhere. But, guess what? I'm
	** just using good old feckin C-style NULL for my NULL. So DEAL.
	**
	** So anyway, yeah, we pass T to test, where it becomes C, and then we pass
	** it a NULL pointer of type C::iterator_category, which is only possible if
	** C::iterator_category exists, which should (normally) only be true for
	** iterators, unless my evaluator really wants to ruin my day. If it exists
	** the compiler thinks the test that returns the yes reference is the best
	** match, so the comparison returns true, and value is set to true.
	** Otherwise, SFINAE opts for the one that returns the no reference so the
	** comparison returns false, and the value is set to false.
	**
	** All this and I still haven't even made sure this is an input_iterator!
	**
	** At least it seems better than just checking if it's not an integral. xD
	** What happened if the vector was a vector of doubles? Or are doubles
	** really just considered integers under the hood?
	*/

	template<typename T>
	struct	has_iterator_category {
		typedef char yes[1];
		typedef char no[2];

		template<typename C>
		static yes & test(typename C::iterator_category *);
		
		template<typename C>
		static no & test(...);

		static const bool value = sizeof(test<T>(NULL)) == sizeof(yes);
	};

	template<typename T>
	struct	has_iterator {
		typedef char yes[1];
		typedef char no[2];

		template<typename C>
		static yes & test(typename C::iterator *);
		
		template<typename C>
		static no & test(...);

		static const bool value = sizeof(test<T>(NULL)) == sizeof(yes);
	};

	template<typename T>
	//bool xD xD xD xD
	//bool is_odd(T = any_integer)
	/*
	** Included this for enable_if and is_integral testing. So original, I know.
	*/
	typename ft::enable_if<ft::is_integral<T>::value,bool>::type is_odd (T i)
	{
		return (bool (i%2));
	}

	//Primary template
	template<typename T>
	struct st_remove_reference
	{
		typedef T type;
	};

	//lvalue reference is removed
	template<typename T>
	struct st_remove_reference<T&>
	{
		typedef T type;
	};

	//std::move implementation
	//type T is deduced context
	template<typename T>
	typename st_remove_reference<T>::type &	move(T & arg)
	{
		return (static_cast<typename st_remove_reference<T>::type & >(arg));
	}
};

#endif
