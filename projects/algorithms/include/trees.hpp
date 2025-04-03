#ifndef TREES_HPP
#define TREES_HPP

/*
	BSTNode
	BSTdictionary

	VarBinNode
	LeafNode
	IntlNode

	ArrayTree
	Heap
	Huffman coding tree
*/

#include <algorithm>

namespace ans
{
	/// Generic Binary Search Tree Node.
	template<typename K, typename T>
	class BSTNode
	{
	public:
		BSTNode();
		BSTNode(const K& key, const T& element);
		BSTNode(const K& key, const T& element, BSTNode* left, BSTNode* right);

		void setKey(const K& newKey);
		void setElement(const T& newElement);
		void setLeft(const T& newLeft);
		void setRight(const T& newRight);

		K& getKey();
		T& getElement();
		const BSTNode<K, T>* getLeft();
		const BSTNode<K, T>* getRight();

		bool isLeaf();

	private:
		K key;			//!< There are various ways to deal with keys and comparing records: (1) Key / value pairs (our choice), (2) Especial comparison method, (3) Passing in a comparator function.
		T element;
		BSTNode<K, T>* left;
		BSTNode<K, T>* right;
	};

	template<typename K, typename T, typename V>
	void preorder(BSTNode<K, T>* root, V* visitor);

	template<typename K, typename T, typename V>
	void postorder(BSTNode<K, T>* root, V* visitor);

	template<typename K, typename T, typename V>
	void inorder(BSTNode<K, T>* root, V* visitor);

	/// Dictionary implemented as a Binary Search Tree. 
	/** Note: Insertion, is done by creating a copy of key and element */
	template<typename K, typename E>
	class BSTdictionary
	{
	public:
		BSTdictionary() : root(nullptr), nodeCount(0) { }

		void insert(const K& key, const E& element);
		void remove(const K& key);
		E& find(const K& key) { return (findHelp(root, key))->getElement(); }

		void clear();
		void removeRoot();
		size_t size() { return nodeCount; }
		
	private:
		BSTNode<K, E>* root;
		size_t nodeCount;

		BSTNode<K, E>* findHelp(BSTNode<K, E>* node, K key);
		BSTNode<K, E>* insertHelp(BSTNode<K, E>* node, const K& key, const E& element);
		BSTNode<K, E>* removeHelp(BSTNode<K, E>* node, const K& key);
		void printHelp(BSTNode<K, E>* node);
		BSTNode<K, E>* deleteMin(BSTNode<K, E>* node);

		BSTNode<K, E>* getMin(BSTNode<K, E>* node);
	};


	/// Variable Binary Node (ADT). Any subclass must implement isLeaf()
	class VarBinNode
	{
	public:
		VarBinNode() { };
		virtual ~VarBinNode() { };

		virtual bool isLeaf() = 0;

		friend void preorder(VarBinNode* root);
		friend void postorder(VarBinNode* root);
		friend void inorder(VarBinNode* root);

	protected:
		virtual void preorder() = 0;
		virtual void postorder() = 0;
		virtual void inorder() = 0;
	};

	void preorder(VarBinNode* root) { if (root) root->preorder(); }
	void postorder(VarBinNode* root) { if (root) root->postorder(); }
	void inorder(VarBinNode* root) { if (root) root->inorder(); }

	/// Leaf node (key + element)
	template<typename K, typename T>
	class LeafNode : public VarBinNode
	{
	public:
		LeafNode() : VarBinNode() { }
		LeafNode(const T& element) : VarBinNode(), element(element) { }

		void setElement(const T& newElement) { element = newElement; }

		T& getElement() { return element; }

		bool isLeaf() override { return true; }

	private:
		T element;

		void preorder() override;
		void postorder() override;
		void inorder() override;
	};

	/// Internal node (key + element + child nodes)
	template<typename K, typename T>
	class IntlNode : public VarBinNode
	{
	public:
		IntlNode() : VarBinNode() { }
		IntlNode(const T& element) : VarBinNode(), element(element) { }
		IntlNode(const T& element, VarBinNode* left, VarBinNode* right) : VarBinNode(), element(element), left(left), right(right) { }

		void setElement(const T& newElement) { element = newElement; }
		void setLeft(const T& newLeft) { left = newLeft; }
		void setRight(const T& newRight) { right = newRight; }

		T& getElement() { return element; }
		const VarBinNode* getLeft() { return left; }
		const VarBinNode* getRight() { return right; }

		bool isLeaf() override { return false; }

	private:
		T element;
		VarBinNode* left;
		VarBinNode* right;

		void preorder() override;
		void postorder() override;
		void inorder() override;
	};


	/// Array tree implementation for Complete Binary Trees
	template<typename E>
	class ArrayTree
	{
	public:
		ArrayTree(size_t reserve, size_t capacity) : n(reserve), capacity(capacity) { elements = new E[capacity]; }
		virtual ~ArrayTree() { delete[] elements; }	// <<<

		void setElement(size_t pos, const E& newElement) { elements[pos] = newElement }
		void setLeft(size_t pos, const E& newElement) { elements[2 * pos + 1] = newElement }
		void setRight(size_t pos, const E& newElement) { elements[2 * pos + 2] = newElement }

		T& getElement(size_t pos) { return elements[pos]; }
		T& getLeft(size_t pos) { return elements[2 * pos + 1]; }
		T& getRight(size_t pos) { return elements[2 * pos + 2]; }

		virtual bool isLeaf(size_t pos) { return pos >= n/2 && pos < n; }
		size_t size() { return n; }

		size_t parent(size_t pos);
		size_t leftChild(size_t pos);
		size_t rightChild(size_t pos);
		size_t leftSibling(size_t pos);
		size_t rightSibling(size_t pos);

	private:
		E* elements;		//!< Pointer to array
		size_t capacity;	//!< Maximum size
		size_t n;			//!< Number of elements
	};

	template<typename E>
	class MaxHeap : public ArrayTree<E>
	{
	public:
		MaxHeap(E* heap, size_t reserve, size_t capacity) : elements(heap), n(reserve), size(capacity), buildHeap() { }

		void insert(const E& value);
		void buildHeap();
		E& removeMax();
		E& remove(size_t pos);

	private:
		void siftDown(size_t pos);
	};


	// ---------- Definitions ----------------------------------------

	template<typename K, typename T>
	BSTNode<K, T>::BSTNode() 
		: left(nullptr), right(nullptr) { }

	template<typename K, typename T>
	BSTNode<K, T>::BSTNode(const K& key, const T& element) 
		: key(key), element(element) { }

	template<typename K, typename T>
	BSTNode<K, T>::BSTNode(const K& key, const T& element, BSTNode* left, BSTNode* right) 
		: key(key), element(element), left(left), right(right) { }

	template<typename K, typename T>
	void BSTNode<K, T>::setKey(const K& newKey) { key = newKey; }

	template<typename K, typename T>
	void BSTNode<K, T>::setElement(const T& newElement) { element = newElement; }

	template<typename K, typename T>
	void BSTNode<K, T>::setLeft(const T& newLeft) { left = &newLeft; }

	template<typename K, typename T>
	void BSTNode<K, T>::setRight(const T& newRight) { right = &newRight; }

	template<typename K, typename T>
	K& BSTNode<K, T>::getKey() { return key; }

	template<typename K, typename T>
	T& BSTNode<K, T>::getElement() { return element; }

	template<typename K, typename T>
	const BSTNode<K, T>* BSTNode<K, T>::getLeft() { return left; }

	template<typename K, typename T>
	const BSTNode<K, T>* BSTNode<K, T>::getRight() { return right; }

	template<typename K, typename T>
	bool BSTNode<K,T>::isLeaf() { return !(left || right); }

	template<typename K, typename T, typename V>
	void preorder(BSTNode<K, T>* root, V* visitor)
	{
		if (!root) return;
		visitor(root);
		preorder(root.getLeft());
		preorder(root.getRight());
	}

	template<typename K, typename T, typename V>
	void postorder(BSTNode<K, T>* root, V* visitor)
	{
		if (!root) return;
		inorder(root->getLeft());
		inorder(root->getRight());
		visitor(root);
	}

	template<typename K, typename T, typename V>
	void inorder(BSTNode<K, T>* root, V* visitor)
	{
		if (!root) return;
		inorder(root->getLeft());
		visitor(root);
		inorder(root->getRight());
	}

	template<typename K, typename T>
	void LeafNode<K, T>::preorder() 
	{ 
		Visit.VisitLeafNode(operand); 
	}

	template<typename K, typename T>
	void LeafNode<K, T>::postorder()
	{
		
	}

	template<typename K, typename T>
	void LeafNode<K, T>::inorder()
	{
		
	}

	template<typename K, typename T>
	void IntlNode<K, T>::preorder()
	{
		Visit.VisitInternalNode(operator);
		if (left) left.preorder();
		if (right) right.preorder();
	}

	template<typename K, typename T>
	void IntlNode<K, T>::postorder()
	{

	}

	template<typename K, typename T>
	void IntlNode<K, T>::inorder()
	{

	}

	template<typename T>
	size_t ArrayTree<T>::parent(size_t pos)
	{
		if (pos != 0) return (pos - 1) / 2
		else return n;
	}

	template<typename T>
	size_t ArrayTree<T>::leftChild(size_t pos)
	{ 
		if (pos < n/2) return 2 * pos + 1;			// equivalent to: if(1 + 2*pos < n)
		else return n;
	}

	template<typename T>
	size_t ArrayTree<T>::rightChild(size_t pos)
	{ 
		if (pos < (n-1)/2) return 2 * pos + 2;		// equivalent to: if(2 + 2*pos < n)
		else return n;
	}

	template<typename T>
	size_t ArrayTree<T>::leftSibling(size_t pos)
	{ 
		if (!(pos % 2)) return pos - 1;
		else return n;
	}

	template<typename T>
	size_t ArrayTree<T>::rightSibling(size_t pos)
	{ 
		if (pos % 2 && pos + 1 < n) return pos + 1;
		else return n;
	}


	template<typename K, typename E>
	void BSTdictionary<K, E>::insert(const K& key, const E& element)
	{
		root = insertHelp(root, key, element);
		nodecount++;
	}

	template<typename K, typename E>
	void BSTdictionary<K, E>::remove(const K& key)
	{
		BSTNode<K, E>* node = findHelp(root, key);
		if (node)
		{
			root = removeHelp(root, k);
			nodecount--;
		}
	}

	template<typename K, typename E>
	void BSTdictionary<K, E>::clear()
	{ 
		root = nullptr; 
		nodeCount = 0; 
	}

	template<typename K, typename E>
	void BSTdictionary<K, E>::removeRoot()
	{
		if (!root) return;

		root = removeHelp(root, root->key());
		nodecount--;
	}

	template<typename K, typename E>
	BSTNode<K, E>* BSTdictionary<K, E>::findHelp(BSTNode<K, E>* node, K key)
	{
		if (!node) return nullptr;
		if (node->getKey().compareTo(key) > 0) return findHelp(node->getLeft(), key);
		else if (node->getKey().compareTo(key) == 0) return node;
		else return findHelp(node->getRight(), key);
	}

	template<typename K, typename E>
	BSTNode<K, E>* BSTdictionary<K, E>::insertHelp(BSTNode<K, E>* node, const K& key, const E& element)
	{
		if (!node) return new BSTNode<K, E>(key, element);

		if (node->getKey().compareTo(k) > 0)
			node->setLeft(insertHelp(root->left(), key, element));
		else
			root->setRight(insertHelp(root->right(), key, element));

		return node;
	}

	/// Delete the node with the given key. Add the same values to the nodes it traverses; except for the node we are looking for. When found, there are 2 options: (1) if it has only one child, assign that child subtree to his parent, (2) if it has 2 childs, get the node with the minimum key value at the right subtree and assign that node to his parent, then delete the original copied node.
	template<typename K, typename E>
	BSTNode<K, E>* BSTdictionary<K, E>::removeHelp(BSTNode<K, E>* node, const K& key)
	{
		if (!node) return nullptr;

		if (node->getKey().compareTo(key) > 0)
			node->setLeft(removeHelp(node->getLeft(), key));
		else if (node->getKey().compareTo(key) < 0)
			node->setRight(removeHelp(node->getRight(), key));
		else
		{
			if (!node->getLeft()) return node->getRight();
			if (!node->getRight()) return node->getLeft();

			BSTNode<K, E> temp = getMin(node->getRight());
			node->setElement(temp.getElement());
			node->setKey(temp.getKey());
			node->setRight(deleteMin(node->getRight()));
		}
		return node;
	}

	template<typename K, typename E>
	void BSTdictionary<K, E>::printHelp(BSTNode<K, E>* node)
	{
		if (!node) return;
		printHelp(node->getLeft());
		printVisitor(node->getElement());
		printHelp(node->getRight());
	}

	/// Delete the node with the smallest key. Add the same values to the left nodes; except for the last left node, which will be deleted, and its right node will be assigned to his parent's left node.
	template<typename K, typename E>
	BSTNode<K, E>* BSTdictionary<K, E>::deleteMin(BSTNode<K, E>* node)
	{
		if (!node->getLeft()) return node->getRight();
		node->setLeft(deleteMin(node->getLeft()));
		return node;
	}

	/// Get the node containing the minimum value.
	template<typename K, typename E>
	BSTNode<K, E>* BSTdictionary<K, E>::getMin(BSTNode<K, E>* node)
	{
		if (!node->getLeft()) return node;
		return getMin(node->getLeft());
	}
}

// Insert value into heap.
template<typename E>
void MaxHeap<E>::insert(const E& value)
{
	if (n >= capacity) return;

	size_t curr = n++;
	elements[curr] = value;		// Start at end of heap
	while (curr != 0 && elements[curr].compareTo(elements[parent(curr)]) > 0)	// Shift up until key of elements[parent(curr)] > key of elements[curr]
	{
		std::swap(elements[curr], elements[parent(curr)]);
		curr = parent(curr);
	}
}

/// Heapify contents of Heap.
template<typename E>
void MaxHeap<E>::buildHeap()
{
	for (size_t i = n / 2 - 1; i >= 0; i--)
		siftDown(i);
}

/// Remove and return maximum value.
template<typename E>
E& MaxHeap<E>::removeMax()
{
	if (!n) return;		// empty heap

	std::swap(elements[0], elements[--n]);
	if (n) siftDown(0);
	return elements[n];
}

/// Remove and return element at a given position.
template<typename E>
E& MaxHeap<E>::remove(size_t pos)
{
	if (pos >= n) return;	// out of range

	if (pos == n - 1) n--;	// last element
	else
	{
		std::swap(elements[pos], elements[--n]);
		while (pos > 0 && elements[pos].compareTo(elements[parent(pos)]) > 0)	// Move elements[pos] towards the root until his parent is bigger than him
		{
			std::swap(elements[pos], elements[parent(pos)]);
			pos = parent(pos);
		}
		if (n) siftDown(pos);
	}
	return elements[n];
}

/// Put element in its correct place (Given node A whose 2 children are heaps, move A to its correct position in the heap). Move the node toward the leaves by swaping nodes along the way until node[pos] < his parent.
template<typename E>
void MaxHeap<E>::siftDown(size_t pos)
{
	if (pos >= n) return;

	while (!isLeaf(pos))	// Loop: Move node downwards to its right position
	{
		int j = leftChild(pos);
		if (j < (n - 1) && elements[j].compareTo(elements[j + 1] < 0) j++;	// Choose the child with highest value
		if(elements[pos].compareTo(elements[j]) >= 0) return;				// If our node's value > child's value, leave.
		std::swap(elements[pos], elements[j]);								// Otherwise, swap
		pos = j;
	}
}

#endif