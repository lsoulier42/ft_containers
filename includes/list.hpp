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
			s_list(const T& value) : content(value) {}
			const T &		content;
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

		virtual ~list() {
				this->clear();
		}

		void clear() {
			//TODO
		}

		void push_back( const T& value ) {
			t_list* new_el = new t_list(value);
			new_el->next = NULL;
			if (!_begin) {
				new_el->prev = NULL;
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
		void pop_back();
		void push_front( const T& value );
		void pop_front();

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
