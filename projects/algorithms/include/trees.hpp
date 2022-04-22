#ifndef TREES_HPP
#define TREES_HPP

/*
	BSTNode
	BSTdictionary

	VarBinNode
	LeafNode
	IntlNode

	ArrayTree
*/

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

	/// Dictionary implemented as a Binary Search Tree
	template<typename K, typename T>
	class BSTdictionary
	{
	public:
		BSTdictionary() : root(nullptr), nodeCount(0) { }

		void insert(const K& key, const T& element) {  }
		T& remove(const K& key) { }
		void clear() { }
		T& removeAny() { }
		T& find(const K& key) { }
		size_t size() { return nodeCount; }
		
	private:
		BSTNode<K, T>* root;
		size_t nodeCount;

		T& findHelp(BSTNode<K, T>* node, K key)
		{
			if (node == nullptr) return nullptr;
			if (node->getKey() > 0) return findHelp(node->getLeft(), key);
			else if (node->getKey() == 0) return node->getElement();
			else return findHelp(node->getRight(), key);
		}
	};


	/// Variable Binary Node (ADT). Any subclass must implement isLeaf()
	class VarBinNode
	{
	public:
		VarBinNode() { };
		virtual ~VarBinNode() { };

		virtual bool isLeaf() = 0;

		friend void preorder(VarBinNode* root);

	protected:
		virtual void preorder() = 0;
	};

	void preorder(VarBinNode* root) { if (root) root->preorder(); }

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
	};


	/// Array tree implementation for Complete Binary Trees
	template<typename T>
	class ArrayTree
	{
	public:
		ArrayTree(size_t size) : size(size) { elements = new T[size]; }
		~ArrayTree() { delete[] elements; }

		void setElement(size_t pos, T newElement) { elements[pos] = newElement }
		void setLeft(size_t pos, T newElement) { elements[2 * pos + 1] = newElement }
		void setRight(size_t pos, T newElement) { elements[2 * pos + 2] = newElement }

		T& getElement(size_t pos) { return elements[pos]; }
		T& getLeft(size_t pos) { return elements[2 * pos + 1]; }
		T& getRight(size_t pos) { return elements[2 * pos + 2]; }
		size_t size() { return size; }

		size_t parent(size_t pos);
		size_t leftChild(size_t pos);
		size_t rightChild(size_t pos);
		size_t leftSibling(size_t pos);
		size_t rightSibling(size_t pos);

	private:
		T* elements;
		size_t size;
	};

	// ---------- Definitions ------------------------------

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
		if (root == nullptr) return;
		visitor(root);
		preorder(root.getLeft());
		preorder(root.getRight());
	}

	template<typename K, typename T, typename V>
	void postorder(BSTNode<K, T>* root, V* visitor)
	{

	}

	template<typename K, typename T, typename V>
	void inorder(BSTNode<K, T>* root, V* visitor)
	{

	}

	template<typename K, typename T>
	void LeafNode<K, T>::preorder() 
	{ 
		Visit.VisitLeafNode(operand); 
	}

	template<typename K, typename T>
	void IntlNode<K, T>::preorder()
	{
		Visit.VisitInternalNode(operator);
		if (left) left.preorder();
		if (right) right.preorder();
	}

	template<typename T>
	size_t ArrayTree<T>::parent(size_t pos)
	{
		if (pos != 0) return (pos - 1) / 2
		else return size;
	}

	template<typename T>
	size_t ArrayTree<T>::leftChild(size_t pos)
	{ 
		if (2 * pos + 1 < size) return 2 * pos + 1;
		else return size;
	}

	template<typename T>
	size_t ArrayTree<T>::rightChild(size_t pos)
	{ 
		if (2 * pos + 2 < size) return 2 * pos + 2
		else return size;
	}

	template<typename T>
	size_t ArrayTree<T>::leftSibling(size_t pos)
	{ 
		if (!(pos % 2)) return pos - 1;
		else return size;
	}

	template<typename T>
	size_t ArrayTree<T>::rightSibling(size_t pos)
	{ 
		if (pos % 2 && pos + 1 < size) return pos + 1;
		else return size;
	}
}

#endif