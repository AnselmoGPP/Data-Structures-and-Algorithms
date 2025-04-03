#ifndef LISTS_HPP
#define LISTS_HPP

#include <initializer_list>
#include <stdexcept>

namespace ans
{
	// Main declarations ----------------------------------------

	//template <typename T> class List;
	//template <typename T> class StaticArray;
	//template <typename T> class DynamicArray;
	//template <typename T> class SinglyLinkedList;
	//template <typename T> class DoubleLinkedList;

	//template<typename T> using SA = StaticArray<T>;
	//template<typename T> using DA = DynamicArray<T>;
	//template<typename T> using SLL = SinglyLinkedList<T>;
	//template<typename T> using DLL = DoubleLinkedList<T>;

	//template <typename T>
	//size_t find(StaticArray<T>& list, const T& item);

	//template <typename T>
	//size_t find(List<T>* list, const T& item);

	//void test_StaticArray();
	//void test_DynamicArray();
	//void test_SinglyLinkedList();
	//void test_DoubleLinkedList();


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

		void clear() override;
		void insert(const T& item) override;   // O(n)
		void append(const T& item) override;
		T remove() override;   // O(n)

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

		//const T& getContent() const;
		//const T& setContent(const T& content);
		
		//DNode* getPrev() const;
		//DNode* getNext() const;
		//void setPrev(DNode* prevNode);
		//void setNext(DNode* nextNode);

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
		if (this != &obj)
		{
			capacity = obj.capacity;
			size = obj.size;
			curr = obj.curr;

			delete[] array;
			array = new T[capacity];
			for (size_t i = 0; i < capacity; i++)
				array[i] = obj.array[i];
		}

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

	/// Store a new element in the list at the current position.
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
	void StaticArray<T>::next() { if (curr < size) curr++; }

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

	/// External template function for StaticArray. If item is found, returns its position. Otherwise, returns array size.
	template <typename T>
	size_t find(StaticArray<T>& list, const T& item)
	{
		for (list.moveToStart(); list.currPos() < list.length(); list.next())
			if (item == list.getValue())
				return list.currPos();

		return list.currPos();
	}

	/// External template function for any List subclass. If item is found, returns its position. Otherwise, returns array size.
	template <typename T>
	size_t find(List<T>* list, const T& item)
	{
		for (list->moveToStart(); list->currPos() < list->length(); list->next())
			if (item == list->getValue())
				return list->currPos();

		return list.currPos();
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
		if (this != &obj)
		{
			capacity = obj.capacity;
			size = obj.size;
			curr = obj.curr;

			delete[] array;
			array = new T[capacity];
			for (size_t i = 0; i < capacity; i++)
				array[i] = obj.array[i];
		}

		return *this;
	}

	/// Increase array capacity if necessary.
	template <typename T>
	void DynamicArray<T>::increaseCapacity()
	{
		if (size == capacity)
		{
			T* newArray = new T[capacity ? capacity * 2 : 1];

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
			T* newArray = new T[capacity / 2];

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
	}

	/// Store a new element in the list at the current position.
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

	/// Destructor. Destroys the next node (which causes the destruction of subsequent nodes).
	template <typename T>
	DNode<T>::~DNode()
	{
		if (prev != nullptr) delete prev;		// <<< problem when removing a node or similar action??
		if (next != nullptr) delete next;
	}

	/// Copy-assignment operator overloading.
	template <typename T>
	DNode<T>& DNode<T>::operator=(const DNode& obj) const
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
	void DNode<T>::setNode(const T& content, DNode* prevNode, DNode* nextNode)
	{
		element = content;
		prev = prevNode;
		next = nextNode;
	}


	// -- SinglyLinkedList --------------------------------------

	/// Constructor.
	template <typename T>
	SinglyLinkedList<T>::SinglyLinkedList()
		: count(0), freelist(nullptr)
	{ 
		curr = head = tail = new SNode<T>(nullptr);	// header node <<< contructor overloading problem if elements are pointers
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
		curr = head = tail = new SNode<T>(nullptr);

		for (SNode<T>* node = obj.head->next; node != nullptr; node = node->next)
			append(node->element);
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
		if (this != &obj)
		{
			curr = head;
			clear();

			for (SNode<T>* pos = obj.head->next; pos != nullptr; pos = pos->next)
				append(pos->element);
		}

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

	/// Store a new node in the list at the current position.
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
	void SinglyLinkedList<T>::next() { if (curr != tail) curr = curr->next; }
	

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

		for (DNode<T>* pos = obj.head->next; pos != obj.tail; pos = pos->next)
			append(pos->element);
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
		
		curr = head;
		clear();

		for (SNode<T>* pos = obj.head->next; pos != obj.tail; pos = pos->next)
			append(pos->element);

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

	/// Move all nodes in the list to the freelist, except header node.
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

	/// Store a new node in the list at the current position.
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
		tail->prev->next = tail->prev = newNode(content, tail->prev, tail);

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
		DNode<T>* node = head->next;
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
	void DoubleLinkedList<T>::moveToEnd() { curr = tail; }

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
	void DoubleLinkedList<T>::next() { if (curr != tail) curr = curr->next; }


	// -- Tests --------------------------------------

	void test_StaticArray()
	{
		StaticArray<int> list1;
	}

	void test_DynamicArray()
	{
		DynamicArray<int> list1;
	}

	void test_SinglyLinkedList()
	{
		SinglyLinkedList<int> list1;
	}

	void test_DoubleLinkedList()
	{
		DoubleLinkedList<int> list1;
	}
}

#endif