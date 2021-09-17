/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:24:08 by tmatis            #+#    #+#             */
/*   Updated: 2021/09/17 12:24:48 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "tree.hpp"

namespace ft
{
	template <class Node>
	class tree_iterator
	{
	public:
		// typedef typename Node::value_type value_type;
		typedef Node value_type;
		typedef value_type *node_ptr;
		typedef Node *pointer;
		typedef Node &reference;
		typedef Node const *const_pointer;
		typedef Node const &const_reference;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename std::ptrdiff_t difference_type;

		tree_iterator(node_ptr node, node_ptr root, node_ptr NIL)
			: _node(node), root(root), NIL(NIL) {}
		tree_iterator(void) : _node(NULL), root(NULL), NIL(NULL) {}
		tree_iterator(const tree_iterator &other)
			: _node(other._node), root(other.root), NIL(other.NIL) {}

		~tree_iterator(void) {}

		//overload for const iterator
		operator tree_iterator<value_type const>(void) const
		{
			return tree_iterator<value_type const>(_node, root, NIL);
		}

		tree_iterator &operator=(const tree_iterator &other)
		{
			_node = other._node;
			root = other.root;
			NIL = other.NIL;
			return *this;
		}

		bool operator==(const tree_iterator &other) const
		{
			return _node == other._node;
		}

		bool operator!=(const tree_iterator &other) const
		{
			return _node != other._node;
		}

		reference operator*(void)
		{
			return _node->data;
		}

		const_reference operator*(void) const
		{
			return _node->data;
		}

		pointer operator->(void)
		{
			return &(operator*());
		}

		const_pointer operator->(void) const
		{
			return &(operator*());
		}

		tree_iterator &operator++(void)
		{
			if (_node != NIL)
				_node = _next();
			return *this;
		}

		tree_iterator operator++(int)
		{
			tree_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		tree_iterator &operator--(void)
		{
			if (_node != NIL)
				_node = _prev();
			else
				_node = max(root);
			return *this;
		}

		tree_iterator operator--(int)
		{
			tree_iterator tmp(*this);
			--(*this);
			return tmp;
		}
	

	private:
		node_ptr _node;
		node_ptr root;
		node_ptr NIL;

		node_ptr max(node_ptr node)
		{
			while (node->right != NIL)
				node = node->right;
			return node;
		}

		node_ptr min(node_ptr node)
		{
			while (node->left != NIL)
				node = node->left;
			return node;
		}

		//find the previous node in the tree
		node_ptr _prev(void)
		{
			node_ptr node = _node;
			node_ptr previous = NIL;

			//       3 <--- start
			//     /   \
			//    1     5
			//   / \
			//  0   2 <-- target
			if (node->left != NIL)
				return max(node->left);
			previous = node->parent;
			while (previous != NIL && node == previous->left)
			{
				node = previous;
				previous = previous->parent;
			}
			return previous;
		}

		//find the next node in the tree
		node_ptr _next(void)
		{
			node_ptr node = _node;
			node_ptr next = NIL;

			if (node->right != NIL)
				return min(node->right);
			
			next = node->parent;
			while (next != NIL && node == next->right)
			{
				node = next;
				next = next->parent;
			}
			return next;
		}
	};
}

#endif