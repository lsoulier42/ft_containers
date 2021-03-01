/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:32:10 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/23 11:32:11 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include <limits>
//TODO: suppress iostream

namespace ft {
	template< class T, class Allocator = std::allocator<T> >
	class List {
	public:

		/* Base double chained link list structure
		 *
		 *
		 *
		 */
		typedef struct	s_list {
			explicit s_list(const T& value) : content(value),
				next(NULL), prev(NULL) {}
			T				content;
			struct s_list	*next;
			struct s_list	*prev;
		}				t_list;


		/* Member types
		 *
		 *
		 *
		 */
		typedef T value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;

		/* Iterator classes
		 *
		 *
		 *
		 */

		class const_iterator {
		public:
			const_iterator() : _current(NULL), _is_end(true) {}
			const_iterator(t_list* current, bool is_end) : _current(current), _is_end(is_end) {}
			const_iterator(const const_iterator& src) { *this = src; }
			const_iterator& operator=(const const_iterator& rhs) {
				if (this != &rhs) {
					_current = rhs._current;
					_is_end = rhs._is_end;
				}
				return *this;
			}
			virtual ~const_iterator() {}
			T& operator*() const { return _current->content; }
			t_list* dereference() const { return _current; }
			bool operator==(const const_iterator& rhs) const {
				return (_current == rhs._current && _is_end == rhs._is_end);
			}
			bool operator!=(const const_iterator& rhs) const {
				return !(*this == rhs);
			}
			const_iterator& operator++() { return *this; }
			const_iterator operator++(int) { return *this; }
			const_iterator& operator--() { return *this; }
			const_iterator operator--(int) { return *this; }

		protected:
			t_list* _current;
			bool	_is_end;
		};

		class iterator : public const_iterator {
		public:
			iterator() : const_iterator() {}
			iterator(t_list* current, bool is_end) : const_iterator(current, is_end) {}
			iterator(const iterator& src) { *this = src; }
			explicit iterator(const const_iterator& src) { *this = src; }
			iterator& operator=(const iterator& rhs) {
				if (this != &rhs) {
					this->_current = rhs._current;
					this->_is_end = rhs._is_end;
				}
				return *this;
			}
			~iterator() {}

			iterator& operator++() {
				if (this->_current->next)
					this->_current = this->_current->next;
				else
					this->_is_end = true;
				return *this;
			}
			iterator operator++(int) {
				t_list* tmp = this->_current;
				bool tmp_bool = this->_is_end;

				if (this->_current->next)
					this->_current = this->_current->next;
				else
					this->_is_end = true;
				return iterator(tmp, tmp_bool);
			}
			iterator& operator--() {
				if (this->_current->prev && !this->_is_end)
					this->_current = this->_current->prev;
				this->_is_end = false;
				return *this;
			}
			iterator operator--(int) {
				t_list* tmp = this->_current;
				if (this->_current->prev && !this->_is_end)
					this->_current = this->_current->prev;
				this->_is_end = false;
				return iterator(tmp, false);
			}
		};

		class const_reverse_iterator : public const_iterator {
			const_reverse_iterator() : const_iterator() {}
			const_reverse_iterator(const const_reverse_iterator& src) { *this = src; }
			const_reverse_iterator& operator=(const const_reverse_iterator& rhs) {
				if (this != &rhs) {
					this->_current = rhs._current;
					this->_is_end = rhs._is_end;
				}
				return *this;
			}
			virtual ~const_reverse_iterator() {}
		};

		class reverse_iterator : public const_iterator {
			reverse_iterator() : const_iterator() {}
			reverse_iterator(const reverse_iterator& src) { *this = src; }
			reverse_iterator& operator=(const reverse_iterator& rhs) {
				if (this != &rhs) {
					this->_current = rhs._current;
					this->_is_end = rhs._is_end;
				}
				return *this;
			}
			virtual ~reverse_iterator() {}

			reverse_iterator& operator++() {
				if (this->_current->prev)
					this->_current = this->_current->prev;
				else
					this->_is_end = true;
				return *this;
			}
			reverse_iterator operator++(int) {
				t_list* tmp = this->_current;
				bool tmp_bool = this->_is_end;

				if (this->_current->prev)
					this->_current = this->_current->prev;
				else
					this->_is_end = true;
				return reverse_iterator(tmp, tmp_bool);
			}
			reverse_iterator& operator--() {
				if (this->_current->next && !this->_is_end)
					this->_current = this->_current->next;
				this->_is_end = false;
				return *this;
			}
			reverse_iterator operator--(int) {
				t_list* tmp = this->_current;
				if (this->_current->next && !this->_is_end)
					this->_current = this->_current->next;
				this->_is_end = false;
				return reverse_iterator(tmp, false);
			}
		};

		/* Member functions
		 *
		 *
		 */
		List() : _begin(NULL), _end(NULL), _count(0),
			_default_ptr(new T()), _default_ref(*_default_ptr) {
		}

		List(const List &src) {
			this->_deep_copy(src);
		}

		List& operator=(const List &rhs) {
			if (this != &rhs)
				this->_deep_copy(rhs);
			return *this;
		}

		virtual ~List() {
			this->clear();
			delete _default_ptr;
		}

		void assign( size_t count, const T& value ) {
			if (_begin)
				this->clear();
			for (size_t i = 0; i < count; i++)
				this->push_back(value);
		}

		/* Member functions : Element access
		 *
		 *
		 *
		 */

		reference front() {
			return _begin ? _begin->content : _default_ref;
		}
		const_reference front() const {
			return _begin ? _begin->content : _default_ref;
		}
		reference back() {
			return _end ? _end->content : _default_ref;
		}
		const_reference back() const {
			return _end ? _end->content : _default_ref;
		}

		/* Member functions : iterators
		 *
		 *
		 */
		iterator begin() {
			return iterator(_begin, _count == 0);
		}
		const_iterator begin() const {
			return const_iterator(_begin, _count == 0);
		}
		iterator end() {
			return iterator(_end, true);
		}
		const_iterator end() const {
			return const_iterator(_end, true);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(_end, _count == 0);
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(_end, _count == 0);
		}
		reverse_iterator rend() {
			return reverse_iterator(_begin, true);
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(_begin, true);
		}

		/* Member functions : capacity
		 *
		 *
		 *
		 */
		size_t size() {
			return this->_count;
		}
		bool empty() {
			return _count == 0;
		}
		size_type max_size() const {
			return std::numeric_limits<difference_type>::max();
		}


		/* Member functions : modifiers
		 *
		 *
		 *
		 */

		void clear() {
			t_list* track = _begin;
			t_list* tmp;
			while(track)
			{
				tmp = track->next;
				delete track;
				track = tmp;
			}
			_begin = NULL;
			_end = NULL;
			_count = 0;
		}

		iterator insert( iterator pos, const T& value ) {
			if (pos == begin()) {
				push_front(value);
				return begin();
			}
			else if (pos == end()) {
				push_back(value);
				return (iterator(_end, 0));
			}
			else {
				t_list* new_el = new t_list(value);
				t_list *el_pos = pos.dereference();

				if (el_pos) {
					t_list *prev = el_pos->prev;
					if (prev)
						prev->next = new_el;
					el_pos->prev = new_el;
					new_el->prev = prev;
				} else
					new_el->prev = NULL;
				new_el->next = el_pos;
				_count += 1;
				return iterator(new_el, 0);
			}
		}

		void insert( iterator pos, size_t count, const T& value ) {
			for (size_t i = 0; i < count; i++)
				insert(pos + i, value);
		}

		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last) {
			for (InputIt it = first; it != last; it++)
				insert(pos, *it);
		}

		iterator erase( iterator pos ) {
			if (pos == begin()) {
				pop_front();
				return begin();
			}
			else if (pos == end()) {
				pop_back();
				return end();
			}
			else {
				t_list *el_pos = pos.dereference();
				t_list *prev = el_pos->prev;
				t_list *next = el_pos->next;
				prev->next = next;
				next->prev = prev;
				delete el_pos;
				_count -= 1;
				return iterator(next, 0);
			}
		}

		iterator erase( iterator first, iterator last ) {
			for (iterator it = first; it != last; it++)
				erase(it);
		}

		void push_back( const T& value ) {
			t_list* new_el = new t_list(value);

			if (!_begin) {
				_begin = new_el;
				_end = _begin;
			}
			else {
				_end->next = new_el;
				new_el->prev = _end;
				_end = new_el;
			}
			_count += 1;
		}

		void pop_back() {
			t_list* tmp;

			if (_end) {
				tmp = _end->prev;
				tmp->next = NULL;
				delete _end;
				_end = tmp;
				_count -= 1;
			}
		}

		void push_front( const T& value ) {
			t_list *new_el = new t_list(value);

			if (!_begin) {
				_begin = new_el;
				_end = new_el;
			}
			else {
				_begin->prev = new_el;
				new_el->next = _begin;
				_begin = new_el;
			}
			_count += 1;
		}
		void pop_front() {
			t_list* tmp;

			if (_begin) {
				tmp = _begin->next;
				tmp->prev = NULL;
				delete _begin;
				_begin = tmp;
				_count -= 1;
			}
		}

		void resize( size_t count, T value = T() ) {
			if (count < _count) {
				for(size_t i = 0; i < count - _count; i++)
					this->pop_back();
			}
			else {
				for(size_t i = 0; i < _count - count; i++)
					this->push_back(value);
			}
		}

		void swap( List& other ) {
			t_list* tmp;
			size_t tmp_count;

			tmp = _begin;
			_begin = other._begin;
			other._begin = tmp;
			tmp = _end;
			_end = other._end;
			other._end = tmp;
			tmp_count = _count;
			_count = other._count;
			other._count = tmp_count;
		}

		/* Member functions : operations
		 *
		 *
		 */

		template <class Compare>
		void merge( List& other, Compare comp ) {
			if (this != &other && other._begin) {
				t_list* track_other = other._begin;
				t_list* track_this = _begin;
				t_list* tmp;
				if (_begin) {
					while (track_other && track_this) {
						if (comp(track_other->content, track_this->content)) {
							if (track_this == _begin)
								_begin = other._begin;
							tmp = track_other->next;
							track_other->next = track_this;
							track_other->prev = track_this->prev;
							if (track_this->prev)
								track_this->prev->next = track_other;
							track_this->prev = track_other;
							track_other = tmp;
						}
						else
							track_this = track_this->next;
					}
					if(!track_this && track_other) {
						_end->next = track_other;
						track_other->prev = _end;
						_end = other._end;
					}
					_count += other._count;
				} else {
					_begin = other._begin;
					_end = other._end;
					_count = other._count;
				}
				_empty_container(other);
			}
		}

		void merge( List& other ) {
			cmp_merge cmp;
			merge(other, cmp);
		}

		void splice( const_iterator pos, List& other ) {
			if (*this != other) {
				if (pos == end()) {
					_end->next = other._begin;
					other._begin->prev = _end;
					_end = other._end;
				} else if (pos == begin()) {
					_begin->prev = other._end;
					other._end->next = _begin;
					_begin = other._begin;
				} else {
					t_list* el_pos = pos.dereference();
					t_list* tmp = el_pos->prev;
					el_pos->prev = other._end;
					tmp->next = other._begin;
					other._begin->prev = tmp;
					other._end->next = el_pos;
				}
				_count += other.size();
				_empty_container(other);
			}
		}

		void splice( const_iterator pos, List& other, const_iterator it ) {
			if (*this != other) {
				t_list* to_insert = _detach_element(other, it);
				if (pos == end()) {
					_end->next = to_insert;
					to_insert->prev = _end;
					_end = to_insert;
				} else if (pos == begin()) {
					_begin->prev = to_insert;
					to_insert->next = _begin;
					_begin = to_insert;
				} else {
					t_list* el_pos = pos.dereference();
					t_list* tmp = el_pos->prev;
					el_pos->prev = to_insert;
					to_insert->next = el_pos;
					to_insert->prev = tmp;
					tmp->next = to_insert;
				}
				_count += 1;
			}
		}

		void splice( const_iterator pos, List& other,
					 const_iterator first, const_iterator last) {
			(void)pos;
			(void)other;
			(void)first;
			(void)last;
			//TODO; implement
		}

		template< class UnaryPredicate >
		void remove_if( UnaryPredicate p ) {
			t_list* track = _begin;
			t_list* tmp;

			while(track) {
				if (p(track->content)) {
					tmp = track->next;
					if (_begin == track)
						_begin = track->next;
					if (_end == track)
						_end = track->prev;
					if (track->prev)
						track->prev->next = track->next;
					if (track->next)
						track->next->prev = track->prev;
					delete track;
					track = tmp;
					_count -= 1;
				}
				else
					track = track->next;
			}
		}
		void remove( const T& value ) {
			cmp_unary cmp(value);
			remove_if(cmp);
		}

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

		template< class BinaryPredicate >
		void unique( BinaryPredicate p ) {
			t_list* track = _begin;
			t_list* tmp;
			while(track) {
				tmp = track->next;
				if (track->prev && p(track->prev->content, track->content)) {
					if (!track->next)
						_end = track->prev;
					track->prev->next = track->next;
					if (track->next)
						track->next->prev = track->prev;
					delete track;
					_count -= 1;
				}
				track = tmp;
			}
		}

		void unique() {
			cmp_unique cmp;
			unique(cmp);
		}
		void sort() {
			//TODO:implement
		}
		/*void sort() {
			t_list* track = _begin;
			t_list* next;
			t_list* tmp;
			while(track && track->next) {
				next = track->next;
				while(next) {
					if (track->content > next->content) {
						if (track == _begin)
							_begin = next;
						if (next == _end)
							_end = track;
						tmp = next->next;
						next->next = track;
						next->prev = track->prev;
						track->next = tmp;
						track->prev = next;
					}
					next = next->next;
				}
				track = track->next;
			}
		}*/


	private:
		//private function members
		void _deep_copy(const List& src) {
			t_list* track = src._begin;
			_count = src._count;
			if (_begin)
				this->clear();
			if (_default_ptr)
				delete _default_ptr;
			while(track) {
				this->push_back(track->content);
				track = track->next;
			}
			_default_ptr = new T();
			_default_ref = *_default_ptr;
		}

		void _empty_container(List& c) {
			c._begin = NULL;
			c._end = NULL;
			c._count = 0;
		}

		t_list* _detach_element(List& other, const_iterator it) {
			t_list* el_ret = it.dereference();
			t_list* tmp_next = el_ret->next;
			t_list* tmp_prev = el_ret->prev;
			if (el_ret == other._begin)
				other._begin = tmp_next;
			else if (el_ret == other._end)
				other._end = tmp_prev;
			if (tmp_next)
				tmp_next->prev = tmp_prev;
			if (tmp_prev)
				tmp_prev->next = tmp_next;
			other._count -= 1;
			return el_ret;
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

		/* private attributes
		 *
		 *
		 *
		 */
		t_list* _begin;
		t_list* _end;
		size_t _count;
		T* _default_ptr;
		T& _default_ref;



		/* non-member functions
		 *
		 *
		 *
		 */
		friend bool operator==(const List<T>& lhs, const List<T>& rhs) {
			t_list* track_lhs = lhs._begin;
			t_list* track_rhs = rhs._begin;
			while (track_lhs && track_rhs
				&& track_lhs->content == track_rhs->content) {
				track_lhs = track_lhs->next;
				track_rhs = track_rhs->next;
			}
			return !track_lhs && !track_rhs;
		}

		friend bool operator!=(const List<T>& lhs, const List<T>& rhs) {
			t_list* track_lhs = lhs._begin;
			t_list* track_rhs = rhs._begin;
			while (track_lhs && track_rhs
				&& track_lhs->content == track_rhs->content) {
				track_lhs = track_lhs->next;
				track_rhs = track_rhs->next;
			}
			return track_lhs || track_rhs;
		}

		friend bool operator<(const List<T>& lhs, const List<T>& rhs) {
			t_list* track_lhs = lhs._begin;
			t_list* track_rhs = rhs._begin;
			while (track_lhs && track_rhs
				   && track_lhs->content == track_rhs->content) {
				track_lhs = track_lhs->next;
				track_rhs = track_rhs->next;
			}
			if (!track_lhs && !track_rhs)
				return (false);
			return track_lhs->content < track_rhs->content;
		}

		friend bool operator<=(const List<T>& lhs, const List<T>& rhs) {
			t_list* track_lhs = lhs._begin;
			t_list* track_rhs = rhs._begin;
			while (track_lhs && track_rhs
				   && track_lhs->content == track_rhs->content) {
				track_lhs = track_lhs->next;
				track_rhs = track_rhs->next;
			}
			if (!track_lhs && !track_rhs)
				return (true);
			return track_lhs->content < track_rhs->content;
		}

		friend bool operator>(const List<T>& lhs, const List<T>& rhs) {
			t_list* track_lhs = lhs._begin;
			t_list* track_rhs = rhs._begin;
			while (track_lhs && track_rhs
				   && track_lhs->content == track_rhs->content) {
				track_lhs = track_lhs->next;
				track_rhs = track_rhs->next;
			}
			if (!track_lhs && !track_rhs)
				return (false);
			return track_lhs->content > track_rhs->content;
		}

		friend bool operator>=(const List& lhs, const List& rhs) {
			t_list* track_lhs = lhs._begin;
			t_list* track_rhs = rhs._begin;
			while (track_lhs && track_rhs
				   && track_lhs->content == track_rhs->content) {
				track_lhs = track_lhs->next;
				track_rhs = track_rhs->next;
			}
			if (!track_lhs && !track_rhs)
				return (true);
			return track_lhs->content > track_rhs->content;
		}
	};

	template<class T>
	void swap(List<T>& lhs, List<T>& rhs) {
		lhs.swap(rhs);
	}
}

#endif
