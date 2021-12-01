/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:09:04 by wperu             #+#    #+#             */
/*   Updated: 2021/12/01 18:44:22 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <limits>
#include <typeinfo>
#include "utils.hpp"
#include "iterator_traits.hpp"
#include "iterator_reverse.hpp"
#include <functional>

namespace ft
{
    template< classe Key, class T,class Compare = std::less<Key>()
	 ,class alloc = std::allocator<pair<const Key, T>>>
     class map
    {
     public:
	    typedef Key											key_type;
		typedef T 											mapped_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef Compare										key_compare;						
		typedef alloc										allocator_type;
		typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
		typedef std::ptrdiff_t 								difference_type;
        typedef typename allocator_type::size_type          size_type;
		
		class value_compare
		class iterator ;
		struct bst;
		class const_iterator;
		typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>     		const_reverse_iterator;
		
		//CONSTRUCTOR

		explicit map (const key_compare& comp = key_compare(),const allocator_type& alloc = allocator_type());
		template <class InputIterator>
  		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
       	const allocator_type& alloc = allocator_type());

		map (const map& x);
		~map();
		map& operator= (const map& x);

		//Iterators

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;
		
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

		//CAPACITY

		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		//ELEMENT ACCESS

		mapped_type& operator[] (const key_type& k);
		
		//MODIFIERS

		pair<iterator,bool> insert (const value_type& val);
		iterator insert (iterator position, const value_type& val);
		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last);
		  
		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);
		
		void swap (map& x);

		void clear();

		//OBSERVERS

		key_compare key_comp() const;
		value_compare value_comp() const;

		//OPERATIONS

		iterator find (const key_type& k);
		const_iterator find (const key_type& k) const;

		size_type count (const key_type& k) const;

		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;

		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		pair<iterator,iterator>             equal_range (const key_type& k);

		//ALLOCATOR

		allocator_type get_allocator() const;
		
	};

	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare
	{   
  		friend class map;
		protected:
  		Compare comp;
  		value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
  			typedef bool result_type;
  			typedef value_type first_argument_type;
  			typedef value_type second_argument_type;
  			bool operator() (const value_type& x, const value_type& y) const
  			{
    			return comp(x.first, y.first);
  			}
	}
	
	struct bst
	{
		typedef bst *base_ptr;
		typedef const *const_base_ptr;
		base_ptr parent;
		base_ptr left;
		base_ptr right;
		
	}
}