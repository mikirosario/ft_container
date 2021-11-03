/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:20:31 by mikiencolor       #+#    #+#             */
/*   Updated: 2021/11/03 15:27:15 by mikiencolor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_H
# define TYPE_TRAITS_H

//#include <uchar.h> //?? To be continued...

// //DEBUG CODE
// #include <type_traits>
// //DEBUG CODE

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
	// template <>
	// struct is_integral<char16_t> : public true_type {};
	// template <>
	// struct is_integral<char32_t> : public true_type {};
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
};

#endif