/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abintree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 14:13:06 by miki              #+#    #+#             */
/*   Updated: 2021/11/30 05:37:11 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ABINTREE_H
# define FT_ABINTREE_H

#include <cstring>

namespace ft
{
	// struct ABintreeNode
	// {
	// 	/*
	// 	** This enum field will define a node color as red or black.
	// 	*/
	// 	typedef enum	e_bstcolor
	// 	{
	// 		BLK = 0, RED
	// 	}				t_bstcolor;
	// 	struct ABintreeNode				*parent;
	// 	struct ABintreeNode				*left;
	// 	struct ABintreeNode				*right;
	// 	struct ABintreeNode				*next;
	// 	struct ABintreeNode				*prev;
	// 	//C_key							key; //store in C_key?? could it be consted then??
	// 	t_bstcolor						color;
		
	// 	private:
	// 		//struct ABintreeNode &	operator=(struct ABintreeNode const & src) { *this = src; return *this; } //nodes can't be assigned
	// };

	//pair specialization
	template<typename Data, typename Key, typename Value>
	struct	BintreeNode
	{
		/*
		** This enum field will define a node color as red or black.
		*/
		typedef enum	e_bstcolor
		{
			BLK = 0, RED
		}				t_bstcolor;
		struct BintreeNode				*parent;
		struct BintreeNode				*left;
		struct BintreeNode				*right;
		struct BintreeNode				*next;
		struct BintreeNode				*prev;
		struct BintreeNode*	const		_end;
		//C_key							key; //store in C_key?? could it be consted then??
		t_bstcolor						color;
		Data							data;
		Key const						*key;
		Value							*value;
		typedef BintreeNode	t_bstnode;
		
		BintreeNode(BintreeNode * const set_end) : _end(set_end) {}
		private:
			BintreeNode(void) {}
			//struct BintreeNode &	operator=(struct BintreeNode const & src) { *this = src; return *this; } //nodes can't be assigned
	};

	template<typename Data, typename Key, typename Value, typename Compare, typename Alloc>
	class Abintree
	{
		public:
			/*
			** I find it really confusing that the mapped_type is the pair value
			** type while the value_type is the pair type, so I use data_type as
			** a synonym for value_type so I don't confuse it with the
			** mapped_type.
			*/
			typedef Data	data_type;
			typedef Data	value_type;
			typedef Key		key_type;
			typedef Value	mapped_type;
			typedef Alloc	allocator_type;
			/*
			** For the double-value implementation of ft::bintree the data type
			** will be ft::pair<X,Y>.
			*/
			typedef std::size_t	size_type;
			
			typedef Compare		key_compare;
			class	C_key
			{
				private:
					key_type	_key;
					key_compare	_is_less;
				public:
					C_key(void) : _key(key_type()) {
					}
					C_key(key_type const & key) : _key(key) {
					}
					~C_key(void) {
					}
				
					C_key operator=(C_key const & src) {
						this->_key = src._key;
					}

					bool	operator<(C_key const & src) const {
						//std::cerr << "WUZ HERE!!!!" << std::endl;
						return (_is_less(this->_key, src._key));
					}
					bool	operator>(C_key const & src) const {
						return (src < *this); //a>b == b<a
					}
					bool	operator<=(C_key const & src) const {
						return (!(src < *this)); //a<=b == !(b<a)
					}
					bool	operator>=(C_key const & src) const {
						return (!(*this < src)); //a>=b == !(a<b)
					}
					bool	operator!=(C_key const & src) const {
						return (*this < src || *this > src);
					}
					bool	operator==(C_key const & src) const {
						return (!(*this != src));
					}
			};

			typedef struct ft::BintreeNode<Data, Key, Value>	t_bstnode;


		protected:
			/* VARIABLES */
			allocator_type	_alloc;
			t_bstnode *		_root;
			t_bstnode *		_min;
			t_bstnode *		_max;
			t_bstnode		_end;
			size_type		_size;
			key_compare		_is_less;

			/* BINTREE_PAIR ITERATOR */
			/* THEY POINT TO NODE */
			template<typename iT, typename Category>
			struct Iterator : public ft::iterator_traits<iT, Category>
			{
				//Constructible
				private: 
					Iterator(void) {} //cannot be NULL-instantiated, as functioning depends on the definition of a non-NULL, tree-instantiation-specific end-address
				public:
				explicit Iterator(t_bstnode * ptr) : _m_ptr(ptr), _last_node(NULL) {}
				Iterator(Iterator const & src) : _m_ptr(src._m_ptr), _last_node(src._last_node) {}
				Iterator(t_bstnode const & node) : _m_ptr(&node), _last_node(NULL) {}
				//Assignment Operator Overload
				Iterator &	operator=(Iterator const & rhs) {
					this->_m_ptr = rhs._m_ptr;
					this->_last_node = rhs._last_node;
					return (*this);
				}
				//Relational Operator Overloads
				bool	operator==(Iterator const & rhs) const {
					return (this->_m_ptr == rhs._m_ptr); //si las direcciones son iguales las keys son iguales cauenlaleche
				}
				bool	operator!=(Iterator const & rhs) const {
					return (!operator==(rhs)); //a!=b == !(a==b)
				}
				bool	operator<(Iterator const & rhs) const {
					//return (_is_less(this->_m_ptr->data.first, rhs._m_ptr->data.first));
					return (C_key(*this->_m_ptr->key) < C_key(*rhs._m_ptr->key));
				}
				bool	operator>(Iterator const & rhs) const {
					return (rhs < *this); //a>b == b<a
				}
				bool	operator<=(Iterator const & rhs) const {
					return (!(rhs < *this)); //a<=b == !(b<a)
				}
				bool	operator>=(Iterator const & rhs) const {
					return (!(*this < rhs)); //a>=b == !(a<b)
				}
				//Arithmetic Operator Overloads
				Iterator &							operator++(void) {
					if (this->_m_ptr != this->_m_ptr->_end)
					{
						// std::cerr << "AAAAAAARRRRGH: " << this->_m_ptr->key << std::endl;
						// std::cerr << "END: " << this->_m_ptr->_end << std::endl;
						// std::cerr << "NEXT IS END: " << this->_m_ptr->next << std::endl;
						this->_last_node = this->_m_ptr;
						this->_m_ptr = this->_m_ptr->next;
						// std::cerr << "I. AM. END.: " << this->_m_ptr << std::endl;
					}
					else
					{
						this->_m_ptr = this->_last_node;
						this->_last_node = this->_m_ptr->_end;
					}
					return (*this);
				}
				Iterator							operator++(int) {
					Iterator	ret(*this);
					operator++();
					return (ret);
				}
				Iterator & 							operator--(void) {
					if (this->_m_ptr != this->_m_ptr->_end)
					{
						this->_last_node = this->_m_ptr;
						this->_m_ptr = this->_m_ptr->prev;
					}
					else
					{	
						this->_m_ptr = this->_last_node;
						this->_last_node = this->_m_ptr->_end;
					}
					return (*this);
				}
				Iterator							operator--(int) {
					Iterator	ret(*this);
					operator--();
					return (ret);
				}
				Iterator &							operator+=(int inc) {
					for (int i = 0; i < inc; ++i)
						operator++();
					return (*this);
				}
				Iterator &							operator-=(int dec) {
					for (int i = 0; i < dec; ++i)
						operator--();
					return (*this);
				}
				Iterator							operator+(int const & rhs) const {
					Iterator	sum(*this);
					return (sum += rhs);
				}
				Iterator							operator-(int const & rhs) const {
					Iterator	dif(*this);
					return (dif -= rhs);
				}
				// typename Iterator::difference_type	operator+(Iterator const & rhs) const {
				// 	typename Iterator::difference_type	hops = 0;
				// 	bintree_search(this->_m_ptr, rhs._m_ptr->data.first, hops);
				// 	return (hops);
				// }
				
				//Referencing Operators
				//The const references/pointers will be consted by the vector
				//instantiation for const_iterators, which uses a const T. 
				//The function is always consted, as it itself doesn't modify
				//any class member.
				typename Iterator::reference	operator*(void) const {
					return(*this->_m_ptr);
				}
				typename Iterator::reference	operator[](typename Iterator::difference_type pos) const {
					return (*(*this + pos));
				}
				//aaaaah!!!! -> . ... claro!!!! :D
				typename Iterator::pointer		operator->(void) const {
					return (this->_m_ptr);
				}
				protected:
					typedef Iterator iterator;
					typename Iterator::pointer	_m_ptr;
					typename Iterator::pointer	_last_node;
					friend bool ft::Abintree<Data, Key, Value, Compare, Alloc>::is_valid_position(iterator const & position, key_type const & key) const;
			};

			typedef Iterator<t_bstnode, std::bidirectional_iterator_tag>		iterator;
			typedef Iterator<const t_bstnode, std::bidirectional_iterator_tag>	const_iterator; //Iterator formed with const T, so its value_type, pointers to value_type, references to value_type, etc, also all refer to const value
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

			/* CONSTRUCTORS AND DESTRUCTOR */
			Abintree(void) : _root(NULL), _min(&_end), _max(&_end), _end(&_end), _size(0) {}
			virtual ~Abintree(void) {}

			/* ---- PROTECTED BINARY TREE CONTROL FUNCTIONS ---- */
			/*
			** These functions are a mix of modified old C functions I wrote to
			** implement red-black binary trees in my libft (personal C library
			** for school), and new functions I added for the containerization
			** and C++ features. Some of them could probably stand a bit of
			** polishing, but the black hole waits for no one...
			*/

			/* IS VALID POSITION */
			/*
			** This function checks whether the node pointed to by the iterator
			** passed as 'position' is a valid insertion position for the key
			** passed as 'key'. It is used by insert with hint to verify hints.
			**
			** This is a friend function to the first argument's iterator type,
			** to facilitate direct access to its protected node pointer.
			**
			** -- RETURN VALUE --
			** If the insertion position is valid, true is returned. Otherwise,
			** false is returned.
			*/
			bool is_valid_position(iterator const & position, key_type const & key) const {
				if (/*position._m_ptr == NULL || */position._m_ptr == &_end ||
				(position._m_ptr->prev != &_end && C_key(*position._m_ptr->prev->key) > C_key(key)) ||
				(position._m_ptr->next != &_end && C_key(*position._m_ptr->next->key) <= C_key(key))) 
					return false;
				return true;
			}

			/* GET NEXT NODE */
			/*
			** Esta función busca el MENOR de los nodos MAYORES que 'node'.
			**
			** Si el nodo a su derecha no es NULL, el MENOR de los nodos MAYORES
			** que 'node' será el de más a la izquierda del de su derecha.
			**
			** Si el nodo a su derecha es NULL, el MENOR de los nodos MAYORES
			** que 'node' será el primer nodo ascendiente mayor que él.
			**
			** Si en ninguno de los dos casos se encuentra un nodo mayor, o
			** si 'node' carece tanto de hijo derecho como de padre, entonces ya
			** es el mayor de los nodos.
			**
			** -- VALOR DE RETORNO --
			** Se devuelve un puntero al menor de los nodos mayores que 'node'.
			** Si 'node' ya es el mayor nodo, se devuelve NULL.
			**
			** This function searches for the LEAST of the nodes that are
			** GREATER than 'node'... eh... I hope that makes sense. I think it
			** makes more sense in Spanish, so I wrote it for myself in Spanish
			** for future reference. xD
			**
			** If the node to the right of 'node' is not NULL, then the LEAST
			** of the nodes GREATER than 'node' is the leftmost node from the
			** node to its right.
			**
			** If the node to the right of 'node' is NULL, then the LEAST of
			** the nodes GREATER than 'node' is the first ascendent node greater
			** than 'node'.
			**
			** If there is no greater node in either case, or if 'node' has no
			** right child and no parent, then 'node' is already the greatest
			** node.
			**
			** -- RETURN VALUE --
			** A pointer to the least of the nodes greater than 'node' is
			** returned. If 'node' is already the greatest, NULL is returned.
			*/
			t_bstnode *	getNextNode(t_bstnode const * node) const {
				if (node->right != NULL)
				{
					node = node->right;
					while (node->left != NULL)
						node = node->left;
				}
				else if (node->parent != NULL)
				{
					t_bstnode const *	ascendent_node = node->parent;
					while (ascendent_node != NULL && C_key(*ascendent_node->key) < C_key(*node->key))
						ascendent_node = ascendent_node->parent;
					node = ascendent_node;
				}
				else
					node = NULL;
				return (const_cast<t_bstnode *>(node));
			}

			/* GET PREV NODE */
			/*
			** Esta función busca el MAYOR de los nodos MENORES que 'node'.
			**
			** Si el nodo a su izquierda no es NULL, el MAYOR de los nodos
			** MENORES que 'node' será el de más a la derecha del de su
			** izquierda.
			**
			** Si el nodo a su izquierda es NULL, el MAYOR de los nodos MENORES
			** que 'node' será el primer ascendiente menor que o igual a él.
			** Nótese que el 'igual a' no será relevante para ft::map, que
			** envuelve esta clase, ya que no admite duplicados.
			**
			** Si en ninguno de los dos casos se encuentra un nodo menor, o si
			** 'node' carece tanto de hijo izquierdo como de padre, entonces ya
			** es el menor de los nodos.
			**
			** -- VALOR DE RETORNO --
			** Se devuelve un puntero al mayor de los nodos menores que 'node'.
			** Si 'node' ya es el menor nodo, se devuelve NULL.
			**
			** This function searches for the greatest of the nodes that are
			** lesser than 'node'.
			**
			** If the node to the left of 'node' is not NULL, then the GREATEST
			** of the nodes that are LESSER than 'node' is the rightmost node
			** from the node to its left.
			**
			** If the node to the left of 'node' is NULL, then the GREATEST of
			** the nodes that are LESSER than 'node' is the first ascendent node
			** less than 'node'.
			**
			** If there is no lesser node in either case, or if 'node' has no
			** left child and no parent, then 'node' is already the least node.
			**
			** -- RETURN VALUE --
			** A pointer to the greatest of the nodes lesser than 'node' is
			** returned. If 'node' is already the least node, NULL is returned.
			*/
			t_bstnode * getPrevNode(t_bstnode const * node) const {
				if (node->left != NULL)
				{
					node = node->left;
					while (node->right != NULL)
						node = node->right;
				}
				else if (node->parent != NULL)
				{
					t_bstnode const *	ascendent_node = node->parent;
					while (ascendent_node != NULL && C_key(*ascendent_node->key) >= C_key(*node->key))
						ascendent_node = ascendent_node->parent;
					node = ascendent_node;
				}
				else
					node = NULL;
				return (const_cast<t_bstnode *>(node));
			}

			/* BINTREE SEARCH */
			/*
			** This function will search the binary tree whose 'root' is passed
			** as the first argument for the value passed as 'key' in the second
			** argument.
			**
			** If the root node pointer is not NULL and the key is not present
			** in that node, this function will recursively call itself, passing
			** the pointer to the left or right branches of that node, as the
			** key is less than, equal to or greater than the key within the
			** node, until either a NULL pointer or a node with matching key is
			** found.
			**
			** -- RETURN VALUE --
			** If the 'key' passed as the second argument is found in the tree,
			** a pointer to the node containing the key is returned. If it is
			** not present in the tree, a NULL pointer is returned.	
			*/
			t_bstnode	*bintree_search(t_bstnode * root, key_type const & key) const
			{
				//std::cerr << root->key << std::endl;
				if (root == NULL || C_key(*root->key) == C_key(key))
					return (root);
				else if (C_key(key) <= C_key(*root->key))
					return (bintree_search(root->left, key));
				else
					return (bintree_search(root->right, key));
			}

			/* BINTREE SEARCH WITH HOP COUNTER */
			/*
			** This overloaded version of bintree_search will keep track of how
			** many node hops were needed to find the matching key, or leaf
			** child of the closest node, and save the result in 'hops'.
			*/
			t_bstnode *	bintree_search(t_bstnode *root, key_type const & key, typename iterator::difference_type & hops) const
			{
				if (root == NULL || C_key(*root->key) == C_key(key))
					return (root);
				else if (C_key(key) <= C_key(*root->key))
					return (bintree_search(root->left, key, ++hops));
				else
					return (bintree_search(root->right, key, ++hops));
			}

			virtual void	assign_key_value_pointers(t_bstnode * node) const = 0;
			/* CREATE NEW NODE */
			/*
			** This function dynamically reserves memory in heap for a new node
			** in a binary tree and sets the data segment of that node to the
			** value of the argument. The left and right child pointers and the
			** next and prev thread pointers are nulled. Each node is RED by
			** default.
			**
			** -- RETURN VALUE / EXCEPTIONS --
			** A pointer to the new binary tree node is returned to the caller.
			** If the memory reservation fails, a NULL pointer is returned and
			** a bad_alloc exception is rethrown to the caller.
			*/
			t_bstnode *	create_new_node(t_bstnode * parent, data_type data) throw (std::bad_alloc, std::exception)
			{
				t_bstnode *	node = NULL;

				try
				{
					node = _alloc.allocate(1);
					_alloc.construct(node, t_bstnode(&_end));
					node->data = data;
					this->assign_key_value_pointers(node);
					node->parent = parent;
					node->left = NULL;
					node->right = NULL;
					node->next = &_end;
					node->prev = &_end;
					//node->_end = &_end;
					node->color = t_bstnode::RED;
				}
				catch (std::bad_alloc const & e)
				{
					throw ;
				}
				catch (std::exception const & e)
				{
					throw ;
				}
				return (node);
			}

			/* BINTREE INSERT */
			/*
			** This function inserts a node into a binary tree. If passed a NULL
			** pointer, a root node will be created.
			**
			** In the binary tree all values less than or equal to any node
			** value will be stored to the 'left' of that node, and all values
			** greater than any node value will be stored to the 'right' of that
			** node (note, 'left' and 'right' here are abstractions, not literal
			** orientations). This makes it possible to zero in on a value
			** within a set of values more quickly when searching for it by
			** using an approximation depending on whether the value is greater
			** than or less than the node value being analysed at any given
			** juncture.
			**
			** To create new nodes in a tree, the function will recursively call
			** itself, seeking a path to the nearest value (in an existing node
			** in the tree) to the value to be inserted, and store the value in
			** relation to that node. That node's right or left pointer will
			** then be set to point to the new node. The rest of the recursively
			** called functions will then return the original unmodified values
			** of the pointer addresses through which they accessed the nodes in
			** the path.
			**
			** So, for insert(root, 220);
			**
			**								200
			**								 |
			**								/ \
			**							 100   300
			**							 / \   / \
			**							 X X 220 X
			**
			** Now, in a set of four numbers (200, 100, 300, 220), a match for
			** 220 can be found from root in just two comparisons (as 220 is
			** greater than 200, as 220 is less than 300), instead of
			** potentially as many as four in an array or list (as 220 is not
			** equal to 200, as 220 is not equal to 100, as 220 is not equal to
			** 300, as 220 is equal to 220).
			**
			** This makes the structure relatively less efficient than lists and
			** arrays for frequent insertions and deletions, but more efficient
			** for frequent searches, such as of ordered key values.
			**
			** -- RETURN VALUE / EXCEPTIONS --
			** This function returns a pointer to the root of the tree passed as
			** an argument. If memory allocation failed, a bad_alloc exception
			** is rethrown to the caller. If memory allocation succeeded, the
			** address of the newly created node is written to the new_node
			** pointer, a reference to which is passed as an argument.
			*/
			t_bstnode *	bintree_insert(t_bstnode * parent, t_bstnode *root, \
			data_type const & data, key_type const & key, t_bstnode *& new_node) throw (std::bad_alloc, std::exception)
			{
				if (root == NULL)
				{
					try
					{
						root = create_new_node(parent, data);
						new_node = root;
					}
					catch (std::bad_alloc const & e)
					{
						throw ;
					}
					catch (std::exception const & e)
					{
						throw ;
					}
				}
				else if (C_key(key) <= C_key(*root->key))
					root->left = bintree_insert(root, root->left, data, key, new_node);
				else
					root->right = bintree_insert(root, root->right, data, key, new_node);
				return (root);
			}

			/* BINTREE ADD */
			/*
			** This function is an adaptation of my original red-black binary
			** tree insert node gateway function in C. The new public method in
			** the C++ class calls this function directly to push new data onto
			** the tree.
			**
			** This function allocates memory. The insert and create_new_node
			** functions, being dependent on memory allocation, now throw
			** exceptions if memory allocation is impossible. The exceptions are
			** safely caught and handled here before any part of the
			** pre-existing tree is modified.
			**
			** If allocation succeeds the function balances the tree as needed,
			** updates the tree's _size variable, and updates the _min and _max
			** pointers if needed. The tree is threaded, so pointers to next and
			** previous nodes are updated as needed.
			**
			** -- RETURN VALUE --
			** A pointer to the new node in the tree is returned. If insertion
			** failed because the node already exists, a pointer to the existing
			** node is returned. If insertion fails due to an allocation error,
			** a NULL pointer is returned.
			*/
			t_bstnode *	bintree_add(t_bstnode *& root, data_type const & data, key_type const new_key) //Not a ref because I was worried it might not jive with a std::move instruction if I ever use one :p
			{
				t_bstnode *		new_node = NULL;

				if ((new_node = bintree_search(root, new_key)) != NULL) //ban duplicate keys
					return (new_node);
				try
				{
					root = bintree_insert(NULL, root, data, new_key, (new_node = NULL)); //note: bintree_insert does not NULL new_node if it fails
					bintree_balance(&_root, new_node);
					++_size;
					t_bstnode *	next_node = getNextNode(new_node);
					t_bstnode * prev_node = getPrevNode(new_node);
					//THREADING
					if (next_node != NULL)
					{
						new_node->next = next_node;
						next_node->prev = new_node;
					}
					if (prev_node != NULL)
					{
						new_node->prev = prev_node;
						prev_node->next = new_node;
					}
					if (_min == &_end || C_key(new_key) < C_key(*_min->key))
						_min = new_node;
					if (_max == &_end || C_key(new_key) > C_key(*_max->key)) 
						_max = new_node;
				}
				catch(std::bad_alloc const & e)
				{
					std::cerr << e.what() << std::endl;
				}
				catch(std::exception const & e)
				{
					std::cerr << e.what() << std::endl;
				}
				return (new_node);
			}

			/* THE NODE DELETE SUITE. TURN AWAY NOW, FOR YOUR SANITY'S SAKE. */

			/* NODE DELETE */
			/*
			** This function destroys a node and deallocates its associated
			** memory using the provided allocator, decrementing the container
			** _size. Rebalancing via node substitution must be performed before
			** this is done.
			**
			** This tree is threaded, so thread pointers are updated here as
			** needed. The associated memory is zeroed before being freed.
			**
			** -- RETURN VALUE --
			** The function always returns a NULL node pointer.
			*/
			t_bstnode *	node_delete(t_bstnode * node)
			{
				std::memset(node, 0, sizeof(t_bstnode));
				_alloc.destroy(node);
				_alloc.deallocate(node, sizeof(t_bstnode));
				--_size;
				return (NULL);
			}

			void	thread_swap(t_bstnode * node1, t_bstnode * node2) {				
					t_bstnode *tmp_next = node1->next;
					t_bstnode *tmp_prev = node1->prev;
					node1->prev = node2->prev;
					node1->next = node2->next;
					if (node1->next != &_end)
						node1->next->prev = node1;
					if (node1->prev != &_end)
						node1->prev->next = node1;
					node2->prev = tmp_prev;
					node2->next = tmp_next;
					if (node2->next != &_end)
						node2->next->prev = node2;
					if (node2->prev != &_end)
						node2->prev->next = node2;
			}


			/* BINTREE DELETE */
			/*
			** Deletes a node from a binary tree. You have NO idea the HORROR,
			** the PAIN that this implies. It's much worse than mere insertion.
			** SO much worse. You monster.
			*/
			t_bstnode * bintree_delete(t_bstnode * node) {
				if (node == NULL)
					return (NULL);
				
				// if (node->next != &_end) //rethread 
				// 	node->next->prev = node->prev;
				// if (node->prev != &_end)
				// 	node->prev->next = node->next;
					
				if (node->right == NULL && node->left == NULL) //it's a leaf/both children are NULL
				{				
					if (node->parent != NULL)
					{
						if (node->parent->right == node)
							node->parent->right = NULL;
						else
							node->parent->left = NULL;
					}
					if (node->color == t_bstnode::RED) //NULLs are black, so if original node is RED
						node->color = t_bstnode::BLK; //replacement node is BLACK
					else // if both original node and replacement node are BLACK
						fix_double_black(node); //replacement node is... DOUBLE BLACK! of course! what you mean that's not a color??? xD
					node_delete(node);
				}
				else if (node->left == NULL) //has only right child
				{		
					//node == v
					//node->right == u
					node->data = node->right->data; //copy child to node
					//this->assign_key_value_pointers(node);
					if (node->color == t_bstnode::RED || node->right->color == t_bstnode::RED) //if either original node or replacement node are RED...
						node->color = t_bstnode::BLK; //replacement node is BLACK
					else //if both original node and replacement node are BLACK...
						fix_double_black(node); //replacement node is... DOUBLE BLACK! of course! what you mean that's not a color??? xD
					thread_swap(node, node->right);
					node->right = node_delete(node->right); //delete the original child
				}
				else if (node->right == NULL) //has only left child
				{
					node->data = node->left->data; // copy child to node
					//this->assign_key_value_pointers(node);
					if (node->color == t_bstnode::RED || node->left->color == t_bstnode::RED)  //if either original node or replacement node are RED...
						node->color = t_bstnode::BLK; //replacement node is BLACK
					else //if both original node and replacement node are BLACK...
						fix_double_black(node); //replacement node is... DOUBLE BLACK! of course! what you mean that's not a color??? xD
					thread_swap(node, node->left);
					node->left = node_delete(node->left); //delete the original child
				}
				else //has two children
				{
					//get successor node, swap data with it, and delete the successor
					t_bstnode * successor = node->right;
					data_type	data;;
					while (successor->left != NULL)
						successor = successor->left;
					data = node->data;
					node->data = successor->data;
					thread_swap(node, successor);
					successor->data = data;
					bintree_delete(successor);
				}
				return (NULL);
			}

			t_bstnode	*root_canal(t_bstnode * root)
			{
				if (root != NULL)
					if (root->left == NULL && root->right == NULL)
						root = node_delete(root);
				return (NULL);
			}

			/* BINTREE FREE */
			/*
			** This is an iterative function for freeing memory used by binary
			** trees. Memory is zeroed before freeing. This is CPU-intensive,
			** but memory-light. It can be used to free trees that would be too
			** big to free with a recursive function.
			**
			** The function searches for childless nodes with a bias for left
			** children. When a childless node is found its memory is zeored and
			** it is freed, and then the next childless node is searched for.
			**
			** The function works through infanticide. Parents kill their
			** childless children. Horrifying, but I couldn't think of a more
			** humane way to do this. That's the world of binary trees. -_-
			**
			** We iterate down the tree with a pointer, starting with left
			** children. If the parent finds a left child, it checks whether its
			** child has children. If the parent finds a grandchild, it becomes
			** the child, and then we check the child's children for children.
			**
			** If the child has no children of its own, the parent DELETES its
			** own child. :_( Then it comes back for another round to check its
			** other child for children...
			**
			** Once the parent is childless, it becomes its own parent, and the
			** grim cycle continues, until everyone is DEAD. The root_canal
			** performs the final suicide.
			**
			** I hope you're happy, Valgrind. :(
			*/
			t_bstnode	*bintree_free(t_bstnode * root)
			{
				t_bstnode	*parent;

				parent = root;
				while (parent != NULL)
				{
					while (parent->left != NULL || parent->right != NULL)
					{
						if (parent->left != NULL)
						{
							if (parent->left->left != NULL || parent->left->right != NULL)
								parent = parent->left;
							else
								parent->left = node_delete(parent->left);
						}
						else if (parent->right != NULL)
						{
							if (parent->right->left != NULL || parent->right->right != NULL)
								parent = parent->right;
							else
								parent->right = node_delete(parent->right);
						}
					}
					parent = parent->parent;
				}
				return (root_canal(root));
			}

			/* MOVE_DOWN */
			/*
			** Moves down the node passed as 'node' and moves the node passed
			** as 'new_parent' in its place.
			*/
			void		move_down(t_bstnode * node, t_bstnode * new_parent) {
				if (node->parent != NULL)
				{
					if (node->parent->left == node) //if i am left child
						node->parent->left = new_parent; //my child is now my parent's left child
					else //if i am right child
						node->parent->right = new_parent; //my child is now my parent's right child
				}
				new_parent->parent = node->parent; //my child's parent is now my parent
				node->parent = new_parent; //my child is now my parent
			}

			/* FIX_DOUBLE_BLACK_RIGHT_ROTATE */
			/*
			** Performs a right rotation.
			*/
			void		fix_double_black_right_rotate(t_bstnode * node) {
				//new parent will be node's left child
				t_bstnode * new_parent = node->left;
				//update root if current node is root
				if (_root == node)
					_root = new_parent;
				move_down(node, new_parent);
				node->left = new_parent->right; //my new parent's (who used to be my child) right child is now my left child
				if (new_parent->right != NULL)
					new_parent->right->parent = node; //if the child I inherited from my former child/new parent is not NULL, its parent is now me
				new_parent->right = node; //my new parent's right child is now me.
			}

			/* FIX_DOUBLE_BLACK_LEFT_ROTATE */
			/*
			** Performs a left rotation.
			*/
			void		fix_double_black_left_rotate(t_bstnode * node) {
				// new parent will be node's right child
				t_bstnode * new_parent = node->right;
				//update root if current node is root
				if (_root == node)
					_root = new_parent;
				move_down(node, new_parent);
				node->right = new_parent->left;  //my new parent's (who used to be my child) left child is now my right child
				if (new_parent->left != NULL)
					new_parent->left->parent = node; //if the child I inherited from my former child/new parent is not NULL, its parent is now me
				new_parent->left = node; //my new parent's left child is now me.
			}

			/* FIX_DOUBLE_BLACK */
			/* 
			** Performs magics to convert double-black nodes into single-black
			** nodes. This rebalances the tree after a deletion that leads to
			** an already-black node being colored black again. MÁTAME PLS.
			*/
			void		fix_double_black(t_bstnode * node) {
				if (node->parent == NULL) //if we0re at the tree root, stop this madness
					return ;
				
				enum	help
				{
					LEFT_CHILD = 0, RIGHT_CHILD
				};
				enum help	my_sibling;
				enum help	myself;
				t_bstnode *	sibling;
				
				if (node->parent->left == node) //if I am the left child
				{
					sibling = node->parent->right;
					my_sibling = RIGHT_CHILD;
					myself = LEFT_CHILD;
				}
				else //if I am the right child
				{
					sibling = node->parent->left;
					my_sibling = LEFT_CHILD;
					myself = RIGHT_CHILD;
				}
				if (sibling == NULL) //if I am an only child, "push" the double black up to my parent!? o_O
					fix_double_black(node->parent);
				else
				{
					if (sibling->color == t_bstnode::RED) //I have a red sibling
					{
						node->parent->color = t_bstnode::RED;
						sibling->color = t_bstnode::BLK;
						if (my_sibling == LEFT_CHILD) //left case
							fix_double_black_right_rotate(node->parent); 
						else //right case
							fix_double_black_left_rotate(node->parent);
						fix_double_black(node);
					}
					else //I have a black sibling
					{
						bool sibling_right_child_is_red = (sibling->right != NULL && sibling->right->color == t_bstnode::RED);
						bool sibling_left_child_is_red = (sibling->left != NULL && sibling->left->color == t_bstnode::RED);
						//sibling has at least one red child
						if (sibling_right_child_is_red || sibling_left_child_is_red)
						{
							//sibling's left child is red
							if (sibling_left_child_is_red)
							{
								//sibling is a left child
								if (my_sibling == LEFT_CHILD) //left left case (sibling is left child with left red child)
								{
									sibling->left->color = sibling->color;
									sibling->color = node->parent->color;
									fix_double_black_right_rotate(node->parent);
								}
								//sibling is a right child
								else // right left case (sibling is right child with left red child)
								{
									sibling->left->color = node->parent->color;
									fix_double_black_right_rotate(sibling);
									fix_double_black_left_rotate(node->parent);
								}
							}
							//sibling's right child is red
							else
							{
								//sibling is a left child
								if (my_sibling == LEFT_CHILD) //left right case (sibling is a left child with right red child)
								{
									sibling->right->color = node->parent->color;
									fix_double_black_left_rotate(sibling);
									fix_double_black_right_rotate(node->parent);
								}
								//sibling is a right child
								else // right right case (sibling is a right child with right red child)
								{
									sibling->right->color = sibling->color;
									sibling->color = node->parent->color;
									fix_double_black_left_rotate(node->parent);
								}
							}
							node->parent->color = t_bstnode::BLK;
						}
						//sibling has two black children
						else
						{
							sibling->color = t_bstnode::RED;
							if (node->parent->color == t_bstnode::BLK)	
								fix_double_black(node->parent);
							else
								node->parent->color = t_bstnode::BLK;
						}
					}
				}
			}

			/* DEPTH */
			/*
			** This recursive function finds the depth of a binary tree.
			** Might make this iterative in future.
			*/
			size_t			bintree_depth(t_bstnode *root) {
				size_t	left_depth;
				size_t	right_depth;

				if (root == NULL)
					return (0);
				else
				{
					left_depth = bintree_depth(root->left);
					right_depth = bintree_depth(root->right);
					if (left_depth > right_depth)
						return (left_depth + 1);
					else
						return (right_depth + 1);
				}	
			}

			/*
			** This function will perform a right rotation on the node passed as
			** root.
			*/
			void	right_rotation(t_bstnode **root, t_bstnode *node)
			{
				t_bstnode	*left;

				left = node->left;
				node->left = left->right;
				if (node->left)
					node->left->parent = node;
				left->parent = node->parent;
				if (!node->parent)
					*root = left;
				else if (node == node->parent->left)
					node->parent->left = left;
				else
					node->parent->right = left;
				left->right = node;
				node->parent = left;
			}

			/*
			** This function will perform a left rotation on the node passed as
			** root.
			*/
			void	left_rotation(t_bstnode **root, t_bstnode *node)
			{
				t_bstnode	*right;

				right = node->right;
				node->right = right->left;
				if (node->right)
					node->right->parent = node;
				right->parent = node->parent;
				if (node->parent == NULL)
					*root = right;
				else if (node == node->parent->left)
					node->parent->left = right;
				else
					node->parent->right = right;
				right->left = node;
				node->parent = right;
			}

			/*
			** This function handles red-black violation Cases 2 and 3 (uncle is
			** black) in which the violating node's parent is a LEFT child of
			** the grandparent.
			**
			** If the uncle is black and the node is a right child of the
			** parent, then a left rotation is applied on the parent. After the
			** left rotation, the parent becomes the node's left child, and the
			** node becomes its parent's parent.
			**
			** The node pointer is then changed to point to the parent.
			**
			** The new node is now a left child of the new parent (the old
			** node), which is also a left child of the grandparent (because it
			** switched places with the old parent, which was a left child). The
			** uncle is still black. So that puts us in Case 3. So we apply the
			** Case 3 correction.
			**
			** If the uncle is black and the node is a left child of the parent,
			** whether originally or because we applied a Case 2 rotation, then
			** we apply a right rotation on the grandparent and switch the
			** grandparent's colour with the parent's colour.
			**
			** The node pointer is then changed to point to the parent to check
			** its compliance with the red-black rules after the change. Note
			** that if a Case 2 rotation was applied, it will end up pointing to
			** the grandparent.
			**
			** -- RETURN VALUE --
			** The new_node's parent after the corrective rotations.
			*/
			t_bstnode	*left_case(t_bstnode *new_node, t_bstnode *parent, t_bstnode *granny, \
			t_bstnode **root)
			{
				typename t_bstnode::t_bstcolor	tmpc;

				if (new_node == parent->right)
				{
					left_rotation(root, parent);
					new_node = parent;
					parent = new_node->parent;
				}
				right_rotation(root, granny);
				tmpc = parent->color;
				parent->color = granny->color;
				granny->color = tmpc;
				new_node = parent;
				return (new_node);
			}

			/*
			** This function handles red-black violation Cases 2 and 3 (uncle is
			** black) in which the violating node's parent is a RIGHT child of
			** the grandparent.
			**
			** If the uncle is black and the node is a left child of the parent,
			** then a right rotation is applied on the parent. After the right
			** rotation, the parent becomes the node's right child, and the node
			** becomes its parent's parent.
			**
			** The node pointer is then changed to point to the parent.
			**
			** The new node is now a right child of the new parent (the old
			** node), which is also a right child of the grandparent (because it
			** switched places with the old parent, which was a right child).
			** The uncle is still black. So that puts us in Case 3. So we apply
			** the Case 3 correction.
			**
			** If the uncle is black and the node is a right child of the
			** parent, whether originally or because we applied a Case 2
			** rotation, then we apply a left rotation on the grandparent and
			** switch the grandparent's colour with the parent's colour.
			**
			** The node pointer is then changed to point to the parent to check
			** its compliance with the red-black rules after the change. Note
			** that if a Case 2 rotation was applied, it will end up pointing to
			** the grandparent.
			**
			** -- RETURN VALUE --
			** The new_node's parent after the corrective rotations.
			*/
			t_bstnode	*right_case(t_bstnode *new_node, t_bstnode *parent, t_bstnode *granny, \
			t_bstnode **root)
			{
				typename t_bstnode::t_bstcolor	tmpc;

				if (new_node == parent->left)
				{
					right_rotation(root, parent);
					new_node = parent;
					parent = new_node->parent;
				}
				left_rotation(root, granny);
				tmpc = parent->color;
				parent->color = granny->color;
				granny->color = tmpc;
				new_node = parent;
				return (new_node);
			}

			/*
			** This iterative balancer function will go up the red-black tree
			** passed as 'root' from the node passed as 'new_node' and perform
			** any operations as needed to correct violations of the red-black
			** requirements and balance the tree.
			**
			** -- RED-BLACK BINARY SEARCH TREE REQUIREMENTS --
			** 1. The red-black tree always has a black root.
			** 2. Other nodes may be black or red.
			** 3. All null nodes (also called 'leaves') are black.
			** 4. A red node may not have a red child.
			**
			** Thus, the outer loop excludes the possibility that the node may
			** be the root, or otherwise that the node may be black (if it is,
			** it doesn't matter if its parent is black or red), or otherwise
			** (if red) that its parent may be black (if it is, it's okay if the
			** node is red). If that check fails, we enter the correction
			** routine.
			**
			** Corrections may involve just changing the colours of the nodes,
			** or may require the nodes to be rotated left or right, or both.
			**
			** There are four different cases for correction, and two different
			** directions of rotation in case a rotation is needed.
			**
			** -- CORRECTION CASES --
			** The cases are, if the offending node's PARENT is a LEFT child:
			**
			** LEFT CASE:
			**
			** Case 0:	The node is the tree root.
			** Case 1:  The node's uncle is red.
			** Case 2:  The node's uncle is black, and the node is the parent's
			**			right child, so it forms a triangle with the parent and
			**			grandparent.
			** Case 3:  The node's uncle is black, and the node is the parent's
			**			left child, so it forms a line with the parent and
			**			grandparent.
			**
			** If the offending node's parent is a RIGHT child the cases are the same, but with left
			** and right switched:
			**
			** RIGHT CASE:
			**
			** Case 0:	The node is the tree root.
			** Case 1:  The node's uncle is red.
			** Case 2:  The node's uncle is black, and the node is the parent's
			**			left child, so it forms a triangle with the parent and
			**			grandparent.
			** Case 3:  The node's uncle is black, and the node is the parent's
			**			right child, so it forms a line with the parent and
			**			grandparent.
			**
			** RIGHT CASE 0 and 1 and LEFT CASE 0 and 1 are always the same, so
			** cases 0 and 1 are evaluated first.
			**
			** If a rotation is needed, it goes in the opposite direction of the
			** node's direction from the parent. That is, if the node is a right
			** child a left rotation would be needed, and if it is a left child
			** a right rotation would be needed. So we call separate functions:
			** left_case if the parent is a LEFT child, and right_case if the
			** parent is a RIGHT child.
			**
			** -- ALGORITHMIC PROCEDURE --
			** First we define the node's parent, grandparent and uncle.
			**
			** If the node's parent is the grandparent's LEFT child, that
			** determines that the uncle *must* be the grandparent's right
			** child. We call this "left_case".
			**
			** If the node's parent is the grandparent's RIGHT child, that
			** determines that the uncle *must* be the grandparent's left child.
			** We call this "right_case".
			**
			** If the uncle is red, it is Case 1.
			**
			** To correct a violation in Case 1, the node's parent, grandparent
			** and uncle are recoloured. The grandparent is coloured red, and
			** the parent and uncle black. The node pointer then moves up to the
			** grandparent to check the grandparent's compliance with red-black
			** rules after the change.
			**
			** If the uncle is black, it is either Case 2 or 3. Depending on
			** whether it is a left case or right case, we call the left_case
			** and right_case functions, respectively, to handle it.
			**
			** Lastly, if we have emerged from the while, we colour the tree
			** root black, as this is obligatory.
			*/
			void	bintree_balance(t_bstnode **root, t_bstnode *new_node)
			{
				t_bstnode	*granny;
				t_bstnode	*parent;
				t_bstnode	*uncle;
							//CASE 0
				while (new_node != *root && new_node->color == t_bstnode::RED && new_node->parent->color == t_bstnode::RED)
				{
					parent = new_node->parent;
					granny = new_node->parent->parent;
					if (parent == granny->left)
						uncle = granny->right;
					else
						uncle = granny->left;
					if (uncle != NULL && uncle->color == t_bstnode::RED) //CASE 1
					{
						granny->color = t_bstnode::RED;
						parent->color = t_bstnode::BLK;
						uncle->color = t_bstnode::BLK;
						new_node = granny;
					}
					else if (parent == granny->left) //PARENT IS LEFT CHILD
						new_node = left_case(new_node, parent, granny, root);
					else							//PARENT IS RIGHT CHILD
						new_node = right_case(new_node, parent, granny, root);
				}
				(*root)->color = t_bstnode::BLK;
			}

			/* GET NEAREST NODE */
			/*
			** This function traverses the tree to the first key equal to 'key'
			** and returns it. If there is no exactly equal key, it traverses to
			** the closest LEAF (NULL node) to the key passed as 'key' and
			** returns its PARENT.
			*/
			t_bstnode	* getNearestNode(t_bstnode const * node, t_bstnode const * parent, key_type const & key) const {
				if (node == NULL)
					return (const_cast<t_bstnode *>(parent));
				else if (C_key(*node->key) == C_key(key))
					return (const_cast<t_bstnode *>(node));
				else if (C_key(*node->key) < C_key(key))
					return (getNearestNode(node->right, node, key));
				else
					return (getNearestNode(node->left, node, key));
			}

			/* RECURSIVE COUNT */
			/*
			** Should I be a lambda? Could I be a lambda? Recursive lambdas?
			**
			** Anyway, this is just a recursive counting function that
			** counts all instances of a key in a binary tree and returns
			** the result. It's redundant in ft::map because duplicates
			** aren't allowed, but, unlike a tree that handles duplicates,
			** a recursive counter is pretty easy to code. So, why not? ;)
			*/
			size_type	recursive_count(t_bstnode * node, key_type const & key) const {
				node = bintree_search(node, key);

				if (node == NULL)
					return (0);
				else
					return (1 + recursive_count(node->right, key) + recursive_count(node->left, key));
			}
		public:
			/* ---- ITERATORS ---- */

			/* BEGIN AND END */
			/*
			** These functions respectively return iterators to the first
			** element of the container and the memory address after the last
			** element of the container. Const containers return
			** const_iterators, which are actually iterators TO const values
			** (the iterators themselves can be modified).
			**
			** In the binary tree, the address 'after' the last element and
			** 'before' the first element is virtualized to NULL, which is not
			** resolvable.
			**
			** Each iterator also stores its last resolvable address, so that if
			** incremented OR decremented from NULL it will return to its last
			** address.
			**
			** Note: If iterators are decremented or incremented past NULL, the
			** iterator will infinitely toggle between the last address and NULL
			** until the direction is reversed! So rather than the typical
			** segmentation fault for iterating out of bounds, you may also get
			** an infinite loop. Avoiding this behaviour would involve extra
			** overhead in the iterator and, frankly, I think the binary tree
			** has more than enough overhead as it is. ;)
			**
			** Note: While technically these are bidirectional iterators, full
			** functionality is implemented.
			*/
			iterator begin(void) {
				return (iterator(_min));
			}
			const_iterator begin(void) const {
				return (const_iterator(_min));
			}
			iterator end(void) {
				return (iterator(_max) + 1);
			}
			const_iterator end(void) const {
				return (const_iterator(_max) + 1);
			}

			iterator rbegin(void) {
				return (iterator(_max) + 1);
			}
			const_iterator rbegin(void) const {
				return (const_iterator(_max) + 1);
			}
			iterator rend(void) {
				return (iterator(_min));
			}
			const_iterator rend(void) const {
				return (const_iterator(_min));
			}

			/* ---- CAPACITY ---- */

			/* SIZE */
			/*
			** This method returns the number of ELEMENTS in the container, NOT
			** its allocated memory!
			*/
			size_type	size(void) const {
				return(_size);
			}

			/* EMPTY */
			/*
			** This method returns true if the container is empty. Otherwise it
			** returns false.
			*/
			bool		empty(void) const {
				return(_size == 0);
			}

			/* MAX_SIZE */
			/*
			** This method returns the container's maximum size, for which we
			** use its allocator's maximum size.
			*/
			size_type			max_size(void) const {
				return (_alloc.max_size());
			}

			void		erase(t_bstnode & node) {
				if (&node != &_end && node._end == &_end) //I check to ensure the node belongs to my tree
				{
					if (node.next != &_end) //rethread 
						node.next->prev = node.prev;
					if (node.prev != &_end)
						node.prev->next = node.next;
					bintree_delete(&node);
					_max = findMax();
					_min = findMin();
				}
			}

			void		erase(iterator position) {
				erase(*position);
			}

			size_type	erase(key_type const & key) {
				size_type	nodes_erased = 0;
				// for (t_bstnode * del_node = bintree_search(_root, key); del_node != NULL; del_node = bintree_search(_root, key))
				// 	erase(*del_node);
				t_bstnode *del_node = bintree_search(_root, key);
				
				if (del_node != NULL && ++nodes_erased)
					erase(*del_node);
				return (nodes_erased);
			}

			void		erase(iterator first, iterator last) {
				ft::vector<key_type>	key_list;
				while (first != last)
				{
					key_list.push_back(*first->key);
					++first;
				}

				for (typename ft::vector<key_type>::iterator it = key_list.begin(), end = key_list.end(); it != end; ++it)
				{
					//std::cerr << *it << std::endl;
					erase(*it);
				}
			}

			void		clear(void) {
				this->_root = bintree_free(this->_root);
			}

			t_bstnode *	getRootNode(void) const {
				return (_root);
			}
			t_bstnode &	getNode(key_type const & key) const {
				return (*(bintree_search(_root, key)));
			}

			/* LOWER BOUND */
			/*
			** This function first obtains the node containing an exact match to
			** 'key' (if one exists), or else the node that would be closest to
			** a node containing 'key', from the getNearestNode function, and
			** creates an iterator out of it. If the nearest_node key is less
			** than 'key', the iterator is incremented by one for the next
			** highest key. If the nearest_node key is greater than or equal to
			** 'key', then it is returned directly.
			**
			** -- RETURN VALUE --
			** The returned iterator points to the node considered to come AFTER
			** a node containing 'key', or to the first node EQUAL to 'key' if
			** one exists.
			*/
			iterator		lower_bound(key_type const & key) {
				t_bstnode *		nearest_node = getNearestNode(_root, NULL, key);
				iterator		ret(nearest_node);

				if (C_key(*nearest_node->key) < C_key(key))
					++ret;
				return (ret);
			}

			const_iterator	lower_bound(key_type const & key) const {
				t_bstnode *		nearest_node = getNearestNode(_root, NULL, key);
				const_iterator	ret(nearest_node);

				if (C_key(*nearest_node->key) < C_key(key))
					++ret;
				return (ret);
			}

			/* UPPER BOUND */
			/*
			** This function first obtains the node containing an exact match to
			** 'key' (if one exists), or else the node that would be closest to
			** a node containing 'key', from the getNearestNode function, and
			** creates an iterator out of it. If the nearest_node key is less
			** than or equal to 'key', the iterator is incremented by one for
			** the next highest key. If the nearest_node key is greater than
			** 'key', then it is returned directly.
			**
			** -- RETURN VALUE --
			** The returned iterator points to the node considered to come AFTER
			** a node containing 'key'.
			*/
			iterator		upper_bound(key_type const & key) {
				t_bstnode * nearest_node = getNearestNode(_root, NULL, key);
				iterator	ret(nearest_node);

				if (C_key(*nearest_node->key) <= C_key(key))
					++ret;
				return(ret);
			}

			const_iterator	upper_bound(key_type const & key) const {
				t_bstnode * 	nearest_node = getNearestNode(_root, NULL, key);
				const_iterator	ret(nearest_node);

				if (C_key(*nearest_node->key) <= C_key(key))
					++ret;
				return(ret);
			}
			
			/* EQUAL RANGE */
			/*
			** This function returns the bounds of a range containing all nodes
			** with a key equal to 'key', wherein the first iterator points to
			** the beginning of the range and the second iterator points past
			** the end of the range. This tree implementation only admits unique
			** keys, so at most the range will consist of one node (the one
			** pointed to by the first iterator).
			**
			** If no match exists for 'key' then both iterators will point to
			** the node that would come after 'key'.
			**
			** The idea here is, imagine that you have a dictionary and one of
			** the keys is 'light', with multiple possible definitions. So you
			** have multiple 'lights' (not in a map, since it only admits unique
			** keys, but maybe in a multimap). For example:
			**
			** KEY		VAL
			** light	electromagnetic wave
			** light	elementary particle
			** light	luminous, bright
			** light	low in weight
			** lot		plot of land
			**
			** So, lower_bound("light") will return the first 'light',
			** upper_bound("light") will return 'lot', and now you can iterate
			** through the range, like so:
			**
			** for (it = lower_bound("light"), end = upper_bound("light"); it != end; ++it)
			**	do_stuff
			**
			** Or using for_each, if you're into that sort of thing, of course.
			** I happen to enjoy writing for loops. ;)
			**
			** In other words, you have a range of equal values - an
			** 'equal_range'.
			**
			** That's probably what you want the *_bound functions for, so the
			** equal_range function just directly retrieves that range for you
			** and sticks it in a pair with two iterators.
			**
			** This is all explained terribly in the reference manuals, because
			** C++ is all about making simple things simple. :p
			**
			** -- RETURN VALUE --
			** A pair of iterators, respectively the lower_bound and upper_bound
			** of the 'key' argument.
			*/
			ft::pair<iterator, iterator>				equal_range(key_type const & key) {
				return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(key_type const & key) const {
				return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}

			/* COUNT */
			/*
			** Returns the number of elements containing the key passed as key.
			** For this tree this will always be either 0 or 1 as duplicates are
			** not allowed, but a private recursive counting function is called
			** that will also work with multimap trees. If I ever make one. ;p
			**
			** -- RETURN VALUE --
			** The number of elements containing the 'key' passed as argument.
			*/
			size_type	count(key_type const & key) const {
				return (recursive_count(_root, key));
			}

			/* FIND */
			/*
			** -- RETURN VALUE --
			** Returns an iterator to the node with a key equal to the argument
			** passed as 'key'. If no such node exists, returns the end
			** iterator.
			*/
			iterator	find(key_type const & key) {
				t_bstnode *	node = bintree_search(_root, key);
				return (node == NULL ? end() : iterator(node));
			}

			t_bstnode * getMax(void) {
				return(_max);
			}

			t_bstnode *	findMax(void) {
				t_bstnode * node = _root;
				while (node->right != NULL)
					node = node->right;
				return (node);
			}
			t_bstnode *	findMin(void) {
				t_bstnode * node = _root;
				while (node->left != NULL)
					node = node->left;
				return (node);
			}
	};
}

#endif