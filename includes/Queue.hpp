/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:50:03 by louise            #+#    #+#             */
/*   Updated: 2021/03/02 10:50:09 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP
# include "List.hpp"

template<class T, class Container = ft::List<T> >
class Queue {
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
    explicit Queue( const Container& cont = Container() ) : _c(cont) {}
    Queue(const Queue& src) { *this = src; }
    Queue& operator=(const Queue& rhs) {
        if (this != &rhs) {
            _c = rhs._c;
        }
        return *this;
    }
    virtual ~Queue() {}


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
    void swap( Queue& other ) { _c->swap(other._c); }

private:
    Container _c;

    /* Non-member functions
     *
     *
     */

    friend bool operator==( const Queue<T,Container>& lhs,
        const Queue<T,Container>& rhs ) {
        return lhs._c == rhs._c;
    }
    friend bool operator!=( const Queue<T,Container>& lhs,
                            const Queue<T,Container>& rhs ) {
        return lhs._c != rhs._c;
    }
    friend bool operator<( const Queue<T,Container>& lhs,
                            const Queue<T,Container>& rhs ) {
        return lhs._c < rhs._c;
    }
    friend bool operator<=( const Queue<T,Container>& lhs,
                            const Queue<T,Container>& rhs ) {
        return lhs._c <= rhs._c;
    }
    friend bool operator>( const Queue<T,Container>& lhs,
                            const Queue<T,Container>& rhs ) {
        return lhs._c > rhs._c;
    }
    friend bool operator>=( const Queue<T,Container>& lhs,
                            const Queue<T,Container>& rhs ) {
        return lhs._c >= rhs._c;
    }
    void swap( Queue<T,Container>& lhs,
               Queue<T,Container>& rhs ) {
        lhs.swap(rhs);
    }
};

#endif
