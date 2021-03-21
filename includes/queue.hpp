/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:50:03 by louise            #+#    #+#             */
/*   Updated: 2021/03/02 10:50:09 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP
# include "list.hpp"

template<class T, class Container = ft::list<T> >
class queue {
public:

    /* Member types
     *
     *
     */

    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

    /* Member functions
     *
     *
     */
    explicit queue( const Container& cont = Container() ) : _c(cont) {}
    queue(const queue& src) { *this = src; }
    queue& operator=(const queue& rhs) {
        if (this != &rhs) {
            _c = rhs._c;
        }
        return *this;
    }
    virtual ~queue() {}


    /* Member functions : Element access
     *
     *
     *
     */
    reference front() { return _c->front(); }
    const_reference front() const { return _c->front(); }
    reference back() { return _c->back(); }
    const_reference back() const { return _c->back(); }

    /* Member functions : capacity
     *
     *
     */
    bool empty() const { return _c->empty(); }
    size_type size() const { return _c->size(); }

    /* Member functions : modifiers
     *
     *
     */
    void push( const value_type& value ) { _c->push_back(value); }
    void pop() { _c->pop_front(); }
    void swap( queue& other ) { _c->swap(other._c); }

private:
    Container _c;

    /* Non-member functions
     *
     *
     */

    friend bool operator==( const queue<T,Container>& lhs,
        const queue<T,Container>& rhs ) {
        return lhs._c == rhs._c;
    }
    friend bool operator!=( const queue<T,Container>& lhs,
        const queue<T,Container>& rhs ) {
        return lhs._c != rhs._c;
    }
    friend bool operator<( const queue<T,Container>& lhs,
        const queue<T,Container>& rhs ) {
        return lhs._c < rhs._c;
    }
    friend bool operator<=( const queue<T,Container>& lhs,
        const queue<T,Container>& rhs ) {
        return lhs._c <= rhs._c;
    }
    friend bool operator>( const queue<T,Container>& lhs,
        const queue<T,Container>& rhs ) {
        return lhs._c > rhs._c;
    }
    friend bool operator>=( const queue<T,Container>& lhs,
        const queue<T,Container>& rhs ) {
        return lhs._c >= rhs._c;
    }
    void swap( queue<T,Container>& lhs,
               queue<T,Container>& rhs ) {
        lhs.swap(rhs);
    }
};

#endif
