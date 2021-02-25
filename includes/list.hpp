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
# include <stdexcept>
# include <iostream>
//TODO: suppress iostream

namespace ft {
	template<typename T>
	class list {
	public:
		typedef struct	s_list {
			explicit s_list(const T& value) : content(value),
				next(NULL), prev(NULL) {}
			T				content;
			struct s_list	*next;
			struct s_list	*prev;
		}				t_list;
		list() : _begin(NULL), _end(NULL), _count(0),
			_default_ptr(new T()), _default_ref(*_default_ptr) {}

		list(const list &src) { this->_deep_copy(src); }

		list& operator=(const list &rhs) {
			if (this != &rhs)
				this->_deep_copy(rhs);
			return *this;
		}

		//TODO : suppress
		const T& operator[](int idx) {
			t_list* track = _begin;
			for(int i = 0; i < idx; i++) {
				if (!track)
					break;
				track = track->next;
			}
			if (track)
				return track->content;
			else
				throw ElementNotFoundException();
		}
		//TODO : suppress

		virtual ~list() {
			this->clear();
			delete _default_ptr;
		}

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

		void assign( size_t count, const T& value ) {
			if (_begin)
				this->clear();
			for (size_t i = 0; i < count; i++)
				this->push_back(value);
		}

		T& front() { return _begin ? _begin->content : _default_ref; }
		T& back() { return _end ? _end->content : _default_ref; }
		//TODO: const front & back

		size_t size() { return this->_count; }
		bool empty() { return _count == 0; }
		//TODO: max_size

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

		void swap( list& other ) {
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

		template <class Compare>
		void merge( list& other, Compare comp ) {
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
				other._begin = NULL;
				other._end = NULL;
				other._count = 0;
			}
		}

		void merge( list& other ) {
			cmp_merge cmp;
			merge(other, cmp);
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

		bool operator==(const list& rhs) {
			t_list* track_this = _begin;
			t_list* track_rhs = rhs._begin;
			while (track_this && track_rhs) {
				if (track_this->content != track_rhs->content)
					return false;
				track_this = track_this->next;
				track_rhs = track_rhs->next;
			}
			return !track_this && !track_rhs;
		}
		bool operator!=(const list& rhs) {
			t_list* track_this = _begin;
			t_list* track_rhs = rhs._begin;
			while (track_this && track_rhs) {
				if (track_this->content != track_rhs->content)
					return true;
				track_this = track_this->next;
				track_rhs = track_rhs->next;
			}
			return track_this || track_rhs;
		}
		bool operator<(const list& rhs) {
			t_list* track_this = _begin;
			t_list* track_rhs = rhs._begin;
			while (track_this && track_rhs) {
				if (track_this->content < track_rhs->content)
					return true;
				track_this = track_this->next;
				track_rhs = track_rhs->next;
			}
			return track_rhs != NULL;
		}
		bool operator<=(const list& rhs) {
			t_list* track_this = _begin;
			t_list* track_rhs = rhs._begin;
			while (track_this && track_rhs) {
				if (track_this->content <= track_rhs->content)
					return true;
				track_this = track_this->next;
				track_rhs = track_rhs->next;
			}
			return track_rhs != NULL;
		}
		bool operator>(const list& rhs) {
			t_list* track_this = _begin;
			t_list* track_rhs = rhs._begin;
			while (track_this && track_rhs) {
				if (track_this->content > track_rhs->content)
					return true;
				track_this = track_this->next;
				track_rhs = track_rhs->next;
			}
			return track_this != NULL;
		}
		bool operator>=(const list& rhs) {
			t_list* track_this = _begin;
			t_list* track_rhs = rhs._begin;
			while (track_this && track_rhs) {
				if (track_this->content >= track_rhs->content)
					return true;
				track_this = track_this->next;
				track_rhs = track_rhs->next;
			}
			return track_this != NULL;
		}

   
	private:
		void _deep_copy(const list & src) {
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

		class ElementNotFoundException : public std::exception {
			virtual const char* what() const throw() {
				return "element not found";
			}
		};

		t_list* _begin;
		t_list* _end;
		size_t _count;
		T* _default_ptr;
		T& _default_ref;
	};
}

#endif
