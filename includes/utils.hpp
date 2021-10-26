/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:53:04 by wperu             #+#    #+#             */
/*   Updated: 2021/10/26 18:30:56 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <cstddef>

namespace ft
{
    template<bool Cond, class T = void> 
    struct enable_if {};
    
    template<class T> 
    struct enable_if<true, T> { typedef T type; };
    
}