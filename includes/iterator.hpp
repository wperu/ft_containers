/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:42:23 by wperu             #+#    #+#             */
/*   Updated: 2021/12/09 20:42:13 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator_traits.hpp"

template<class Category, class T, class Distance, class Pointer, class Reference>
struct ft::base_iterator
{
	typedef T			value_type;
	typedef Distance 	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category 	iterator_category;
};