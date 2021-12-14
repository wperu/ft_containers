/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:09:04 by wperu             #+#    #+#             */
/*   Updated: 2021/12/14 17:07:13 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <limits>
#include <typeinfo>
#include "utils.hpp"
#include "iterator_traits.hpp"
#include "iterator_reverse.hpp"
#include "iterator.hpp"
#include <functional>


namespace ft
{
    template< class Key, class T,class Compare = std::less<Key>
	 ,class alloc = std::allocator<pair<const Key, T> > >
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
		
		class value_compare;
		struct bst;
		class iterator;
		class const_iterator;
		typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>     		const_reverse_iterator;
		
		//CONSTRUCTOR

		explicit map (const key_compare& comp = key_compare(),const allocator_type& Alloc = allocator_type());
		template <class InputIterator>
  		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
       	const allocator_type& Alloc = allocator_type());

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

		pair<iterator,bool> insert (const value_type& val)
		{
			bst	*tmp;

			tmp = bst_look(val.first, data);
			if (tmp)
				return (make_pair(iterator(&data, tmp), false));
			data = bst_insert(val, data);
		return (make_pair(iterator(&data, bst_look(val.first,data)), true));
	}
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

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
        return (make_pair(lower_bound(k),upper_bound(k)));
    	}
		pair<iterator,iterator>             equal_range (const key_type& k)
		{
        	return (make_pair(lower_bound(k),upper_bound(k)));
    	}
		//ALLOCATOR

		allocator_type get_allocator() const;
		
		private:
		typedef typename allocator_type::template rebind<bst>::other node_allocator;
		key_compare _comp;
		bst *data;
		allocator_type _alloc;
		//BST member
		size_type bst_size_key(bst *curr, const key_type& k) const
		{
			if(!curr)
				return(0);
			return(bst_size_key(curr->left, k) + bst_size_key(curr->right, k) + (curr->value->first == k));
		}

		bst *bst_deep_copy(bst const *src)
		{
			bst *curr;
			
			curr = node_allocator(_alloc).allocate(1);
			curr = new (curr) bst(NULL,NULL,NULL,NULL);
			curr->value = _alloc.allocate(1);
			curr->value = new (curr->value) value_type(*(src->value));
			if(src->left)
			{
				curr->left = bst_deep_copy(src->left);
				curr->left->parent = curr;
			}
			if(src->right)
			{
				curr->right = bst_deep_copy(src->right);
				curr->right->parent = curr;
			}
			return(curr);
		}
		
		bst *bst_look(const key_type &key, bst *curr) const
		{
			if(!curr)
				return(NULL);
			if(curr->value->first == key)
				return(curr);
			if(_comp(key,curr->value->first))
				return(bst_look(key,curr->left));
			return (bst_look(key, curr->right));
		}
		
		bst *bst_insert_get_parent(value_type data, bst *curr)
		{
			if(!curr)
				return(NULL);
			if(_comp(data.first, curr->value->first))
			{
				if(curr->left)
					return(bst_insert_get_parent(data, curr->left));
				return(curr);
			}
			if(curr->right)
				return(bst_insert_get_parent(data,curr->right));
			return(curr);
		}
		
		bst *bst_insert(value_type new_data, bst *root)
		{
			bst *new_bst;

			new_bst = node_allocator(_alloc).allocate(1);
			new_bst = new (new_bst)
			bst(bst_insert_get_parent(new_data, root), NULL, NULL, NULL);
			new_bst->value = _alloc.allocate(1);
			new_bst->value = new (new_bst->value) value_type(new_data);
			if (!new_bst->parent)
				return (new_bst);
			if (_comp(new_data.first, new_bst->parent->value->first))
				new_bst->parent->left = new_bst;
			else
				new_bst->parent->right = new_bst;
			return (root);
		}
		bst *bst_high_parent(bst* root)
		{
			if(!root->parent)
				return(root);
			return(bst_high_parent(root->parent));
		}
		bst *bst_remove_zero_child(bst *to_remove)
		{
			bst *new_bst = bst_high_parent(to_remove);
			if(new_bst == to_remove)
				new_bst = NULL;
			if(to_remove->parent && to_remove->parent->left == to_remove)
				to_remove->parent->left = NULL;
			else if(to_remove->parent && to_remove->parent->right == to_remove)
					to_remove->parent->right = NULL;
			_alloc.deallocate(to_remove->value, 1);
			node_allocator(_alloc).deallocate(to_remove, 1);
			return(new_bst);
		}
		bst *bst_remove_one_child(bst *to_remove)
		{
			bst *child;

			child = to_remove->left != NULL ? to_remove->left : to_remove->right;
			if (to_remove->parent)
			{
				if(to_remove->parent->left == to_remove)
					to_remove->parent->left = child;
				else if(to_remove->parent->right == to_remove)
					to_remove->parent->right = child;
			}
			child->parent = to_remove->parent;
			_alloc.deallocate(to_remove->value, 1);
			node_allocator(_alloc).deallocate(to_remove, 1);
			return(bst_high_parent(child));
		}
		
		bst *bst_remove_two_children(bst *to_remove)
		{
			bst *child;

			child = to_remove->right;
			while(child->left)
			{
				child = child->left;
			}
			_alloc.deallocate(to_remove->value,1);
			to_remove->value = _alloc.allocate(1);
			to_remove->value = new (to_remove->value) value_type(*(child->value));
			if(child->left || child->right)
				bst_remove_one_child(child);
			else
				bst_remove_zero_child(child);
			return(bst_high_parent(to_remove));
		}
		
		bst *bst_remove(const key_type &key, bst *root)
		{
			bst		*to_remove;

			if (!(to_remove = bst_look(key, root)))
				return (root);
			if (to_remove->left && to_remove->right)
				return (bst_remove_two_children(to_remove));
			else if ((to_remove->left != NULL) != (to_remove->right != NULL))
				return (bst_remove_one_child(to_remove));
			else
				return (bst_remove_zero_child(to_remove));
		}
		size_type bst_size(bst *root) const
		{
			if(!root)
				return(0);
			return(bst_size(root->left) + bst_size(root->right) + 1);
		}
		
		void bst_clear(bst *root)
		{
			
			if(root)
			{
				bst_clear(root->left);
				bst_clear(root->right);
				_alloc.deallocate(root->value, 1);
				node_allocator(_alloc).deallocate(root,1);
			}
		
		}
		bst *get_min(bst* tree) const
		{
			if(!tree)
				return(NULL);
			if(tree->left)
				return(get_min(tree->left));
			return(tree);
		}
	
	};

	template <class Key, class T, class Compare, class alloc>
	struct map<Key,T,Compare,alloc>::bst
	{
		
		
		bst* parent;
		bst* left;
		bst* right;

		value_type *value;
		bst(bst *n_parent, bst *n_left, bst *n_right, value_type *n_value)
		: parent(n_parent), left(n_left),right(n_right), value(n_value) {}
	};

	template <class Key, class T, class Compare, class alloc>
	class map<Key,T,Compare,alloc>::value_compare
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
	};



	//iterator

	template <class Key, class T, class Compare, class Alloc>
	class	ft::map<Key, T, Compare, Alloc>::iterator : public ft::base_iterator<bidirectional_iterator_tag, ft::pair<const Key, T> >
	{
		public :

		iterator(void) {}
		iterator(bst **root, bst *start) : _root(root), _current(start) {}
		iterator(iterator const &src) : _root(src._root), _current(src._current) {}
		virtual	~iterator(void) {}

		iterator	&operator=(iterator const &src)
		{
			_current = src._current;
			_root = src._root;
			return (*this);
		}
		bool		operator==(iterator const &src) const
		{
			return (_current == src._current);
		}
		bool		operator!=(iterator const &src) const
		{
			return (_current != src._current);
		}
		value_type			&operator*(void)
		{
			return (*(_current->value));
		}
		value_type const	&operator*(void) const
		{
			return (*(_current->value));
		}
		value_type			*operator->(void)
		{
			return (_current->value);
		}
		value_type const		*operator->() const
		{
			return (_current->data);
		}
		iterator	&operator++() //prefix
		{
			_current = _get_next_bst(_current);
			return (*this);
		}
		iterator	operator++(int) //postfix
		{
			iterator	copy(*this);

			_current = _get_next_bst(_current);
			return (copy);
		}
		iterator	&operator--() //prefix
		{
			if (!_current)
				_current = _get_max(*_root);
			else
				_current = _get_previous_bst(_current);
			return (*this);
		}
		iterator	operator--(int) //postfix
		{
			iterator	copy(*this);

			if (!_current)
				_current = _get_max(*_root);
			else
				_current = _get_previous_bst(_current);
			return (copy);
		}
		operator	const_iterator() const
		{
			return (const_iterator(_root, _current));
		}

		private :

		bst **_root;
		bst *_current;

	// private functions
		
		bst	*_get_next_bigger_parent(bst *origin)
		{
			if (!origin->parent)
				return (NULL);
			else if (key_compare()(origin->value->first, origin->parent->value->first))
				return (origin->parent);
			else
				return (_get_next_bigger_parent(origin->parent));
		}
		bst	*_get_next_bst(bst *src)
		{
			if (src->right)
				return (_get_min(src->right));
			else
				return (_get_next_bigger_parent(src));
		}
		bst	*_get_min(bst *tree)
		{
			if (tree->left)
				return (_get_min(tree->left));
			return (tree);
		}
		bst	*_get_next_smaller_parent(bst *origin)
		{
			if (!origin->parent)
				return (NULL);
			else if (key_compare()(origin->parent->value->first, origin->value->first))
				return (origin->parent);
			else
				return (_get_next_smaller_parent(origin->parent));
		}
		bst	*_get_previous_bst(bst *src)
		{
			if (src->left)
				return (_get_max(src->left));
			else
				return (_get_next_smaller_parent(src));
		}
		bst	*_get_max(bst *tree) const
		{
			if (tree->right)
				return (_get_max(tree->right));
			return (tree);
		}
	};

	// const_iterator

	template <class Key, class T, class Compare, class Alloc>
	class	ft::map<Key, T, Compare, Alloc>::const_iterator : public ft::base_iterator<bidirectional_iterator_tag, ft::pair<const Key, T> >
	{

		public :

		const_iterator(void) {}
		const_iterator(bst * const *root, bst *start) : _root(root), _current(start) {}
		const_iterator(const_iterator const &src) : _root(src._root), _current(src._current) {}
		virtual	~const_iterator(void) {}

		const_iterator		&operator=(const_iterator const &src)
		{
			_current = src._current;
			_root = src._root;
			return (*this);
		}
		bool				operator==(const_iterator const &src) const
		{
			return (_current == src._current);
		}
		bool				operator!=(const_iterator const &src) const
		{
			return (_current != src._current);
		}
		value_type const	&operator*(void) const
		{
			return (*(_current->data));
		}
		value_type const	*operator->() const
		{
			return (_current->data);
		}
		const_iterator		&operator++() //prefix
		{
			_current = _get_next_bst(_current);
			return (*this);
		}
		const_iterator		operator++(int) //postfix
		{
			const_iterator	copy(*this);

			_current = _get_next_bst(_current);
			return (copy);
		}
		const_iterator		&operator--() //prefix
		{
			if (!_current)
				_current = _get_max(*_root);
			else
				_current = _get_previous_bst(_current);
			return (*this);
		}
		const_iterator		operator--(int) //postfix
		{
			const_iterator	copy(*this);

			if (!_current)
				_current = _get_max(*_root);
			else
				_current = _get_previous_bst(_current);
			return (copy);
		}

		private :

		bst * const *_root;
		bst const *_current;

	// private functions
		
		bst const	*_get_next_bigger_parent(bst const *origin) const
		{
			if (!origin->parent)
				return (NULL);
			else if (key_compare()(origin->data->first, origin->parent->data->first))
				return (origin->parent);
			else
				return (_get_next_bigger_parent(origin->parent));
		}
		bst const	*_get_next_bst(bst const *src) const
		{
			if (src->right)
				return (_get_min(src->right));
			else
				return (_get_next_bigger_parent(src));
		}
		bst const	*_get_min(bst const *tree) const
		{
			if (tree->left)
				return (_get_min(tree->left));
			return (tree);
		}
		bst const	*_get_next_smaller_parent(bst const *origin) const
		{
			if (!origin->parent)
				return (NULL);
			else if (key_compare()(origin->parent->data->first, origin->data->first))
				return (origin->parent);
			else
				return (_get_next_smaller_parent(origin->parent));
		}
		bst const	*_get_previous_bst(bst const *src) const
		{
			if (src->left)
				return (_get_max(src->left));
			else
				return (_get_next_smaller_parent(src));
		}
		bst const	*_get_max(bst const *tree) const
		{
			if (tree->right)
				return (_get_max(tree->right));
			return (tree);
		}
	};

	
}