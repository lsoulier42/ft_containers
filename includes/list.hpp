/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:14:46 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/19 13:15:06 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP
# include <memory>
# include <iterator>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class list {
	public:
		list() : _begin(NULL), _end(NULL), _count(0) {
		}

		list(const list & src) : _count(src._count) {
			if (this->_begin)
				this->clear();
			t_list* track = src._begin;
			this->_begin = NULL;
			while(track)
			{
				this->push_back(track->content);
				track = track->next;
			}
		}

		list& operator=( const list& other ) {
			if (this != &other)
			{
				this->_count = other._count;
				if (this->_begin)
					this->clear();
				t_list* track = other._begin;
				this->_begin = NULL;
				while(track)
				{
					this->push_back(track->content);
					track = track->next;
				}
			}
			return *this;
		}

		virtual ~list() {
			this->clear();
		}

		//member types
		typedef T value_type;
		typedef std::allocator<value_type> allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		/*
		typedef std::iterator<std::bidirectional_iterator_tag, value_type> iterator;
		typedef const std::iterator<std::bidirectional_iterator_tag, value_type> const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef const std::reverse_iterator<const_iterator> const_reverse_iterator;
		*/

		class iterator : public std::iterator<std::bidirectional_iterator_tag,
				value_type, difference_type, pointer, reference> {
			public:
				iterator();
				iterator(const iterator & src);
				iterator & operator=(const iterator & rhs);
				virtual ~iterator();

			private:
				pointer _
		};

		//member functions
		void assign( size_type count, const T& value ) {
			this->clear();
			for(size_type i = 0; i < count; i++)
				this->push_back(value);
		}
		template< class InputIt >
		void assign( InputIt first, InputIt last ) {
			this->clear();
			for(InputIt it = first; it != last; it++)
				this->push_back(*it);
		}

		reference front() {	return *(this->_begin);	}
		const_reference front() const {	return const_cast<const_reference>(*(this->_begin)); }
		reference back() { return *(this->_end); }
		const_reference back() const { return const_cast<const_reference>(*(this->_end)); }

		iterator begin() {
			iterator ret;


		}
		const_iterator begin() const { return this->_begin; }
		iterator end() { return this->_end; }
		const_iterator end() const { return this->_end; }
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		bool		empty() const;
		size_type	size() const;
		size_type	max_size() const;

		void clear();
		iterator insert( iterator pos, const T& value );
		void insert( iterator pos, size_type count, const T& value );
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last);
		iterator erase( iterator pos );
		iterator erase( iterator first, iterator last );
		void push_back( const T& value );
		void pop_back();
		void push_front( const T& value );
		void pop_front();
		void resize( size_type count, T value = T() );
		void swap( list& other );

		void merge( list& other );
		template <class Compare>
		void merge( list& other, Compare comp );
		void splice( const_iterator pos, list& other );
		void splice( const_iterator pos, list& other, const_iterator it );
		void splice( const_iterator pos, list& other,
			const_iterator first, const_iterator last);
		void remove( const T& value );
		template< class UnaryPredicate >
		void remove_if( UnaryPredicate p );
		void reverse();
		void unique();
		template< class BinaryPredicate >
		void unique( BinaryPredicate p );

		void sort();
		template< class Compare >
		void sort( Compare comp );


	private:
		typedef struct	s_list {
			const T &		content;
			struct s_list	*next;
			struct s_list	*previous;
		}				t_list;
		t_list*			_begin;
		t_list*			_end;
		size_type 		_count;
	};
}

#endif
