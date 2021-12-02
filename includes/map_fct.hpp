/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fct.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:12:07 by wperu             #+#    #+#             */
/*   Updated: 2021/12/02 20:19:32 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map.hpp"

namespace ft
{
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::allocator_type map<Key,T,Compare,alloc>::get_allocator() const
	{
		return this->_alloc;
	}
	
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::key_compare map<Key,T,Compare,alloc>::key_comp() const
    {
        return(this->comp);
    }

    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::value_compare map<Key,T,Compare,alloc>::value_comp() const
    {
        return(this->comp);
    }
    Create

    
} 
