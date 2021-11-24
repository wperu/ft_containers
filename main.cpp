/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 18:06:08 by wperu             #+#    #+#             */
/*   Updated: 2021/11/23 19:10:15 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
#include "includes/stack.hpp"
#include "includes/stack_fct.hpp"
#include <stack>

int main()
{
    ft::stack<int> stack;
    ft::stack<int> mystack;

    mystack.push(10);
    mystack.push(19);
    stack.push(10);
    stack.push(20);
    if(stack == mystack)
        std::cout << "ok" << std::endl;
    stack.top() -= 5;
    
    
    std::cout << "stack.top() is now " << stack.top() << std::endl;
    return(0);
}*/

#include <iostream>     // std::cout
#include <iterator>     // std::reverse_iterator
#include <vector>      
#include "includes/iterator_reverse.hpp" // std::vector
/*
int main () {
  std::vector<int>::iterator it;
  std::vector<int> myvector(5,10);

  typedef std::vector<int>::iterator iter_type;
                                                         // ? 0 1 2 3 4 5 6 7 8 9 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  ft::reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
  while (rev_from != rev_until)
    std::cout << ' ' << *rev_from++;
  std::cout << '\n';

  return 0;
}
*/
// vector::rbegin/rend

int main ()
{
  std::vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5,10);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (size_t i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
   std::cout <<"lol = "<< myvector.at(33)<<std::endl;;

  return 0;
}