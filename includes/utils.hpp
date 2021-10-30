/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:53:04 by wperu             #+#    #+#             */
/*   Updated: 2021/10/30 15:08:15 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <cstddef>
#incldue <iostream>

namespace ft
{
    template<bool Cond, class T = void> 
    struct enable_if {};
    
    template<class T> 
    struct enable_if<true, T> { typedef T type; };

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1<*first2) 
                return true;
            ++first1;
            ++first2;
        }
    return (first2!=last2);
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2,
                                    Compare comp)
    {
        while(first1 != last1)
        {
            if(comp(*first1,*first2))
                return true;
            if(comp(*first2, first1))
                return false;
            ++first1;
            ++first2;  
        }
        return (first2 != last2);
    }

    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair():first(),second(){};
        pair (const first_type& a, const second_type& b):first(a),second(b){} ;
        template<class U, class V>
        pair (const pair<U,V>& ptr):first(ptr.first),second(ptr.second){};
        
        pair& operator=(const pair& rhs)
        {
            if(*this != rhs)
            {
                this->first = rhs.first;
                this->second = rhs.second;
            }
            return *this;
        }
        
    };
    
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first && lhs.second==rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }
    
    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return ( pair<T1,T2>(x,y) );
    }


    template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
    while (first1!=last1) 
    {
        if (!(*first1 == *first2))
           return false;
        ++first1; ++first2;
    }
        return true;
    }
    
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, BinaryPredicate pred)
    {
        while (first1!=last1)
        {
            if (!pred(*first1,*first2))  
                return false;
            ++first1; ++first2;
        }
        return true;
    }
    
}