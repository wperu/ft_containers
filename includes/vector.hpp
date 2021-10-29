/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:01:48 by wperu             #+#    #+#             */
/*   Updated: 2021/10/29 17:53:43 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <typeinfo>
#include <utils.hpp>

namespace ft
{
    template <class T, class alloc = std::allocator <T> >
    class vector
    {
        typedef T                                                       type_value;
        typedef alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef typename ft::random_access_iterator<type_value>         iterator;
        typedef typename ft::random_access_iterator<const type_value>   const_iterator;
        typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::const_reverse_iterator<const iterator>     const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef typename allocator_type::size_type                      size_type;
    
        
        explicit vector(const allocator_type& alloc = allocator_type()));
        explicit vector(size_type n, const type_value& val = value_type(), const allocator_type &alloc = allocateur_type());
        
        template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type);
        
        vector (const vector& src);
        
        
    };
}

