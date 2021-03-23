/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
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
# include <iostream>
# include "enable_if.hpp"
# include "iterator.hpp"
# include "comparison.hpp"

namespace ft {

	template<class T>
	struct t_list {
		T		content;
		t_list	*next;
		t_list	*prev;
	};

	template < class T >
	class listIterator : public ft::iterator<bidirectional_iterator_tag,
			T, std::ptrdiff_t , T*, T&>  {
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef t_list<T> t_list;
		typedef ft::bidirectional_iterator_tag iterator_category;

		listIterator() {}
		listIterator(t_list* node) : _node(node) {}
		listIterator(const listIterator& src) { *this = src; }
		listIterator& operator=(const listIterator& rhs) {
			if (this != &rhs)
				this->_node = rhs._node;
			return *this;
		}
		virtual ~listIterator() {}

		reference operator*() const {
			return this->_node->content;
		}
		pointer operator->() const {
			return &(this->_node->content);
		}
		friend bool operator==(const listIterator& lhs, const listIterator& rhs) {
			return (lhs._node == rhs._node);
		}
		friend bool operator!=(const listIterator& lhs, const listIterator& rhs) {
			return (lhs._node != rhs._node);
		}

		listIterator& operator++() {
			this->_node = this->_node->next;
			return *this;
		}
		listIterator operator++(int) {
			listIterator tmp = *this;
			++(*this);
			return tmp;
		}
		listIterator& operator--() {
			this->_node = this->_node->prev;
			return *this;
		}
		listIterator operator--(int) {
			listIterator tmp = *this;
			--(*this);
			return tmp;
		}

		t_list* _node;
	};

	template < class T >
	class listConstIterator : public ft::iterator<bidirectional_iterator_tag,
			T, std::ptrdiff_t , T*, T&> {
	public:
		typedef std::ptrdiff_t difference_type;
		typedef const T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef t_list<T> t_list;
		typedef ft::bidirectional_iterator_tag iterator_category;

		listConstIterator() {}
		listConstIterator(const listConstIterator& src) { *this = src; }
		listConstIterator(t_list* node) : _node(node) {}
		listConstIterator(const listIterator<T>& src) : _node(src._node) {}
		listConstIterator& operator=(const listConstIterator& rhs) {
			if (this != &rhs)
				this->_node = rhs._node;
			return *this;
		}
		virtual ~listConstIterator() {}

		reference operator*() const {
			return this->_node->content;
		}
		pointer operator->() const {
			return &(this->_node->content);
		}
		friend bool operator==(const listConstIterator& lhs, const listConstIterator& rhs) {
			return (lhs._node == rhs._node);
		}
		friend bool operator!=(const listConstIterator& lhs, const listConstIterator& rhs) {
			return (lhs._node != rhs._node);
		}

		listConstIterator& operator++() {
			this->_node = this->_node->next;
			return *this;
		}
		listConstIterator operator++(int) {
			listConstIterator tmp = *this;
			++(*this);
			return tmp;
		}
		listConstIterator& operator--() {
			this->_node = this->_node->prev;
			return *this;
		}
		listConstIterator operator--(int) {
			listConstIterator tmp = *this;
			--(*this);
			return tmp;
		}

		t_list* _node;
	};

	template< class T, class Allocator = std::allocator<T> >
	class list {
	public:
		/* Member types
		 *
		 *
		 *
		 */
        typedef t_list<T> t_list;
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef listIterator<T> iterator;
		typedef listConstIterator<T> const_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;

		/* Member functions : constructors
		 *
		 *
		 *
		 */
		list() {
			_init_constructor(Allocator());
		}
		explicit list( const Allocator& alloc ) {
			_init_constructor(alloc);
		}
		explicit list( size_type count,	const T& value = T(),
			const Allocator& alloc = Allocator() ) {
			_init_constructor(alloc);
			this->assign(count, value);
		}
		template< class InputIt >
		list( InputIt first, InputIt last,
			const Allocator& alloc = Allocator(),
			typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL) {
			_init_constructor(alloc);
			this->assign(first, last);
		}
		list( const list& other ) {
			_init_constructor(Allocator());
			this->_deep_copy(other);
		}

		/* Member functions : destructor
		 *
		 *
		 *
		 */
		virtual ~list() {
			this->clear();
			_lstdelone(_end);
		}

		/* Member functions : assignation operator
		 *
		 *
		 *
		 */
		list& operator=( const list& other ) {
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
			return _a_type;
		}

		/* Member functions : assign()
		 * 1/Replaces the contents with count copies of value value.
		 * 2/Replaces the contents with copies of those in the range [first, last).
		 *
		 */
		void assign( size_type count, const T& value ) {
			this->clear();
			for (size_type i = 0; i < count; i++) {
				this->push_back(value);
			}
		}
		template< class InputIt >
		void assign( InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL ) {
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
			return *(--end());
		}
		const_reference back() const {
			return *(--end());
		}

		/* Member functions : iterators
		 *
		 *
		 *
		 */
		iterator begin() {
			return iterator(this->_end->next);
		}
		const_iterator begin() const {
			return const_iterator(this->_end->next);
		}
		iterator end() {
			return iterator(this->_end);
		}
		const_iterator end() const {
			return const_iterator(this->_end);
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

		/* Member functions : empty()
		 * Checks if the container has no elements.
		 *
		 *
		 */
		bool empty() const { return _size == 0; }

		/* Member functions : size()
		 * Returns the number of elements in the container.
		 *
		 *
		 */
		size_type size() const { return _size; }

		/* Member functions : max_size()
		 * Returns the maximum number of elements the container is able to hold.
		 * due to system or library implementation limitations.
		 *
		 */
		size_type max_size() const {
			return _a_node.max_size();
		}

		/* Member functions : clear()
		 * Erases all elements from the container. After this call, size() returns zero.
		 *
		 *
		 */
		void clear() {
			if (this->empty())
				return ;
			t_list* track = _end->next;
			t_list* tmp;
			while(track != _end) {
				tmp  = track->next;
				this->_lstdelone(track);
				track = tmp;
			}
			_link_el(_end, _end);
			_size = 0;
		}

		/* Member functions : insert()
		 * 1/inserts value before pos.
		 * 2/inserts count copies of the value before pos.
		 * 3/inserts elements from range [first, last) before pos.
		 */
		iterator insert( iterator pos, const T& value ) {
			if (pos == begin()) {
				this->push_front(value);
				return begin();
			}
			if (pos == end()) {
				this->push_back(value);
				iterator it = end();
				it--;
				return it;
			}
			t_list* new_el = this->_lstnew(value);
			this->_lstinsert_el(pos._node, new_el);
			this->_size += 1;
			return iterator(new_el);
		}
		void insert( iterator pos, size_type count, const T& value ) {
			for(size_type i = 0; i < count; i++)
				insert(pos, value);
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last,
			   typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL) {
			for (InputIt it = first; it != last; it++)
				insert(pos, *it);
		}

		/* Member functions : erase()
		 * 1) Removes the element at pos.
		 * 2) Removes the elements in the range [first, last).
		 *
		 */
		iterator erase( iterator pos ) {
			if (pos == begin()) {
				this->pop_front();
				return begin();
			}
			if (pos == end()) {
				this->pop_back();
				return end();
			}
			if (this->empty())
				return pos;
			t_list* to_erase = pos._node;
			t_list* to_return = to_erase->next;
			this->_lstdetach_el(to_erase);
			this->_lstdelone(to_erase);
			_size -= 1;
			return iterator(to_return);
		}
		iterator erase( iterator first, iterator last ) {
			iterator ret;
			for(iterator it = first; it != last; it++)
				ret = erase(it);
			return ret;
		}

		/* Member functions : push_back()
		 * The new element is initialized as a copy of value.
		 *
		 *
		 */
		void push_back( const T& value ) {
			t_list* new_el;
			new_el = this->_lstnew(value);
			this->_lstinsert_el(_end, new_el);
			_size += 1;
		}

		/* Member functions : pop_back()
		 * Removes the last element of the container.
		 *
		 *
		 */
		void pop_back() {
			if (this->empty())
				return ;
			t_list* to_pop;
			to_pop = _end->prev;
			this->_lstdetach_el(to_pop);
			this->_lstdelone(to_pop);
			_size -= 1;
		}

		/* Member functions : push_front()
		 * Prepends the given element value to the beginning of the container.
		 *
		 *
		 */
		void push_front( const T& value ) {
			t_list* new_el;
			new_el = this->_lstnew(value);
			this->_lstinsert_el(_end->next, new_el);
			_size += 1;
		}

		/* Member functions : pop_front()
		 * Removes the first element of the container.
		 *
		 *
		 */
		void pop_front() {
			if (this->empty())
				return ;
			t_list* to_pop;
			to_pop = _end->next;
			this->_lstdetach_el(to_pop);
			this->_lstdelone(to_pop);
			_size -= 1;
		}

		/* Member functions : resize()
		 * Resizes the container to contain count elements.
		 * If the current size is greater than count, the container is reduced to its first count elements.
		 * If the current size is less than count,
		 *  2/ additional default-inserted elements are appended
		 *  1/ additional copies of value are appended.
		 *
		 */
		void resize( size_type count, T value ) {
			size_type old_size = this->_size;
			if (count < old_size) {
				for (size_type i = 0; i < old_size - count; i++)
					this->pop_back();
			}
			else if (count > this->_size) {
				for (size_type i = 0; i < count - old_size; i++)
					this->push_back(value);
			}
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
		void swap( list& other ) {
			size_type tmp_size = other._size;
			t_list* tmp_end = other._end;

			other._size = _size;
			_size = tmp_size;
			other._end = _end;
			_end = tmp_end;
		}

		/* Member functions : merge()
		 * Merges two sorted lists into one. The lists should be sorted into ascending order.
		 * No elements are copied. The container other becomes empty after the operation.
		 *
		 *
		 */
		template <class Compare>
		void merge( list& other, Compare comp ) {
			if (this == &other || other.empty())
				return ;
			if (this->empty())
				return this->swap(other);
			t_list* track_other = other._end->next;
			t_list* track_this = _end->next;
			t_list* tmp;
			while (track_other != other._end && track_this != _end) {
				if (comp(track_other->content, track_this->content)) {
					tmp = track_other->next;
					this->_lstdetach_el(track_other);
					this->_lstinsert_el(track_this, track_other);
					track_other = tmp;
				}
				else
					track_this = track_this->next;
			}
			if (track_other != other._end)
				while(track_other != other._end) {
					tmp = track_other->next;
					this->_lstdetach_el(track_other);
					this->_lstinsert_el(track_this, track_other);
					track_other = tmp;
				}
			_size += other._size;
			other._size = 0;
		}
		void merge( list& other ) {
			ft::less<T> comp;
			this->merge(other, comp);
		}

		/* Member functions : splice()
		 * Transfers elements from one list to another.
		 * No elements are copied or moved, only the internal pointers of the list nodes are re-pointed
		 *
		 */
		void splice( const_iterator pos, list& other, const_iterator it ) {
			t_list* to_move;
			to_move = it._node;
			this->_lstdetach_el(to_move);
			this->_lstinsert_el(pos._node, to_move);
			other._size -= 1;
			_size += 1;
		}
		void splice( const_iterator pos, list& other,
			const_iterator first, const_iterator last) {
			const_iterator it = first, tmp;
			while (it != last) {
				tmp = iterator(it._node->next);
				splice(pos, other, it);
				it = tmp;
			}
		}
		void splice( const_iterator pos, list& other ) {
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
			if (this->empty())
				return ;
			t_list* track = _end->next;
			t_list* tmp;
			while (track != _end) {
				if (p(track->content)) {
					tmp = track->next;
					this->_lstdetach_el(track);
					this->_lstdelone(track);
					track = tmp;
					_size -= 1;
				} else
					track = track->next;
			}
		}
		void remove( const T& value ) {
			ft::equal_to_unary<T> comp(value);
			remove_if(comp);
		}

		/* Member functions : reverse()
		 * Reverses the order of the elements in the container.
		 *
		 *
		 */
		void reverse() {
			t_list* track = _end->next;
			t_list* tmp;
			while(1) {
				tmp = track->next;
				track->next = track->prev;
				track->prev = tmp;
				if (track == _end)
					break ;
				track = tmp;
			}
		}

		/* Member functions : unique()
		 * Removes all consecutive duplicate elements from the container
		 * Only the first element in each group of equal elements is left
		 *
		 *
		 */
		template< class BinaryPredicate >
		void unique( BinaryPredicate p ) {
			if (_size < 2)
				return ;
			t_list* track = _end->next->next;
			t_list* tmp;

			while(track != _end) {
				tmp = track->next;
				if (p(track->prev->content, track->content)) {
					this->_lstdetach_el(track);
					this->_lstdelone(track);
					_size -= 1;
				}
				track = tmp;
			}
		}
		void unique() {
			ft::equal_to<T> comp;
			unique(comp);
		}

		/* Member function : sort()
		 * Sorts the elements in ascending order
		 * The first version uses comparison function comp to compare the elements,
		 * the second version uses operator<.
		 * Merge sort algorithm is used for N log N complexity
		 *
		 */

		template< class Compare >
		void sort( Compare comp ) {
			if (_size < 2)
				return ;
			// first make the double linked list uncircular
			t_list* head = _end->next;
			t_list* tail = _end->prev;
			head->prev = NULL;
			tail->next = NULL;

			//the merge sort algorithm
			head = this->_merge_sort(head, comp);

			//restore circular characteristics
			head->prev = _end;
			_end->next = head;
			tail = head;
			while(tail->next)
				tail = tail->next;
			tail->next = _end;
			_end->prev = tail;
		}
		void sort() {
			ft::less<T> comp;
			this->sort(comp);
		}


	private:
		/* private functions for management of linked list
		 *
		 *
		 *
		 */
		void _init_constructor( const Allocator& alloc ) {
			T default_val = T();

			_a_type = alloc;
			_end = _lstnew(default_val);
			_link_el(_end, _end);
			_size = 0;
		}

		void _link_el( t_list* first, t_list *second ) {
			first->next = second;
			second->prev = first;
		}

		void _swap_el( t_list* first, t_list *second ) {
			T tmp;

			tmp = first->content;
			first->content = second->content;
			second->content = tmp;
		}

		t_list* _lstnew( const_reference val ) {
			t_list* new_el;

			new_el = _a_node.allocate(1);
			_a_type.construct(&new_el->content, val);
			new_el->next = NULL;
			new_el->prev = NULL;
			return (new_el);
		}

		void _lstinsert_el(t_list* el_before, t_list* el_toadd) {
			t_list* tmp;

			tmp = el_before->prev;
			el_before->prev = el_toadd;
			el_toadd->next = el_before;
			el_toadd->prev = tmp;
			tmp->next = el_toadd;
		}

		void _lstdelone( t_list* element ) {
			_a_type.destroy(&element->content);
			_a_node.deallocate(element, 1);
		}

		void _lstdetach_el(t_list* el_todetach) {
			t_list *prev, *next;

			prev = el_todetach->prev;
			next = el_todetach->next;
			prev->next = next;
			next->prev = prev;
		}

		void _deep_copy( const list& other ) {
			_a_type = other._a_type;
			_a_node = other._a_node;
			for (const_iterator it = other.begin(); it != other.end(); it++)
				this->push_back(*it);
		}

		template< class Compare >
		t_list* _merge_sort(t_list* head, Compare comp)
		{
			if (!head || !head->next)
				return head;
			//principle : split the list in 2 smaller lists till the list is 2 elements
			t_list* second = this->_split(head);

			// recursive call to merge the 2 smaller lists
			head = this->_merge_sort(head, comp);
			second = this->_merge_sort(second, comp);

			// then merge the 2 newly sorted lists
			return this->_merge(head, second, comp);
		}

		template< class Compare >
		t_list* _merge(t_list* first, t_list* second, Compare comp)
		{
			//if the split has made empty lists : return the not empty one
			if (!first)
				return second;
			if (!second)
				return first;

			//swap elements recursively on the smaller lists
			if (comp(first->content, second->content))
			{
				first->next = this->_merge(first->next, second, comp);
				first->next->prev = first;
				first->prev = NULL;
				return first;
			}
			else
			{
				second->next = this->_merge(first, second->next, comp);
				second->next->prev = second;
				second->prev = NULL;
				return second;
			}
		}

		t_list* _split(t_list* head)
		{
			t_list *fast = head, *slow = head;
			while (fast->next && fast->next->next)
			{
				fast = fast->next->next;
				slow = slow->next;
			}
			t_list* temp = slow->next;
			slow->next = NULL;
			return temp;
		}

		/* private attributes
		 *
		 *
		 *
		 */
		allocator_type _a_type;
		typename Allocator::template rebind<t_list>::other _a_node;
		t_list* _end;
		size_type _size;
	};

	/* non-member functions
	 * operator overloads
	 *
	 *
	 */
	template< class T, class Allocator >
	bool operator==(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class T, class Allocator >
	bool operator!=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return !(lhs == rhs);
	}
	template< class T, class Allocator >
	bool operator<(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class T, class Allocator >
	bool operator<=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return lhs < rhs || lhs == rhs;
	}
	template< class T, class Allocator >
	bool operator>(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return !(lhs <= rhs);
	}
	template< class T, class Allocator >
	bool operator>=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return !(lhs < rhs);
	}

	template< class T, class Alloc >
	void swap(list<T, Alloc>& lhs, list<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif
