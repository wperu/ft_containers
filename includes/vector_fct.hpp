/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_fct.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:38:04 by wperu             #+#    #+#             */
/*   Updated: 2021/12/07 13:59:53 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
    template< typename T, typename alloc>
    vector<T,alloc>::vector(const allocator_type& allocator) : data(NULL),_capacity(0),_size(0), _alloc(allocator)
    {}
    
    template< typename T, typename alloc>
    vector<T,alloc>::vector(size_type n, const value_type& val , const allocator_type& allocator) : data(NULL),_capacity(n),_size(n),_alloc(allocator)
    {
        this->init_data(n,val);
    }

	template< typename T, typename alloc>
    vector<T,alloc>::vector(const vector& src)
	{
		*this = src;
	}
	
    
    template< typename T, typename alloc>
    vector<T,alloc>& vector<T,alloc>::operator=(const vector& x)
    {
        this->data = this->_alloc.allocate(x._capacity);
        this->assign(x.begin(),x.end());
        return *this;
    }

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
        return vector<T,alloc>::iterator(&data[_size]);
    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::const_iterator vector<T,alloc>::end() const
    {
        return vector<T,alloc>::const_iterator(&data[_size]);
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
        return this->_size;
    }
    
    template<typename T, typename alloc>
    typename vector<T,alloc>::size_type vector<T,alloc>::max_size() const
    {
        return std::numeric_limits<difference_type>::max();
    }

    template<typename T, typename alloc>
    void vector<T,alloc>::resize(size_type n, value_type val )
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
            this->_alloc.construct(&(this->data[this->_size]),val);
            this->_size++;
        }
        return ;
        
    }

    template<typename T, typename alloc>
    typename vector<T,alloc>::size_type vector<T,alloc>::capacity(void) const
    {
        return this->_capacity;
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
		if(n <= this->_capacity)
            return;
        if(n > this->max_size())
            n = this->max_size();
		typename vector<T,alloc>::size_type oldcapacity = this->_capacity;
		if(this->_capacity == 0)
            this->_capacity++;
		while(this->_capacity < n)
			this->_capacity++;
		T *tmp = this->_alloc.allocate(this->_capacity);
        while(i < this->_size)
		{
			this->_alloc.construct(&tmp[i],this->data[i]);
			i++;
		}
		this->destroy_data();
        this->_alloc.deallocate(this->data,oldcapacity);
		this->data = tmp;
    }

	template<typename T, typename alloc>
    typename vector<T,alloc>::reference vector<T,alloc>::operator[](vector<T,alloc>::size_type n)
    {
		return this->data[n];
	}
	template<typename T, typename alloc>
    typename vector<T,alloc>::const_reference vector<T,alloc>::operator[](size_type n) const
	{
		return this->data[n];	
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
		return this->data[n];	
	}

	template<typename T, typename alloc>
    typename vector<T,alloc>::reference vector<T,alloc>::front() 
	{
		return this->data[0];	
	}

	template<typename T, typename alloc>
    typename vector<T,alloc>::const_reference vector<T,alloc>::front() const
	{
		return this->data[0];	
	}

	template<typename T, typename alloc>
    typename vector<T,alloc>::reference vector<T,alloc>::back() 
	{
		return this->data[this->_size - 1];	
	}

	template<typename T, typename alloc>
    typename vector<T,alloc>::const_reference vector<T,alloc>::back() const
	{
		return this->data[this->_size - 1];	
	}

	template<typename T,typename alloc>
	template<class InputIterator>
	void  vector<T,alloc>::assign(typename ft::enable_if< is_iterator<InputIterator>::value, InputIterator>::type first,
	InputIterator last)
	{
        typename vector<T, alloc>::size_type i = 0;
        typename vector<T, alloc>::difference_type size = std::abs(last - first);
        this->reserve(size);
        while(first != last)
        {
            this->_alloc.destroy(&this->data[i]);
            this->_alloc.construct(&this->data[i],*first);
			std::cout << *first << std::endl;
            ++first;
            ++i;
        }
	}

    template<typename T,typename alloc>
    void vector<T,alloc>::assign(size_type n, const value_type& val)
    {
        typename vector<T, alloc>::size_type i = 0;
        this->reserve(n);
        this->resize(n);
        while(i != n)
        {
           // this->_alloc.destroy(&this->data[i]);
            this->_alloc.construct(&this->data[i],val);
            std::cout << this->_data[i] << std::endl;
            ++i;
        }
    }
    
    template <typename T, typename alloc>
    void vector<T,alloc>::push_back(const value_type& val)
    {
        if(this->_size == this->_capacity)
        {
            size_type n = this->_size + 1;
			//this->reserve(this->_size + 1);
			size_type i = 0;
			typename vector<T,alloc>::size_type oldcapacity = this->_capacity;
			if(this->_capacity == 0)
				this->_capacity++;
			while(this->_capacity < this->_size + 1)
				this->_capacity *= 2;
			T *tmp = this->_alloc.allocate(this->_capacity);
			while(i < this->_size)
			{
				this->_alloc.construct(&tmp[i],this->data[i]);
				i++;
			}
			this->destroy_data();
			this->_alloc.deallocate(this->data,oldcapacity);
			this->data = tmp;
        }
        this->_alloc.construct(&this->data[this->_size],val);
        this->_size++;
    }
    
    template <typename T, typename alloc>
    void vector<T,alloc>::pop_back()
    {
        this->_alloc.destroy(&this->data[this->_size]);
        this->reserve(this->_size - 1);
        this->_size--;
    }
    
    template <typename T, typename alloc>
    typename vector<T,alloc>::iterator vector<T,alloc>::insert (iterator position, const value_type& val)
    {
        value_type tmp;
        value_type before;
        vector<T,alloc>::iterator first = position;

        reserve(this->size + 1);
        this->size++;
        tmp = *position;
		before = tmp;
        *position = value_type(val);
        ++position;
        while(position != this->end())
        {
			tmp = before;
			before = *position;
			*position = tmp;
			++position;
        }
		return first;
    }
    
	template <typename T, typename alloc>
	void vector<T, alloc>::insert(iterator position, size_type n, const value_type& val)
	{
		size_type limit;
		size_type oldsize = this->_size;

		if(n == 0)
			return ;
		this->reserve(this->_size + n);
        this->_size += n;
		limit = position - this->begin();
		while(--oldsize >= limit)
			this->data[oldsize + n ] = this->data[oldsize];
        oldsize = limit + n;
		while(--oldsize >= limit)
			this->data[oldsize] = value_type(val);
		return ;
	}

	template <typename T, typename alloc>
    typename vector<T,alloc>::iterator vector<T,alloc>::erase(iterator position)
	{
        typename vector<T, alloc>::iterator ret_value = this->begin();
		iterator it = ret_value;
		for (; it != this->end() && it != position; ++it)
			;
		if (it == this->end())
			return ret_value;
		ret_value = it + 1;
		while (it != this->end() - 1)
		{
			*it = *(it + 1);
			++it;
		}
		--this->_size;
		return ret_value;
	}

	template <typename T, typename alloc>
    typename vector<T,alloc>::iterator vector<T,alloc>::erase(iterator first ,iterator last)
	{
		typename vector<T, alloc>::iterator ret_value = this->begin();
		iterator itf = ret_value;
		iterator itl = ret_value;

		for (; itf != this->end() && itf != first; ++itf)
			;
		for (; itl != this->end() && itl != last; ++itl)
			;
		if (itf == this->end() || itl == this->end())
			return ret_value;
		while (itf != this->end() && itl != this->end())
		{
			*itf = *itl;
			++itf;
			++itl;
		}
		this->_size -= std::abs(last - first);
		return itf;
	}
	
	template <typename T, typename alloc>
	void vector<T,alloc>::swap(vector& x)
	{
		size_type tmpc = this->_capacity;
		size_type tmps = this->_size;
		value_type *tmpd = this->data;
		
		this->data = x.data;
		this->_capacity = x._capacity;
		this->_size = x._size;
		x.data = tmpd;
		x._capacity = tmpc;
		x._size = tmps; 
	}

	template <typename T, typename alloc>
	void vector<T,alloc>::clear()
	{
		//vector<T,alloc>::iterator first = this->begin();
		this->destroy_data();
		this->_size = 0;
	}

	//Allocator

	template <typename T, typename alloc>
	typename vector<T,alloc>::allocator_type vector<T,alloc>::get_allocator() const
	{
		return this->_alloc;
	}
	
	template<typename T,typename alloc>
	void vector<T,alloc>::init_data(size_type n , const value_type val)
	{
		size_type i = 0;
		this->data=this->_alloc.allocate(n);
	
		while(i < n)
		{
			this->_alloc.construct(&this->data[i],val);
			i++;
		}
		this->_size = n;
		this->_capacity = n;
	}

	template<typename T, typename alloc>
	void vector<T,alloc>::destroy_data()
	{
		size_type i = 0 ;
		while(i < this->_size)
		{
			this->_alloc.destroy(&this->data[i]);
			i++;
		}	
	}


	//no members

	template<class T, class alloc>
	void swap (vector<T,alloc>& x, vector<T,alloc>& y)
	{
		x.swap(y);
	}

	template <class T, class alloc>
	bool operator== (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs)
	{
		return (ft::equal<
			typename vector<T, alloc>::const_iterator,
			typename vector<T, alloc>::const_iterator >(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class alloc>
	bool operator!= (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class alloc>
	bool operator< (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class alloc>
	bool operator<= (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class alloc>
	bool operator> (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class alloc>
	bool operator>= (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs)
	{
		return !(lhs < rhs);
	}
	
}