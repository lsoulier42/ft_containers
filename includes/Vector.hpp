/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:26:37 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/07 14:26:38 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <limits>
# include <memory>
# include <iostream>
# include "enable_if.hpp"
# include <stdexcept>
# include <string>
# include <sstream>
# include "Iterator.hpp"
# define FIRST_ELEMENT 0
# define LAST_ELEMENT(x) x - 1
# define END_PTR(x) x

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class Vector {
	public:
		/* Member types
		 *
		 *
		 *
		 */
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		/* Iterator classes
		 * vector has random access tag
		 *
		 *
		 *
		 */

		 class const_iterator : public iterator<random_access_iterator_tag,
		 	value_type, difference_type, pointer, reference > {
		 public:
		     const_iterator() : _node(NULL) { }
		     const_iterator(pointer node) : _node(node) {}
		     const_iterator(const const_iterator& src) { *this = src; }
		     const_iterator& operator=(const const_iterator& rhs) {
		         if (this != &rhs)
		             _node = rhs._node;
		         return *this;
		     }
		     virtual ~const_iterator() {}

		     value_type operator*() {
		         return *_node;
		     }
		     bool operator==(const const_iterator& rhs) {
		     	return _node == rhs._node;
		     }
		     bool operator!=(const const_iterator& rhs) {
		     	return !(*this == rhs);
		     }
		     const_iterator& operator++() const { return *this; }
			 const_iterator operator++(int) const { return *this; }
			 const_iterator& operator--() const { return *this; }
			 const_iterator operator--(int) const { return *this; }
			 const_iterator& operator+=(int) const { return *this; }
			 const_iterator operator+(int) const { return *this; }
			 const_iterator& operator-=(int) const { return *this; }
			 const_iterator operator-(int) const { return *this; }

			 difference_type operator-(const const_iterator& rhs) {
				 difference_type ret;
				 ret = rhs._node - this->_node;
				 return ret;
			 }

			 reference operator[](int n) {
				 return *(this->_node + n);
			 }
			 bool operator<(const const_iterator& rhs) {
		     	return *_node < rhs;
		     }
			 bool operator>(const const_iterator& rhs) {
				 return *_node > rhs;
			 }
			 bool operator<=(const const_iterator& rhs) {
				 return *_node <= rhs;
			 }
			 bool operator>=(const const_iterator& rhs) {
				 return *_node >= rhs;
			 }

		 private:
		     pointer _node;
		 };

		 class iterator : public const_iterator {
		 	iterator() : const_iterator() {}
		 	iterator(pointer node) : const_iterator(node) {}
		 	iterator(const iterator& src) { *this = src; }
		 	iterator& operator=(const iterator& rhs) {
		 		if (this != &rhs)
		 			this->_node = rhs._node;
		 		return *this;
		 	}
		 	virtual ~iterator() {}

			 iterator& operator++() const {
		 		this->_node += 1;
		 		return *this;
			 }
			 iterator operator++(int) const {
		 		iterator tmp = *this;
		 		this->_node += 1;
		 		return tmp;
			 }
			 iterator& operator--() const {
				 this->_node -= 1;
				 return *this;
			 }
			 iterator operator--(int) const {
				 iterator tmp = *this;
				 this->_node -= 1;
				 return tmp;
			 }
			 iterator& operator+=(int n) const {
				 this->_node += n;
				 return *this;
			 }
			 iterator operator+(int n) const {
		 		 iterator tmp = *this;
		 		 this->_node += n;
		 		 return tmp;
			 }
			 iterator& operator-=(int n) const {
				 this->_node -= n;
				 return *this;
			 }
			 iterator operator-(int n) const {
				 iterator tmp = *this;
				 this->_node -= n;
				 return tmp;
			 }
		 };

		 class const_reverse_iterator;
		 class reverse_iterator;

		 /* Member functions : constructors
		  *
		  *
		  *
		  */
		 Vector() {
            _init_constructor(Allocator());
		 }
		 explicit Vector( const Allocator& alloc ) {
            _init_constructor(alloc, 1);
		 }
		 explicit Vector( size_type count,
			const T& value = T(), const Allocator& alloc = Allocator()) {
             _init_constructor(alloc, count);
             this->assign(count, value);
		 }
		template< class InputIt >
		Vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) {
            _init_constructor(alloc, last - first);
            this->assign(first, last);
		 }
		Vector( const Vector& other ) {
            this->_deep_copy(other);
		 }

		 /* Member functions : destructor
		  *
		  *
		  *
		  *
		  */
		 virtual ~Vector() {
		     this->clear();
             _a.deconstruct(_vla[END_PTR(_size)], 1);
		     _a.desallocate(_vla);
             _capacity = 0;
             _size = 0;
		 }

		 /* Member functions : assignation operator
		  *
		  *
		  *
		  */

        Vector& operator=( const Vector& other ) {
            if (this != &other)
                this->_deep_copy(other);
            return *this;
        }

        /* Member functions : assign()
         * 1) Replaces the contents with count copies of value value
         * 2) Replaces the contents with copies of those in the range [first, last).
         *
         *
         */

        void assign( size_type count, const T& value ) {
            this->clear();
            if (count >= _capacity)
                _realloc(count);
            for (size_type i = 0; i < count; i++)
                _vla[i] = value;
            _size = count;
            _set_end_pointer();
        }
        template< class InputIt >
        void assign( typename enable_if<is_integral<InputIt>::value>::type first, InputIt last ) {
            this->clear();
            int i = 0;
            if (last - first >= _capacity)
                _realloc(last - first);
            for (iterator it = first; it != last; it++)
                _vla[i++] = *it;
            _size = i;
            _set_end_pointer();
        }

        /* Member function : at()
         * Returns a reference to the element at specified location pos, with bounds checking.
         *
         *
         *
         */
        reference at( size_type pos ) {
            if (pos >= this->size()) {
                std::stringstream ss;
                ss << pos;
                throw std::out_of_range(ss.str());
            }
            return _vla[pos];
        }
        const_reference at( size_type pos ) const {
            return const_cast<reference>(this->at(pos));
        }

        /* Member function : operator[]
         * Returns a reference to the element at specified location pos.
         * No bounds checking is performed.
         *
         *
         */
        reference operator[]( size_type pos ) {
            return _vla[pos];
        }
        const_reference operator[]( size_type pos ) const {
            return const_cast<reference>(_vla[pos]);
        }

        /* Member function : front()
         * Returns a reference to the first element in the container.
         *
         *
         *
         */
        reference front() {
            return _vla[FIRST_ELEMENT];
        }
        const_reference front() const {
            return const_cast<reference>(_vla[FIRST_ELEMENT]);
        }

        /* Member function : back()
         * Returns a reference to the last element in the container.
         *
         *
         */
        reference back() {
            return _vla[LAST_ELEMENT(_size)];
        }
        const_reference back() const {
            return const_cast<reference>(LAST_ELEMENT(_size));
        }

        /* Member function : begin()
         * Iterator to the first element.
         *
         *
         */
        iterator begin() {
            return iterator(_vla);
        }
        const_iterator begin() const {
            return const_iterator(_vla);
        }

        /* Member function : end()
         * Returns an iterator to the element following the last element of the vector.
         *
         *
         */
        iterator end() {
            return iterator(_vla + END_PTR(_size));
        }

	private:
		/* Private attributes
		 * _size is the number of current element in the array
		 * _capacity is the number of T already allocated
		 * _vla is the array that is going to grow if _size == _capacity
		 *
		 *
		 */

		void _init_constructor(const allocator_type& alloc, size_type capacity) {
		    _a = alloc;
		    _size = 0;
		    _realloc(capacity);
		    _set_end_pointer();
		}

		void _deep_copy(const Vector& other) {
		    this->clear();
		    if (_capacity < other._capacity)
		        _realloc(other._capacity);
		    _size = other._size;
		    _capacity = other._capacity;
		    _vla = _a.allocate(_capacity);
		    for (size_type i = 0; i < _size; i++)
		        _a.construct(_vla + i, other._vla[i]);
		    _set_end_pointer();
		}

		void _set_end_pointer() {
            _a.construct(_vla[END_PTR(_size)], T());
		}

		void _realloc(size_t new_capacity) {
		   pointer new_vla = _a.allocate(new_capacity);
		    for (size_type i = 0; i < _size; i++) {
                _a.construct(new_vla + i, _vla[i]);
                _a.deconstruct(_vla + i, 1);
            }
		    _a.desallocate(_capacity);
		    _capacity = new_capacity;
		    _vla = new_vla;
		    _set_end_pointer();
		}

		void _realloc(void) {
		    return _realloc(_capacity * 2);
		}

		allocator_type _a;
        size_type _size;
        size_type _capacity;
		pointer _vla;
	};
}
#endif
