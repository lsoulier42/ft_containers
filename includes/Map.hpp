/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
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
# include "Iterator.hpp"
# include "enable_if.hpp"
# include "pair.hpp"
# include "less.hpp"

namespace ft {
	/* Base structure : binary search tree
	 *
	 *
	 */
	template<class T>
	struct bstree {
		T content;
		bstree* parent;
		bstree* left;
		bstree* right;
	};

    template< class Key, class T,
        class Compare = ft::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> >
    > class Map {
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
         * //TODO: implement
         *
         */

        class const_iterator;
        class iterator;

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
		Map() {
			_init_constructor(Compare(), Allocator());
		}
		explicit Map( const Compare& comp,
					  const Allocator& alloc = Allocator() ) {
			_init_constructor(comp, alloc);
		}
		template< class InputIt >
		Map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) {
			_init_constructor(comp, alloc);
			for (InputIt it = first; it != last; it++)
				this->insert(*it);
		}
		Map( const Map& other ) { *this = other; }
		~Map() {
			this->clear();
		}
		/* Member functions : assignation operator
		 *
		 *
		 */
		Map& operator=( const Map& other ) {
			if (!this->empty())
				this->clear();
			if (this != &other) {
				_comp_key_less = other._comp_key_less;
				_comp_pair_less = other._comp_pair_less;
				_comp_pair_equal = other._comp_pair_equal;
				_a_type = other._a_type;
				_a_node = other._a_node;
				_root = other._root;
				_size = other._size;
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
				return (*it).second;
		}

		/* Iterator functions
		 *
		 */
		iterator begin() {
			return iterator(_root);
		}
		const_iterator begin() const {
			return const_iterator(_root);
		}
		iterator end() {
			return iterator(_last_node()->left);
		}
		const_iterator end() const {
			return const_iterator(_last_node()->left);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(_last_node()->left);
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(_last_node()->left);
		}
		reverse_iterator rend() {
			return reverse_iterator(_root);
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(_root);
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
			return std::numeric_limits<difference_type>::max();
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
			_size = 0;
		}

    private:
    	void _init_constructor(const Compare& comp,
			const Allocator& alloc) {
			_comp_key_less = comp;
			_comp_pair_less = value_compare(_comp_key_less);
			_a_type = alloc;
			_root = NULL;
			_size = 0;
		}

		bstree* _create_node(const value_type& content) {
			bstree* new_node = _a_node.allocate(1);
			_a_type.construct(&new_node->content, content);
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->parent = NULL;
		}

		void _erase_node(bstree* node) {
			_a_type.destroy(&node->content);
			_a_node.deallocate(node);
		}

		bstree* _search(const value_type& content, bstree* node) {
			if (node == NULL || _comp_pair_equal(content, node->content))
				return node;
			else if (_comp_pair_less(content, node->content))
				return _search(content, node->left);
			else
				return _search(content, node->right);
		}
		bstree* _search(const value_type& content) {
			if (!_root)
				return NULL;
			return _search(content, _root);
		}

		bstree* _insert(const value_type& content, bstree* node) {
			if (!node)
				return NULL;
			if (!node->left) {
				node->left = _create_node(content);
				node->left->parent = node;
				return node->left;
			}
			else if (!node->right) {
				node->right = _create_node(content);
				node->right->parent = node;
				return node->right;
			}
			else if (_comp_pair_less(content, node->content))
				return _insert(content, node->left);
			else if (!_comp_pair_equal(content, node->content))
				return _insert(content, node->right);
			return node;
		}
		bstree* _insert(const value_type& content) {
			return _insert(content, _root);
		}

		bstree* _last_node(bstree* node) {
			bstree* last = node;

			if (node->left)
				last = _last_node(node->left);
			if (node->right)
				last = _last_node(node->right);
			return last;
		}

		bstree* _last_node() {
			return _root ? _last_node(_root) : NULL;
		}

		bstree* _delete_node(const value_type& content, bstree* root) {
			if (root == NULL)
				return root;
			if (_comp_pair_less(content, root->content)) {
				root->left = _delete_node(content, root->left);
				return root;
			}
			else if (_comp_pair_less(root->content, content)) {
				root->right = _delete_node(content, root->right);
				return root->right;
			}

			//case one child empty
			if (root->left == NULL) {
				bstree* tmp = root->right;
				bstree* tmpgp = root->parent;
				_erase_node(root);
				tmp->parent = tmpgp;
				return tmp;
			}
			else if (root->right == NULL) {
				bstree* tmp = root->left;
				bstree* tmpgp = root->parent;
				_erase_node(root);
				tmp->parent = tmpgp;
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

				//then delete successor
				if (successor_parent != root)
					successor_parent->left = successor->right;
				else
					successor_parent->right = successor->right;
				successor->right->parent = successor_parent;
				root->content = successor->content;
				_erase_node(successor);
				return root;
			}
		}
		bstree* _delete_node(const value_type& content) {
			return _delete_node(content, _root);
		}

		void _clear_tree(bstree* node) {
			if (node->left)
				_clear_tree(node->left);
			if (node->right)
				_clear_tree(node->right);
			_erase_node(node);
		}

		class _comp_equal {
		public:
			_comp_equal() {}
			~_comp_equal() {}

			bool operator()( const value_type& lhs, const value_type& rhs ) const {
				return lhs.first == rhs.first;
			}
		};

		Compare _comp_key_less;
		value_compare _comp_pair_less;
		_comp_equal _comp_pair_equal;
    	Allocator _a_type;
		typename Allocator::template rebind<bstree>::other _a_node;
		bstree* _root;
		size_type _size;
    };

}

#endif
