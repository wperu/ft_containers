/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:38:57 by wperu             #+#    #+#             */
/*   Updated: 2021/10/26 18:22:11 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <cstddef>



namespace ft
{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag       : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
    struct iterator 
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
    
    template < typename Iter>
    struct iterator_traits
    {
        typedef typename Iter::difference_type   difference_type;
        typedef typename Iter::value_type        value_type;
        typedef typename Iter::pointer           pointer;
        typedef typename Iter::reference         reference;
        typedef typename Iter::iterator_category iterator_category;
    };
    
    template <typename Iter_type>
    struct iterator_traits<Iter_type*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef Iter_type                  value_type;
        typedef std::ptrdiff_t             difference_type;
        typedef Iter_type*                 pointer;
        typedef Iter_type&                 reference;
    };
    
    template <typename Iter_type>
    struct iterator_traits<const Iter_type*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef Iter_type                  value_type;
        typedef std::ptrdiff_t             difference_type;
        typedef Iter_type*                 pointer;
        typedef Iter_type&                 reference;
    };

    
    
    
}