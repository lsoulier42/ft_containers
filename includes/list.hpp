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

namespace ft {
	template<typename T>
	class list {
	public:
		typedef struct	s_list {
			s_list(const T& value) : content(value),
				next(NULL), prev(NULL) {}
			T				content;
			struct s_list	*next;
			struct s_list	*prev;
		}				t_list;
		list() : _begin(NULL), _end(NULL), _count(0) {}

		list(const list &src) { this->_deep_copy(src); }

		list operator=(const list &rhs) {
			if (this != &rhs)
				this->_deep_copy(rhs);
			return *this;
		}

		//doesn't exist in stl
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
		}

		void clear() {
			t_list* track = _begin;
			t_list* tmp;
			while(track)
			{
				tmp = track->next;
				delete [] track;
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

		T& front() { return _begin->content; }
		T& back() { return _end->content; }
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
				delete [] _end;
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
				delete [] _begin;
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
			//TODO understant why ref and iterators keep their values
		}

		//TODO: merge()

		void remove( const T& value ) {
			t_list* track = _begin;
			t_list* tmp;

			while(track) {
				if (track->content == value) {
					tmp = track->next;
					//TODO : reset _begin/ _end if necessary
					if (track->prev)
						track->prev->next = track->next;
					if (track->next)
						track->next->prev = track->prev;
					delete [] track;
					track = tmp;
					_count -= 1;
				}
				else
					track = track->next;
			}

		}


	class ElementNotFoundException : public std::exception {
		virtual const char* what() const throw() {
			return "element not found";
		}
	};

	private:
		void _deep_copy(const list & src);
		t_list* _begin;
		t_list* _end;
		size_t _count;
	};
}

#endif
