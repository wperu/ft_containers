/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_fct.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:38:04 by wperu             #+#    #+#             */
/*   Updated: 2021/12/14 17:02:09 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
	//****CONSTRUCTOR****
	
    template< typename T, typename alloc>
    vector<T,alloc>::vector(const allocator_type& allocator) : data(NULL),_capacity(0),_size(0), _alloc(allocator)
    {}
    
    template< typename T, typename alloc>
    vector<T,alloc>::vector(size_type n, const value_type& val , const allocator_type& allocator) : data(NULL),_capacity(n),_size(n),_alloc(allocator)
    {
        this->init_data(n,val);
    }
	
	template< typename T, typename alloc>
	template <class InputIterator>
    vector<T,alloc>::vector(InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& allocator):_alloc(allocator)
	{
		size_t	i;

		_size = last - first;
		_capacity = 2 * _size;
		data = allocator_type(_alloc).allocate(_capacity, 0);
		i = 0;
		while (i < _size)
			data[i++] = *(first++);
	}

	template< typename T, typename alloc>
    vector<T,alloc>::vector(const vector& src): _capacity(src._capacity),_size(src._size), _alloc(allocator_type(src._alloc))
	{
		size_type	i;

		i = 0;
		data = _alloc.allocate(_capacity);
		while (i < _size)
		{
			data[i] = src.data[i];
			i++;
		}
	}
	
    
    template< typename T, typename alloc>
    vector<T,alloc>& vector<T,alloc>::operator=(const vector& x)
    {
        this->data = this->_alloc.allocate(x._capacity);
		this->_capacity = x._capacity;
        this->assign(x.begin(),x.end());
        return *this;
    }
	
	//****DESTRUCTOR****

    template<typename T,typename alloc>
    vector<T,alloc>::~vector()
    {
        this->destroy_data();
        this->_alloc.deallocate(this->data,this->_capacity);

    }
	
	//***ITERATOR***

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


    //****CAPACITY****

    template<typename T, typename alloc>
    typename vector<T,alloc>::size_type vector<T,alloc>::size(void) const
    {
        return this->_size;
    }
    
    template<typename T, typename alloc>
    typename vector<T,alloc>::size_type vector<T,alloc>::max_size() const
    {
        return (std::numeric_limits<difference_type>::max() / sizeof(value_type));
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

	//****ELEMENT_ACCESS****

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
		return(this->data[n]);	
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

	//****MODIFIERS****

	template<typename T,typename alloc>
	template<class InputIterator>
	void  vector<T,alloc>::assign (InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
	{
        size_type	i;
	
		i = 0;
		while (i < _size)
			data[i++].~value_type();
		_size = last - first;
		if (_size > _capacity)
		{
			_alloc.deallocate(data, _capacity);
			_capacity = _size * 2;
			data = _alloc.allocate(_capacity);
		}
		i = 0;
		while (first != last)
		{
			data[i++] = *first;
			first++;
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
            this->_alloc.construct(&this->data[i],val);
            ++i;
        }
    }
    
    template <typename T, typename alloc>
    void vector<T,alloc>::push_back(const value_type& val)
    {
        value_type	*new_data;
		size_type	i;

		if (_size == _capacity)
		{
			_capacity = (_size + 1) * 2;
			new_data = _alloc.allocate(_capacity);
			i = 0;
			while (i < _size)
			{
				new_data[i] = data[i];
				i++;
			}
			_alloc.deallocate(data, _size);
			data = new_data;
		}
		value_type *tmp = data + _size;
		tmp = new (tmp) value_type(val);
		_size++;
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
        value_type	*new_data;
		iterator	it;
		iterator	it_end;
		size_type	i;
		size_type	location;

		if (_size == _capacity)
		{
			_capacity = (_size + 1) * 2;
			new_data = _alloc.allocate(_capacity);
			i = 0;
			it = begin();
			it_end = end();
			while (it != position)
				new_data[i++] = *(it++);
			location = i;
			new_data[i++] = val;
			while (it != it_end)
				new_data[i++] = *(it++);
			_alloc.deallocate(data, _size);
			data = new_data;
		}
		else
		{
			it = end();
			while (it != position)
			{
				*it = *(it - 1);
				it--;
			}
			location = position - begin();
			*it = val;
		}
		_size++;
		return (iterator(data + location));
    }
    
	template <typename T, typename alloc>
	void vector<T, alloc>::insert(iterator position, size_type n, const value_type& val)
	{
		value_type	*new_data;
		iterator	it;
		iterator	it_end;
		size_type	i;
		size_type	new_capacity;

		if (_capacity < _size + n)
		{
			_size += n;
			new_capacity = _size * 2;
			new_data = _alloc.allocate(new_capacity);
			i = 0;
			it = begin();
			it_end = end();
			while (it != position)
				new_data[i++] = *(it++);
			n += i;
			while (i < n)
				new_data[i++] = val;
			new_data[i++] = val;
			while (it != it_end)
				new_data[i++] = *(it++);
			_alloc.deallocate(data, _capacity);
			_capacity = new_capacity;
			data = new_data;
		}
		else
		{
			_size += n;
			it = end() + (n - 1);
			while (it != position + (n - 1))
			{
				*it = *(it - n);
				it--;
			}
			while (it != position - 1)
				*(it--) = val;
		}
	}
	template <typename T, typename alloc>
	template <class InputIterator>
	void vector<T,alloc>::insert (iterator position, InputIterator first,typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
	{
		value_type *new_data;
		size_type insert_size;
		iterator  data_it;
		iterator data_end;
		size_type i;
		insert_size = last - first;
		if(_capacity <_size + insert_size)
		{
			_capacity =(_size + insert_size) * 2;
			new_data = _alloc.allocate(_capacity);
			data_it = begin();
			i  = 0;
			while(data_it != position)
				new_data[i++] = *(data_it++);
			while(first != last)
				new_data[i++] = *(first++);
			data_end = end();
			while(data_it < data_end)
				new_data[i++] = *(data_it++);
			_alloc.deallocate(data,_size);
			data = new_data;
		}
		else
		{
			data_it = end() +(insert_size - 1);
			while(data_it != position + (insert_size - 1))
			{
				*data_it = *(data_it - insert_size);
				data_it--;
			}
			while(last != first)
				*(data_it--) = *(--last);
		}
		_size += insert_size; 
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
		this->destroy_data();
		this->_size = 0;
	}

	//****ALLOCATOR****

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


	//****NON-MEMBER***

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