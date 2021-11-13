/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:03:19 by wperu             #+#    #+#             */
/*   Updated: 2021/11/13 18:09:47 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <deque>
//#include  "utils.hpp"

namespace ft
{
    template <class T, class Container = std::deque<T> > class stack
    {
        public: 
            typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::const_reference	const_reference;
			typedef typename Container::reference		reference;

			explicit stack(const Container & ctnr = Container()):c(ctnr)
			{}
			~stack(){};

			bool empty() const
			{
				return this->c.empty();
			}
			
			size_type size() const
			{
				return this->c.size();
			}

			reference top()
			{
				return c.back();
			}
			/*
			const_reference top()
			{
				return c.back();
			}*/
			
			void push (const value_type& val)
			{
				this->c.push_back(val);
			}
			
			void pop()
			{
				this->c.pop_back();
			}

			
		
		protected:
			Container c;
    };

	template <class T, class Container>
  		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return(lhs.c == rhs.c);}
	template <class T, class Container>
  		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return(lhs.c != rhs.c);}
	template <class T, class Container>
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return ( lhs.c < rhs.c);}
	template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return(lhs.c <= rhs.c);}	
	template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{ return(lhs.c > rhs.c);}
	template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	
        { return(lhs.c >= rhs.c);}
}
