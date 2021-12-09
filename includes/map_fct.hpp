/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fct.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:12:07 by wperu             #+#    #+#             */
/*   Updated: 2021/12/09 20:56:44 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map.hpp"

namespace ft
{
    //****CONSTRUCTOR
    
    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::map(const key_compare& comp,const allocator_type& Alloc):_comp(comp),_alloc(Alloc),data(NULL)
    {}
    
    template <class Key, class T, class Compare, class alloc>
    template <class InputIterator>
    map<Key,T,Compare,alloc>::map(InputIterator first, InputIterator last, const key_compare& comp,const allocator_type& Alloc)
    :_comp(comp),_alloc(Alloc),data(NULL)
    {
        while(first_it != last_it)
        {
            if(!bst_look((*first_it).first,_root))
                _root = bst_insert(*first_it,root);
            first_i++;
        }
        
    }

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::map(const map& x) : _comp(x._comp), alloc(x._alloc)
    {
        _root = bst_deep_copy(x.data);
    }
    
    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>& map<Key,T,Compare,alloc>::operator=(const map& x)
    {
        bst_clear(data);
        data = bst_deep_copy(x.root);
        return(*this);
    }

    //****DESTUCTOR****

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::~map()
    {
        bst_clear(data);
    }

    //****ITERATOR****
    
    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::iterator map<Key,T,Compare,alloc>::begin()
    {
        return(iterator(&data,get_min(data)));
    }

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::const_iterator map<Key,T,Compare,alloc>::begin() const
    {
        return(const_iterator(&data,get_min(data)));
    }

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::iterator map<Key,T,Compare,alloc>::end()
    {
        return(iterator(&data,NULL));
    }

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::const_iterator map<Key,T,Compare,alloc>::end() const
    {
        return(const_iterator(&data,NULL));
    }

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::reverse_iterator map<Key,T,Compare,alloc>::rbegin()
    {
      return reverse_iterator(end());
    }

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::const_reverse_iterator map<Key,T,Compare,alloc>::rbegin() const
    {
      return const_reverse_iterator(end());
    }

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::reverse_iterator map<Key,T,Compare,alloc>::rend()
    {
      return reverse_iterator(begin());
    }

    template <class Key, class T, class Compare, class alloc>
    map<Key,T,Compare,alloc>::const_reverse_iterator map<Key,T,Compare,alloc>::rend() const
    {
      return const_reverse_iterator(begin());
    }
    
    //****CAPACITY
    template <class Key, class T, class Compare, class alloc>
    bool map<Key,T,Compare,alloc>::empty() const
    {
        return(data == NULL);
    }
    
    template <class Key, class T, class Compare, class alloc>
    typename map<Key,T,Compare,alloc>::size_type map<Key,T,Compare,alloc>::size() const
    {
        return(bst_size(data));
    }

    template <class Key, class T, class Compare, class alloc>
    typename map<Key,T,Compare,alloc>::size_type map<Key,T,Compare,alloc>::max_size() const
    {
        return(std::numeric_limits<size_type>::max()/sizeof(bst));
    }

    //****ELEMENT ACCESS****
    template <class Key, class T, class Compare, class alloc>
    typename map<Key,T,Compare,alloc>::mapped_type& map<Key,T,Compare,alloc>::operator[](const key_type& k)
    {
        *bst *current;
        current = bst_look(k, data);
        if(!current)
        {
            data = bst_insert(value_type(k,mapped_type()),data);
            current = bst_look(k, data);
        }
        return(current->value->second);
    }

    //****MODIFIERS****
    template <class Key, class T, class Compare, class alloc>
    typename map<Key,T,Compare,alloc>::iterator map<Key,T,Compare,alloc>::insert(iterator position, const value_type& val)
    {
        bst *tmp;
        (void)position;
        tmp = bst_look(val.first,data);
        if(tmp)
            return(iterator(&data,tmp));
        data = bst_insert(val,data);
        return(iterator(&data, bst_look(val.first,data)));
    }
    
    template <class Key, class T, class Compare, class alloc>
    template <class InputIterator>
    void map<Key,T,Compare,alloc>::insert(InputIterator first, InputIterator last)
    {
        while(first != last)
        {
            if(!bst_look((*first).first, data))
                data = bst_insert(*first, data);
            first++;
        }
    }

    template <class Key, class T, class Compare, class alloc>
    void map<Key,T,Compare,alloc>::erase(iterator position)
    {
        data = bst_remove((*position).first,data);
    }

    template <class Key, class T, class Compare, class alloc>
    typename map<Key,T,Compare,alloc>::size_type map<Key,T,Compare,alloc>::erase(const key_type& k)
    {
        size_type tmp;
        tmp = 0;
        if(bst_look(k,data))
            tmp = 1;
        data = bst_remove(k,data);
        return (tmp);
    }     

    template <class Key, class T, class Compare, class alloc>
    void map<Key,T,Compare,alloc>::erase(iterator first, iterator last)
    {
        iterator first_cpy(first);
        size_type size;
        size_type i;
        key_type  *target;
        typename allocator_type::template rebind<key_type>::other tmp_alloc(_alloc);

        size = 0;
        while(first != last)
        {
            size++;
            first++;
        }
        target = tmp_alloc.allocate(size);
        i = 0;
        while(first_clone != last)
        {
            target[i++] = (*first_clone).first;
            first_clone++;
        }
        i =  0;
        while(_comp(i,size))
            data = bst_remove(target[i++],data);
        tmp_alloc.deallocate(target, i);
    }

        
    template <class Key, class T, class Compare, class alloc>
    void map<Key,T,Compare,alloc>::swap(map& x)
    {
        key_compare comp_tmp = _comp;
        allocator_type alloc_tmp = _alloc;
        bst            *bst_tmp = data;

        _comp = x._comp;
        _alloc = x._alloc;
        data = x.data;

        x._comp = comp_tmp;
        x._alloc = alloc_tmp;
        x.data = bst_tmp; 
    }
    
    template <class Key, class T, class Compare, class alloc>
    void map<Key,T,Compare,alloc>::clear()
    {
        bst_clear(data);
        data = NULL;
    }

    //****OBSERVERS
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::key_compare map<Key,T,Compare,alloc>::key_comp() const
    {
        return(this->comp);
    }

    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::value_compare map<Key,T,Compare,alloc>::value_comp() const
    {
        return(this->comp);
    }

    //****OPERATIONS****

    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::iterator map<Key,T,Compare,alloc>::find(const key_type& k)
    {
        return(iterator(&data, bst_look(k,data)));
    }
    
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::const_iterator map<Key,T,Compare,alloc>::find(const key_type& k) const
    {
        return(const_iterator(&data,bst_look(k,data)));    
    }
    
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::size_type map<Key,T,Compare,alloc>::count(const key_type& k) const
    {
        return(bst_size_key(data,k));
    }

    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::iterator map<Key,T,Compare,alloc>::lower_bound(const key_type& k)
    {
        iterator it = begin();
        iterator itend = end();

        while(it != itend && _comp((*it).first,k))
            i++;
        return (it);
    }
    
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::const_iterator map<Key,T,Compare,alloc>::lower_bound(const key_type& k) const
    {
        const_iterator it = begin();
        const_iterator itend = end();

        while(it != itend && _comp((*it).first,k))
            i++;
        return (it);
    }

    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::iterator map<Key,T,Compare,alloc>::upper_bound(const key_type& k)
    {
        reverse_iterator it = rbegin();
        reverse_iterator itend = rend();

        while(it != itend && _comp((*it).first,k))
            i++;
        return (it.base());
    }
    
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::const_iterator map<Key,T,Compare,alloc>::upper_bound(const key_type& k) const
    {
        const_reverse_iterator it = rbegin();
        const_reverse_iterator itend = rend();

        while(it != itend && _comp((*it).first,k))
            i++;
        return (it.base());
    }
    /*
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::pair<map<Key,T,Compare,alloc>::const_iterator,map<Key,T,Compare,alloc>::const_iterator> map<Key,T,Compare,alloc>::equal_range(const key_type& k) const
    {
        return (make_pair(lower_bound(k),upper_bound(k)));
    }
    
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::pair<map<Key,T,Compare,alloc>::iterator,map<Key,T,Compare,alloc>::iterator> map<Key,T,Compare,alloc>::equal_range(const key_type& k)
    {
        return (make_pair(lower_bound(k),upper_bound(k)));
    }
*/
    //****ALLOCATOR****
    template <class Key, class T, class Compare, class alloc>
	typename map<Key,T,Compare,alloc>::allocator_type map<Key,T,Compare,alloc>::get_allocator() const
	{
		return this->_alloc;
	}
/*
    //****BST MEMBER****
    template <class Key, class T, class Compare, class alloc>
    typename map<Key,T,Compare,alloc>::size_type map<Key,T,Compare,alloc>::bst_size_key(bst *curr, const key_type& k) const
    {
        
    }
    
    */
    
} 
