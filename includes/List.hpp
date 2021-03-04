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
# include <limits>
# include <memory>
# define NULL (void*)0

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

		/* Iterator classes definition
		 *
		 *
		 *
		 */

		class const_iterator {
		public:
			const_iterator() : _node(NULL) {}
			explicit const_iterator(const t_list* node): _node(node) {}
			const_iterator(const const_iterator& src) { *this = src; }
			const_iterator& operator=(const const_iterator& rhs) {
				if (this != &rhs)
					_node = rhs._node;
				return *this;
			}
			virtual ~const_iterator() {}

			reference operator*() {
				if (_node->next && _node->prev)
					return _node->content;
				if (!_node->next)
					return _node->prev->content;
				if (!_node->prev)
					return _node->next->content;
				return _node->content;
			}
			bool operator==(const const_iterator& rhs) const {
				return (_node == rhs._node);
			}
			bool operator!=(const const_iterator& rhs) const {
				return !(*this == rhs);
			}
			const_iterator& operator++() { return *this; }
			const_iterator operator++(int) { return *this; }
			const_iterator& operator--() { return *this; }
			const_iterator operator--(int) { return *this;}

			//public attribute
			t_list* _node;
		};

		class iterator : public const_iterator {
			iterator() : const_iterator() {}
			explicit iterator(const t_list* node) : const_iterator(node) {}
			iterator(const iterator& src) { *this = src; }
			explicit iterator(const const_iterator& src) {
				this->_node = src._node;
			}
			iterator& operator=(const iterator& rhs) {
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}
			~iterator() {}

			iterator& operator++() {
				if (this->_node->next)
					this->_node = this->_node->next;
				return *this;
			}
			iterator operator++(int) {
				iterator tmp = *this;
				if (this->_node->next)
					this->_node = this->_node->next;
				return tmp;
			}
			iterator& operator--() {
				if(this->_node->prev
					&& this->_node->prev->prev)
					this->_node = this->_node->prev;
				return *this;
			}
			iterator operator--(int) {
				iterator tmp = *this;
				if (this->_node->prev
					&& this->_node->prev->prev)
					this->_node = this->_node->prev;
				return tmp;
			}
		};

		class const_reverse_iterator {
		public:
			const_reverse_iterator() : _node(NULL) {}
			const_reverse_iterator(const t_list* node) : _node(node) {}
			const_reverse_iterator(const const_reverse_iterator& src) { *this = src; }
			const_reverse_iterator& operator=(const const_reverse_iterator& rhs) {
				if (this != &rhs)
					_node = rhs._node;
				return *this;
			}
			virtual ~const_reverse_iterator() {}

			reference operator*() {
				if (_node->next && _node->prev)
					return _node->content;
				if (!_node->next)
					return _node->prev->content;
				if (!_node->prev)
					return _node->next->content;
				return _node->content;
			}
			bool operator==(const const_reverse_iterator& rhs) const {
				return this->_node == rhs._node;
			}
			bool operator!=(const const_reverse_iterator& rhs) const {
				return !(*this == rhs);
			}
			const_reverse_iterator& operator++() { return *this; }
			const_reverse_iterator operator++(int) { return *this; }
			const_reverse_iterator& operator--() { return *this; }
			const_reverse_iterator operator--(int) { return *this;}

			//public attribute
			t_list* _node;
		};

		class reverse_iterator : public const_reverse_iterator {
		public:
			reverse_iterator() : const_reverse_iterator() {}
			explicit reverse_iterator(const t_list* node) : const_reverse_iterator(node) {}
			reverse_iterator(const reverse_iterator& src) { *this = src; }
			explicit reverse_iterator(const const_reverse_iterator& src) {
				this->_node = src._node;
			}
			reverse_iterator& operator=(const reverse_iterator& rhs) {
				if (this != &rhs)
					this->_node = rhs._node;
				return *this;
			}
			~reverse_iterator() {}

			reverse_iterator& operator++() {
				if (this->_node->prev)
					this->_node = this->_node->prev;
				return *this;
			}
			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				if (this->_node->prev)
					this->_node = this->_node->prev;
				return tmp;
			}
			reverse_iterator& operator--() {
				if (this->_node->next && this->_node->next->next)
					this->_node = this->_node->next;
				return *this;
			}
			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				if (this->_node->next && this->_node->next->next)
					this->_node = this->_node->next;
				return tmp;
			}
		};

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
		iterator begin() {
			if (_count > 0)
				return iterator(this->_begin->next);
			return end();
		}
		const_iterator begin() const {
			if (_count > 0)
				return const_iterator(this->_begin->next);
			return end();
		}
		iterator end() {
			return iterator(this->_end);
		}
		const_iterator end() const {
			return const_iterator(this->_end);
		}

		reverse_iterator rbegin() {
			if (_count > 0)
				return reverse_iterator(this->_end->prev);
			return rend();
		}
		const_reverse_iterator rbegin() const {
			if (_count > 0)
				return const_reverse_iterator(this->_end->prev);
			return rend();
		}
		reverse_iterator rend() {
			return reverse_iterator(this->_begin);
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(this->_begin);
		}

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
			this->_count += 1;
			if (pos == begin()) {
				_lstadd_front(_lstnew(value));
				return begin();
			}
			if (pos == end()) {
				_lstadd_back(_lstnew(value));
				return --end();
			}

			t_list* node = pos._node;
			t_list* tmp = node->prev;
			t_list* new_el = this->_lstnew(value);

			node->prev = new_el;
			new_el->next = node;
			new_el->prev = tmp;
			tmp->next = new_el;
			return iterator(new_el);
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
			if (_count > 0) {
				_count -= 1;
				t_list* tmp;
				t_list* to_erase = pos._node;

				if (pos == begin()) {
					tmp = to_erase->next;
					_begin->next = tmp;
					tmp->prev = _begin;
					this->_lstdelone(to_erase);
					return begin();
				}
				if (pos == end()) {
					to_erase = pos._node->prev;
					tmp = to_erase->prev;
					_end->prev = tmp;
					tmp->next = _end;
					this->_lstdelone(to_erase);
					return end();
				}
				tmp = to_erase->next;
				tmp->prev = to_erase->prev;
				to_erase->prev->next = tmp;
				this->_lstdelone(to_erase);
				return iterator(tmp);
			}
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
			if (count < this->_count) {
				iterator it = begin();
				for(size_type i = 0; i < count; i++)
					it++;
				this->erase(it, end());
			}
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
			size_type tmp_count = _count;
			_count = other._count;
			other._count = tmp_count;
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
			if (this == &other || other.empty())
				return ;
			if (this->empty())
				return this->swap(other);
			t_list* track_other = other._begin->next;
			t_list* track_this = _begin->next;
			t_list* tmp;
			while (track_other != other._end && track_this != _end) {
				if (comp(track_other->content, track_this->content)) {
					tmp = track_other->next;
					track_other->next = track_this;
					track_other->prev = track_this->prev;
					track_this->prev->next = track_other;
					track_this->prev = track_other;
					track_other = tmp;
				}
				else
					track_this = track_this->next;
			}
			_count += other._count;
			other._count = 0;
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
		 *
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
			_swap_el(_begin, _end);
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

		void _lstadd_front( t_list* el ) {
			t_list* tmp;

			tmp = _begin->next;
			_begin->next = el;
			el->prev = _begin;
			el->next = tmp;
			tmp->prev = el;
		}

		void _lstadd_back( t_list* el ) {
			t_list* tmp;

			tmp = _end->prev;
			_end->prev = el;
			el->next = _end;
			el->prev = tmp;
			tmp->next = el;
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
