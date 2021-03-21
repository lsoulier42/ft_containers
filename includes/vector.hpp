/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
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
# include <stdexcept>
# include <string>
# include <sstream>
# include "Iterator.hpp"
# include "enable_if.hpp"
# include "Comparison.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
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

		class const_iterator : public ft::iterator<random_access_iterator_tag, T,
			difference_type, pointer, reference> {
		public:
			const_iterator() {}
			const_iterator(T* node) : _node(node) {}
			const_iterator(const const_iterator& src) { *this = src; }
			const_iterator& operator=(const const_iterator& rhs) {
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}
			virtual ~const_iterator() {}

			/* Random access iterator : access
			 *
			 *
			 */
			reference operator*() const {
				return *_node;
			}
			pointer operator->() const {
				return _node;
			}
			difference_type operator-(const const_iterator& rhs) {
				difference_type ret;
				ret = rhs._node - _node;
				return ret;
			}
			reference operator[](int n) {
				return *(_node + n);
			}

			/* Random access iterator : comparison
			 *
			 *
			 */
			bool operator==(const const_iterator& rhs) {
				return _node == rhs._node;
			}
			bool operator!=(const const_iterator& rhs) {
				return _node != rhs._node;
			}
			bool operator<(const const_iterator& rhs) {
				return _node < rhs._node;
			}
			bool operator>(const const_iterator& rhs) {
				return  _node > rhs._node;
			}
			bool operator<=(const const_iterator& rhs) {
				return  _node <= rhs._node;
			}
			bool operator>=(const const_iterator& rhs) {
				return  _node >= rhs._node;
			}

			/* Random access iterator : arythmetic operator
			 *
			 *
			 */

			const_iterator& operator++() {
				this->_node++;
				return *this;
			}
			const_iterator operator++(int) {
				const_iterator tmp = *this;
				++(*this);
				return tmp;
			}
			const_iterator& operator--() {
				this->_node--;
				return *this;
			}
			const_iterator operator--(int) {
				const_iterator tmp = *this;
				--(*this);
				return tmp;
			}
			const_iterator& operator+=(int n) {
				this->_node += n;
				return *this;
			}
			const_iterator operator+(int n) {
				this->_node += n;
				return *this;
			}
			const_iterator& operator-=(int n) {
				this->_node -= n;
				return *this;
			}
			const_iterator operator-(int n) {
				this->_node -= n;
				return *this;
			}

			/* Random access iterator : public attribute
			 *
			 *
			 */
			T* _node;
		};

		class iterator : public const_iterator  {
		public:
			iterator() {}
			iterator(T* node) : const_iterator(node) {}
			iterator(const iterator& src) { *this = src; }
			iterator(const const_iterator& other) : const_iterator(other) {}
			iterator& operator=(const iterator& rhs) {
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}
			virtual ~iterator() {}
		};

		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;

		 /* Member functions : constructors
		  *
		  *
		  *
		  */
		 vector() {
            _init_constructor(Allocator(), 1);
		 }
		 explicit vector( const Allocator& alloc ) {
            _init_constructor(alloc, 1);
		 }
		 explicit vector( size_type count,
			const T& value = T(), const Allocator& alloc = Allocator()) {
             _init_constructor(alloc, count);
             this->assign(count, value);
		 }
		template< class InputIt >
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) {
            _init_constructor(alloc, last - first);
            this->assign(first, last);
		 }
		vector( const vector& other ) {
			_init_constructor(Allocator(), 1);
            this->_deep_copy(other);
		 }

		 /* Member functions : destructor
		  *
		  */
		 virtual ~vector() {
		     this->clear();
			 _a.deallocate(_vla, _capacity);
             _capacity = 0;
             _size = 0;
		 }

		 /* Member functions : assignation operator
		  *
		  *
		  *
		  */

        vector& operator=( const vector& other ) {
        	if (this != &other) {
				this->clear();
				this->_deep_copy(other);
			}
            return *this;
        }

		/* Member functions : get_allocator
		 * Returns the allocator associated with the container.
		 *
		 *
		 */
		allocator_type get_allocator() const {
			return _a;
		}

        /* Member functions : assign()
         * 1) Replaces the contents with count copies of value value
         * 2) Replaces the contents with copies of those in the range [first, last).
         *
         *
         */

        void assign( size_type count, const T& value ) {
			this->clear();
            this->insert(begin(), count, value);
        }
        template< class InputIt >
        void assign( InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL ) {
			this->clear();
			this->insert(begin(), first, last);
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
            return _vla[0];
        }
        const_reference front() const {
            return const_cast<reference>(_vla[0]);
        }

        /* Member function : back()
         * Returns a reference to the last element in the container.
         *
         *
         */
        reference back() {
            return _vla[_size - 1];
        }
        const_reference back() const {
            return _vla[_size - 1];
        }

        /* Member function : iterator functions
         *
         *
         *
         */
        iterator begin() {
            return iterator(_vla);
        }
        const_iterator begin() const {
            return const_iterator(_vla);
        }
        iterator end() {
            return iterator(_vla + _size);
        }
		const_iterator end() const {
        	return const_iterator(_vla + _size);
        }
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		/* Member function : empty()
		 * Checks if the container has no elements
		 *
		 */

		bool empty() const {
			return _size == 0;
		}

		/* Member function : size();
		 * Returns the number of elements in the container
		 *
		 */
		size_type size() const {
			return _size;
		}

		/* Member function : max_size()
		 * Returns the maximum number of elements the container is able to hold
		 * due to system or library implementation limitations
		 *
		 */
		size_type max_size() {
			return _a.max_size();
		}

		/* Member function : reserve()
		 * Increase the capacity of the vector to a value that's greater or equal to new_cap
		 * If new_cap is greater than the current capacity(), new storage is allocated,
		 * otherwise the method does nothing.
		 * If new_cap is greater than capacity(), all iterators, including the past-the-end iterator,
		 * and all references to the elements are invalidated
		 *
		 */
		void reserve( size_type new_cap ) {
			if (new_cap > _capacity)
				_realloc(new_cap);
		}

		/* Member function : capacity()
		 * Returns the number of elements that the container has currently allocated space for.
		 *
		 *
		 *
		 */
		size_type capacity() const {
			return _capacity;
		}

		/* Member function : clear()
		 * Erases all elements from the container. After this call, size() returns zero.
		 * Invalidates any references, pointers, or iterators referring to contained elements.
		 * Any past-the-end iterators are also invalidated.
		 * Leaves the capacity() of the vector unchanged
		 *
		 */
		void clear() {
			if (_size == 0)
				return ;
			for(size_type i = 0; i < _size; i++)
				_a.destroy(_vla + i);
			_size = 0;
		}

		/* Member function : insert()
		 * Inserts elements at the specified location in the container.
		 * 1/ inserts value before pos
		 * 2/ inserts count copies of the value before pos
		 * 3/ inserts elements from range [first, last) before pos.
		 *
		 */
		iterator insert( iterator pos, const T& value ) {
			size_type index = pos._node - _vla;
			this->insert(pos, 1, value);
			return iterator(_vla + index);
		}
		void insert( iterator pos, size_type count, const T& value ) {
			size_type index = pos._node - _vla;
			while (_size + count > _capacity)
				_realloc(_capacity * 2);
			this->_shift_right_elements(index, count);
			for (size_type i = index; i < count + index; i++)
				_a.construct(_vla + i, value);
			_size += count;
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last,
			   typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL) {
			size_type count = 0;
			for(InputIt it = first; it != last; it++)
				count++;
			size_type index = pos._node - _vla;
			while (_size + count > _capacity)
				_realloc(_capacity * 2);
			this->_shift_right_elements(index, count);
			size_type i = index;
			for (InputIt it = first; it != last; it++)
				_a.construct(_vla + i++, *it);
			_size += count;
		}

		/* Member function : erase()
		 * Erases the specified elements from the container.
		 * 1) Removes the element at pos.
		 * 2) Removes the elements in the range [first, last).
		 * Invalidates iterators and references at or after the point of the erase, including the end() iterator.
		 *
		 */
		iterator erase( iterator pos ) {
			size_type index = pos._node - _vla;

			_a.destroy(pos._node);
			for (size_type i = index; i < _size - 1; i++) {
				_a.construct(_vla + i, _vla[i + 1]);
				_a.destroy(_vla + i + 1);
			}
			_size -= 1;
			return iterator(_vla + index);
		}
		iterator erase( iterator first, iterator last ) {
			size_type to_erase = last - first;
			size_type index_dst = first._node - _vla;
			size_type index_src = last._node - _vla;
			size_type nb_to_move = _size - to_erase;

			for (size_type i = 0; i < to_erase; i++)
				_a.destroy(first._node + i);
			for (size_type i = index_dst; i < nb_to_move; i++) {
				_a.construct(_vla + i, _vla[index_src]);
				_a.destroy(_vla + index_src++);
			}
			_size -= to_erase;
			return iterator(_vla + index_dst);
		}
		/* Member function : push_back()
		 * Appends the given element value to the end of the container.
		 * The new element is initialized as a copy of value.
		 *
		 */
		void push_back( const T& value ) {
			this->insert(end(), value);
		}

		/* Member function : pop_back()
		 * Removes the last element of the container.
		 * Calling pop_back on an empty container results in undefined behavior.
		 * Iterators and references to the last element, as well as the end() iterator, are invalidated.
		 *
		 */
		void pop_back() {
			this->erase(--end());
		}

		/* Member function : resize()
		 * Resizes the container to contain count elements.
		 * If the current size is greater than count, the container is reduced to its first count elements.
		 * If the current size is less than count, additional copies of value are appended.
		 *
		 */
		void resize( size_type count, T value = T() ) {
			if (count < _size)
				this->erase(begin() + count, end());
			else
				this->insert(end(), count - _size, value);
		}

		/* Member function : swap()
		 * Exchanges the contents of the container with those of other
		 * Does not invoke any move, copy, or swap operations on individual elements.
		 * All iterators and references remain valid. The past-the-end iterator is invalidated.
		 *
		 */
		void swap( vector& other ) {
			vector tmp = other;
			other = *this;
			*this = tmp;
		}

	private:
		/* Private attributes
		 * _size is the number of current element in the array
		 * _capacity is the number of T already allocated
		 * _vla is the array that is going to grow when _size == _capacity
		 *
		 *
		 */

		void _init_constructor(const allocator_type& alloc, size_type count) {
		    _a = alloc;
		    _size = 0;
		    _capacity = count;
		    _vla = _a.allocate(_capacity);
		    for(size_type i = 0; i < _capacity; i++)
		    	_a.construct(_vla + i, T());
		}

		void _deep_copy(const vector& other) {
	        _realloc(other._capacity);
		    _a = other._a;
		    _size = other._size;
		    _vla = _a.allocate(_capacity);
		    for (size_type i = 0; i < _size; i++)
		        _a.construct(_vla + i, other._vla[i]);
		}

		void _shift_right_elements(const size_type& first_index, const size_type& count) {
			if (!this->empty()) {
				for (size_type i = _size; i > first_index; i--) {
					_a.construct(_vla + i + count - 1, _vla[i - 1]);
					_a.destroy(_vla + i - 1);
				}
			}
		}

		void _realloc(const size_type& new_capacity) {
		   pointer new_vla = _a.allocate(new_capacity);
		   for (size_type i = 0; i < _size; i++) {
		   		_a.construct(new_vla + i, _vla[i]);
				_a.destroy(_vla + i);
		   }
		   _a.deallocate(_vla, _capacity);
		   _capacity = new_capacity;
		   _vla = new_vla;
		}

		/* private attributes
		 *
		 *
		 *
		 */

		allocator_type _a;
        size_type _size;
        size_type _capacity;
		pointer _vla;
	};
		/* Non-member functions : comparison operator overloads
		 *
		 *
		 */
		template< class T, class Allocator >
		bool operator==( const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs ) {
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		template< class T, class Allocator >
		bool operator!=( const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs ) {
			return !(lhs == rhs);
		}
		template< class T, class Allocator >
		bool operator<( const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs ) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		template< class T, class Allocator >
		bool operator<=( const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs ) {
			return (lhs < rhs || lhs == rhs);
		}
		template< class T, class Allocator >
		bool operator>( const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs ) {
			return !(lhs <= rhs);
		}
		template< class T, class Allocator >
		bool operator>=( const ft::vector<T, Allocator>& lhs, const ft::vector<T, Allocator>& rhs ) {
			return !(lhs < rhs);
		}

		/* Non-member functions : ft::swap()
		 * Specializes the std::swap algorithm for std::vector.
		 * Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
		 *
		 */
		template<class T, class Allocator>
		void swap( ft::vector<T, Allocator>& lhs, ft::vector<T, Allocator>& rhs ) {
			lhs.swap(rhs);
		}
}
#endif