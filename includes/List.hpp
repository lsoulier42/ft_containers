/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:42:57 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/03 20:43:00 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <limits>
# include <memory>
//TODO: suppress iostream

namespace ft {
	template< class T, class Allocator = std::allocator<T> >
	class List {
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

		class const_iterator;
		class iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		/* Member functions : constructors
		 *
		 *
		 *
		 */
		List() {
			_init_constructor(Allocator());
		}
		explicit List( const Allocator& alloc ) {
			_init_constructor(alloc);
		}
		explicit List( size_type count,	const T& value = T(),
			const Allocator& alloc = Allocator() ) {
			_init_constructor(alloc);
			this->assign(count, value);
		}
		template< class InputIt >
		List( InputIt first, InputIt last,
			const Allocator& alloc = Allocator() ) {
			_init_constructor(alloc);
			this->assign(first, last);
		}
		List( const List& other ) {
			this->_deep_copy(other);
		}

		/* Member functions : destructor
		 *
		 *
		 *
		 */
		virtual ~List() {
			if (_count > 0)
				this->clear();
			_lstdelone(_begin);
			_lstdelone(_end);
		}

		/* Member functions : assignation operator
		 *
		 *
		 *
		 */
		List& operator=( const List& other ) {
			if (this != other)
				this->_deep_copy(other);
			return *this;
		}

		/* Member functions : assign()
		 * 1/Replaces the contents with count copies of value value.
		 * 2/Replaces the contents with copies of those in the range [first, last).
		 *
		 */
		void assign( size_type count, const T& value ) {
			if (_count > 0)
				this->clear();
			for (size_type i = 0; i < count; i++) {
				this->push_back(value);
			}
		}
		template< class InputIt >
		void assign( InputIt first, InputIt last ) {
			if (_count > 0)
				this->clear();
			for (InputIt it = first; it != last; it++)
				this->push_back(*it);
		}

		/* Member functions : front()
		 * Returns a reference to the first element in the container.
		 *
		 *
		 */
		reference front() {
			return *(this->begin());
		}
		const_reference front() const {
			return *(this->begin());
		}

		/* Member functions : back()
		 * Returns a reference to the last element in the container.
		 *
		 *
		 */
		reference back() {
			return *(this->end());
		}
		const_reference back() const {
			return *(this->end());
		}

		/* Member functions : iterators
		 *
		 *
		 *
		 */
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		//TODO: implement

		/* Member functions : empty()
		 * Checks if the container has no elements.
		 *
		 *
		 */
		bool empty() const { return _count == 0; }

		/* Member functions : size()
		 * Returns the number of elements in the container.
		 *
		 *
		 */
		size_type size() const { return _count; }

		/* Member functions : max_size()
		 * Returns the maximum number of elements the container is able to hold.
		 * due to system or library implementation limitations.
		 *
		 */
		size_type max_size() const {
			return std::numeric_limits<difference_type>::max();
		}

		/* Member functions : clear()
		 * Erases all elements from the container. After this call, size() returns zero.
		 *
		 *
		 */
		void clear() {
			this->erase(this->begin(), this->end());
		}

		/* Member functions : insert()
		 * 1/inserts value before pos.
		 * 2/inserts count copies of the value before pos.
		 * 3/inserts elements from range [first, last) before pos.
		 */
		iterator insert( iterator pos, const T& value ) {
			//TODO: implement
		}
		void insert( iterator pos, size_type count, const T& value ) {
			for(size_type i = 0; i < count; i++)
				insert(pos, value);
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last ) {
			for (InputIt it = first; it != last; it++)
				insert(pos, *it);
		}

		/* Member functions : erase()
		 * 1) Removes the element at pos.
		 * 2) Removes the elements in the range [first, last).
		 *
		 */
		iterator erase( iterator pos ) {
			//TODO: implement, not forgetting to update the _count
		}
		iterator erase( iterator first, iterator last ) {
			for(iterator it = first; it != last; it++)
				erase(it);
		}

		/* Member functions : push_back()
		 * The new element is initialized as a copy of value.
		 *
		 *
		 */
		void push_back( const T& value ) {
			this->insert(this->end(), value);
		}

		/* Member functions : pop_back()
		 * Removes the last element of the container.
		 *
		 *
		 */
		void pop_back() {
			this->erase(this->end());
		}

		/* Member functions : push_front()
		 * Prepends the given element value to the beginning of the container.
		 *
		 *
		 */
		void push_front( const T& value ) {
			this->insert(this->begin(), value);
		}

		/* Member functions : pop_front()
		 * Removes the first element of the container.
		 *
		 *
		 */
		void pop_front() {
			this->erase(this->begin());
		}

		/* Member functions : resize()
		 * Resizes the container to contain count elements.
		 * If the current size is greater than count, the container is reduced to its first count elements.
		 * If the current size is less than count,
		 *  2/ additional default-inserted elements are appended
		 *  1/ additional copies of value are appended.
		 *
		 */
		void resize( size_type count, T value = T() ) {
			if (count < this->_count)
				this->erase(begin() + count, end());
			else if (count > this->_count)
				this->push_back(value);
		}
		void resize( size_type count ) {
			this->resize(count, T());
		}

		/* Member functions : swap()
		 * Exchanges the contents of the container with those of other
		 *
		 *
		 *
		 */
		void swap( List& other ) {
			this->_swap_el(_begin, other._begin);
			this->_swap_el(_end, other._end);
		}

		/* Member functions : merge()
		 * Merges two sorted lists into one. The lists should be sorted into ascending order.
		 * No elements are copied. The container other becomes empty after the operation.
		 *
		 *
		 */
		template <class Compare>
		void merge( List& other, Compare comp ) {
			//TODO: implement
		}
		void merge( List& other ) {
			cmp_merge comp;
			this->merge(other, comp);
		}

		/* Member functions : splice()
		 * Transfers elements from one list to another.
		 * No elements are copied or moved, only the internal pointers of the list nodes are re-pointed
		 *
		 */
		void splice( const_iterator pos, List& other, const_iterator it ) {
			//TODO: implement
		}
		void splice( const_iterator pos, List& other,
			const_iterator first, const_iterator last) {
			for (iterator it = first; it != last; it++)
				splice(pos, other, it);
		}
		void splice( const_iterator pos, List& other ) {
			splice(pos, other, other.begin(), other.end());
		}

		/* Member functions : remove(), remove_if()
		 * Removes all elements satisfying specific criteria.
		 * 1/ removes all elements for which predicate p returns true.
		 * 2/ removes all elements that are equal to value
		 *
		 */
		template< class UnaryPredicate >
		void remove_if( UnaryPredicate p ) {
			//TODO: implement
		}
		void remove( const T& value ) {
			cmp_unary comp(value);
			remove_if(comp);
		}

		/* Member functions : reverse()
		 * Reverses the order of the elements in the container.
		 * //TODO: no modification from previous version, should be weird...
		 *
		 */
		void reverse() {
			t_list* track = _begin;
			t_list* tmp;

			while(track) {
				tmp = track->next;
				track->next = track->prev;
				track->prev = tmp;
				track = tmp;
			}
			tmp = _begin;
			_begin = _end;
			_end = tmp;
		}

		/* Member functions : unique()
		 * Removes all consecutive duplicate elements from the container
		 * Only the first element in each group of equal elements is left
		 *
		 *
		 */
		template< class BinaryPredicate >
		size_type unique( BinaryPredicate p ) {
			//TODO: implement
		}
		void unique() {
			cmp_unique comp;
			unique(comp);
		}

	private:
		/* Base double chained link list structure
		 *
		 *
		 *
		 */
		typedef struct	s_list {
			pointer			content;
			struct s_list	*next;
			struct s_list	*prev;
		}				t_list;

		/* private attributes
		 *
		 *
		 *
		 */
		allocator_type _a;
		t_list* _begin;
		t_list* _end;
		size_type _count;

		void _init_constructor( const Allocator& alloc ) {
			T default_val = T();

			_begin = _lstnew(default_val);
			_end = _lstnew(default_val);
			_link_el(_begin, _end);
			_count = 0;
		}

		void _link_el( t_list* first, t_list *second ) {
			first->next = second;
			second->prev = first;
		}

		void _invert_el( t_list* first, t_list *second ) {
			t_list* tmp;

			first->next = second->next;
			second->next = first;
			tmp = first->prev;
			first->prev = second;
			second->prev = tmp;
		}

		void _swap_el( t_list* first, t_list *second ) {
			t_list* tmp;

			tmp = first->next;
			first->next = second->next;
			second->next = tmp;
			tmp = first->prev;
			first->prev = second->prev;
			second->prev = tmp;
		}

		t_list* _lstnew( const_reference val ) {
			t_list* new_el;

			new_el = new t_list;
			new_el->content = _a.allocate(1);
			_a.construct(new_el->content, val);
			new_el->next = NULL;
			new_el->prev = NULL;
		}

		void _lstdelone( t_list* element ) {
			_a.destroy(element->content);
			_a.deallocate(element->content, 1);
			delete element;
		}

		void _deep_copy( const List& other ) {
			if (_count > 0)
				this->clear();
			for (iterator it = other.begin(); it != other.end(); it++)
				this->push_back(*it);
		}

		class cmp_unary {
		public:
			explicit cmp_unary(const T& ref) : _ref(ref) {}
			cmp_unary(const cmp_unary & src) : _ref(src._ref) { *this = src; }
			cmp_unary& operator=(const cmp_unary & rhs) {
				(void)rhs;
				return *this;
			}
			virtual ~cmp_unary() {}
			bool operator()(const T& other) const { return other == _ref; }
		private:
			cmp_unary() {}
			const T& _ref;
		};

		class cmp_merge {
		public:
			cmp_merge() {}
			cmp_merge(const cmp_merge & src) { *this = src; }
			cmp_merge& operator=(const cmp_merge & rhs) {
				(void)rhs;
				return *this;
			}
			bool operator() (const T& content1,
							 const T& content2) const { return content1 < content2; }
			virtual ~cmp_merge() {}
		};

		class cmp_unique {
		public:
			cmp_unique() {}
			cmp_unique(const cmp_unique & src) { *this = src; }
			cmp_unique& operator=(const cmp_unique & src) {
				(void)src;
				return *this;
			}
			bool operator() (const T& content1,
							 const T& content2) const { return content1 == content2; }
			virtual ~cmp_unique() {}
		};

		/* non-member functions
		 *
		 *
		 *
		 */
		friend bool operator==(const List<T>& lhs, const List<T>& rhs);
		friend bool operator!=(const List<T>& lhs, const List<T>& rhs);
		friend bool operator<(const List<T>& lhs, const List<T>& rhs);
		friend bool operator<=(const List<T>& lhs, const List<T>& rhs);
		friend bool operator>(const List<T>& lhs, const List<T>& rhs);
		friend bool operator>=(const List& lhs, const List& rhs);
	};

	template<class T>
	void swap(List<T>& lhs, List<T>& rhs) {
		lhs.swap(rhs);
	}
}

#endif
