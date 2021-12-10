/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_reverse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:22:16 by wperu             #+#    #+#             */
/*   Updated: 2021/12/10 15:56:35 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "iterator_traits.hpp"
#pragma once

namespace ft
{
    template<class Iterator>
    class reverse_iterator
    {
        protected:
        	Iterator current;
        public:
        	typedef Iterator                                            iterator_type;
    		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iterator>::reference       reference;
			typedef typename ft::iterator_traits<Iterator>::pointer         pointer;
    
		reverse_iterator(): current() {}
		explicit reverse_iterator(iterator_type it): current(it) {}
		reverse_iterator(const reverse_iterator<Iterator>& rev_it): current(rev_it.current){}
		~reverse_iterator() {}
		
		iterator_type base() const
		{ return current; }
	
	//operator
	
		reference operator*() const
		{
			Iterator tmp = current;
        	return *--tmp;
		}
		
		pointer operator->()const
		{
			return &(operator*());
		}


		reverse_iterator &operator++()
		{
			--current;
        	return *this;
		}
		
		reverse_iterator operator++(int) 
		{
  			reverse_iterator temp = *this;
  			--current;
  			return temp;
		}

		reverse_iterator &operator--()
		{
			++current;
        	return *this;
		}
		
		reverse_iterator operator--(int) 
		{
  			reverse_iterator temp = *this;
  			++current;
  			return temp;
		}

		reverse_iterator operator+ (difference_type n) const
		{
			return(reverse_iterator(current - n));
		}

		reverse_iterator operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reverse_iterator operator- (difference_type n) const
		{
			return(reverse_iterator(current + n));
		}

		reverse_iterator operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,	const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base()==rhs.base());
	}
		
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base()!=rhs.base());
	}	
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base()<rhs.base());
	}
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base()<=rhs.base());
	}	
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base()>rhs.base());
	}
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base()>=rhs.base());
	}
}