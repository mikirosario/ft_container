/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:36:06 by miki              #+#    #+#             */
/*   Updated: 2022/01/21 06:29:08 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

#include "ft_vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef std::size_t	size_type;

			explicit stack(container_type const & ctnr = container_type()) : c(ctnr) {}
			
			bool	empty(void) const {
				return (c.empty());
			}
			
			size_type	size(void) const {
				return (c.size());
			}

			value_type & top(void) {
				return (c.back());
			}

			value_type const & top(void) const {
				return (c.back());
			}

			void	push(value_type const & val) {
				c.push_back(val);
			}

			void	pop(void) {
				c.pop_back();
			}

			template<typename T_op, typename Container_op>
			friend bool	operator==(stack<T_op, Container_op> const & lhs, stack<T_op, Container_op> const & rhs);

			template<typename T_op, typename Container_op>
			friend bool	operator!=(stack<T_op, Container_op> const & lhs, stack<T_op, Container_op> const & rhs);

			template<typename T_op, typename Container_op>
			friend bool	operator<(stack<T_op, Container_op> const & lhs, stack<T_op, Container_op> const & rhs);

			template<typename T_op, typename Container_op>
			friend bool	operator<=(stack<T_op, Container_op> const & lhs, stack<T_op, Container_op> const & rhs);

			template<typename T_op, typename Container_op>
			friend bool	operator>(stack<T_op, Container_op> const & lhs, stack<T_op, Container_op> const & rhs);

			template<typename T_op, typename Container_op>
			friend bool	operator>=(stack<T_op, Container_op> const & lhs, stack<T_op, Container_op> const & rhs);
		protected:
			container_type	c;
	};

	template<class T, class Container>
	bool	operator==(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs.c == rhs.c);
	}

	template<class T, class Container>
	bool	operator!=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs.c != rhs.c);
	}

	template<class T, class Container>
	bool	operator<(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs.c < rhs.c);
	}

	template<class T, class Container>
	bool	operator<=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs.c <= rhs.c);
	}

	template<class T, class Container>
	bool	operator>(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs.c > rhs.c);
	}

	template<class T, class Container>
	bool	operator>=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs.c >= rhs.c);
	}
};

#endif
