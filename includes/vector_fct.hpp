/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_fct.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:38:04 by wperu             #+#    #+#             */
/*   Updated: 2021/11/23 20:58:03 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
    template< typename T, typename alloc>
    vector<T,alloc>::vector(const allocator_type& allocator = allocator_type()) : data(NULL),_capacity(0),_size(0), _alloc(allocator)
    {}
    
    template< typename T, typename alloc>
    vector<T,alloc>::vector(size_type n, const value_type& val = value_type(), const allocator_type& allocator = allocator_type()) : data(NULL),_capacity(n),_size(n),_alloc(allocator)
    {
        this->init_data(n,val);
    }
    
    /*template< typename T, typename alloc>
   // vector<T,alloc>::
    {
        this->data = this->alloc.allocated(src.capacity);
        this->assign(src.begin(),src.end());
    }
*/
    template<typename T,typename alloc>
    vector<T,alloc>::~vector()
    {
        this->destroy_data();
        this->_alloc.deallocate(this->data,this->_capacity);

    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::iterator vector<T,alloc>::begin()
    {
        return vector<T,alloc>::iterator(data);
    }
    
    template<typename T, typename alloc>
    typename vector<T,alloc>::const_iterator vector<T,alloc>::begin() const
    {
        return vector<T,alloc>::const_iterator(data);
    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::iterator vector<T,alloc>::end()
    {
        return vector<T,alloc>::iterator(data[_size]);
    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::const_iterator vector<T,alloc>::end() const
    {
        return vector<T,alloc>::const_iterator(data[_size]);
    }

   //***ITERATOR***

    template<typename T, typename alloc>
    typename vector<T,alloc>::reverse_iterator vector<T,alloc>::rbegin()
    {
        return reverse_iterator(end());
    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::const_reverse_iterator vector<T,alloc>::rbegin() const
    {
        return const_reverse_iterator(end());
    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::reverse_iterator vector<T,alloc>::rend()
    {
        return reverse_iterator(begin());
    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::const_reverse_iterator vector<T,alloc>::rend() const
    {
        return const_reverse_iterator(begin());
    }


    //Capacity

    template<typename T, typename alloc>
    typename vector<T,alloc>::size_type vector<T,alloc>::size(void) const
    {
        return this->size;
    }
    
    template<typename T, typename alloc>
    typename vector<T,alloc>::size_type vector<T,alloc>::max_size() const
    {
        return std::numeric_limits<difference_type>::max();
    }

    template<typename T, typename alloc>
    void vector<T,alloc>::resize(size_type n, value_type val = value_type())
    {
        if(n <= this->_size)
        {
            while(this->_size > n)
            {
                --this->_size;
                this->_alloc.destroy(&(this->data[this->_size]));
            }
            return ;
        }
        this->reserve(n);
        std::cout<<"size: "<<this->_size <<std::endl;
        while(this->_size < n)
        {
            this->_alloc.destroy(&(this->data[this->_size]));
            this->_alloc.construct(&(this->data[this->_size]));
            this->_size++;
        }
        return ;
        
    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::size_type vector<T,alloc>::capacity(void) const
    {
        return this->capacity;
    }
    
    template<typename T, typename alloc>
    bool vector<T,alloc>::empty() const
    {
        return (begin() == end());
    }
    
    template<typename T, typename alloc>
    void vector<T,alloc>::reserve(size_type n)
    {
        size_type i = 0;
		if(n < this->size)
            return;
        if(n > this->max_size())
            n = this->max_size();
		vector<T,alloc>::size_type oldcapacity = this->_capacity;
		if(this->_capacity == 0)
            this->_capacity++;
		if(this->_capacity < n)
			this->_capacity *= 2;
		T *tmp = this->_alloc.allocate(this->_capacity);
        while(i < this->_size)
		{
			this->_alloc.construct(&tmp[i],this->data[i]));
			i++;
		}
		this->destroy_data();
        this->_alloc.deallocate(this->data,oldcapacity);
		data = tmp;
    }

	template<typename T, typename alloc>
    typename vector<T,alloc>::reference vector<T,alloc>::operator[](size_type n)
    {
		this->data[n];	
	}
	template<typename T, typename alloc>
    typename vector<T,alloc>::const_reference vector<T,alloc>::operator[](size_type n) const
	{
		this->data[n];	
	}

	template<typename T, typename alloc>
	typename vector<T,alloc>::reference vector<T,alloc>::at(size_type n)
	{
		if(n > this->_size)
			throw std::out_of_range("vector");
		this->data[n];	
	}

	template<typename T, typename alloc>
	typename vector<T,alloc>::const_reference vector<T,alloc>::at(size_type n) const
	{
		if(n > this->_size)
			throw std::out_of_range("vector");
		this->data[n];	
	}

	template<typename T, typename alloc>
    typename vector<T,alloc>::const_reference vector<T,alloc>::front() const
	{
		this->data[0];	
	}

	template<typename T, typename alloc>
    typename vector<T,alloc>::const_reference vector<T,alloc>::front() const
	{
		this->data[0];	
	}

	template<typename T, typename alloc>
    typename vector<T,alloc>::const_reference vector<T,alloc>::back() const
	{
		this->data[this->_size - 1];	
	}

	template<typename T, typename alloc>
    typename vector<T,alloc>::const_reference vector<T,alloc>::back() const
	{
		this->data[this->_size - 1];	
	}

	template<typename T,typename alloc>
	template<class InputIterator>
	void  vector<T,alloc>::assign(typename ft::enable_if< is_iterator<InputIterator>::value, InputIterator>::type first,
	InputIterator last)
	{
        typename vector<T, alloc>::size_type i = 0;
        typename vector<T, alloc>::difference_type size = std::abs(first - last);
        this->reserve(size);
        while(first != last)
        {
            this->_alloc.destroy(&this->data[i]);
            this->_alloc.construct(&this->data[i],*first);
            std::cout << this->_data[i] << std::endl;
            ++first;
            ++i;
        }
	}

    template<typename T,typename alloc>
    void vector<T,alloc>::assign(size_type n, const value_type& val)
    {
        
    }
	
}