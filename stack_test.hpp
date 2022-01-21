/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:10:02 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/21 10:24:00 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"
#include <stack>
#include "stack.hpp"

template <typename Stack_T>
void	stack_test(void)
{
	//DEFAULT CONSTRUCTOR (NO OTHERS IN C++98)
	PRINT	<< TXT_NL << TXT_BYEL << "STACK CONSTRUCTION TEST" << END;
	Stack_T	the_stack;

	//SIZE
	PRINT << the_stack.size() << TXT_NL;
	//EMPTY FUNCTION
	PRINT	<< the_stack.empty() << TXT_NL;
	//PUSH FUNCTION
	PRINT	<< TXT_NL << TXT_BYEL << "PUSH TESTS" << END;
	the_stack.push(42);
	the_stack.push(84);
	the_stack.push(168);
	the_stack.push(336);
	//TOP FUNCTION
	PRINT	<< TXT_NL << TXT_BYEL << "TOP TEST" << END;
	PRINT	<< the_stack.top() << TXT_NL;
	//POP FUNCTION
	PRINT	<< TXT_NL << TXT_BYEL << "POP TEST" << END;
	the_stack.pop();
	PRINT	<< the_stack.top() << TXT_NL;
	PRINT	<< the_stack.size() << TXT_NL;
}
