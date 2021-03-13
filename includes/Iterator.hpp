/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:29:04 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/09 22:29:05 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template< class Category,
			class T,
			class Distance = std::ptrdiff_t,
			class Pointer = T*,
			class Reference = T& >
	struct iterator {
		typedef Distance difference_type;
		typedef T value_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

    template< class Node,
            class T,
            class Distance = std::ptrdiff_t,
            class Pointer = T*,
            class Reference = T& >
	class bidirectionalIterator {
	public:
	    typedef Node node_type;
        typedef Distance difference_type;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef bidirectional_iterator_tag iterator_category;

	    bidirectionalIterator() {}
        bidirectionalIterator(node_type node) : _node(node) {}
        bidirectionalIterator(const bidirectionalIterator& src) { *this = src; }
        bidirectionalIterator& operator=(const bidirectionalIterator& rhs) {
	        if (this != &rhs)
	            _node = rhs._node;
	        return *this;
	    }
	    virtual ~bidirectionalIterator() {}

        reference operator*() {
            return *_node;
        }
        pointer operator->() {
            return &(*_node);
        }
        bool operator==(const bidirectionalIterator& rhs) const {
            return (_node == rhs._node);
        }
        bool operator!=(const bidirectionalIterator& rhs) const {
            return (_node != rhs._node);
        }
        bidirectionalIterator& operator++() {
	        _node++;
            return *this;
        }
        bidirectionalIterator operator++(int) {
            bidirectionalIterator tmp = *this;
            _node++;
            return tmp;
        }
        bidirectionalIterator& operator--() {
            _node--;
            return *this;
        }
        bidirectionalIterator operator--(int) {
            bidirectionalIterator tmp = *this;
            _node--;
            return tmp;
        }

	    node_type _node;
	};

    template< class Node,
            class T,
            class Distance = std::ptrdiff_t,
            class Pointer = T*,
            class Reference = T& >
    class constBidirectionalIterator : public bidirectionalIterator<Node, T, Distance, Pointer, Reference> {
    public:
        typedef Node node_type;
        typedef Distance difference_type;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef bidirectional_iterator_tag iterator_category;
        typedef bidirectionalIterator<Node, T, Distance, Pointer, Reference> bidirectionalIterator;

        constBidirectionalIterator() {}
        constBidirectionalIterator(const constBidirectionalIterator& src) { *this = src; }
        constBidirectionalIterator(const bidirectionalIterator& x) : bidirectionalIterator(x._node) {}
        constBidirectionalIterator(const node_type& x) : bidirectionalIterator(x) {}
        virtual ~constBidirectionalIterator() {}

        constBidirectionalIterator& operator++() { return *this; }
        constBidirectionalIterator operator++(int) { return *this; }
        constBidirectionalIterator& operator--() { return *this; }
        constBidirectionalIterator operator--(int) { return *this; }
    };

    template< class Node,
            class T,
            class Distance = std::ptrdiff_t,
            class Pointer = T*,
            class Reference = T& >
    class randomAccessIterator : public bidirectionalIterator<Node,
            T, Distance, Pointer, Reference> {
    public:
        typedef Node node_type;
        typedef Distance difference_type;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef random_access_iterator_tag iterator_category;

        randomAccessIterator() {}
        randomAccessIterator(const randomAccessIterator& src) { *this = src; }
        randomAccessIterator(const Node& x) : bidirectionalIterator<Node,
            T, Distance, Pointer, Reference>(x) {}
        randomAccessIterator& operator=(const randomAccessIterator& rhs) {
            if (this != &rhs)
                this->_node = rhs._node;
            return *this;
        }
        virtual ~randomAccessIterator() {}

        difference_type operator-(const randomAccessIterator& rhs) {
            difference_type ret;
            ret = rhs._node - this->_node;
            return ret;
        }
        reference operator[](int n) {
            return *(this->_node + n);
        }

        bool operator==(const randomAccessIterator& rhs) {
            return this->_node == rhs._node;
        }
        bool operator!=(const randomAccessIterator& rhs) {
            return !(*this == rhs);
        }

        bool operator<(const randomAccessIterator& rhs) {
            return *this->_node < rhs;
        }
        bool operator>(const randomAccessIterator& rhs) {
            return *this->_node > rhs;
        }
        bool operator<=(const randomAccessIterator& rhs) {
            return *this->_node <= rhs;
        }
        bool operator>=(const randomAccessIterator& rhs) {
            return *this->_node >= rhs;
        }

        randomAccessIterator& operator+=(int n) {
            this->_node += n;
            return *this;
        }
        randomAccessIterator operator+(int n) {
            this->_node += n;
            return *this;
        }
        randomAccessIterator& operator-=(int n) {
            this->_node -= n;
            return *this;
        }
        randomAccessIterator operator-(int n) {
            this->_node -= n;
            return *this;
        }
    };

    template< class Node,
            class T,
            class Distance = std::ptrdiff_t,
            class Pointer = T*,
            class Reference = T& >
    class constRandomAccessIterator : public randomAccessIterator<Node, T,
            Distance, Pointer, Reference> {
    public:
        typedef Node node_type;
        typedef Distance difference_type;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef random_access_iterator_tag iterator_category;
        typedef randomAccessIterator<Node, T,
                Distance, Pointer, Reference> randomAccessIterator;

        constRandomAccessIterator() {}
        constRandomAccessIterator(const constRandomAccessIterator& src) { *this = src; }
        constRandomAccessIterator(const randomAccessIterator& x) : randomAccessIterator(x._node) {}
        constRandomAccessIterator(const node_type& x) : randomAccessIterator(x) {}
        virtual ~constRandomAccessIterator() {}

        constRandomAccessIterator& operator++() const { return *this; }
        constRandomAccessIterator operator++(int) const { return *this; }
        constRandomAccessIterator& operator--() const { return *this; }
        constRandomAccessIterator operator--(int) const { return *this; }
        constRandomAccessIterator& operator+=(int) const { return *this; }
        constRandomAccessIterator operator+(int) const { return *this; }
        constRandomAccessIterator& operator-=(int) const { return *this; }
        constRandomAccessIterator operator-(int) const { return *this; }
    };

	template< class Iter >
	struct iterator_traits {
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template< class T >
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	template< class Iter >
	class reverse_iterator {
	public:
		/* Member types :
		 * Inherit from iterator_traits for difference_type, value_type,
		 * pointer, reference and iterator category.
		 * Add iterator_type typedef.
		 *
		 */
		typedef Iter iterator_type;
		typedef typename iterator_traits<Iter>::difference_type difference_type;
		typedef typename iterator_traits<Iter>::value_type value_type;
		typedef typename iterator_traits<Iter>::reference reference;
		typedef typename iterator_traits<Iter>::pointer pointer;
		typedef typename iterator_traits<Iter>::iterator_category iterator_category;

		/* Member functions : constructors
		 * assignation operator
		 * and virtual destructor
		 */

		reverse_iterator() {}
		explicit reverse_iterator( iterator_type x ) : _current(x) {}
		template< class U >
		reverse_iterator( const reverse_iterator<U>& other ) { *this = other; }
		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other ) {
			if (this != &other)
				_current = other._current;
			return *this;
		}
		virtual ~reverse_iterator() {}

		/* Member function : base()
		 * return the underlying base iterator
		 *
		 *
		 */
		iterator_type base() const {
			return _current;
		}

		/* Member function : operator* and operator->
		 * Returns a reference or pointer to the element previous to current.
		 *
		 *
		 */
		reference operator*() const {
			Iter tmp = _current;
			return *--tmp;
		}
		pointer operator->() const {
			return &(this->operator*());
		}

		/* Member function : operator[]
		 * Returns a reference to the element at specified relative location.
		 *
		 *
		 */
		reference operator[]( difference_type n ) const {
			return _current[n - 1];
		}

		/* Member function : incrementation operators
		 * Increments or decrements the iterator.
		 * Inverse operations are applied to the underlying operator because of the reverse order.
		 *
		 */
		reverse_iterator& operator++() {
			_current--;
			return *this;
		}
		reverse_iterator& operator--() {
			_current++;
			return *this;
		}
		reverse_iterator operator++( int ) {
			reverse_iterator tmp = *this;
			_current--;
			return tmp;
		}
		reverse_iterator operator--( int ) {
			reverse_iterator tmp = *this;
			_current++;
			return tmp;
		}
		reverse_iterator operator+( difference_type n ) const {
			return reverse_iterator(_current - n);
		}
		reverse_iterator operator-( difference_type n ) const {
			return reverse_iterator(_current + n);
		}
		reverse_iterator& operator+=( difference_type n ) {
			_current -= n;
			return *this;
		}
		reverse_iterator& operator-=( difference_type n ) {
			_current += n;
			return *this;
		}

	protected:
		Iter _current;
	};

	/* Non member functions : comparison operators overloads
	 *
	 *
	 */

	template< class Iterator1, class Iterator2 >
	bool operator==( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() == rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator!=( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() != rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator<( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() < rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() <= rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator>( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() > rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
					 const std::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	/* Non member functions : addition operator
	 * Returns the iterator it incremented by n.
	 *
	 */
	template< class Iter >
	reverse_iterator<Iter>
	operator+( typename reverse_iterator<Iter>::difference_type n,
			   const reverse_iterator<Iter>& it ) {
		return reverse_iterator<Iter>(it.base() - n);
	}

	/* Non member functions : substraction operator
	 * Returns the distance between two iterator adaptors.
	 *
	 *
	 */

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type
	operator-( const reverse_iterator<Iterator>& lhs,
			   const reverse_iterator<Iterator>& rhs ) {
		return rhs.base() - lhs.base();
	}

}

#endif
