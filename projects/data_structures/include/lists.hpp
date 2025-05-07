#ifndef LISTS_HPP
#define LISTS_HPP

#include <initializer_list>
#include <stdexcept>
#include <vector>

namespace dss   // Data Structures namespace
{
	// Main declarations ----------------------------------------

	template <typename T> class List;
	template <typename T> class StaticArray;
	template <typename K, typename E> class SortedStaticArray;
	template <typename T> class DynamicArray;
	template <typename T> class SinglyLinkedList;
	template <typename T> class DoubleLinkedList;
	template <typename T> class XorLinkedList;

	template <typename T> class Stack;
	template <typename T> class SArrayStack;
	template <typename T> class LinkedStack;

	template <typename T> class Queue;
	template <typename T> class SArrayQueue;
	template <typename T> class LinkedQueue;

	template <typename K, typename E> class Dictionary;
	template <typename K, typename E> class StaticArrayDictionary;
	template <typename K, typename E> class SortedStaticArrayDictionary;
		
	template <typename T>
	size_t find(List<T>* list, const T& item);

	template <typename T>
	void printList(List<T>* list);

	template <typename T>
	void swap(T& a, T& b);

	template<template<typename> class T> void test_List();
	template<template<typename, typename> class T> void test_SortedList();
	template<template<typename> class T> void test_Stack();
	template<template<typename> class T> void test_Queue();
	template<template<typename, typename> class T> void test_Dictionary();

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

		//virtual List& operator=(const List& obj) = 0;   // Copy-assignment (cannot be virtual)
		virtual T& operator[](size_t i) const = 0;   // Subscript
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

		void copyFrom(const StaticArray& obj);   // O(n)

	public:
		StaticArray(size_t capacity = 1);   // O(n) if T has constructor
		StaticArray(const std::initializer_list<T>& il);   // O(n)
		StaticArray(const StaticArray& obj);   // O(n)
		virtual ~StaticArray() override;   // O(n) if T has destructor

		StaticArray& operator=(const StaticArray& obj);   // O(n)
		T& operator[](size_t i) const override;

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
		~DynamicArray() override;   // O(n) if T has destructor

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

		Node& operator=(const Node& obj);
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

		SNode& operator=(const SNode& obj);

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
		
		DNode& operator=(const DNode& obj);

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

		XorNode& operator=(const XorNode& obj);

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
		void copyFrom(const SinglyLinkedList& obj);   // O(n)

	public:
		SinglyLinkedList(size_t unusedArg = 0);
		SinglyLinkedList(const std::initializer_list<T>& il);   // O(n)
		SinglyLinkedList(const SinglyLinkedList& obj);   // O(n)
		~SinglyLinkedList() override;   // O(n)

		SinglyLinkedList& operator=(const SinglyLinkedList& obj);   // O(n)
		T& operator[](size_t i) const override;   // O(n)

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
		void copyFrom(const DoubleLinkedList& obj);   // O(n)

	public:
		DoubleLinkedList(size_t unusedArg = 0);
		DoubleLinkedList(const std::initializer_list<T>& il);   // O(n)
		DoubleLinkedList(const DoubleLinkedList& obj);   // O(n)
		~DoubleLinkedList() override;   // O(n)

		DoubleLinkedList& operator=(const DoubleLinkedList& obj);   // O(n)
		T& operator[](size_t i) const override;   // O(n)

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
		XorNode<T>* currPrev;   // Node preceding curr node (allows access curr.next in O(1) time).
		size_t count;   // Number of nodes
		XorNode<T>* freelist;   // Object pool for unused nodes. Avoids calling "new SNode" too much.

		XorNode<T>* newNode(const T& content, XorNode<T>* prevNode, XorNode<T>* nextNode);
		void deleteNode(XorNode<T>* node);
		void deleteList(XorNode<T>* node, XorNode<T>* prevNode);   // O(n)
		void copyFrom(const XorLinkedList& obj);   // O(n)

	public:
		XorLinkedList(size_t unusedArg = 0);
		XorLinkedList(const std::initializer_list<T>& il);   // O(n)
		XorLinkedList(const XorLinkedList& obj);   // O(n)
		~XorLinkedList() override;   // O(n)

		XorLinkedList& operator=(const XorLinkedList& obj);   // O(n)
		T& operator[](size_t i) const override;   // O(n)

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

	/// Abstract class: Stack.
	template <typename T>
	class Stack
	{
	public:
		Stack() { };
		Stack(const Stack& obj) { };   // Copy constructor
		virtual ~Stack() { };

		virtual void clear() = 0;
		virtual void push(const T& newElement) = 0;
		virtual T pop() = 0;
		virtual const T& topValue() const = 0;
		virtual size_t length() const = 0;
	};

	/// Static-array stack.
	template <typename T>
	class SArrayStack : public Stack<T>
	{
	private:
		T* array;
		size_t capacity;   // Max. size (n)
		size_t top;   // Array index of first free position. Range [0, n]
		
		void copyFrom(const SArrayStack& obj);

	public:
		SArrayStack(size_t size = 1);   // O(n) if T has constructor
		SArrayStack(const SArrayStack& obj);   // O(n) if T has constructor
		~SArrayStack() override;   // O(n) if T has destructor

		SArrayStack& operator=(const SArrayStack& obj);

		void clear() override;
		void push(const T& newElement) override;
		T pop() override;
		const T& topValue() const override;
		size_t length() const override;
	};

	/// Linked stack.
	template <typename T>
	class LinkedStack : public Stack<T>
	{
	private:
		SNode<T>* top;   // Pointer to first element
		size_t size;   // Number of elements

		void copyFrom(const LinkedStack& obj);

	public:
		LinkedStack(size_t unusedArg = 0);
		LinkedStack(const LinkedStack& obj);   // O(n) if T has constructor
		~LinkedStack() override;   // O(n) if T has destructor

		LinkedStack& operator=(const LinkedStack& obj);

		void clear() override;   // O(n)
		void push(const T& newElement) override;
		T pop() override;
		const T& topValue() const override;
		size_t length() const override;
	};

	/// Abstract class: Queue.
	template <typename T>
	class Queue
	{
	public:
		Queue() { }
		Queue(const Queue& obj) { }
		virtual ~Queue() { }

		virtual void clear() = 0;
		virtual void enqueue(const T& newElement) = 0;
		virtual T dequeue() = 0;
		virtual const T& frontValue() const = 0;
		virtual size_t length() const = 0;
	};

	/// Static-array queue.
	template <typename T>
	class SArrayQueue : public Queue<T>
	{
		private:
			size_t capacity;
			size_t front;
			size_t rear;
			T* array;

			void copyFrom(const SArrayQueue& obj);

			// override

		public:
			SArrayQueue(size_t size = 1);
			SArrayQueue(const SArrayQueue& obj);   // O(n) if T has constructor
			~SArrayQueue() override;   // O(n) if T has destructor

			SArrayQueue& operator=(const SArrayQueue& obj);
			
			void clear() override;
			void enqueue(const T& newElement) override;
			T dequeue() override;
			const T& frontValue() const override;
			size_t length() const override;
	};

	/// Linked queue.
	template <typename T>
	class LinkedQueue : public Queue<T>
	{
	private:
		SNode<T>* front;
		SNode<T>* rear;
		size_t size;

		void copyFrom(const LinkedQueue& obj);

	public:
		LinkedQueue(size_t unusedArg = 0);
		LinkedQueue(const LinkedQueue& obj);   // O(n) if T has constructor
		~LinkedQueue() override;   // O(n) if T has destructor

		LinkedQueue& operator=(const LinkedQueue& obj);

		void clear();   // O(n)
		void enqueue(const T& newElement);
		T dequeue();
		const T& frontValue() const;
		virtual size_t length() const;
	};
	
	// <<< should k be passed as reference?
	/// Abstract class: Dictionary
	template <typename K, typename E>
	class Dictionary
	{		
	public:
		Dictionary() { }
		Dictionary(const Dictionary& obj) { }
		virtual ~Dictionary() { }

		//virtual List& operator=(const List& obj) = 0;   // Copy-assignment (cannot be virtual)
		virtual E& operator[](K k) const = 0;   // Subscript

		virtual void clear() = 0;
		virtual void insert(const K& k, const E& e) = 0;
		virtual E remove(const K& k) = 0;
		virtual E removeAny() = 0;
		virtual const E* find(const K& k) const = 0;
		virtual int length() = 0;
	};

	/// Key-value pair container.
	template <typename K, typename E>
	class KVpair
	{
	public:
		KVpair();
		KVpair(K key, E element);
		KVpair(const KVpair& obj);

		KVpair<K,E>& operator=(const KVpair& obj);

		K key;
		E element;
	};

	/// Unsorted array dictionary.
	template <typename K, typename E>
	class StaticArrayDictionary : public Dictionary<K, E>
	{
	private:
		StaticArray<KVpair<K,E>>* list;

	public:
		StaticArrayDictionary(int size = 1);
		StaticArrayDictionary(const StaticArrayDictionary& obj);
		~StaticArrayDictionary();

		StaticArrayDictionary& operator=(const StaticArrayDictionary& obj);
		E& operator[](K k) const override;

		void clear();
		void insert(const K& k, const E& e);
		E remove(const K& k);
		E removeAny();
		const E* find(const K& k) const;
		int length();
	};

	/// Sorted static array for key-value pairs. It inherits from protected StaticArray, so we can hide insert and append, redefine insert, and expose all remaining methods.
	template <typename K, typename E>
	class SortedStaticArray : protected StaticArray<KVpair<K,E>>
	{
	public:
		SortedStaticArray(size_t capacity = 1);
		SortedStaticArray(const std::initializer_list<KVpair<K,E>>& il);
		SortedStaticArray(const SortedStaticArray& obj);
		~SortedStaticArray() override;

		SortedStaticArray& operator=(const SortedStaticArray& obj);
		E& operator[](size_t i) const override;

		void insert(KVpair<K,E>& it);   // Redefined

		StaticArray<KVpair<K,E>>::clear;
		//StaticArray<KVpair<K,E>>::insert;   // Made inaccessible
		//StaticArray<KVpair<K,E>>::append;   // Made inaccessible
		StaticArray<KVpair<K,E>>::remove;

		StaticArray<KVpair<K,E>>::length;
		StaticArray<KVpair<K,E>>::currPos;
		StaticArray<KVpair<K,E>>::getValue;
		
		StaticArray<KVpair<K,E>>::moveToStart;
		StaticArray<KVpair<K,E>>::moveToEnd;
		StaticArray<KVpair<K,E>>::moveToPos;
		StaticArray<KVpair<K,E>>::prev;
		StaticArray<KVpair<K,E>>::next;
	};

	/// Abstract class: Comparator. Used for comparing keys.
	class Comparator
	{
	public:
		virtual ~Comparator() { }
	};

	/// Comparator class for integer keys.
	class IntCompare : public Comparator
	{
	public:
		static bool lt(int x, int y) { return x <  y; }
		static bool eq(int x, int y) { return x == y; }
		static bool gt(int x, int y) { return x >  y; }
	};

	/// Compare character strings.
	class CharStrCompare : public Comparator
	{
	public:
		static bool lt(char* x, char* y) { return strcmp(x, y) <  0; }
		static bool eq(char* x, char* y) { return strcmp(x, y) == 0; }
		static bool gt(char* x, char* y) { return strcmp(x, y) >  0; }
	};

	/// Sorted static array dictionary.
	template <typename K, typename E>
	class SortedStaticArrayDictionary : public Dictionary<K, E> {
	private:
		SortedStaticArray<K, E>* list;
	public:
		SortedStaticArrayDictionary(int size = 1);
		SortedStaticArrayDictionary(const SortedStaticArrayDictionary& obj);
		~SortedStaticArrayDictionary();

		SortedStaticArrayDictionary& operator=(const SortedStaticArrayDictionary& obj);
		E& operator[](size_t i) const override;

		void clear();
		void insert(const K& k, const E& e);
		E remove(const K& k);
		E removeAny();
		E find(const K& k) const;
		int size();
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
		copyFrom(obj);
	}

	/// Destructor. Delete the memory allocated by the constructor for this list. 
	template <typename T>
	StaticArray<T>::~StaticArray() { delete[] array; }

	/// Copy-assignment operator overloading.
	template <typename T>
	StaticArray<T>& StaticArray<T>::operator=(const StaticArray& obj)
	{
		if (this == &obj) return *this;

		if (array) delete[] array;
		
		copyFrom(obj);

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

	/// Make the object a copy of another.
	template <typename T>
	void StaticArray<T>::copyFrom(const StaticArray& obj)
	{
		capacity = obj.capacity;
		size = obj.size;
		curr = obj.curr;
		
		array = new T[capacity];
		for (size_t i = 0; i < size; i++)
			array[i] = obj.array[i];
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

		for (size_t i = curr; i < size - 1; i++)
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

	/// External template function for any List subclass. If item is found, returns its position. Otherwise, returns array size. List::currPos' value can be modified.
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

		if(array) delete[] array;

		copyFrom(obj);

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

		for (size_t i = curr; i < size - 1; i++)
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
	Node<T>& Node<T>::operator=(const Node& obj) 
	{ 
		if (this == &obj) return *this;

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
		if (next) delete next; 
	}

	/// Copy-assignment operator overloading.
	template <typename T>
	SNode<T>& SNode<T>::operator=(const SNode &obj)
	{
		if (this == &obj) return *this;
		
		(Node&)(*this) = obj;
		next = obj.next;

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
	DNode<T>& DNode<T>::operator=(const DNode& obj)
	{
		if (this == &obj) return *this;
		
		(Node&)(*this) = obj;
		prev = obj.prev;
		next = obj.next;

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
	XorNode<T>& XorNode<T>::operator=(const XorNode& obj)
	{
		if (this == &obj) return *this;

		(Node&)(*this) = obj;
		npx = obj.npx;

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
	SinglyLinkedList<T>::SinglyLinkedList(size_t unusedArg)
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
	{
		copyFrom(obj);
	}

	/// Destructor. Delete all nodes in the list, including header node.
	template <typename T>
	SinglyLinkedList<T>::~SinglyLinkedList()
	{
		::delete head;
		::delete freelist;
	}

	/// Copy-assignment operator overloading.
	template <typename T>
	SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& obj)
	{
		if (this == &obj) return *this;
		
		clear();

		copyFrom(obj);

		return *this;
	}

	/// Subscript operator overloading. It returns "const T&" instead of "T&" because node<T>::element returns "const T&". The current node is not changed.
	template <typename T>
	T& SinglyLinkedList<T>::operator[](size_t pos) const
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
		if (!freelist)
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

	/// Make the object a copy of another.
	template <typename T>
	void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList& obj)
	{
		count = 0;
		freelist = nullptr;
		head = tail = curr = new SNode<T>(nullptr);

		for (SNode<T>* node = obj.head->next; node != nullptr; node = node->next)
		{
			append(node->element);
			if (obj.curr == node) curr = tail;
		}

		// freelist is not copied
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
	DoubleLinkedList<T>::DoubleLinkedList(size_t unusedArg)
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
	{
		copyFrom(obj);
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
		
		if(head) delete head;
		if(freelist) delete freelist;

		copyFrom(obj);

		return *this;
	}
	
	/// Subscript operator overloading. It returns "const T&" instead of "T&" because node<T>::element returns "const T&". The current node is not changed.
	template <typename T>
	T& DoubleLinkedList<T>::operator[](size_t pos) const
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
		if (!freelist)
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

	/// Make the object a copy of another.
	template <typename T>
	void DoubleLinkedList<T>::copyFrom(const DoubleLinkedList& obj)
	{
		head = new DNode<T>();
		tail = new DNode<T>();
		head->next = tail;
		tail->prev = head;
		curr = head;
		count = 0;
		freelist = nullptr;

		for (DNode<T>* node = obj.head->next; node != obj.tail; node = node->next)
		{
			append(node->element);
			if (obj.curr == node) curr = tail->prev;
		}

		// freelist is not copied
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
	XorLinkedList<T>::XorLinkedList(size_t unusedArg)
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
	{
		copyFrom(obj);
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
		if (this == &obj) return *this;

		deleteList(head, nullptr);
		deleteList(freelist, nullptr);

		copyFrom(obj);

		return *this;
	}

	/// Subscript operator overloading. It returns "const T&" instead of "T&" because node<T>::element returns "const T&". The current node is not changed.
	template <typename T>
	T& XorLinkedList<T>::operator[](size_t pos) const
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
		if (!freelist)
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
		if(freelist)
			freelist->setNode(node, freelist->next(nullptr));

		node->setNode(nullptr, freelist);
		freelist = node;
	}

	/// Delete all nodes in a list. Used in the destructor.
	template <typename T>
	void XorLinkedList<T>::deleteList(XorNode<T>* node, XorNode<T>* prevNode)
	{
		XorNode<T>* nextNode;
		while (node)
		{
			nextNode = node->next(prevNode);
			prevNode = node;
			delete node;
			node = nextNode;
		}
	}

	/// Make the object a copy of another.
	template <typename T>
	void XorLinkedList<T>::copyFrom(const XorLinkedList& obj)
	{
		count = 0;
		freelist = nullptr;
		head = new XorNode<T>();
		tail = new XorNode<T>();
		head->setNode(nullptr, tail);
		tail->setNode(head, nullptr);
		curr = head;
		currPrev = nullptr;

		XorNode<T>* temp, * node = obj.head, * prevNode = nullptr;
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

	/// Move all nodes in the list to the freelist, except header and tail node.
	template <typename T>
	void XorLinkedList<T>::clear()
	{
		if (count == 0) return;

		XorNode<T>* prevTail = tail->prev(nullptr);
		XorNode<T>* nextHead = head->next(nullptr);
		
		prevTail->setNode(prevTail->prev(tail), freelist);
		nextHead->setNode(nullptr, nextHead->next(head));

		if(freelist)
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


	// -- SArrayStack --------------------------------------

	/// Constructor.
	template<typename T>
	SArrayStack<T>::SArrayStack(size_t size)
		: Stack(), array(new T[size]), capacity(size), top(0) { }

	/// Copy constructor.
	template<typename T>
	SArrayStack<T>::SArrayStack(const SArrayStack& obj)
		: Stack(obj)
	{
		copyFrom(obj);
	}

	/// Destructor.
	template<typename T>
	SArrayStack<T>::~SArrayStack() { delete[] array; }

	/// Make the object a copy of another.
	template<typename T>
	void SArrayStack<T>::copyFrom(const SArrayStack& obj)
	{
		array = new T[obj.capacity];
		capacity = obj.capacity;
		top = obj.top;
		
		for (size_t i = 0; i < top; i++)
			array[i] = obj.array[i];
	}

	/// Copy-assignment operator overloading.
	template <typename T>
	SArrayStack<T>& SArrayStack<T>::operator=(const SArrayStack& obj)
	{
		if (this == &obj) return *this;

		if (array) delete[] array;

		copyFrom(obj);

		return *this;
	}

	/// Remove all elements.
	template<typename T>
	void SArrayStack<T>::clear() { top = 0; }

	/// Insert new element at the top.
	template<typename T>
	void SArrayStack<T>::push(const T& newElement)
	{
		if(top == capacity) throw std::out_of_range("Stack is full");

		array[top++] = newElement;
	}

	/// Extract top element
	template<typename T>
	T SArrayStack<T>::pop()
	{
		if(top == 0) throw std::out_of_range("Stack is empty");
		
		return array[--top];
	}

	/// Get top element
	template<typename T>
	const T& SArrayStack<T>::topValue() const
	{
		if(top == 0) throw std::out_of_range("Stack is empty");

		return array[top - 1];
	}

	/// Get number of active elements.
	template<typename T>
	size_t SArrayStack<T>::length() const { return top; }


	// -- LinkedStack --------------------------------------

	/// Constructor.
	template<typename T>
	LinkedStack<T>::LinkedStack(size_t unusedArg) : top(nullptr), size(0) { }

	/// Copy constructor
	template<typename T>
	LinkedStack<T>::LinkedStack(const LinkedStack& obj)
	{
		copyFrom(obj);
	}

	/// Destructor.
	template<typename T>
	LinkedStack<T>::~LinkedStack() { clear(); }

	/// Copy assignment operator overloading.
	template<typename T>
	LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack& obj)
	{
		if (this == &obj) return *this;

		if (top) delete[] top;

		copyFrom(obj);

		return *this;
	}

	/// Delete current elements and copy the elements stored in another linked list 
	template<typename T>
	void LinkedStack<T>::copyFrom(const LinkedStack& obj)
	{
		size = 0;
		top = nullptr;

		std::vector<T*> elements;
		for(SNode<T>* node = obj.top; node; node = node->next)
			elements.push_back(&(node->element));

		for (auto it = elements.rbegin(); it != elements.rend(); ++it)
			push(**it);
	}

	/// Remove al elements.
	template<typename T>
	void LinkedStack<T>::clear()
	{
		delete top;
		top = nullptr;
		size = 0;
	}

	/// Insert new node.
	template<typename T>
	void LinkedStack<T>::push(const T& newElement)
	{
		top = new SNode<T>(newElement, top);
		size++;
	}

	/// Extract top node.
	template<typename T>
	T LinkedStack<T>::pop()
	{
		if (!top) throw std::out_of_range("Stack is empty");

		T content = top->element;
		SNode<T>* nextNode = top->next;
		top->next = nullptr;
		delete top;
		top = nextNode;
		size--;
		return content;
	}

	/// Get element's value from the top node.
	template<typename T>
	const T& LinkedStack<T>::topValue() const
	{
		if (!top) throw std::out_of_range("Stack is empty");

		return top->element;
	}

	/// Return the list length.
	template<typename T>
	size_t LinkedStack<T>::length() const { return size; }


	// -- SArrayQueue --------------------------------------

	/// Constructor. Make list array one position larger for empty slot.
	template<typename T>
	SArrayQueue<T>::SArrayQueue(size_t size)
		: capacity(size + 1), rear(0), front(1), array(new T[capacity]) { }

	/// Copy constructor
	template<typename T>
	SArrayQueue<T>::SArrayQueue(const SArrayQueue& obj)
		: capacity(obj.capacity), rear(obj.rear), front(obj.front), array(new T[capacity])
	{
		copyFrom(obj);
	}

	/// Destructor
	template<typename T>
	SArrayQueue<T>::~SArrayQueue() { if(array) delete[] array; }

	/// Copy-assignment operator overloading
	template<typename T>
	SArrayQueue<T>& SArrayQueue<T>::operator=(const SArrayQueue& obj)
	{
		if (this == &obj) return *this;

		if (array) delete[] array;

		copyFrom(obj);

		return *this;
	}

	/// Make an object a copy of another.
	template<typename T>
	void SArrayQueue<T>::copyFrom(const SArrayQueue& obj)
	{
		capacity = obj.capacity;
		rear = obj.rear;
		front = obj.front;
		array = new T[capacity];

		size_t pos, size = length();
		for (size_t i = 0; i < size; i++)
		{
			pos = (front + i) % capacity;
			array[pos] = obj.array[pos];
		}
	}

	/// Reinitialize the queue.
	template<typename T>
	void SArrayQueue<T>::clear()
	{
		rear = 0;
		front = 1;
	}

	/// Insert new element at the rear. Queue is full when rear is 2 steps behind front.
	template<typename T>
	void SArrayQueue<T>::enqueue(const T& newElement)
	{
		if ((rear + 2) % capacity == front) throw std::out_of_range("Queue is full");

		rear = (rear + 1) % capacity;
		array[rear] = newElement;
	}

	/// Extract element from the front. Queue is empty when rear is right before front.
	template<typename T>
	T SArrayQueue<T>::dequeue()
	{
		if ((rear + 1) % capacity == front) throw std::out_of_range("Queue is empty");
		T it = array[front];
		front = (front + 1) % capacity;
		return it;
	}

	/// Get value of front element.
	template<typename T>
	const T& SArrayQueue<T>::frontValue() const
	{
		if (length() == 0) throw std::out_of_range("Queue is empty");
		return array[front];
	}

	/// Return length.
	template<typename T>
	size_t SArrayQueue<T>::length() const { return (rear - front + 1 + capacity) % capacity; }


	// -- LinkedQueue --------------------------------------

	template<typename T>
	LinkedQueue<T>::LinkedQueue(size_t unusedArg)
		: front(new SNode<T>), rear(front), size(0) { }
	
	template<typename T>
	LinkedQueue<T>::LinkedQueue(const LinkedQueue& obj)
	{
		copyFrom(obj);
	}

	template<typename T>
	LinkedQueue<T>::~LinkedQueue()
	{
		delete front;
	}

	template<typename T>
	LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue& obj)
	{
		if (this == &obj) return *this;

		if(front) delete front;
		copyFrom(obj);

		return *this;
	}

	template<typename T>
	void LinkedQueue<T>::copyFrom(const LinkedQueue& obj)
	{
		size = 0;
		front = rear = new SNode<T>;

		for(SNode<T>* node = obj.front->next; node; node = node->next)
			enqueue(node->element);
	}

	/// Reinitialize the queue.
	template<typename T>
	void LinkedQueue<T>::clear()
	{
		if (front->next) delete front->next;
		
		front->next = nullptr;
		rear = front;
		size = 0;
	}

	/// Insert new element at the rear.
	template<typename T>
	void LinkedQueue<T>::enqueue(const T& newElement)
	{
		rear = rear->next = new SNode<T>(newElement, nullptr);
		size++;
	}

	/// Extract element from the front.
	template<typename T>
	T LinkedQueue<T>::dequeue()
	{
		if (size == 0) throw std::out_of_range("Queue is empty");
		if (size == 1) rear = front;

		SNode<T>* node = front->next;
		T element = node->element;

		front->next = node->next;
		node->next = nullptr;
		delete node;
		size--;
		return element;
	}

	/// Get value of front element.
	template<typename T>
	const T& LinkedQueue<T>::frontValue() const
	{
		if (!size) throw std::out_of_range("Queue is empty");

		return front->next->element;
	}

	/// Return length.
	template<typename T>
	size_t LinkedQueue<T>::length() const { return size; }


	// -- KVpair --------------------------------------

	/// Default constructor.
	template<typename K, typename E>
	KVpair<K,E>::KVpair() { }

	/// Constructor.
	template<typename K, typename E>
	KVpair<K,E>::KVpair(K key, E element)
		: key(key), element(element) { }

	/// Copy constructor.
	template<typename K, typename E>
	KVpair<K,E>::KVpair(const KVpair& obj)
		: key(obj.key), element(obj.element) { }
	
	/// Copy-assignment operator overloading.
	template<typename K, typename E>
	KVpair<K, E>& KVpair<K,E>::operator=(const KVpair& obj)
	{
		if (this == &obj) return *this;

		key = obj.key;
		element = obj.element;

		return *this;
	}


	// -- StaticArrayDictionary --------------------------------------

	/// Constructor.
	template <typename K, typename E>
	StaticArrayDictionary<K,E>::StaticArrayDictionary(int size)
		: list(new StaticArray<KVpair<K,E>>(size)) { }

	/// Copy-constructor.
	template <typename K, typename E>
	StaticArrayDictionary<K,E>::StaticArrayDictionary(const StaticArrayDictionary& obj)
		: list(new StaticArray<KVpair<K, E>>(*obj.list)) { }

	/// Destructor.
	template <typename K, typename E>
	StaticArrayDictionary<K,E>::~StaticArrayDictionary() { delete list; }

	/// Copy-assignment operator overloading.
	template <typename K, typename E>
	StaticArrayDictionary<K, E>& StaticArrayDictionary<K, E>::operator=(const StaticArrayDictionary& obj)
	{
		if (this == &obj) return *this;

		if(list) delete list;

		list = new StaticArray<KVpair<K, E>>(*obj.list);

		return *this;
	}

	/// Subscript operator overloading.
	template <typename K, typename E>
	E& StaticArrayDictionary<K, E>::operator [](K k) const
	{
		if(!find(k)) throw std::out_of_range("No current element");

		for (list->moveToStart(); list->currPos() < list->length(); list->next())
		{
			if (k == list->getValue().key)
				return (*list)[list->currPos()].element;
		}
	}

	/// Reinitialize dictionary.
	template <typename K, typename E>
	void StaticArrayDictionary<K, E>::clear() { list->clear(); }

	/// Insert new element. Append it to the list.
	template <typename K, typename E>
	void StaticArrayDictionary<K, E>::insert(const K& k, const E& e)
	{
		if (find(k))
			(*this)[k] = e;
		else
		{
			KVpair<K, E> temp(k, e);
			list->append(temp);
		}
	}

	// Find the element to remove using sequential search.
	template <typename K, typename E>
	E StaticArrayDictionary<K, E>::remove(const K& k)
	{
		const E* ptr = find(k);
		if (!ptr) throw std::out_of_range("Non-existent element");
		E temp = *ptr;
		list->remove();
		return temp;
	}

	/// Remove the last element.
	template <typename K, typename E>
	E StaticArrayDictionary<K, E>::removeAny()
	{
		if(!length()) throw std::out_of_range("Dictionary is empty");

		list->moveToEnd();
		list->prev();
		return list->remove().element;
	}

	/// Find an element using sequential search.
	template <typename K, typename E>
	const E* StaticArrayDictionary<K, E>::find(const K& k) const
	{
		const KVpair<K, E>* temp;

		for (list->moveToStart(); list->currPos() < list->length(); list->next())
		{
			temp = &list->getValue();
			if (k == temp->key)
				return &temp->element;
		}

		return nullptr;
	}

	/// Return list size.
	template <typename K, typename E>
	int StaticArrayDictionary<K, E>::length() { return list->length(); }


	// -- SortedStaticArray --------------------------------------

	template <typename K, typename E>
	SortedStaticArray<K,E>::SortedStaticArray(size_t capacity)
		: StaticArray<KVpair<K,E>>(capacity) { }

	template <typename K, typename E>
	SortedStaticArray<K,E>::SortedStaticArray(const std::initializer_list<KVpair<K,E>>& il) { };

	template <typename K, typename E>
	SortedStaticArray<K,E>::SortedStaticArray(const SortedStaticArray& obj) { };

	template <typename K, typename E>
	SortedStaticArray<K,E>::~SortedStaticArray() { };

	template <typename K, typename E>
	SortedStaticArray<K,E>& SortedStaticArray<K,E>::operator=(const SortedStaticArray& obj)
	{
	
	};

	template <typename K, typename E>
	E& SortedStaticArray<K,E>::operator[](size_t i) const
	{
	
	};

	template <typename K, typename E>
	void SortedStaticArray<K,E>::insert(KVpair<K,E>& it)
	{
		KVpair<K,E> curr;
		for (moveToStart(); currPos() < length(); next())
		{
			curr = getValue();
			if (curr.key() > it.key())
				break;
		}

		StaticArray<KVpair<K,E>>::insert(it);
	}


	// -- SortedStaticArrayDictionary --------------------------------------

	/// Constructor.
	template<typename K, typename E>
	SortedStaticArrayDictionary<K,E>::SortedStaticArrayDictionary(int size)
	{
		list = new SAList<K, E>(size);
	}

	/// Copy constructor.
	template<typename K, typename E>
	SortedStaticArrayDictionary<K, E>::SortedStaticArrayDictionary(const SortedStaticArrayDictionary& obj)
	{

	}

	/// Destructor
	template<typename K, typename E>
	SortedStaticArrayDictionary<K, E>::~SortedStaticArrayDictionary() { delete list; }

	/// Copy-assignment operator overloading.
	template<typename K, typename E>
	SortedStaticArrayDictionary<K, E>& SortedStaticArrayDictionary<K, E>::operator=(const SortedStaticArrayDictionary& obj)
	{

	}

	/// Subscript operator overloading.
	template<typename K, typename E>
	E& SortedStaticArrayDictionary<K, E>::operator[](size_t i) const
	{

	}

	/// Reinitialization.
	template<typename K, typename E>
	void SortedStaticArrayDictionary<K, E>::clear() { list->clear(); }

	/// Insert an element while keeping elements sorted.
	template<typename K, typename E>
	void SortedStaticArrayDictionary<K, E>::insert(const K& k, const E& e)
	{
		KVpair<K, E> temp(k, e);
		list->insert(temp);
	}

	/// Find element to remove using binary search, remove it, and shift subsequent elements.
	template<typename K, typename E>
	E SortedStaticArrayDictionary<K, E>::remove(const K& k)
	{
		E temp = find(k);
		if (temp != NULL) list->remove();//<<< uses sequential search
		return temp;
	}

	/// Remove last element.
	template<typename K, typename E>
	E SortedStaticArrayDictionary<K, E>::removeAny()
	{
		Assert(size() != 0, "Dictionary is empty");
		list->moveToEnd();
		list->prev();
		KVpair<K, E> e = list->remove();
		return e.value();
	}

	// Find key using binary search.
	template<typename K, typename E>
	E SortedStaticArrayDictionary<K, E>::find(const K& k) const {
		int l = -1;
		int r = list->length();
		while (l + 1 != r)
		{ // Stop when l and r meet
			int i = (l + r) / 2; // Check middle of remaining subarray
			list->moveToPos(i);
			KVpair<Key, E> temp = list->getValue();
			if (k < temp.key()) r = i;
			// In left
			if (k == temp.key()) return temp.value(); // Found it
			if (k > temp.key()) l = i;
			// In right
		}
		return NULL; // "k" does not appear in dictionary
	}

	/// Return list size.
	template<typename K, typename E>
	int SortedStaticArrayDictionary<K, E>::size() { return list->length(); }


	// -- Tests --------------------------------------

	/// Tests for lists.
	template<template<typename> class T>
	void test_List()
	{
		size_t testNumber = 0;
		std::cout << typeid(T).name() << ": " << std::flush;

		std::cout << ++testNumber << " " << std::flush;   // 1
		T<int> list1(0);
		list1.clear();
		list1.moveToEnd();
		if (list1.length() != 0) throw std::exception("Failed at length()");
		if (list1.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << ++testNumber << " " << std::flush;   // 2
		T<int> list2(10);
		list2.append(0);
		list2.append(1);
		list2.append(3);
		list2.append(4);
		list2.moveToEnd();
		list2.prev();
		list2.prev();
		list2.insert(2);
		list2.insert(3);
		list2.append(5);
		list2.append(6);
		list2.append(8);
		list2.moveToPos(8);
		list2.insert(7);
		list2.moveToStart();
		list2.next();
		list2.next();
		list2.remove();
		if (list2.length() != 9) throw std::exception("Failed at length()");
		if (list2.currPos() != 2) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 2) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if (dss::find(&list2, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		T<int> list3({ 0,1,2,3,4,5,6,7,8,9 });
		list3.moveToPos(3);
		if (list3.length() != 10) throw std::exception("Failed at length()");
		if (list3.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list3.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list3[6] != 6) throw std::exception("Failed at operator[]");
		if (dss::find(&list3, 9) != 9) throw std::exception("Failed at find()");
		list3.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 4
		T<int> list4(list3);
		if (list4.length() != 10) throw std::exception("Failed at length()");
		if (list4.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list4.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list4[6] != 6) throw std::exception("Failed at operator[]");
		if (dss::find(&list4, 9) != 9) throw std::exception("Failed at find()");
		list4.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 5
		T<int> list5 = list4;
		if (list5.length() != 10) throw std::exception("Failed at length()");
		if (list5.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list5.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list5[6] != 6) throw std::exception("Failed at operator[]");
		if (dss::find(&list5, 9) != 9) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 6
		T<int> list6 = list5;
		list6.clear();
		if (list6.length() != 0) throw std::exception("Failed at length()");
		if (list6.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << ++testNumber << " " << std::flush;   // 7
		T<int> list7(15);
		list7.clear();
		list7.moveToEnd();
		list7.append(0);
		list7.append(1);
		list7.append(2);
		list7.append(3);
		list7.append(4);
		list7.append(5);
		list7.append(6);
		list7.append(7);
		list7.append(8);
		list7.append(9);
		list7.append(10);
		if (list7.length() != 11) throw std::exception("Failed at length()");
		if (list7.currPos() != 0) throw std::exception("Failed at currPos()");
		if (list7.getValue() != 0) throw std::exception("Failed at getValue()");
		if (list7[7] != 7) throw std::exception("Failed at operator[]");
		if (dss::find(&list7, 5) != 5) throw std::exception("Failed at find()");
		list7.moveToPos(0);

		std::cout << ++testNumber << " " << std::flush;   // 8
		list2 = list7;
		
		if (list2.length() != 11) throw std::exception("Failed at length()");
		if (list2.currPos() != 0) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 0) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if (dss::find(&list7, 5) != 5) throw std::exception("Failed at find()");

		std::cout << std::endl;
	}

	/// Tests for sorted lists.
	template<template<typename, typename> class T>
	void test_SortedList()
	{
		// <<< std::pair
		/*
		SortedStaticArray(size_t capacity = 1);
		SortedStaticArray(const std::initializer_list<KVpair<K, E>>&il);
		SortedStaticArray(const SortedStaticArray & obj);
		~SortedStaticArray() override;

		SortedStaticArray& operator=(const SortedStaticArray & obj);
		E& operator[](size_t i) const override;

		void insert(KVpair<K, E>&it);   // Redefined

		StaticArray<KVpair<K, E>>::clear;
		//StaticArray<KVpair<K,E>>::insert;   // Made inaccessible
		//StaticArray<KVpair<K,E>>::append;   // Made inaccessible
		StaticArray<KVpair<K, E>>::remove;

		StaticArray<KVpair<K, E>>::length;
		StaticArray<KVpair<K, E>>::currPos;
		StaticArray<KVpair<K, E>>::getValue;

		StaticArray<KVpair<K, E>>::moveToStart;
		StaticArray<KVpair<K, E>>::moveToEnd;
		StaticArray<KVpair<K, E>>::moveToPos;
		StaticArray<KVpair<K, E>>::prev;
		StaticArray<KVpair<K, E>>::next;
		*/



		size_t testNumber = 0;
		std::cout << typeid(T).name() << ": " << std::flush;

		std::cout << ++testNumber << " " << std::flush;   // 1
		T<int> list1(0);
		list1.clear();
		list1.moveToEnd();
		if (list1.length() != 0) throw std::exception("Failed at length()");
		if (list1.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << ++testNumber << " " << std::flush;   // 2
		T<int> list2(10);
		list2.append(0);
		list2.append(1);
		list2.append(3);
		list2.append(4);
		list2.moveToEnd();
		list2.prev();
		list2.prev();
		list2.insert(2);
		list2.insert(3);
		list2.append(5);
		list2.append(6);
		list2.append(8);
		list2.moveToPos(8);
		list2.insert(7);
		list2.moveToStart();
		list2.next();
		list2.next();
		list2.remove();
		if (list2.length() != 9) throw std::exception("Failed at length()");
		if (list2.currPos() != 2) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 2) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if (dss::find(&list2, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		T<int> list3({ 0,1,2,3,4,5,6,7,8,9 });
		list3.moveToPos(3);
		if (list3.length() != 10) throw std::exception("Failed at length()");
		if (list3.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list3.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list3[6] != 6) throw std::exception("Failed at operator[]");
		if (dss::find(&list3, 9) != 9) throw std::exception("Failed at find()");
		list3.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 4
		T<int> list4(list3);
		if (list4.length() != 10) throw std::exception("Failed at length()");
		if (list4.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list4.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list4[6] != 6) throw std::exception("Failed at operator[]");
		if (dss::find(&list4, 9) != 9) throw std::exception("Failed at find()");
		list4.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 5
		T<int> list5 = list4;
		if (list5.length() != 10) throw std::exception("Failed at length()");
		if (list5.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list5.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list5[6] != 6) throw std::exception("Failed at operator[]");
		if (dss::find(&list5, 9) != 9) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 6
		T<int> list6 = list5;
		list6.clear();
		if (list6.length() != 0) throw std::exception("Failed at length()");
		if (list6.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << ++testNumber << " " << std::flush;   // 7
		T<int> list7(15);
		list7.clear();
		list7.moveToEnd();
		list7.append(0);
		list7.append(1);
		list7.append(2);
		list7.append(3);
		list7.append(4);
		list7.append(5);
		list7.append(6);
		list7.append(7);
		list7.append(8);
		list7.append(9);
		list7.append(10);
		if (list7.length() != 11) throw std::exception("Failed at length()");
		if (list7.currPos() != 0) throw std::exception("Failed at currPos()");
		if (list7.getValue() != 0) throw std::exception("Failed at getValue()");
		if (list7[7] != 7) throw std::exception("Failed at operator[]");
		if (dss::find(&list7, 5) != 5) throw std::exception("Failed at find()");
		list7.moveToPos(0);

		std::cout << ++testNumber << " " << std::flush;   // 8
		list2 = list7;

		if (list2.length() != 11) throw std::exception("Failed at length()");
		if (list2.currPos() != 0) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 0) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if (dss::find(&list7, 5) != 5) throw std::exception("Failed at find()");

		std::cout << std::endl;
	}

	/// Tests for stacks.
	template<template<typename> class T>
	void test_Stack()
	{
		size_t testNumber = 0;
		std::cout << typeid(T).name() << ": " << std::flush;

		std::cout << ++testNumber << " " << std::flush;   // 1
		T<int> stack1(0);
		if (stack1.length() != 0) throw std::exception("Failed at length()");

		std::cout << ++testNumber << " " << std::flush;   // 2
		T<int> stack2(0);
		stack2.clear();
		if (stack2.length() != 0) throw std::exception("Failed at length()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		T<int> stack3(10);
		stack3.push(1);
		stack3.push(2);
		stack3.clear();
		if (stack3.length() != 0) throw std::exception("Failed at length()");

		std::cout << ++testNumber << " " << std::flush;   // 4
		T<int> stack4;
		stack4.push(5);
		stack4.pop();
		stack4.push(4);
		if (stack4.length() != 1) throw std::exception("Failed at length()");
		if (stack4.topValue() != 4) throw std::exception("Failed at topValue()");

		std::cout << ++testNumber << " " << std::flush;   // 5
		T<int> stack5(5);
		stack5.push(1);
		stack5.pop();
		stack5.push(2);
		stack5.push(3);
		stack5.push(4);
		stack5.pop();
		stack5.push(5);
		stack5.push(6);
		stack5.push(7);
		stack5.pop();
		if (stack5.length() != 4) throw std::exception("Failed at length()");
		if (stack5.topValue() != 6) throw std::exception("Failed at topValue()");

		std::cout << ++testNumber << " " << std::flush;   // 6
		T<int> stack6(stack5);
		if (stack6.length() != 4) throw std::exception("Failed at length()");
		if (stack6.topValue() != 6) throw std::exception("Failed at topValue()");

		std::cout << ++testNumber << " " << std::flush;   // 7
		T<int> stack7 = stack5;
		if (stack7.length() != 4) throw std::exception("Failed at length()");
		if (stack7.topValue() != 6) throw std::exception("Failed at topValue()");

		std::cout << ++testNumber << " " << std::flush;   // 8
		stack4 = stack5;
		if (stack4.length() != 4) throw std::exception("Failed at length()");
		if (stack4.topValue() != 6) throw std::exception("Failed at topValue()");

		std::cout << std::endl;
	}

	/// Tests for queues.
	template<template<typename> class T>
	void test_Queue()
	{
		size_t testNumber = 0;
		std::cout << typeid(T).name() << ": " << std::flush;
		
		std::cout << ++testNumber << " " << std::flush;   // 1
		T<int> queue1(0);
		if (queue1.length() != 0) throw std::exception("Failed at length()");
		
		std::cout << ++testNumber << " " << std::flush;   // 2
		T<int> queue2(0);
		queue2.clear();
		if (queue2.length() != 0) throw std::exception("Failed at length()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		T<int> queue3(10);
		queue3.enqueue(1);
		queue3.enqueue(2);
		queue3.clear();
		if (queue3.length() != 0) throw std::exception("Failed at length()");
		
		std::cout << ++testNumber << " " << std::flush;   // 4
		T<int> queue4;
		queue4.enqueue(5);
		queue4.dequeue();
		queue4.enqueue(4);
		if (queue4.length() != 1) throw std::exception("Failed at length()");
		if (queue4.frontValue() != 4) throw std::exception("Failed at frontValue()");
		
		std::cout << ++testNumber << " " << std::flush;   // 5
		T<int> queue5(5);
		queue5.enqueue(1);
		queue5.dequeue();
		queue5.enqueue(2);
		queue5.enqueue(3);
		queue5.enqueue(4);
		queue5.dequeue();
		queue5.enqueue(5);
		queue5.enqueue(6);
		queue5.enqueue(7);
		queue5.dequeue();
		if (queue5.length() != 4) throw std::exception("Failed at length()");
		if (queue5.frontValue() != 4) throw std::exception("Failed at frontValue()");
		
		std::cout << ++testNumber << " " << std::flush;   // 6
		T<int> queue6(queue5);
		if (queue6.length() != 4) throw std::exception("Failed at length()");
		if (queue6.frontValue() != 4) throw std::exception("Failed at frontValue()");
		
		std::cout << ++testNumber << " " << std::flush;   // 7
		T<int> queue7 = queue5;
		if (queue7.length() != 4) throw std::exception("Failed at length()");
		if (queue7.frontValue() != 4) throw std::exception("Failed at frontValue()");

		std::cout << ++testNumber << " " << std::flush;   // 8
		queue5 = queue4;
		if (queue5.length() != 1) throw std::exception("Failed at length()");
		if (queue5.frontValue() != 4) throw std::exception("Failed at frontValue()");

		std::cout << std::endl;
	}

	/// Tests for dictionaries.
	template<template<typename, typename> class T>
	void test_Dictionary()
	{
		size_t testNumber = 0;
		std::cout << typeid(T).name() << ": " << std::flush;

		std::cout << ++testNumber << " " << std::flush;   // 1
		StaticArrayDictionary<int, std::string> dict1(0);
		dict1.clear();
		if (dict1.length() != 0) throw std::exception("Failed at length()");

		std::cout << ++testNumber << " " << std::flush;   // 2
		StaticArrayDictionary<int, std::string> dict2(10);
		dict2.insert(1, "pos 1");
		dict2.insert(2, "pos 2");
		dict2.insert(3, "pos 3");
		dict2.remove(2);
		dict2.insert(4, "pos 4");
		dict2.insert(5, "pos 5");
		dict2.removeAny();
		if (dict2.length() != 3) throw std::exception("Failed at length()");
		if (*dict2.find(4) != "pos 4") throw std::exception("Failed at find()");
		if (dict2[3] != "pos 3") throw std::exception("Failed at operator []");
		
		std::cout << ++testNumber << " " << std::flush;   // 3
		StaticArrayDictionary<int, std::string> dict3(dict2);
		dict3.insert(2, "pos 2");
		dict3.insert(5, "pos 5");
		dict3.insert(6, "pos 6");
		dict3.remove(2);
		dict3.insert(2, "pos 2 new");
		dict3.insert(7, "pos 7");
		dict3.removeAny();
		if (dict3.length() != 6) throw std::exception("Failed at length()");
		if (*dict3.find(2) != std::string("pos 2 new")) throw std::exception("Failed at find()");
		if (*dict3.find(3) != std::string("pos 3")) throw std::exception("Failed at find()");
		if (dict3[5] != "pos 5") throw std::exception("Failed at operator []");

		std::cout << ++testNumber << " " << std::flush;   // 4
		StaticArrayDictionary<int, std::string> dict4 = dict3;
		dict4.insert(9, "pos 9");
		dict4.insert(7, "pos 7");
		dict4.insert(7, "pos 7 new");
		dict4.remove(9);
		dict4.insert(9, "pos 9 again");
		dict4.insert(8, "pos 8");
		dict4.removeAny();
		if (dict4.length() != 8) throw std::exception("Failed at length()");
		if (*dict4.find(7) != std::string("pos 7 new")) throw std::exception("Failed at find()");
		if (*dict4.find(3) != std::string("pos 3")) throw std::exception("Failed at find()");
		if (*dict4.find(9) != std::string("pos 9 again")) throw std::exception("Failed at find()");
		if (dict4[5] != "pos 5") throw std::exception("Failed at operator []");

		std::cout << ++testNumber << " " << std::flush;   // 5
		dict3 = dict4;
		if (dict3.length() != 8) throw std::exception("Failed at length()");
		if (*dict3.find(7) != std::string("pos 7 new")) throw std::exception("Failed at find()");
		if (*dict3.find(3) != std::string("pos 3")) throw std::exception("Failed at find()");
		if (*dict3.find(9) != std::string("pos 9 again")) throw std::exception("Failed at find()");
		if (dict3[5] != "pos 5") throw std::exception("Failed at operator []");

		std::cout << ++testNumber << " " << std::flush;   // 6
		StaticArrayDictionary<int, std::string> dict5 = dict4;
		dict5.clear();
		if (dict5.length() != 0) throw std::exception("Failed at length()");

		std::cout << std::endl;
	}
}

#endif