/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:01:48 by wperu             #+#    #+#             */
/*   Updated: 2021/11/23 20:37:16 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <typeinfo>
#include <utils.hpp>
#include "iterator_traits.hpp"
#include "iterator_reverse.hpp"

namespace ft
{
    template <class T, class alloc = std::allocator <T> >
    class vector
    {
        typedef T                                                       value_type;
        typedef alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef typename allocator_type::size_type                     	size_type;


		class iterator
		{
			protected:
				iterator current;
			
			typedef ft::iterator_traits<iterator> trait_type;
			
			public:
				typedef iterator								iterator_type;
				typedef typename ft::random_access_iterator_tag	iterator_category;
				typedef typename trait_type::value_type			value_type;
				typedef typename trait_type::difference_type	difference_type;
				typedef typename trait_type::reference			reference;
				typedef typename trait_type::pointer			pointer;
			
			iterator() : current(){};
			explicit iterator(iterator_type it) : current(it) {};
			iterator(const iterator<iterator>& it): current(it.current){}
			
			iterator base() const
			{ return current; }

			//operator

			reference operator*() const
			{ return *current; }

			pointer operator->() const
			{ return current; }

			iterator &operator++() 
			{
				++current;
				return *this;
			}

			iterator operator++() 
			{
				return iterator(current++);
			}

			iterator &operator--() 
			{
				--current;
				return *this;
			}

			iterator operator--()
			{
				return iterator(current--);
			}

			iterator operator[](difference_type n) const
			{
				return current[n];
			}
			
			iterator operator+=(difference_type n)
			{
				current += n;
				return this;
			}

			iterator operator+(difference_type n) const
			{
				return iterator(current + n);
			}

			iterator operator-=(difference_type n)
			{
				current -= n;
				return this;
			}

			iterator operator-(difference_type n) const
			{
				return iterator(current - n);
			}
			
			bool operator==(const iterator& lhs, const iterator& rhs )
			{
				return(lhs.base()==rhs.base());
			}
			
			bool operator!=(const iterator& lhs, const iterator& rhs )
			{
				return(lhs.base()!=rhs.base());
			}

			bool operator<(const iterator& lhs, const iterator& rhs )
			{
				return(lhs.base()<rhs.base());
			}
			bool operator<=(const iterator& lhs, const iterator& rhs )
			{
				return(lhs.base()<=rhs.base());
			}

			bool operator>(const iterator& lhs, const iterator& rhs )
			{
				return(lhs.base()>rhs.base());
			}
			
			bool operator>=(const iterator& lhs, const iterator& rhs )
			{
				return(lhs.base()>=rhs.base());
			}
		};
		
		class const_iterator
		{
			protected:
				const iterator current;
			
			typedef ft::iterator_traits<iterator> trait_type;
			
			public:
				typedef const iterator								iterator_type;
				typedef typename ft::random_access_iterator_tag	iterator_category;
				typedef typename trait_type::value_type			value_type;
				typedef typename trait_type::difference_type	difference_type;
				typedef typename trait_type::reference			reference;
				typedef typename trait_type::pointer			pointer;
			
			const_iterator() : current(){};
			explicit const_iterator(iterator_type it) : current(it) {};
			const_iterator(const const_iterator& it): current(it.current){}
			const_iterator() {}
			
			const_iterator base() const
			{ return current; }

			//operator

			reference operator*() const
			{ return *current; }

			pointer operator->() const
			{ return current; }

			const_iterator &operator++() 
			{
				++current;
				return *this;
			}

			const_iterator operator++() 
			{
				return const_iterator(current++);
			}

			const_iterator &operator--() 
			{
				--current;
				return *this;
			}

			const_iterator operator--()
			{
				return const_iterator(current--);
			}

			const_iterator operator[](difference_type n) const
			{
				return current[n];
			}
			
			const_iterator operator+=(difference_type n)
			{
				current += n;
				return this;
			}

			const_iterator operator+(difference_type n) const
			{
				return const_iterator(current + n);
			}

			const_iterator operator-=(difference_type n)
			{
				current -= n;
				return this;
			}

			const_iterator operator-(difference_type n) const
			{
				return const_iterator(current - n);
			}
			
			bool operator==(const const_iterator& lhs, const const_iterator& rhs )
			{
				return(lhs.base()==rhs.base());
			}
			
			bool operator!=(const const_iterator& lhs, const const_iterator& rhs )
			{
				return(lhs.base()!=rhs.base());
			}

			bool operator<(const const_iterator& lhs, const const_iterator& rhs )
			{
				return(lhs.base()<rhs.base());
			}
			bool operator<=(const const_iterator& lhs, const const_iterator& rhs )
			{
				return(lhs.base()<=rhs.base());
			}

			bool operator>(const const_iterator& lhs, const const_iterator& rhs )
			{
				return(lhs.base()>rhs.base());
			}
			
			bool operator>=(const const_iterator& lhs, const const_iterator& rhs )
			{
				return(lhs.base()>=rhs.base());
			}
		};
		
		typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>     		const_reverse_iterator;
		
		//constructor
		
		explicit vector(const allocator_type& alloc = allocator_type());
        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type &alloc = allocateur_type());
        
        template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type);
        
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
		template <class InputIterator>
   		 void insert (iterator position, InputIterator first, InputIterator last);

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

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

	

	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
}

