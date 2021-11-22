/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_fct.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:38:04 by wperu             #+#    #+#             */
/*   Updated: 2021/11/22 19:32:43 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
    template< typename T, typename Allocator>
    vector<T,Allocator>::vector(const allocator_type& alloc = allocator_type()) : data(NULL),capacity(0),size(0), alloc(alloc)
    {}
    
    template< typename T, typename Allocator>
    vector<T,Allocator>::vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : data(NULL),capacity(n),size(n),alloc(alloc)
    {
        init_data(n,val);
    }

        
    
}