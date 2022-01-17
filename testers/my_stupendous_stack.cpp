/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_stupendous_stack.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:04:48 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/17 19:46:14 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../testers.hpp"
#include "../ft_stack.hpp"
#include <stack>

bool	my_stupendous_stack(void)
{
	bool			ret = true;
	char const *	color = TXT_BGRN;

	//DEFAULT CONSTRUCTOR (NO OTHERS IN C++98)
	PRINT	<< TXT_NL << TXT_BYEL << "STACK CONSTRUCTION TEST"
			<< TXT_NL << TXT_TAB << "stack<int>" << END;
	ft::stack<int>	mi_stack;
	std::stack<int>	su_stack;
	check(mi_stack.size() == su_stack.size(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.size()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.size() << END;
	//EMPTY FUNCTION
	PRINT	<< TXT_NL << TXT_BYEL << "EMPTY TEST"
			<< TXT_NL << TXT_TAB << "stack.empty()" << END;
	check(mi_stack.empty() == su_stack.empty(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.empty()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.empty() << END;
	//PUSH FUNCTION
	PRINT	<< TXT_NL << TXT_BYEL << "PUSH TESTS"
			<< TXT_NL << TXT_BYEL << TXT_NL << TXT_TAB << "stack.push(42)"
			<< TXT_NL << TXT_TAB << "stack.size()" << END;
	mi_stack.push(42);
	su_stack.push(42);
	check(mi_stack.size() == su_stack.size(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.size()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.size() << END;
	PRINT	<< TXT_BYEL << TXT_TAB << "stack.empty()" << END;
	check(mi_stack.empty() == su_stack.empty(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.empty()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.empty() << END;
	
	PRINT	<< TXT_NL << TXT_BYEL << TXT_NL << TXT_TAB << "stack.push(84)"
			<< TXT_NL << TXT_TAB << "stack.size()" << END;
	mi_stack.push(84);
	su_stack.push(84);
	check(mi_stack.size() == su_stack.size(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.size()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.size() << END;
	PRINT	<< TXT_BYEL << TXT_TAB << "stack.empty()" << END;
	check(mi_stack.empty() == su_stack.empty(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.empty()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.empty() << END;

	PRINT	<< TXT_NL << TXT_BYEL << TXT_NL << TXT_TAB << "stack.push(168)"
			<< TXT_NL << TXT_TAB << "stack.size()" << END;
	mi_stack.push(168);
	su_stack.push(168);
	check(mi_stack.size() == su_stack.size(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.size()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.size() << END;
	PRINT	<< TXT_BYEL << TXT_TAB << "stack.empty()" << END;
	check(mi_stack.empty() == su_stack.empty(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.empty()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.empty() << END;
	
	PRINT	<< TXT_NL << TXT_BYEL << TXT_NL << TXT_TAB << "stack.push(336)"
			<< TXT_NL << TXT_TAB << "stack.size()" << END;
	mi_stack.push(336);
	su_stack.push(336);
	check(mi_stack.size() == su_stack.size(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.size()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.size() << END;
	PRINT	<< TXT_BYEL << TXT_TAB << "stack.empty()" << END;
	check(mi_stack.empty() == su_stack.empty(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << mi_stack.empty()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << su_stack.empty() << END;
	//TOP FUNCTION
	PRINT	<< TXT_NL << TXT_BYEL << "TOP TEST" << END;
	check(mi_stack.top() == su_stack.top(), color, ret);
	PRINT	<< TXT_TAB << color << "FT::STACK: " << TXT_TAB << mi_stack.top()
			<< TXT_NL << TXT_TAB << "STD::STACK: " << TXT_TAB << su_stack.top() << END;
	
	//POP FUNCTION
	PRINT	<< TXT_NL << TXT_BYEL << "POP TEST"
			<< TXT_NL << TXT_TAB << "stack.pop()" << END;
	mi_stack.pop();
	su_stack.pop();
	check(mi_stack.top() == su_stack.top(), color, ret);
	PRINT	<< TXT_TAB << TXT_BYEL << "Top:"
			<< TXT_NL << TXT_TAB << color << mi_stack.top()
			<< TXT_NL << TXT_TAB << su_stack.top() << END;
	
	check(mi_stack.size() == su_stack.size(), color, ret);
	PRINT	<< TXT_NL << TXT_TAB << TXT_BYEL << "Size:"
			<< TXT_NL << TXT_TAB << color << mi_stack.size()
			<< TXT_NL << TXT_TAB << su_stack.size() << END;
	
	//RELATIONAL OPERATORS
	PRINT << TXT_NL;
	ft::stack<int>	mi_other_stack;
	std::stack<int>	su_other_stack;
	mi_other_stack.push(525);
	su_other_stack.push(525);
	comparison_operator_log(su_stack, su_other_stack, mi_stack, mi_other_stack, ret);
	return (ret);
}
