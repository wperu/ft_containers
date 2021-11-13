/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:06:08 by wperu             #+#    #+#             */
/*   Updated: 2021/11/13 18:18:32 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.hpp"

int main()
{
    ft::stack<int> stack;
    ft::stack<int> mystack;
    
    stack.push(10);
    stack.push(20);
    stack.top() -= 5;
    stack.pop();
    std::cout << "stack.top() is now " << stack.top() << "\n";
    return(0);
}