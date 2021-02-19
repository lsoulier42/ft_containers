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

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class list {
	public:
		list();
		list(const list & src);
		list& operator=( const list& other );
		virtual ~list();

		//member functions
		void assign( size_type count, const T& value );
		template< class InputIt >
		void assign( InputIt first, InputIt last );

		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
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


		//member types
		typedef T value_type;
		typedef std::allocator<value_type> allocator_type;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;

		BirectionalIterator<value_type> iterator;
		const BirectionalIterator<value_type> const_iterator;
		std::reverse_iterator<iterator> reverse_iterator;
		const std::reverse_iterator<const_iterator> const_reverse_iterator;


	private:
		typedef struct	s_list {
			value_type 		content;
			struct s_list	*next;
			struct s_list	*previous;
		}				t_list;
		t_list*			_begin;
		size_t			_count;
	};
}

#endif
