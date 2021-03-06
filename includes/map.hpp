/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:33:49 by louise            #+#    #+#             */
/*   Updated: 2021/03/13 10:33:50 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <iostream>
# include <limits>
# include "iterator.hpp"
# include "enable_if.hpp"
# include "pair.hpp"
# include "comparison.hpp"

namespace ft {
    template< class Key, class T,
        class Compare = ft::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> >
    > class map {
    public:
        /* Member types
         *
         *
         *
         */

        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
		typedef bstree<value_type> bstree;

        /* Iterators
         *
         *
         */

		typedef mapIterator<value_type> iterator;
		typedef mapConstIterator<value_type> const_iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

		/* Member classes : value_compare
		 * compares objects of type value_type
		 *
		 */
		class value_compare {
		public:
			explicit value_compare( Compare c ) : comp(c) {}

			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()( const value_type& lhs, const value_type& rhs ) const {
				return comp(lhs.first, rhs.first);
			}

		protected:
			Compare comp;
		};

		/* Member functions : constructors
		 *
		 *
		 */
		map() {
			_init_constructor(Compare(), Allocator());
		}
		explicit map( const Compare& comp,
					  const Allocator& alloc = Allocator() ) {
			_init_constructor(comp, alloc);
		}
		template< class InputIt >
		map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) {
			_init_constructor(comp, alloc);
			for (InputIt it = first; it != last; it++)
				this->insert(*it);
		}
		map( const map& other ) {
			_init_constructor(Compare(), Allocator());
			this->_deep_copy(other);
		}
		~map() {
			this->clear();
			this->_free_node(_end);
		}
		/* Member functions : assignation operator
		 *
		 *
		 */

		map& operator=( const map& other ) {
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

		/* Member functions : operator[]
		 * Returns a reference to the value that is mapped to a key equivalent to key,
		 * performing an insertion if such key does not already exist.
		 *
		 */
		T& operator[]( const Key& key ) {
			iterator it = this->find(key);
			if (it == this->end())
				return this->insert(ft::make_pair(key, T())).first->second;
			else
				return it->second;
		}

		/* Iterator functions
		 *
		 */
		iterator begin() {
			bstree* first_element = _root;
			while (first_element->left)
				first_element = first_element->left;
			return iterator(first_element);
		}
		const_iterator begin() const {
			bstree* first_element = _root;
			while (first_element->left)
				first_element = first_element->left;
			return const_iterator(first_element);
		}
		iterator end() {
			return iterator(_end);
		}
		const_iterator end() const {
			return const_iterator(_end);
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

		/* Member functions : empty(), size(), max_size()
		 * 1/Checks if the container has no elements
		 * 2/Returns the number of elements in the container
		 * 3/Returns the maximum number of elements the container is able to hold
		 * due to system or library implementation limitations
		 */
		bool empty() const {
			return _size == 0;
		}
		size_type size() const {
			return _size;
		}

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
				return;
			this->_clear_tree(_root);
			_root = _end;
			_end->parent = NULL;
			_already_present = NULL;
			_last_created = NULL;
			_size = 0;
		}

		/* Member functions : insert()
		 * Inserts element(s) into the container,
		 * if the container doesn't already contain an element with an equivalent key.
		 *
		 */

		ft::pair<iterator,bool> insert( const value_type& value ) {
			size_type old_size = _size;
			bstree* node;
			this->_insert(value, _root);
			node = _size != old_size ? _last_created : _already_present;
			if (_root == _end) {
				_root = node;
				_root->right = _end;
				_end->parent = _root;
			}
			return ft::make_pair(iterator(node), _size != old_size);
		}

		iterator insert( iterator hint, const value_type& value ) {
			size_type old_size = _size;
			bstree* node;
			bstree* root = hint._node;
			while (root->parent)
				root = root->parent;
			this->_insert(value, root);
			node = _size != old_size ? _last_created : _already_present;
			if (_root == _end) {
				_root = node;
				_root->right = _end;
				_end->parent = _root;
			}
			return iterator(node);
		}
		template< class InputIt >
		void insert( InputIt first, InputIt last ) {
			for (InputIt it = first; it != last; it++)
				insert(*it);
		}

		/* Member functions : erase()
		 * Removes specified elements from the container.
		 *
		 */
        void erase( iterator pos ) {
        	erase(pos._node->content.first);
        }
        void erase( iterator first, iterator last ) {
            for (iterator it = first; it != last; it++)
                erase(it._node->content.first);
        }
		size_type erase( const key_type& key ) {
        	size_type old_size = _size;
			this->_delete_node(key);
        	return _size != old_size;
        }

        /* Member functions : swap()
         * Exchanges the contents of the container with those of other.
         *
         */
        void swap( map& other ) {
			bstree* root_tmp = _root;
			_root = other._root;
			other._root = root_tmp;

			bstree* last_created_tmp = _last_created;
			_last_created = other._last_created;
			other._last_created = last_created_tmp;

			bstree* already_present_tmp = _already_present;
			_already_present = other._already_present;
			other._already_present = already_present_tmp;

			bstree* end_tmp = _end;
			_end = other._end;
			other._end = end_tmp;

			size_type size_tmp = _size;
			_size = other._size;
			other._size = size_tmp;
        }

        /* Member functions: count()
         * Returns the number of elements with key that compares equivalent to the specified argument,
         * which is either 1 or 0 since this container does not allow duplicates.
         */
        size_type count( const Key& key ) const {
            return find(key) != end();
        }

        iterator find( const Key& key ) {
            bstree* found = _search(key);
            return (found != NULL && found != _end ? iterator(found) : end());
        }
        const_iterator find( const Key& key ) const {
            bstree* found = _search(key);
            return found != NULL && found != _end ? const_iterator(found) : end();
        }

        /* Member functions : equal_range()
         * Returns a range containing all elements with the given key in the container.
         * The range is defined by two iterators, one pointing to the first element that is not less than key
         * and another pointing to the first element greater than key.
         *
         */
    	ft::pair<iterator,iterator> equal_range( const Key& key ) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }
    	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
			return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        /* Member functions : lower_bound()
         * Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
         *
         */
        iterator lower_bound( const Key& key ) {
			iterator it = begin();
			while (it != end()) {
				if (it->first == key || !_comp_key_less(it->first, key))
					return it;
				it++;
			}
			return end();
        }
        const_iterator lower_bound( const Key& key ) const {
			const_iterator it = begin();
			while (it != end()) {
				if (it->first == key || !_comp_key_less(it->first, key))
					return it;
				it++;
			}
			return end();
        }

        /* Member functions : upper_bound()
         *
         *
         */
        iterator upper_bound( const Key& key ) {
			iterator it = begin();
			while (it != end()) {
				if (!_comp_key_less(it->first, key) && it->first != key)
					return it;
				it++;
			}
			return end();
        }
        const_iterator upper_bound( const Key& key ) const {
			const_iterator it = begin();
			while (it != end()) {
				if (!_comp_key_less(it->first, key) && it->first != key)
					return it;
				it++;
			}
			return end();
        }

        /* Observers : key_comp()
         * Returns the function object that compares the keys,
         * which is a copy of this container's constructor argument comp.
         *
         */
        key_compare key_comp() const {
            return _comp_key_less;
        }

        /* Observers : value_comp()
         * Returns a function object that compares objects
         * of type std::map::value_type (key-value pairs) by using key_comp to compare the first components of the pairs.
         */
        value_compare value_comp() const {
            return value_compare(_comp_key_less);
        }

    private:

    	void _init_constructor(const Compare& comp,
			const Allocator& alloc) {
			_comp_key_less = comp;
			_a_type = alloc;
			_root = _create_node(ft::make_pair(key_type(), mapped_type()));
			_last_created = NULL;
			_already_present = NULL;
			_end = _root;
			_size = 0;
		}

		bstree* _create_node(const value_type& content) {
			bstree* new_node = _a_node.allocate(1);
			_a_type.construct(&new_node->content, content);
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->parent = NULL;
			return new_node;
		}

		void _free_node(bstree* node) {
			_a_type.destroy(&node->content);
			_a_node.deallocate(node, 1);
		}

		bstree* _search(const Key& key, bstree* node) const {
			if (!node || node == _end
				|| (node != NULL && node != _end && key == node->content.first))
				return node;
			else if (_comp_key_less(key, node->content.first))
				return _search(key, node->left);
			else
				return _search(key, node->right);
		}
		bstree* _search(const Key& key) const {
			return _search(key, _root);
		}

		bstree* _insert(const value_type& content, bstree* node) {
			if (node == NULL || node == _end) {
				_size += 1;
				_last_created = _create_node(content);
				if (node == _end) {
					_end->parent = _last_created;
					_last_created->right = _end;
				}
				return _last_created;
			}
			if (_comp_key_less(content.first, node->content.first)) {
				bstree* left_child = _insert(content, node->left);
				node->left = left_child;
				left_child->parent = node;
			}
			else if (content.first != node->content.first) {
				bstree* right_child = _insert(content, node->right);
				node->right = right_child;
				right_child->parent = node;
			}
			else
				_already_present = node;
			return node;
		}

		bstree* _delete_node(const key_type& key , bstree* root) {
			//key not found
			if (root == NULL || root == _end)
				return root;

			//search the node
			if (_comp_key_less(key, root->content.first)) {
				root->left = _delete_node(key, root->left);
				return root;
			}
			else if (_comp_key_less(root->content.first, key)) {
				root->right = _delete_node(key, root->right);
				return root;
			}

			_size -= 1;
			//case no child
			if (!root->left && !root->right) {
				if (root == _root)
					_root = _end;
				this->_free_node(root);
				return NULL;
			} else if (!root->left || !root->right) {
				bstree* tmp = root->left == NULL ? root->right : root->left;
				tmp->parent = root->parent;
				if (root == _root)
					_root = tmp;
				this->_free_node(root);
				return tmp;
			}
			else { // case both children exist
				bstree* successor_parent = root;

				//first start by finding successor,
				// ie. the first element with no left child (so the smallest)
				bstree* successor = root->right;
				while (successor->left != NULL) {
					successor_parent = successor;
					successor = successor->left;
				}
				if (successor_parent != root)
					successor_parent->left = successor->right;
				else
					successor_parent->right = successor->right;
				if (successor->right)
					successor->right->parent = successor_parent;

				successor->right = root->right;
				if (successor->right)
					successor->right->parent = successor;
				successor->left = root->left;
				if (successor->left)
					successor->left->parent = successor;
				successor->parent = root->parent;
				if (root == _root)
					_root = successor;
				this->_free_node(root);
				return successor;
			}
		}
		bstree* _delete_node(const key_type& key) {
			return _delete_node(key, _root);
		}

		void _clear_tree(bstree* node) {
			if (node->left)
				_clear_tree(node->left);
			if (node->right && node->right != _end)
				_clear_tree(node->right);
			this->_free_node(node);
		}

		void _deep_copy(const map& other) {
    		_comp_key_less = other._comp_key_less;
    		_a_type = other._a_type;
    		_a_node = other._a_node;
			for(const_iterator it = other.begin(); it != other.end(); it++)
				this->insert(*it);
    	}

		/* private attributes
		 *
		 *
		 *
		 */

		Compare _comp_key_less;
    	Allocator _a_type;
		typename Allocator::template rebind<bstree>::other _a_node;
		bstree* _root;
		bstree* _last_created;
		bstree* _already_present;
		bstree* _end;
		size_type _size;
	};

    /* Non member functions : comparison operators
     * Checks if the contents of lhs and rhs are equal,
     * that is, they have the same number of elements
     * and each element in lhs compares equal with the element in rhs at the same position.
     *
     */

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
		const ft::map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
					 const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					 const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (lhs == rhs || lhs < rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					 const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs <= rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

	/* Non member functions : ft::swap() map specialization
	 * Swaps the contents of lhs and rhs.
	 *
	 */
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
			   ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}
#endif
