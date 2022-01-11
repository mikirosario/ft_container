/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:36:06 by miki              #+#    #+#             */
/*   Updated: 2022/01/11 14:55:20 by miki             ###   ########.fr       */
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

			explicit stack(container_type const & ctnr = container_type()) : _ctnr(ctnr) {}
			
			bool	empty(void) const {
				return (_ctnr.empty());
			}
			
			size_type	size(void) const {
				return (_ctnr.size());
			}

			value_type & top(void) {
				return (_ctnr.back());
			}

			value_type const & top(void) const {
				return (_ctnr.back());
			}

			void	push(value_type const & val) {
				_ctnr.push_back(val);
			}

			void	pop(void) {
				_ctnr.pop_back();
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
		private:
				private:
			container_type	_ctnr;
	};

	template<class T, class Container>
	bool	operator==(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs._ctnr == rhs._ctnr);
	}

	template<class T, class Container>
	bool	operator!=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs._ctnr != rhs._ctnr);
	}

	template<class T, class Container>
	bool	operator<(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs._ctnr < rhs._ctnr);
	}

	template<class T, class Container>
	bool	operator<=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs._ctnr <= rhs._ctnr);
	}

	template<class T, class Container>
	bool	operator>(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs._ctnr > rhs._ctnr);
	}

	template<class T, class Container>
	bool	operator>=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs) {
		return (lhs._ctnr >= rhs._ctnr);
	}
};

#endif