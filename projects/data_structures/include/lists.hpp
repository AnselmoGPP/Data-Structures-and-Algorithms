#ifndef LISTS_HPP
#define LISTS_HPP

#include <initializer_list>
#include <stdexcept>

namespace dsa
{
	// Main declarations ----------------------------------------

	template <typename T> class List;
	template <typename T> class StaticArray;
	template <typename T> class DynamicArray;
	template <typename T> class SinglyLinkedList;
	template <typename T> class DoubleLinkedList;
	template <typename T> class XorLinkedList;
		
	template <typename T>
	size_t find(List<T>* list, const T& item);

	template <typename T>
	void printList(List<T>* list);

	template <typename T>
	void swap(T& a, T& b);

	void test_StaticArray();
	void test_DynamicArray();
	void test_SinglyLinkedList();
	void test_DoubleLinkedList();
	void test_XorLinkedList();

	template<typename T> using SA = StaticArray<T>;
	template<typename T> using DA = DynamicArray<T>;
	template<typename T> using SLL = SinglyLinkedList<T>;
	template<typename T> using DLL = DoubleLinkedList<T>;
	template<typename T> using XLL = XorLinkedList<T>;


	// Classes ----------------------------------------

	/// Abstract class: List.
	template <typename T>
	class List
	{
	public:
		typedef	T value_type;
		typedef	size_t size_type;

		List() = default;
		List(size_t size) { };
		List(const std::initializer_list<T>& il) { };
		List(const List& obj) { };   // Copy constructor
		virtual ~List() { };

		virtual	void clear() = 0;
		virtual	void insert(const T& item) = 0;
		virtual	void append(const T& item) = 0;
		virtual	T remove() = 0;
		
		virtual	size_t length() const = 0;
		virtual	size_t currPos() const = 0;
		virtual	const T& getValue() const = 0;
		
		virtual	void moveToStart() = 0;
		virtual	void moveToEnd() = 0;
		virtual	void moveToPos(size_t pos) = 0;
		virtual	void prev() = 0;
		virtual	void next() = 0;

		//virtual List& operator=(const List& obj) { return *this; };   // Copy-assignment operator
		//virtual T& operator[](size_t i) const = 0;   // Subscript operator
	};


	/// Static array-based list class. It stores a dynamic number of elements (size) of type T in an internal array of static capacity (capacity).  
	template <typename T>
	class StaticArray : public List<T>
	{
	protected:
		T* array;
		size_t capacity;   // Max. size (x)
		size_t size;   // Active elements (n)
		size_t curr;   // Range: [0, n]

	public:
		StaticArray(size_t capacity = 1);   // O(n) if T has constructor
		StaticArray(const std::initializer_list<T>& il);   // O(n)
		StaticArray(const StaticArray& obj);   // O(n)
		virtual ~StaticArray() override;   // O(n) if T has constructor

		StaticArray& operator=(const StaticArray& obj);   // O(n)
		T& operator[](size_t i) const;

		virtual void clear() override;
		virtual void insert(const T& item) override;   // O(n)
		virtual void append(const T& item) override;
		virtual T remove() override;   // O(n)

		size_t length() const override;
		size_t currPos() const override;
		const T& getValue() const override;

		void moveToStart() override;
		void moveToEnd() override;
		void moveToPos(size_t pos) override;
		void prev() override;
		void next() override;
	};


	/// Dynamic array-based list class. It stores a dynamic number of elements (size) of type T in an internal array of dynamic capacity (capacity).  
	template<typename T>
	class DynamicArray : public StaticArray<T>
	{
		inline void increaseCapacity();   // O(n)
		inline void decreaseCapacity();   // O(n)

	public:
		DynamicArray(size_t size = 0);   // O(n) if T has constructor
		DynamicArray(const std::initializer_list<T>& il);   // O(n)
		DynamicArray(const DynamicArray& obj);   // O(n)
		~DynamicArray() override;   // O(n) if T has constructor

		DynamicArray& operator=(const DynamicArray& obj);   // O(n)

		void clear() override;   // O(n) if T has destructor
		void insert(const T& item) override;   // O(n)
		void append(const T& item) override;   // O(n)
		T remove() override;   // O(n)
	};


	/// Base class: Node. It stores the item (element) and the methods to retrieve it and modify it.
	template <typename T>
	class Node
	{
	public:
		typedef T value_type;
		typedef size_t size_type;

		 Node();
		 Node(T content);
		 Node(const Node& obj);
		virtual ~Node();

		T element;

		Node& operator=(const Node& obj) const;

		//void* operator new(size t);
		//void operator delete(void* ptr);
	};

	/// Node type for a singly linked list. Contains an item (content) of type T and a pointer to the next node (next). 
	template <typename T>
	class SNode : public Node<T>
	{
	public:
		 SNode(const T &content, SNode *nextNode = nullptr);
		 SNode(SNode* nextNode = nullptr);
		 SNode(const SNode &obj);
		 ~SNode();

		SNode& operator=(const SNode& obj) const;

		SNode* next;

		void setNode(const T& content, SNode* nextNode);
	};

	/// Node type for a double linked list. Contains an item (content) of type T and two pointers: next node (next) and previous node (prev). 
	template <typename T>
	class DNode : public Node<T>
	{
	public:
		DNode(const T& content, DNode* prevNode = nullptr, DNode* nextNode = nullptr);
		DNode(DNode* prevNode = nullptr, DNode* nextNode = nullptr);
		DNode(const DNode& obj);
		~DNode();
		
		DNode& operator=(const DNode& obj) const;

		DNode* next;
		DNode* prev;

		void setNode(const T& content, DNode* prevNode, DNode* nextNode);
	};

	/// Node type for a double linked list, but memory optimized (space/time tradeoff). Instead of containing two pointers, it has the XOR of both (a XOR b = C) (bitwise exclusive OR). To know any of the 2 pointers, you have to provide the other (a = b XOR C) (b = a XOR C).
	template <typename T>
	class XorNode : public Node<T>
	{
		XorNode* npx; // = prev XOR next

		XorNode* XOR(XorNode* x, XorNode* a);

	public:
		XorNode(const T& content, XorNode* prevNode = nullptr, XorNode* nextNode = nullptr);
		XorNode(XorNode* prevNode = nullptr, XorNode* nextNode = nullptr);
		XorNode(const XorNode& obj);
		~XorNode();

		XorNode& operator=(const XorNode& obj) const;

		void setNode(const T& content, XorNode* prev, XorNode* next);
		void setNode(XorNode* prev, XorNode* next);
		inline XorNode* next(XorNode* prev);
		inline XorNode* prev(XorNode* next);
	};

	/// Singly linked list class that stores a set of linked nodes, each one containing some item of type T (content).
	template <typename T>
	class SinglyLinkedList : public List<T>
	{
		SNode<T>* head;   // Header node: Additional first node whose value is ignored.
		SNode<T>* tail;   // Last node
		SNode<T>* curr;   // Node preceding the current node. Used to select a node.
		size_t count;   // Number of nodes
		SNode<T>* freelist;   // Object pool for unused nodes. Avoids calling "new SNode" too much.

		SNode<T>* newNode(const T& content, SNode<T>* nextNode);
		void deleteNode(SNode<T>* node);

	public:
		SinglyLinkedList();
		SinglyLinkedList(const std::initializer_list<T>& il);   // O(n)
		SinglyLinkedList(const SinglyLinkedList& obj);   // O(n)
		~SinglyLinkedList() override;   // O(n)

		SinglyLinkedList& operator=(const SinglyLinkedList& obj);   // O(n)
		const T& operator[](size_t i) const;   // O(n)

		void clear() override;
		void insert(const T& content) override;
		void append(const T& content) override;
		T remove() override;

		size_t length() const override;
		size_t currPos() const override;   // O(n)
		const T& getValue() const override;

		void moveToStart() override;
		void moveToEnd() override;
		void moveToPos(size_t pos) override;   // O(n)
		void prev() override;   // O(n)
		void next() override;
	};

	/// Double linked list class that stores a set of linked nodes, each one containing some item of type T (content).
	template <typename T>
	class DoubleLinkedList : public List<T>
	{
		DNode<T>* head;   // Header node: Additional first node whose value is ignored.
		DNode<T>* tail;   // Tailer node: Additional last node whose value is ignored.
		DNode<T>* curr;   // Node preceding the current node. Used to select a node.
		size_t count;   // Number of nodes
		DNode<T>* freelist;   // Object pool for unused nodes. Avoids calling "new SNode" too much.

		DNode<T>* newNode(const T& content, DNode<T>* prevNode, DNode<T>* nextNode);
		void deleteNode(DNode<T>* node);

	public:
		DoubleLinkedList();
		DoubleLinkedList(const std::initializer_list<T>& il);   // O(n)
		DoubleLinkedList(const DoubleLinkedList& obj);   // O(n)
		~DoubleLinkedList() override;   // O(n)

		DoubleLinkedList& operator=(const DoubleLinkedList& obj);   // O(n)
		const T& operator[](size_t i) const;   // O(n)

		void clear() override;
		void insert(const T& content) override;
		void append(const T& content) override;
		T remove() override;

		size_t length() const override;
		size_t currPos() const override;   // O(n)
		const T& getValue() const override; 

		void moveToStart() override;
		void moveToEnd() override;
		void moveToPos(size_t pos) override;   // O(n)
		void prev() override;
		void next() override;
	};

	/// Double linked list class, but memory optimized (space/time tradeoff) since it uses DNodeXor nodes (only store one pointer).
	template <typename T>
	class XorLinkedList : public List<T>
	{
		XorNode<T>* head;   // Header node: Additional first node whose value is ignored.
		XorNode<T>* tail;   // Tailer node: Additional last node whose value is ignored.
		XorNode<T>* curr;   // Node preceding the current node. Used to select a node.
		XorNode<T>* currPrev;   // Node preceding curr node (needed for accessing curr.next in O(1) time).
		size_t count;   // Number of nodes
		XorNode<T>* freelist;   // Object pool for unused nodes. Avoids calling "new SNode" too much.

		XorNode<T>* newNode(const T& content, XorNode<T>* prevNode, XorNode<T>* nextNode);
		void deleteNode(XorNode<T>* node);
		void deleteList(XorNode<T>* node, XorNode<T>* prevNode);   // O(n)

	public:
		XorLinkedList();
		XorLinkedList(const std::initializer_list<T>& il);   // O(n)
		XorLinkedList(const XorLinkedList& obj);   // O(n)
		~XorLinkedList() override;   // O(n)

		XorLinkedList& operator=(const XorLinkedList& obj);   // O(n)
		const T& operator[](size_t i) const;   // O(n)

		void clear() override;
		void insert(const T& content) override;
		void append(const T& content) override;
		T remove() override;

		size_t length() const override;
		size_t currPos() const override;   // O(n)
		const T& getValue() const override;

		void moveToStart() override;
		void moveToEnd() override;
		void moveToPos(size_t pos) override;   // O(n)
		void prev() override;
		void next() override;
	};


	// Definitions ----------------------------------------

	// -- StaticArray --------------------------------------

	/// Constructor. Allocate memory for a number of elements.
	template <typename T>
	StaticArray<T>::StaticArray(size_t capacity)
		: List(), capacity(capacity), size(0), curr(0)
	{
		array = new T[capacity];
	}

	/// Constructor. Allocate memory for the elements in the initializer list and copy them into our list.
	template <typename T>
	StaticArray<T>::StaticArray(const std::initializer_list<T>& il)
		: capacity(il.size()), size(il.size()), curr(0)
	{
		array = new T[il.size()];

		const T* item = il.begin();
		for (size_t i = 0; i < il.size(); i++)
			array[i] = item[i];
	}

	/// Copy constructor.
	template <typename T>
	StaticArray<T>::StaticArray(const StaticArray& obj)
	{
		capacity = obj.capacity;
		size = obj.size;
		curr = obj.curr;

		array = new T[capacity];
		for (size_t i = 0; i < capacity; i++)
			array[i] = obj.array[i];
	}

	/// Destructor. Delete the memory allocated by the constructor for this list. 
	template <typename T>
	StaticArray<T>::~StaticArray() { delete[] array; }

	/// Copy-assignment operator overloading.
	template <typename T>
	StaticArray<T>& StaticArray<T>::operator=(const StaticArray& obj)
	{
		if (this == &obj) return *this;
		
		capacity = obj.capacity;
		size = obj.size;
		curr = obj.curr;

		delete[] array;
		array = new T[capacity];
		for (size_t i = 0; i < capacity; i++)
			array[i] = obj.array[i];

		return *this;
	}

	/// Subscript operator overloading.
	template <typename T>
	T& StaticArray<T>::operator[](size_t i) const
	{
		if (i >= size)
			throw std::out_of_range("Subscript out of range");

		return array[i];
	}

	/// Set size to 0 (capacity remains the same).
	template <typename T>
	void StaticArray<T>::clear() { size = curr = 0; }

	/// Store a new element in the list just before the current position.
	template <typename T>
	void StaticArray<T>::insert(const T& item)
	{
		if (size == capacity)
			throw std::out_of_range("List capacity exceeded");

		for (size_t i = size; i > curr; i--)
			array[i] = array[i - 1];

		array[curr] = item;
		size++;
	}

	/// Store a new element at the end of the list (size).
	template <typename T>
	void StaticArray<T>::append(const T& item)
	{
		if (size == capacity)
			throw std::out_of_range("List capacity exceeded");

		array[size++] = item;
	}

	/// Remove the current element from the list.
	template <typename T>
	T StaticArray<T>::remove()
	{
		if (curr >= capacity)
			throw std::out_of_range("No current element");

		T item = array[curr];

		for (int i = curr; i < size - 1; i++)
			array[i] = array[i + 1];

		size--;
		return item;
	}

	/// Move curr to the first element.
	template <typename T>
	void StaticArray<T>::moveToStart() { curr = 0; }

	/// Move curr to element one-past-the-end.
	template <typename T>
	void StaticArray<T>::moveToEnd() { curr = size; }

	/// Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void StaticArray<T>::moveToPos(size_t pos)
	{
		if (pos > size)
			throw std::out_of_range("Pos out of range");

		curr = pos;
	}

	/// Move curr to the previous element, except when curr==0.
	template <typename T>
	void StaticArray<T>::prev() { if (curr != 0) curr--; }

	/// Move curr to the next element, it it exists (including one-past-the-end).
	template <typename T>
	void StaticArray<T>::next() { if (curr <= size) curr++; }

	/// Get the number of elements in the list.
	template <typename T>
	size_t StaticArray<T>::length() const { return size; }

	/// Get the position number of the current element.
	template <typename T>
	size_t StaticArray<T>::currPos() const { return curr; }

	/// Get the element stored in the current position.
	template <typename T>
	const T& StaticArray<T>::getValue() const
	{
		if (curr >= size)
			throw std::out_of_range("No current element");

		return array[curr];
	}

	/// External template function for any List subclass. If item is found, returns its position. Otherwise, returns array size. The value of List::currPos can be modified.
	template <typename T>
	size_t find(List<T>* list, const T& item)
	{
		int i = 0;
		for (list->moveToStart(); list->currPos() < list->length(); list->next())
		{
			if (item == list->getValue())
				return list->currPos();
		}

		return list->currPos();
	}

	/// Print all the elements in the list.
	template <typename T>
	void printList(List<T>* list)
	{
		for (list->moveToStart(); list->currPos() < list->length(); list->next())
			std::cout << list->getValue() << " ";

		std::cout << std::endl;
	}

	/// Memory efficient swap operation. Alternatively, it can be made faster using more memory.
	template <typename T>
	void swap(T& a, T& b)
	{
		// Option 1: Faster, but uses more space.
		// T temp = a;
		// a = b;
		// b = temp;

		// Option 2: Slower, but uses less space.
		a = a + b;
		b = a - b;
		a = a - b;
	}


	// -- DynamicArray --------------------------------------

	/// Constructor. Allocate memory for a number of elements.
	template <typename T>
	DynamicArray<T>::DynamicArray(size_t size) : StaticArray(size) { }

	/// Constructor. Allocate memory for the elements in the initializer list and copy them into our list.
	template <typename T>
	DynamicArray<T>::DynamicArray(const std::initializer_list<T>& il) : StaticArray(il) { }

	/// Copy constructor.
	template <typename T>
	DynamicArray<T>::DynamicArray(const DynamicArray& obj) : StaticArray(obj) { }

	/// Destructor. Delete the memory allocated by the constructor for this list. 
	template <typename T>
	DynamicArray<T>::~DynamicArray() { }

	/// Copy-assignment operator overloading.
	template <typename T>
	DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& obj)
	{
		if (this == &obj) return *this;
		
		capacity = obj.capacity;
		size = obj.size;
		curr = obj.curr;

		delete[] array;
		array = new T[capacity];
		for (size_t i = 0; i < capacity; i++)
			array[i] = obj.array[i];

		return *this;
	}

	/// Increase array capacity if necessary.
	template <typename T>
	void DynamicArray<T>::increaseCapacity()
	{
		if (size == capacity)
		{
			capacity = capacity ? capacity * 2 : 1;
			T* newArray = new T[capacity];

			for (size_t i = 0; i < size; i++)
				newArray[i] = array[i];

			delete[] array;
			array = newArray;
		}
	}

	/// Decrease array capacity if necessary.
	template <typename T>
	void DynamicArray<T>::decreaseCapacity()
	{
		if (capacity && size == (capacity / 4))
		{
			capacity /= 2;
			T* newArray = new T[capacity];

			for (size_t i = 0; i < size; i++)
				newArray[i] = array[i];

			delete[] array;
			array = newArray;
		}
	}

	/// Set size to 0 (capacity remains the same).
	template <typename T>
	void DynamicArray<T>::clear()
	{
		capacity = size = curr = 0;
		delete[] array;
		array = new T[0];
	}

	/// Store a new element in the list just before the current position.
	template <typename T>
	void DynamicArray<T>::insert(const T& item)
	{
		increaseCapacity();

		for (size_t i = size; i > curr; i--)
			array[i] = array[i - 1];

		array[curr] = item;
		size++;
	}

	/// Store a new element at the end of the list (size).
	template <typename T>
	void DynamicArray<T>::append(const T& item)
	{
		increaseCapacity();

		array[size++] = item;
	}

	/// Remove the current element from the list.
	template <typename T>
	T DynamicArray<T>::remove()
	{
		if (curr >= capacity)
			throw std::out_of_range("No current element");

		decreaseCapacity();

		T item = array[curr];

		for (int i = curr; i < size - 1; i++)
			array[i] = array[i + 1];

		size--;
		return item;
	}


	// -- Node --------------------------------------

	/// Constructor.
	template <typename T>
	Node<T>::Node() { };

	/// Constructor.
	template <typename T>
	Node<T>::Node(T content) : element(content) { };

	/// Copy constructor.
	template <typename T>
	Node<T>::Node(const Node& obj) : element(obj.element) { };

	/// Destructor.
	template <typename T>
	Node<T>::~Node() { };

	/// Copy-assignment operator overloading.
	template <typename T>
	Node<T>& Node<T>::operator=(const Node& obj) const 
	{ 
		if (this != &obj) 
			element = obj.element; 

		return *this; 
	};


	// -- SNode --------------------------------------

	/// Constructor. Specify the item (element) and next node.
	template <typename T>
	SNode<T>::SNode(const T& content, SNode* nextNode)
		: Node(content), next(nextNode) { }

	/// Constructor. Specify next node.
	template <typename T>
	SNode<T>::SNode(SNode* nextNode)
		: Node(), next(nextNode) { }

	/// Copy constructor. Be careful: The pointer to next node is copied (multiple pointers pointing to the same node may cause problems when such node is destroyed).
	template <typename T>
	SNode<T>::SNode(const SNode& obj)
		: Node(obj.element), next(obj.next) { }

	/// Destructor. Destroys the next node (which causes the destruction of subsequent nodes).
	template <typename T>
	SNode<T>::~SNode()
	{ 
		if (next != nullptr) delete next; 
	}

	/// Copy-assignment operator overloading.
	template <typename T>
	SNode<T>& SNode<T>::operator=(const SNode &obj) const
	{
		if (this != &obj)
		{
			(Node&)(*this) = obj;
			next = obj.next;
		}

		return *this;
	}

	/// Set all member variables of the node.
	template <typename T>
	void SNode<T>::setNode(const T& content, SNode* nextNode)
	{
		element = content;
		next = nextNode;
	}


	// -- DNode --------------------------------------

	/// Constructor. Specify the item (element) and previous and next nodes.
	template <typename T>
	DNode<T>::DNode(const T& content, DNode* prevNode, DNode* nextNode)
		: Node(content), prev(prevNode), next(nextNode) { }

	/// Constructor. Specify previous and next nodes.
	template <typename T>
	DNode<T>::DNode(DNode* prevNode, DNode* nextNode)
		: Node(), prev(prevNode), next(nextNode) { }

	/// Copy constructor. Be careful: The pointers to previous and next node are copied (multiple pointers pointing to the same node may cause problems when such node is destroyed).
	template <typename T>
	DNode<T>::DNode(const DNode& obj)
		: Node(obj.element), prev(obj.prev), next(obj.next) { }

	/// Destructor. Destroys the next link node (which causes the destruction of subsequent nodes), but not prev link node.
	template <typename T>
	DNode<T>::~DNode()
	{
		//if (prev != nullptr) delete prev;
		if (next != nullptr) delete next;
	}

	/// Copy-assignment operator overloading.
	template <typename T>
	DNode<T>& DNode<T>::operator=(const DNode& obj) const
	{
		if (this != &obj)
		{
			(Node&)(*this) = obj;
			prev = obj.prev;
			next = obj.next;
		}

		return *this;
	}
	
	/// Set all member variables of the node.
	template <typename T>
	void DNode<T>::setNode(const T& content, DNode* prevNode, DNode* nextNode)
	{
		element = content;
		prev = prevNode;
		next = nextNode;
	}


	// -- DNodeXor --------------------------------------

	/// Constructor. Specify the item (element) and previous and next nodes.
	template <typename T>
	XorNode<T>::XorNode(const T& content, XorNode* prevNode, XorNode* nextNode)
		: Node(content), npx(XOR(prevNode, nextNode)) { }

	/// Constructor. Specify previous and next nodes.
	template <typename T>
	XorNode<T>::XorNode(XorNode* prevNode, XorNode* nextNode)
		: Node(), npx(XOR(prevNode, nextNode)) { }

	/// Copy constructor. Be careful: The pointers to previous and next node are copied (multiple pointers pointing to the same node may cause problems when such node is destroyed).
	template <typename T>
	XorNode<T>::XorNode(const XorNode& obj)
		: Node(obj.element), npx(nullptr) { }

	/// Destructor. User is responsible for deleting link nodes. XorNode cannot delete any link node by itself (unlike SNode or DNode) because needs user-provided information about a link-node.
	template <typename T>
	XorNode<T>::~XorNode() { }

	/// Copy-assignment operator overloading.
	template <typename T>
	XorNode<T>& XorNode<T>::operator=(const XorNode& obj) const
	{
		if (this != &obj)
		{
			(Node&)(*this) = obj;
			npx = obj.npx;
		}

		return *this;
	}

	/// Set all member variables of the node (npx member is set based on the prev and next link nodes).
	template <typename T>
	void XorNode<T>::setNode(const T& content, XorNode* prev, XorNode* next)
	{
		element = content;
		npx = XOR(prev, next);
	}

	/// Set the npx member based on the prev and next link nodes.
	template <typename T>
	void XorNode<T>::setNode(XorNode* prev, XorNode* next)
	{
		npx = XOR(prev, next);
	}

	template <typename T>
	XorNode<T>* XorNode<T>::next(XorNode* prev) { return XOR(npx, prev); }

	template <typename T>
	XorNode<T>* XorNode<T>::prev(XorNode* next) { return XOR(npx, next); }

	/// XOR operator. Useful for finding out the other link pointer (given x=aXORb, then a=xXORb and b = xXORa)
	template <typename T>
	XorNode<T>* XorNode<T>::XOR(XorNode* x, XorNode* a)
	{
		return reinterpret_cast<XorNode*>(reinterpret_cast<uintptr_t>(x) ^ reinterpret_cast<uintptr_t>(a));
	}


	// -- SinglyLinkedList --------------------------------------

	/// Constructor.
	template <typename T>
	SinglyLinkedList<T>::SinglyLinkedList()
		: count(0), freelist(nullptr)
	{ 
		curr = head = tail = new SNode<T>(nullptr);
	}

	/// Constructor. It takes an initialization list.
	template <typename T>
	SinglyLinkedList<T>::SinglyLinkedList(const std::initializer_list<T>& il)
		: count(0), freelist(nullptr)
	{
		curr = head = tail = new SNode<T>(nullptr);

		for(const T& item : il)
			append(item);
	}

	/// Copy constructor.
	template <typename T>
	SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& obj)
		: count(0), freelist(nullptr)
	{
		head = tail = curr = new SNode<T>(nullptr);

		for (SNode<T>* node = obj.head->next; node != nullptr; node = node->next)
		{
			append(node->element);
			if (obj.curr == node) curr = tail;
		}

		// freelist is not copied
	}

	/// Destructor. Delete all nodes in the list, including header node.
	template <typename T>
	SinglyLinkedList<T>::~SinglyLinkedList()
	{
		delete head;
		delete freelist;
	}

	/// Copy-assignment operator overloading.
	template <typename T>
	SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& obj)
	{
		if (this == &obj) return *this;
		
		clear();

		for (SNode<T>* node = obj.head->next; node != nullptr; node = node->next)
		{
			append(node->element);
			if (obj.curr == node) curr = tail;
		}

		// freelist is not copied

		return *this;
	}

	/// Subscript operator overloading. It returns "const T&" instead of "T&" because node<T>::element returns "const T&". The current node is not changed.
	template <typename T>
	const T& SinglyLinkedList<T>::operator[](size_t pos) const
	{
		if (pos >= count)
			throw std::out_of_range("No current element");

		SNode<T>* nod = head->next;
		for (size_t i = 0; i < pos; i++)
			nod = nod->next;

		return nod->element;
	}

	/// Allocate memory for a node (or take one node's address from freelist, if available), configure the new node, and return a pointer to it.
	template <typename T>
	SNode<T>* SinglyLinkedList<T>::newNode(const T& content, SNode<T>* nextNode)
	{
		if (freelist == nullptr)
			return new SNode<T>(content, nextNode);

		SNode<T>* newNode = freelist;
		freelist = freelist->next;
		newNode->setNode(content, nextNode);
		return newNode;
	}

	/// Save this node in the freelist (head)
	template <typename T>
	void SinglyLinkedList<T>::deleteNode(SNode<T>* node)
	{
		node->next = freelist;
		freelist = node;
	}

	/// Move all nodes in the list to the freelist, except header node.
	template <typename T>
	void SinglyLinkedList<T>::clear()
	{
		if (count == 0) return;

		tail->next = freelist;
		freelist = head->next;
		head->next = nullptr;

		curr = tail = head;
		count = 0;
	}

	/// Store a new node in the list just before the current position.
	template <typename T>
	void SinglyLinkedList<T>::insert(const T &content)
	{
		curr->next = newNode(content, curr->next);   // New node inserted after curr (to insert in the head, we use header node)
		if (tail == curr) tail = curr->next;
		count++;
	}
	
	/// Store a new node at the end of the list (tail).
	template <typename T>
	void SinglyLinkedList<T>::append(const T& content)
	{
		tail = tail->next = newNode(content, nullptr);
		count++;
	}

	/// Remove the current node from the list and save it in the freelist.
	template <typename T>
	T SinglyLinkedList<T>::remove()
	{	
		if (curr == tail) throw std::out_of_range("No current element");
		if (curr->next == tail) tail = curr;
		
		SNode<T>* extract = curr->next;
		T content = extract->element;

		curr->next = curr->next->next;
		deleteNode(extract);
		count--;
		return content;
	}

	/// Get the number of nodes in the list.
	template <typename T>
	size_t SinglyLinkedList<T>::length() const { return count; }

	/// Get the position number of the current node.
	template <typename T>
	size_t SinglyLinkedList<T>::currPos() const
	{
		SNode<T> *node = head;
		size_t i;

		for (i = 0; curr != node; i++)
			node = node->next;

		return i;
	}

	/// Get the item stored in the current node.
	template <typename T>
	const T& SinglyLinkedList<T>::getValue() const
	{
		if (curr == tail)
			throw std::out_of_range("No current element");

		return curr->next->element;
	}

	/// Move curr to the header node.
	template <typename T>
	void SinglyLinkedList<T>::moveToStart() { curr = head; }

	/// Move curr to the tail (node one-past-the-end).
	template <typename T>
	void SinglyLinkedList<T>::moveToEnd() { curr = tail; }

	/// Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void SinglyLinkedList<T>::moveToPos(size_t pos)
	{
		if (pos > count)
			throw std::out_of_range("No current element");

		curr = head;
		for (size_t i = 0; i < pos; i++) 
			curr = curr->next;
	}

	/// Move curr to the previous node, except when curr==head.
	template <typename T>
	void SinglyLinkedList<T>::prev()
	{
		if (curr != head)
		{
			SNode<T>* node = head;
			while (node->next != curr) node = node->next;
			curr = node;
		}
	}

	/// Move curr to the next node, if it exists (including one-past-the-end).
	template <typename T>
	void SinglyLinkedList<T>::next()
	{
		if (curr != tail)
			curr = curr->next;
	}
	

	// -- DoubleLinkedList --------------------------------------

	/// Constructor.
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList()
		: count(0), freelist(nullptr)
	{
		head = new DNode<T>();
		tail = new DNode<T>();
		head->next = tail;
		tail->prev = head;
		curr = head;
	}

	/// Constructor. It takes an initialization list.
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(const std::initializer_list<T>& il)
		: count(0), freelist(nullptr)
	{
		head = new DNode<T>();
		tail = new DNode<T>();
		head->next = tail;
		tail->prev = head;
		curr = head;

		for (const T& item : il)
			append(item);
	}

	/// Copy constructor.
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& obj)
		: count(0), freelist(nullptr)
	{
		head = new DNode<T>();
		tail = new DNode<T>();
		head->next = tail;
		tail->prev = head;
		curr = head;

		for (DNode<T>* node = obj.head->next; node != obj.tail; node = node->next)
		{
			append(node->element);
			if (obj.curr == node) curr = tail->prev;
		}

		// freelist is not copied
	}

	/// Destructor. Delete all nodes in the list, including header node.
	template <typename T>
	DoubleLinkedList<T>::~DoubleLinkedList()
	{
		delete head;
		delete freelist;
	}
	
	/// Copy-assignment operator overloading.
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& obj)
	{
		if (this == &obj) return *this;
		
		clear();

		for (SNode<T>* node = obj.head->next; node != obj.tail; node = node->next)
		{
			append(node->element);
			if (obj.curr == node) curr = tail->prev;
		}

		// freelist is not copied

		return *this;
	}
	
	/// Subscript operator overloading. It returns "const T&" instead of "T&" because node<T>::element returns "const T&". The current node is not changed.
	template <typename T>
	const T& DoubleLinkedList<T>::operator[](size_t pos) const
	{
		if (pos >= count)
			throw std::out_of_range("No current element");

		DNode<T>* node = head->next;
		for (size_t i = 0; i < pos; i++)
			node = node->next;

		return node->element;
	}
	
	/// Allocate memory for a node (or take one node's address from freelist, if available), configure the new node, and return a pointer to it.
	template <typename T>
	DNode<T>* DoubleLinkedList<T>::newNode(const T& content, DNode<T>* prevNode, DNode<T>* nextNode)
	{
		if (freelist == nullptr)
			return new DNode<T>(content, prevNode, nextNode);

		DNode<T>* newNode = freelist;
		freelist = freelist->next;
		newNode->setNode(content, prevNode, nextNode);
		return newNode;
	}

	/// Save this node in the freelist (head)
	template <typename T>
	void DoubleLinkedList<T>::deleteNode(DNode<T>* node)
	{
		node->next = freelist;
		freelist = node;
	}

	/// Move all nodes in the list to the freelist, except header and tail node.
	template <typename T>
	void DoubleLinkedList<T>::clear()
	{
		if (count == 0) return;

		tail->prev->next = freelist;
		freelist = head->next;

		head->next = tail;
		tail->prev = head;

		curr = head;
		count = 0;
	}

	/// Store a new node in the list just before the current position.
	template <typename T>
	void DoubleLinkedList<T>::insert(const T& content)
	{
		curr->next = curr->next->prev = newNode(content, curr, curr->next);

		count++;
	}

	/// Store a new node at the end of the list (tail).
	template <typename T>
	void DoubleLinkedList<T>::append(const T& content)
	{
		tail->prev = tail->prev->next = newNode(content, tail->prev, tail);
		
		count++;
	}

	/// Remove the current node from the list and save it in the freelist.
	template <typename T>
	T DoubleLinkedList<T>::remove()
	{
		if (curr->next == tail) throw std::out_of_range("No current element");

		DNode<T>* extract = curr->next;
		T content = extract->element;

		curr->next->next->prev = curr;
		curr->next = curr->next->next;
		
		deleteNode(extract);
		count--;
		return content;
	}

	/// Get the number of nodes in the list.
	template <typename T>
	size_t DoubleLinkedList<T>::length() const { return count; }

	/// Get the position number of the current node.
	template <typename T>
	size_t DoubleLinkedList<T>::currPos() const
	{
		DNode<T>* node = head;
		size_t i;

		for (i = 0; curr != node; i++)
			node = node->next;

		return i;
	}

	/// Get the item stored in the current node.
	template <typename T>
	const T& DoubleLinkedList<T>::getValue() const
	{
		if (curr == tail->prev)
			throw std::out_of_range("No current element");
		
		return curr->next->element;
	}

	/// Move curr to the header node.
	template <typename T>
	void DoubleLinkedList<T>::moveToStart() { curr = head; }

	/// Move curr to the tail (node one-past-the-end).
	template <typename T>
	void DoubleLinkedList<T>::moveToEnd() { curr = tail->prev; }

	/// Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void DoubleLinkedList<T>::moveToPos(size_t pos)
	{
		if (pos > count)
			throw std::out_of_range("No current element");

		curr = head;
		for (size_t i = 0; i < pos; i++)
			curr = curr->next;
	}

	/// Move curr to the previous node, except when curr==head.
	template <typename T>
	void DoubleLinkedList<T>::prev() { if (curr != head) curr = curr->prev; }

	/// Move curr to the next node, if it exists (including one-past-the-end).
	template <typename T>
	void DoubleLinkedList<T>::next()
	{
		if (curr != tail->prev)
			curr = curr->next;
	}


	// -- XorLinkedList --------------------------------------

	/// Constructor.
	template <typename T>
	XorLinkedList<T>::XorLinkedList()
		: count(0), freelist(nullptr)
	{
		head = new XorNode<T>();
		tail = new XorNode<T>();
		head->setNode(nullptr, tail);
		tail->setNode(head, nullptr);
		curr = head;
		currPrev = nullptr;
	}

	/// Constructor. It takes an initialization list.
	template <typename T>
	XorLinkedList<T>::XorLinkedList(const std::initializer_list<T>& il)
		: count(0), freelist(nullptr)
	{
		head = new XorNode<T>();
		tail = new XorNode<T>();
		head->setNode(nullptr, tail);
		tail->setNode(head, nullptr);
		curr = head;
		currPrev = nullptr;

		for (const T& item : il)
			append(item);
	}

	/// Copy constructor.
	template <typename T>
	XorLinkedList<T>::XorLinkedList(const XorLinkedList& obj)
		: count(0), freelist(nullptr)
	{
		head = new XorNode<T>();
		tail = new XorNode<T>();
		head->setNode(nullptr, tail);
		tail->setNode(head, nullptr);
		curr = head;
		currPrev = nullptr;

		XorNode<T> *temp, *node = obj.head, *prevNode = nullptr;
		while (node != obj.tail->prev(nullptr))
		{
			temp = node;
			node = node->next(prevNode);
			prevNode = temp;

			append(node->element);
			if (obj.curr == node)
			{
				curr = tail->prev(nullptr);
				currPrev = curr->prev(tail);
			}
		}

		// freelist is not copied
	}

	/// Destructor. Delete all nodes in the list, including header node.
	template <typename T>
	XorLinkedList<T>::~XorLinkedList()
	{
		deleteList(head, nullptr);
		deleteList(freelist, nullptr);
	}

	/// Copy-assignment operator overloading.
	template <typename T>
	XorLinkedList<T>& XorLinkedList<T>::operator=(const XorLinkedList<T>& obj)
	{
		std::cout << "A" << std::flush;
		if (this == &obj) return *this;

		clear();

		XorNode<T>* temp, prevNode = nullptr, node = obj.head;
		while (node != obj.tail)
		{
			temp = node;
			node = node->next(prevNode);
			prevNode = temp;

			append(node->element);
			if (obj.curr == node)
			{
				curr = tail->prev(nullptr);
				currPrev = tail->prev(nullptr)->prev(tail);
			}
		}

		// freelist is not copied
		std::cout << "B" << std::flush;
		return *this;
	}

	/// Subscript operator overloading. It returns "const T&" instead of "T&" because node<T>::element returns "const T&". The current node is not changed.
	template <typename T>
	const T& XorLinkedList<T>::operator[](size_t pos) const
	{
		if (pos >= count)
			throw std::out_of_range("No current element");

		XorNode<T>* temp, *prevNode = head, *node = head->next(nullptr);
		for (size_t i = 0; i < pos; i++)
		{
			temp = node;
			node = node->next(prevNode);
			prevNode = temp;
		}
		
		return node->element;
	}

	/// Allocate memory for a node (or take one node's address from freelist, if available), configure the new node, and return a pointer to it.
	template <typename T>
	XorNode<T>* XorLinkedList<T>::newNode(const T& content, XorNode<T>* prevNode, XorNode<T>* nextNode)
	{
		if (freelist == nullptr)
			return new XorNode<T>(content, prevNode, nextNode);

		XorNode<T>* node = freelist;
		freelist = freelist->next(nullptr);
		freelist->setNode(nullptr, freelist->next(node));
		node->setNode(content, prevNode, nextNode);
		return node;
	}

	/// Save this node in the freelist (head)
	template <typename T>
	void XorLinkedList<T>::deleteNode(XorNode<T>* node)
	{
		if(freelist != nullptr)
			freelist->setNode(node, freelist->next(nullptr));

		node->setNode(nullptr, freelist);
		freelist = node;
	}

	/// Delete all nodes in a list. Used in the destructor.
	template <typename T>
	void XorLinkedList<T>::deleteList(XorNode<T>* node, XorNode<T>* prevNode)
	{
		XorNode<T>* nextNode;
		while (node != nullptr)
		{
			nextNode = node->next(prevNode);
			prevNode = node;
			delete node;
			node = nextNode;
		}
	}

	/// Move all nodes in the list to the freelist, except header and tail node.
	template <typename T>
	void XorLinkedList<T>::clear()
	{
		if (count == 0) return;

		XorNode<T>* prevTail = tail->prev(nullptr);
		XorNode<T>* nextHead = head->next(nullptr);
		
		prevTail->setNode(prevTail->prev(tail), freelist);
		nextHead->setNode(nullptr, nextHead->next(head));

		if(freelist != nullptr)
			freelist->setNode(prevTail, freelist->next(nullptr));
		freelist = nextHead;
		
		head->setNode(nullptr, tail);
		tail->setNode(head, nullptr);

		curr = head;
		currPrev = nullptr;
		count = 0;
	}

	/// Store a new node in the list just before the current position.
	template <typename T>
	void XorLinkedList<T>::insert(const T& content)
	{
		XorNode<T>* nextNode = curr->next(currPrev);
		XorNode<T>* node = newNode(content, curr, nextNode);
		
		nextNode->setNode(node, nextNode->next(curr));
		curr->setNode(currPrev, node);

		count++;
	}

	/// Store a new node at the end of the list (tail).
	template <typename T>
	void XorLinkedList<T>::append(const T& content)
	{
		XorNode<T>* prevNode = tail->prev(nullptr);
		XorNode<T>* node = newNode(content, prevNode, tail);

		prevNode->setNode(prevNode->prev(tail), node);
		tail->setNode(node, nullptr);

		count++;
	}

	/// Remove the current node from the list and save it in the freelist.
	template <typename T>
	T XorLinkedList<T>::remove()
	{
		if (curr->next(currPrev) == tail) throw std::out_of_range("No current element");

		XorNode<T>* remNode = curr->next(currPrev);
		T content = remNode->element;
		XorNode<T>* nextNode = remNode->next(curr);
		
		curr->setNode(currPrev, nextNode);
		nextNode->setNode(curr, nextNode->next(remNode));

		deleteNode(remNode);
		count--;
		return content;
	}

	/// Get the number of nodes in the list.
	template <typename T>
	size_t XorLinkedList<T>::length() const { return count; }

	/// Get the position number of the current node.
	template <typename T>
	size_t XorLinkedList<T>::currPos() const
	{
		XorNode<T> *nextNode, *prevNode = nullptr, *node = head;
		size_t i = 0;
		while (node != curr)
		{
			nextNode = node->next(prevNode);
			prevNode = node;
			node = nextNode;
			i++;
		}

		return i;
	}

	/// Get the item stored in the current node.
	template <typename T>
	const T& XorLinkedList<T>::getValue() const
	{
		if (curr == tail->prev(nullptr))
			throw std::out_of_range("No current element");

		return curr->next(currPrev)->element;
	}

	/// Move curr to the header node.
	template <typename T>
	void XorLinkedList<T>::moveToStart()
	{
		curr = head;
		currPrev = nullptr;
	}

	/// Move curr to the tail (node one-past-the-end).
	template <typename T>
	void XorLinkedList<T>::moveToEnd()
	{
		curr = tail->prev(nullptr);
		currPrev = curr->prev(tail);
	}

	/// Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void XorLinkedList<T>::moveToPos(size_t pos)
	{
		if (pos > count)
			throw std::out_of_range("No current element");

		curr = head;
		currPrev = nullptr;
		XorNode<T>* temp;
		for (size_t i = 0; i < pos; i++)
		{
			temp = curr;
			curr = curr->next(currPrev);
			currPrev = temp;
		}
	}

	/// Move curr to the previous node, except when curr==head.
	template <typename T>
	void XorLinkedList<T>::prev()
	{
		if (curr != head)
		{
			XorNode<T>* temp = curr;
			curr = curr->prev(curr->next(currPrev));
			currPrev = curr->prev(temp);
		}
	}

	/// Move curr to the next node, if it exists (including one-past-the-end).
	template <typename T>
	void XorLinkedList<T>::next()
	{
		if (curr != tail->prev(nullptr))
		{
			XorNode<T>* temp = curr;
			curr = curr->next(currPrev);
			currPrev = temp;
		}
	}
}

#endif