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
         *
         *
         */

        class const_iterator : public ft::iterator<bidirectional_iterator_tag, T, difference_type, pointer, reference> {
        public:
            const_iterator() {}
            const_iterator(const const_iterator& src) { *this = src; }
            const_iterator(bstree* x) : _node(x) {}
            virtual ~const_iterator() {}

            reference operator*() {
                return this->_node->content;
            }
            pointer operator->() const {
                return this->_node;
            }
            bool operator==(const const_iterator& rhs) const {
                return (_node == rhs._node);
            }
            bool operator!=(const const_iterator& rhs) const {
                return (_node != rhs._node);
            }

            const_iterator& operator++() { return *this; }
            const_iterator operator++(int) { return *this; }
            const_iterator& operator--() { return *this; }
            const_iterator operator--(int) { return *this; }

            bstree* _node;
        };
        class iterator : public const_iterator {
        public:
            iterator() {}
            iterator(bstree* node) : const_iterator(node) {}
            iterator(const iterator& src) { *this = src; }
            iterator(const const_iterator& other) : const_iterator(other) {}
            iterator& operator=(const iterator& rhs) {
                if (this != &rhs)
                    this->_node = rhs._node;
                return *this;
            }
            virtual ~iterator() {}


            iterator& operator++() {
                if (this->_node) {
                    if (this->_node->left)
                        this->_node = this->_node->left;
                    else if (this->_node->right)
                        this->_node = this->_node->right;
                }
                return *this;
            }
            iterator operator++(int) {
                iterator tmp = *this;
                if (this->_node) {
                    if (this->_node->left)
                        this->_node = this->_node->left;
                    else if (this->_node->right)
                        this->_node = this->_node->right;
                }
                return tmp;
            }
            iterator& operator--() {
                if (this->_node && this->_node->parent)
                    this->_node = this->_node->parent;
                return *this;
            }
            iterator operator--(int) {
                iterator tmp = *this;
                if (this->_node && this->_node->parent)
                    this->_node = this->_node->parent;
                return tmp;
            }
        };

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

		/* Member functions : insert()
		 * Inserts element(s) into the container,
		 * if the container doesn't already contain an element with an equivalent key.
		 *
		 */

		std::pair<iterator,bool> insert( const value_type& value ) {
			if (!_root) {
				_root = _create_node(value);
				_size += 1;
				return ft::make_pair(_root, true);
			} else
				insert(begin(), value);
		}
		iterator insert( iterator hint, const value_type& value ) {
			if (!_root)
				insert(value);
			else {
				bstree* found = _search(value.first, hint._node);
				if (!found) {
					found = this->_insert(value);
					_size += 1;
					return ft::make_pair(found, true);
				}
				return ft::make_pair(iterator(found), false);
			}
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
            bstree* deleted_node = pos._node;
            bstree* new_root = this->_delete_node(*pos);
            if (_root == deleted_node)
                _root = new_root;
            _size -= 1;
        }
        void erase( iterator first, iterator last ) {
            for (iterator it = first; it != last; it++)
                erase(it);
        }

        /* Member functions : swap()
         * Exchanges the contents of the container with those of other.
         *
         */
        void swap( Map& other ) {
            Map tmp = other;
            other = *this;
            *this = tmp;
        }

        /* Member functions: count()
         * Returns the number of elements with key that compares equivalent to the specified argument,
         * which is either 1 or 0 since this container does not allow duplicates.
         */
        size_type count( const Key& key ) const {
            bstree* found = _search(key);
            return found != NULL ? 1 : 0;
        }

        iterator find( const Key& key ) {
            bstree* found = _search(key);
            return found != NULL ? iterator(found) : end();
        }
        const_iterator find( const Key& key ) const {
            bstree* found = _search(key);
            return found != NULL ? const_iterator(found) : end();
        }

        /* Member functions : equal_range()
         * Returns a range containing all elements with the given key in the container.
         * The range is defined by two iterators, one pointing to the first element that is not less than key
         * and another pointing to the first element greater than key.
         *
         */
        std::pair<iterator,iterator> equal_range( const Key& key ) {
            bstree* found = _search(key);
            iterator not_less;
            iterator greater;

            not_less = found && found->parent ? iterator(found) : end();
            greater = found && found->next ? iterator(found->right) : end();
            return ft::make_pair(not_less, greater);
        }
        std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
            bstree* found = _search(key);
            const_iterator not_less;
            const_iterator greater;

            not_less = found && found->parent ? iterator(found) : end();
            greater = found && found->next ? iterator(found->right) : end();
            return ft::make_pair(not_less, greater);
        }

        /* Member functions : lower_bound()
         * Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
         *
         */
        iterator lower_bound( const Key& key ) {
            bstree* found = _search(key);
            iterator not_less;

            not_less = found && found->parent ? iterator(found) : end();
            return not_less;
        }
        const_iterator lower_bound( const Key& key ) const {
            bstree* found = _search(key);
            const_iterator not_less;

            not_less = found && found->parent ? iterator(found) : end();
            return not_less;
        }

        /* Member functions : upper_bound()
         *
         *
         */
        iterator upper_bound( const Key& key ) {
            bstree* found = _search(key);
            iterator greater;

            greater = found && found->next ? iterator(found->right) : end();
            return greater;
        }
        const_iterator upper_bound( const Key& key ) const {
            bstree* found = _search(key);
            const_iterator greater;

            greater = found && found->next ? iterator(found->right) : end();
            return greater;
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

		bstree* _search(const Key& key, bstree* node) {
			if (!node || (node != NULL && key == node->content.first))
				return node;
			else if (_comp_key_less(key, node->content.first))
				return _search(key, node->left);
			else
				return _search(key, node->right);
		}
		bstree* _search(const Key& key) {
			return _search(key, _root);
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
			else if (_comp_key_less(content.first, node->content.first))
				return _insert(content, node->left);
			else if (content.first != node->content.first)
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
			if (_comp_key_less(content.first, root->content.first)) {
				root->left = _delete_node(content, root->left);
				return root;
			}
			else if (_comp_key_less(root->content.first, content.first)) {
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

		Compare _comp_key_less;
    	Allocator _a_type;
		typename Allocator::template rebind<bstree>::other _a_node;
		bstree* _root;
		size_type _size;
    };



}

#endif
