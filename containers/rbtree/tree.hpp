/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 21:33:23 by tmatis            #+#    #+#             */
/*   Updated: 2021/09/15 20:43:55 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <iomanip>

#define BLACK false
#define RED true

// ref https://www.programiz.com/dsa/insertion-in-a-red-black-tree

namespace ft
{
	template <class T>
	struct _rb_node
	{
		_rb_node *parent;
		_rb_node *left;
		_rb_node *right;
		bool color;
		T data;
	};

	template <class T, class Compare, class Allocator = std::allocator<_rb_node<T> > >
	class _rb_tree
	{
	public:
		// typedef
		typedef _rb_node<T> node;
		typedef node *node_ptr;
		typedef Compare compare;
		typedef Allocator allocator;
		typedef T value_type;
		// constructors
		_rb_tree(allocator allocator_ = allocator()) : _compare(compare())
		{
			this->_allocator = allocator_;

			this->NIL = _allocator.allocate(1);
			NIL->parent = NIL;
			NIL->left = NIL;
			NIL->right = NIL;
			NIL->color = BLACK;

			this->root = NIL;
		}
		~_rb_tree()
		{
			this->clear();
			_allocator.deallocate(NIL, 1);
		}


		value_type *find(value_type value)
		{
			node_ptr found = _find_node(value);

			if (!found)
				return (NULL);
			else
				return (&found->data);
		}

		void insert(value_type value)
		{
			node_ptr n = _new_node(value);

			_insert_recursive(this->root, n);

			if (n->parent == NIL)
				n->color = BLACK;
			else
				_insert_fixup(n);
			//search for new root
			this->root = n;
			while (this->root->parent != NIL)
				this->root = this->root->parent;
		}

		void remove(value_type value)
		{
			node_ptr n = _find_node(value);

			if (n)
				_delete_node(n);
		}

		void clear()
		{
			_recursive_clear(this->root);
			this->root = NIL;
		}
		
		void print(node *p = NULL, int indent = 0) const
		{
			if (p == NULL)
				p = this->root;
			if (p != NIL)
			{
				if (p->right != NIL)
				{
					print(p->right, indent + 4);
				}
				if (indent)
				{
					std::cout << std::setw(indent) << ' ';
				}
				if (p->right != NIL)
					std::cout << " /\n"
							  << std::setw(indent) << ' ';
				if (p->color == RED)
					std::cout << "\033[0;31m";
				std::cout << p->data << "\n ";
				std::cout << "\033[0m";
				if (p->left != NIL)
				{
					std::cout << std::setw(indent) << ' ' << " \\\n";
					print(p->left, indent + 4);
				}
			}
		}

	private:
		node_ptr root;
		node_ptr NIL;		  //sentinel
		compare _compare;	  // used to compare nodes
		allocator _allocator; // used to allocate nodes

		// new node
		node *_new_node(value_type data)
		{
			node *node = _allocator.allocate(1);
			node->data = data;
			node->color = RED;
			node->left = node->right = NIL;
			node->parent = NIL;
			return node;
		}

		node_ptr _grand_parent(node_ptr const node) const
		{
			node_ptr grand_parent = node->parent->parent;
			return grand_parent;
		}

		node_ptr _sibling(node_ptr const node) const
		{
			node_ptr parent = node->parent;
			if (node == parent->left)
				return parent->right;
			else
				return parent->left;
		}
 
		node_ptr _uncle(node_ptr const node) const
		{
			node_ptr grand_parent = _grand_parent(node);
			return _sibling(grand_parent);
		}

		// rotate left
		void _rotate_left(node_ptr x)
		{
			node_ptr y = x->right;
			x->right = y->left;
			if (y->left != NIL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NIL)
				this->root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		// rotate right
		void _rotate_right(node_ptr x)
		{
			node_ptr y = x->left;
			x->left = y->right;
			if (y->right != NIL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NIL)
				this->root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		// insert
		void _insert_recursive(node_ptr root, node_ptr n)
		{
			if (root != NIL && _compare(n->data, root->data))
			{
				if (root->left != NIL)
				{
					_insert_recursive(root->left, n);
					return;
				}
				else
					root->left = n;
			}
			else if (root != NIL)
			{
				if (root->right != NIL)
				{
					_insert_recursive(root->right, n);
					return;
				}
				else
					root->right = n;
			}
			n->parent = root;
			n->color = RED;
			n->left = n->right = NIL;
		}

		// insert fixup
		void _insert_fixup(node_ptr k)
		{
			node_ptr u;

			while (k->parent->color == RED)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							_rotate_right(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						_rotate_left(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;

					if (u->color == RED)
					{
						u->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							_rotate_left(k);
						}
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						_rotate_right(k->parent->parent);
					}
				}
				if (k == root)
					break;
			}
			root->color = BLACK;
		}

		node_ptr _find_node(value_type const data)
		{
			node_ptr current = this->root;
			while (current != NIL)
			{
				if (this->_compare(data, current->data))
					current = current->left;
				else if (this->_compare(current->data, data))
					current = current->right;
				else
					return current;
			}
			return NULL;
		}

		void _transplant(node_ptr u, node_ptr v)
		{
			if (u->parent == NIL)
				this->root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		node_ptr _minimum(node_ptr x)
		{
			while (x->left != NIL)
				x = x->left;
			return x;
		}
		void _delete_node(node_ptr z)
		{
			node_ptr y = z;
			node_ptr x;
			bool y_original_color = y->color;
			if (z->left == NIL)
			{
				x = z->right;
				_transplant(z, z->right);
			}
			else if (z->right == NIL)
			{
				x = z->left;
				_transplant(z, z->left);
			}
			else
			{
				y = _minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			_allocator.destroy(z);
			_allocator.deallocate(z, 1);
			if (y_original_color == BLACK)
				_delete_fixup(x);
		}

		void _delete_fixup(node_ptr x)
		{
			node_ptr s;
			while (x != root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_rotate_left(x->parent);
						s = x->parent->right;
					}
					if (s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							_rotate_right(s);
							s = x->parent->right;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->right->color = BLACK;
						_rotate_left(x->parent);
						x = root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						_rotate_right(x->parent);
						s = x->parent->left;
					}
					if (s->right->color == BLACK && s->left->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->left->color == BLACK)
						{
							s->right->color = BLACK;
							s->color = RED;
							_rotate_left(s);
							s = x->parent->left;
						}
						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->left->color = BLACK;
						_rotate_right(x->parent);
						x = root;
					}
				}
			}
			x->color = BLACK;
		}

		void _recursive_clear(node_ptr x = NULL)
		{
			if (x == NULL)
				x = this->root;
			if (x != NIL)
			{
				_recursive_clear(x->left);
				_recursive_clear(x->right);
				_allocator.destroy(x);
				_allocator.deallocate(x, 1);
			}
		}
	};
}

#endif