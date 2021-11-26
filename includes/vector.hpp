/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:01:48 by wperu             #+#    #+#             */
/*   Updated: 2021/11/26 16:25:36 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <typeinfo>
#include "utils.hpp"
#include "iterator_traits.hpp"
#include "iterator_reverse.hpp"

namespace ft
{
    template <class T, class alloc = std::allocator <T> >
    class vector
    {
        public:
		typedef T                                                       value_type;
        typedef alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef std::ptrdiff_t 											difference_type;
        typedef typename allocator_type::size_type                     	size_type;


		class iterator
			{
				public:
					typedef ptrdiff_t							difference_type;
					typedef T									value_type;
					typedef value_type*							pointer;
					typedef value_type&							reference;
					typedef ft::random_access_iterator_tag		iterator_category;

				protected:
					value_type 		*_value;
					
				public:
					iterator()
					{
						this->_value = nullptr;
					}
					iterator(value_type* value)
					{
						this->_value = value;
					}
					iterator(const iterator& src)
					{
						this->_value = src._value;
					}
					~iterator()
					{}

					iterator							&operator=(const iterator &rhs)
					{
						if ( this != &rhs)
						{
							this->_value = rhs._value;
						}
						return *this;
					}

					reference							operator*(void) const
					{
						return *(this->_value);
					}

					pointer								operator->(void) const
					{
						return (this->value);
					}
					
					iterator::difference_type			operator+(const iterator & rhs)
					{
						return (this->_value + rhs._value);
					}
					
					iterator::difference_type			operator-(const iterator & rhs)
					{
						return (this->_value - rhs._value);
					}
					
					iterator							operator+(difference_type n)
					{
						return iterator(this->_value + n);
					}
					
					iterator							operator-(difference_type n)
					{
						return iterator(this->_value - n);
					}
					
					iterator							&operator+=(difference_type n)
					{
						this->_value += n;
						return *this;
					}

					iterator							&operator-=(difference_type n)
					{
						this->_value -= n;
						return *this;
					}

					bool								operator!=(const iterator &rhs) const {
						return (this->_value != rhs._value);
					}

					bool								operator==(const iterator &rhs) const {
						return (this->_value == rhs._value);
					}
					
					iterator			&operator++(void)
					{
						
						++this->_value;
						return *this;
					}

					iterator			operator++(int)
					{
						iterator cpy(*this);
						++this->_value;
						return cpy;
					}

					iterator			&operator--(void)
					{
						--this->_value;
						return *this;
					}

					iterator			operator--(int)
					{
						iterator cpy(*this);
						--this->_value;
						return cpy;
					}
					bool				operator<(const iterator& rhs)
					{
						return (this->_value < rhs._value);
					}
					
					bool				operator>(const iterator& rhs)
					{
						return (this->_value > rhs._value);
					}
					
					bool				operator<=(const iterator& rhs)
					{
						return (this->_value <= rhs._value);
					}
					
					bool				operator>=(const iterator& rhs)
					{
						return (this->_value >= rhs._value);
					}

			};

			class const_iterator
			{
				public:
					typedef const T			value_type;
					typedef value_type&		reference;
					typedef value_type*		pointer;
					typedef ptrdiff_t		difference_type;
					typedef ft::random_access_iterator_tag		iterator_category;

				protected:
					value_type 		*_value;
					
				public:
					const_iterator()
					{
						this->_value = nullptr;
					}
					const_iterator(value_type* value)
					{
						this->_value = value;
					}
					const_iterator(const const_iterator& src)
					{
						this->_value = src._value;
					}
					~const_iterator()
					{}

					const_iterator							&operator=(const const_iterator &rhs)
					{
						if ( this != &rhs)
						{
							this->_value = rhs._value;
						}
						return *this;
					}

					reference								operator*(void) const
					{
						return *(this->_value);
					}

					pointer									operator->(void) const
					{
						return (this->value);
					}
					
					const_iterator::difference_type			operator+(const const_iterator & rhs)
					{
						return (this->_value + rhs._value);
					}
					
					const_iterator::difference_type			operator-(const const_iterator & rhs)
					{
						return (this->_value - rhs._value);
					}
					
					const_iterator							operator+(difference_type n)
					{
						return const_iterator(this->_value + n);
					}
					
					const_iterator							operator-(difference_type n)
					{
						return const_iterator(this->_value - n);
					}
					
					const_iterator							&operator+=(difference_type n)
					{
						this->_value += n;
						return *this;
					}

					const_iterator							&operator-=(difference_type n)
					{
						this->_value -= n;
						return *this;
					}

					bool									operator!=(const const_iterator &rhs) const {
						return (this->_value != rhs._value);
					}
					
					bool									operator==(const const_iterator &rhs) const {
						return (this->_value == rhs._value);
					}
					const_iterator							&operator++(void)
					{
						++this->_value;
						return *this;
					}

					const_iterator							operator++(int)
					{
						const_iterator cpy(*this);
						++this->_value;
						return cpy;
					}

					const_iterator							&operator--(void)
					{
						--this->_value;
						return *this;
					}

					const_iterator							operator--(int)
					{
						const_iterator cpy(*this);
						--this->_value;
						return cpy;
					}

					bool									operator<(const const_iterator& rhs)
					{
						return (this->_value < rhs._value);
					}
					
					bool									operator>(const const_iterator& rhs)
					{
						return (this->_value > rhs._value);
					}
					
					bool									operator<=(const const_iterator& rhs)
					{
						return (this->_value <= rhs._value);
					}
					
					bool									operator>=(const const_iterator& rhs)
					{
						return (this->_value >= rhs._value);
					}

			};
		
		typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>     		const_reverse_iterator;
		
		//constructor
		
		vector(const allocator_type& allocator = allocator_type());
		

        vector(size_type n, const value_type& val = value_type(), const allocator_type &allo = allocator_type());
        
        /*template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type);
        */
        vector (const vector& src);
        ~vector();
		vector& operator= (const vector& x);

		//Iterators

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;
		
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;
		
		//Capacity

		size_type size() const;
		size_type max_size() const;
		void resize (size_type n, value_type val = value_type());
		size_type capacity(void) const;
		bool empty() const;
		void reserve (size_type n);

		//Element access
		
		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;

		reference at (size_type n);
		const_reference at (size_type n) const;

		reference front();
		const_reference front() const;
		
		reference back();
		const_reference back() const;

		//Modifiers

		template <class InputIterator>
  		void assign (typename ft::enable_if< is_iterator<InputIterator>::value, InputIterator>::type first,
					InputIterator last);
		void assign (size_type n, const value_type& val);
		void push_back (const value_type& val);
		void pop_back();
		
		iterator insert (iterator position, const value_type& val);
    	void insert (iterator position, size_type n, const value_type& val);
		/*template <class InputIterator>
   		 void insert (iterator position, InputIterator first, InputIterator last);*/

		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);
		void swap (vector& x);
		void clear();

		//Allocator
		allocator_type get_allocator() const;

		
        private:
            value_type *data;
            size_type  _capacity;
            size_type  _size;
            allocator_type _alloc;

			void init_data(size_type n, const value_type val);
			void destroy_data();

    };

	//No-member
	template <class T, class alloc>
  	void swap (vector<T,alloc>& x, vector<T,alloc>& y);

	

	template <class T, class alloc>
		bool operator== (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs);

	template <class T, class alloc>
		bool operator!= (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs);

	template <class T, class alloc>
		bool operator<  (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs);

	template <class T, class alloc>
		bool operator<= (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs);

	template <class T, class alloc>
		bool operator>  (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs);

	template <class T, class alloc>
		bool operator>= (const vector<T,alloc>& lhs, const vector<T,alloc>& rhs);
}

