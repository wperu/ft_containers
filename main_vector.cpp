/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:26:36 by wperu             #+#    #+#             */
/*   Updated: 2021/11/24 20:20:56 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vector_fct.hpp"
#include <iostream>
//#include "includes/vector.hpp"

int main()
{
    ft::vector<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<10; i++) myints.push_back(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert (myints.end(),10,100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.pop_back();
  std::cout << "3. size: " << myints.size() << '\n';
    
    return(0);
    
}
