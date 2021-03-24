/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_structures.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 02:16:15 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/24 02:16:16 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_STRUCTURES_HPP
# define BASE_STRUCTURES_HPP

namespace ft {
	/* Base structure : double circular linked list
	 * List container
	 *
	 */
	template<class T>
	struct t_list {
		T		content;
		t_list	*next;
		t_list	*prev;
	};

	/* Merge sort algorithm
	 * used for sorting list container
	 *
	 *
	 */

	template< class T, class Compare >
	t_list<T>* _merge_sort(t_list<T>* head, Compare comp)
	{
		if (!head || !head->next)
			return head;
		//principle : split the list in 2 smaller lists till the list is 2 elements
		t_list<T>* second = _split(head);

		// recursive call to merge the 2 smaller lists
		head = _merge_sort(head, comp);
		second = _merge_sort(second, comp);

		// then merge the 2 newly sorted lists
		return _merge(head, second, comp);
	}

	template< class T, class Compare >
	t_list<T>* _merge(t_list<T>* first, t_list<T>* second, Compare comp)
	{
		//if the split has made empty lists : return the not empty one
		if (!first)
			return second;
		if (!second)
			return first;

		//swap elements recursively on the smaller lists
		if (comp(first->content, second->content))
		{
			first->next = _merge(first->next, second, comp);
			first->next->prev = first;
			first->prev = NULL;
			return first;
		}
		else
		{
			second->next = _merge(first, second->next, comp);
			second->next->prev = second;
			second->prev = NULL;
			return second;
		}
	}

	template< class T >
	t_list<T>* _split(t_list<T>* head)
	{
		t_list<T> *fast = head, *slow = head;
		while (fast->next && fast->next->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		t_list<T>* temp = slow->next;
		slow->next = NULL;
		return temp;
	}


	/* Base structure : binary search tree
	 * Map container
	 *
	 */

	template<class T>
	struct bstree {
		T content;
		bool color_orange;
		#ifdef __linux__
			int fake_rbtree;
		#endif

		bstree* parent;
		bstree* left;
		bstree* right;
	};

	/* Find successor, predecessor
	 * algorithm for iterators
	 *
	 *
	 */

	template<class T>
	bstree<T>* _min_value(bstree<T>* node) {
		bstree<T>* current = node;
		while(current->left)
			current = current->left;
		return current;
	}
	template<class T>
	bstree<T>* _max_value(bstree<T>* node) {
		bstree<T>* current = node;
		while(current->right)
			current = current->right;
		return current;
	}
	template<class T>
	bstree<T>* _find_next(bstree<T>* node) {
		if (node->right)
			return _min_value(node->right);
		bstree<T>* parent = node->parent;
		while (parent && node == parent->right) {
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
	template<class T>
	bstree<T>* _find_prev(bstree<T>* node) {
		if (node->left)
			return _max_value(node->left);
		bstree<T>* parent = node->parent;
		while(parent && node == parent->left) {
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
}

#endif
