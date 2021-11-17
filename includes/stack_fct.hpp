/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_fct.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:43:25 by wperu             #+#    #+#             */
/*   Updated: 2021/11/17 18:06:24 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stack.hpp"
namespace ft
{
    template <class T, class Alloc>
	bool operator== (const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
	{
		return (ft::equal<
			typename stack<T, Alloc>::const_iterator,
			typename stack<T, Alloc>::const_iterator >(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator< (const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator> (const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
}