#ifndef LISTS_HPP
#define LISTS_HPP

/*
	Classes:

		List
			ArrayBasedList
			SinglyLinkedList
			DoubleLinkedList

		Node
			SNode
			DNode

	Sorted list: Its elements are positioned in ascending order of value
	Unsorted list: No particular relationship between element values and positions

	Dynamic array: Array-based list that grows and shrink depending on the number of elements (example: std::vector), 
	getting around the array-based list limitation. Disadvantage: dealing with space adjustments takes time. Each time 
	the array grows in size, its contents must be copied. A good idea is to double the size of the array when it becomes 
	full, and cut it in size when it becomes one quarter full.

	Element implementations:
	List users must decide whether they wish to store a copy or a reference of a given element on each list that contains it. 
	Using references allow multiple list nodes to point to the same record rather than making copies. The disadvantage of using 
	pointers is that they require space of its own (references do not).

	Homogeneity: Usually, DSs store the same type, but could store different types.

*/

#include <initializer_list>
#include <stdexcept>

namespace ans
{

	/// Abstract class: List.
	template <typename T>
	class List
	{
	public:
		typedef	T			value_type;
		typedef	size_t		size_type;

							List()										= default;
							List(size_t size)							{ };
							List(const std::initializer_list<T>& il)	{ };
							List(const List& obj)						{ };				// Copy constructor
		virtual				~List()										{ };

		//virtual List&		operator=(const List& obj)					{ return *this; };	// Copy-assignment operator
		//virtual T&		operator[](size_t i) const					= 0;				// Subscript operator

		virtual	void		clear()										= 0;
		virtual	void		insert(const T& item)						= 0;
		virtual	void		append(const T& item)						= 0;
		virtual	const T		remove()									= 0;
		
		virtual	size_t		length() const								= 0;
		virtual	size_t		currPos() const								= 0;
		virtual	const T&	getValue() const							= 0;
		
		virtual	void		moveToStart()								= 0;
		virtual	void		moveToEnd()									= 0;
		virtual	void		moveToPos(size_t pos)						= 0;
		virtual	void		prev()										= 0;
		virtual	void		next()										= 0;
	};


	/// Array-based list class. It stores a dynamic number of elements ("listSize") of type T in an internal array of capacity "maxSize".  
	template <typename T>
	class ArrayBasedList : public List<T>
	{
		T*				listArray;
		size_t			maxSize;	// x
		size_t			listSize;	// n (contained in x)
		size_t			curr;		// Range: [0, n] (not n-1)

	public:
						ArrayBasedList(size_t size = 100);
						ArrayBasedList(const std::initializer_list<T>& il);	// O(n)
						ArrayBasedList(const ArrayBasedList& obj);			// O(n)
						~ArrayBasedList()						override;

		ArrayBasedList&	operator=(const ArrayBasedList& obj);				// O(n)
		T&				operator[](size_t i) const;							// O(n)

		void			clear()									override;
		void			insert(const T& item)					override;	// O(n)
		void			append(const T& item)					override;
		const T			remove()								override;	// O(n)

		size_t			length() const							override;
		size_t			currPos() const							override;
		const T&		getValue() const						override;

		void			moveToStart()							override;
		void			moveToEnd()								override;
		void			moveToPos(size_t pos)					override;
		void			prev()									override;
		void			next()									override;
	};

	template <typename T>
	size_t find(ArrayBasedList<T>& list, const T& item);


	/// Base class: Node. It stores the item (content) and the methods to retrieve it and modify it.
	template <typename T>// <<< add type N<T> will avoid repeated methods?
	class Node
	{
	protected:
		T			content;	// Item

	public:
		typedef		T		value_type;
		typedef		size_t	size_type;

					Node();
					Node(T content);
					Node(const Node& obj);
		virtual		~Node();

		Node&		operator=(const Node& obj) const;

		const T&	getContent() const;
		const T&	setContent(const T& content);
	};

	/// Node type for a singly linked list. Contains an item (content) of type T and a pointer to the next node (next). 
	template <typename T>
	class SNode : public Node<T>
	{
		SNode*			next;		// Next node
		
		static SNode*	freelist;
		static size_t	activeNodes;
		void			clearFreelist() const;

	public:
						SNode(const T &content, SNode *nextNode);
						SNode(SNode* nextNode);
						SNode(const SNode &obj);
						~SNode();

		SNode&			operator=(const SNode& obj) const;

		SNode*			getNext() const;
		SNode*			setNext(SNode *nextNode);

		static SNode*	get(const T &content, SNode *nextNode);
		void			release();
		void			release(SNode* tail, size_t size);
	};

	/// Node type for a double linked list. Contains an item (content) of type T and two pointers: next node (next) and previous node (prev). 
	template <typename T>
	class DNode : public Node<T>
	{
		DNode*			next;		// Next node
		DNode*			prev;		// Previous node

		static DNode*	freelist;
		static size_t	activeNodes;
		void			clearFreelist() const;

	public:
						DNode(const T& content, DNode* prevNode, DNode* nextNode);
						DNode(DNode* prevNode, DNode* nextNode);
						DNode(const DNode& obj);
						~DNode();
		
		DNode&			operator=(const DNode& obj) const;

		DNode*			getPrev() const;
		DNode*			setPrev(DNode* prevNode);
		DNode*			getNext() const;
		DNode*			setNext(DNode* nextNode);

		static DNode*	get(const T& content, DNode* prevNode, DNode* nextNode);
		void			release();
		void			release(DNode* tail, size_t size);
	};

	/// Singly linked list class that stores a set of linked nodes, each one containing some item of type T (content).
	template <typename T>
	class SinglyLinkedList : public List<T>
	{
		SNode<T>*			head;		// Header node: Additional first node whose value is ignored. Every linked list always has one. It helps with special cases.
		SNode<T>*			tail;		// Last node
		size_t				count;		// Number of nodes

	protected:
		SNode<T>*			curr;		// Node preceding the current node (used for selecting a node).
	
	public:
							SinglyLinkedList(size_t size = 0);
							SinglyLinkedList(const std::initializer_list<T>& il);		// O(n)
							SinglyLinkedList(const SinglyLinkedList& obj);				// O(n)
							~SinglyLinkedList()								override;	// O(n)

		SinglyLinkedList&	operator=(const SinglyLinkedList& obj);						// O(n)
		const T&			operator[](size_t i) const;									// O(n)

		void				clear()											override;
		void				insert(const T& content)						override;
		void				append(const T& content)						override;
		const T				remove()										override;

		size_t				length() const									override;
		size_t				currPos() const									override;	// O(n)
		const T&			getValue() const								override;

		void				moveToStart()									override;
		void				moveToEnd()										override;
		void				moveToPos(size_t pos)							override;	// O(n)
		void				prev()											override;	// O(n)
		void				next()											override;
	};

	template<typename T>
	using SLL = SinglyLinkedList<T>;

	/// Double linked list class that stores a set of linked nodes, each one containing some item of type T (content).
	template <typename T>
	class DoubleLinkedList : public List<T>
	{
		DNode<T>* head;		// Header node: Additional first node whose value is ignored. Every linked list always has one. It helps with special cases.
		DNode<T>* tail;		// Tailer node: Additional last node whose value is ignored. Every double linked list always has one. It helps with special cases. It is one-past-one-past-the-end.
		size_t	count;		// Number of nodes

	protected:
		DNode<T>* curr;		// Node preceding (for consistency) the current node (used for selecting a node).

	public:
							DoubleLinkedList(size_t size = 0);
							DoubleLinkedList(const std::initializer_list<T>& il);		// O(n)
							DoubleLinkedList(const DoubleLinkedList& obj);				// O(n)
							~DoubleLinkedList()								override;	// O(n)

		DoubleLinkedList&	operator=(const DoubleLinkedList& obj);						// O(n)
		const T&			operator[](size_t i) const;									// O(n)

		void				clear()											override;
		void				insert(const T& content)						override;
		void				append(const T& content)						override;
		const T				remove()										override;

		size_t				length() const									override;
		size_t				currPos() const									override;	// O(n)
		const T&			getValue() const								override;

		void				moveToStart()									override;
		void				moveToEnd()										override;
		void				moveToPos(size_t pos)							override;	// O(n)
		void				prev()											override;	// O(n)
		void				next()											override;
	};

	template<typename T>
	using DLL = DoubleLinkedList<T>;

	// ---------- ArrayBasedList ------------------------------

	/// O(1) Constructor. Allocate memory for a number of elements.
	template <typename T>
	ArrayBasedList<T>::ArrayBasedList(size_t size) : maxSize(size), listSize(0), curr(0) { listArray = new T[size]; }

	/// O(n) Constructor. Allocate memory for the elements in the initializer list and copy them into our list.
	template <typename T>
	ArrayBasedList<T>::ArrayBasedList(const std::initializer_list<T>& il) : maxSize(il.size()), listSize(il.size()), curr(0)
	{
		listArray = new T[il.size()];

		const T* item = il.begin();
		for (size_t i = 0; i < il.size(); i++)
			listArray[i] = item[i];
	}

	/// O(n) Copy constructor.
	template <typename T>
	ArrayBasedList<T>::ArrayBasedList(const ArrayBasedList& obj)
	{
		maxSize = obj.maxSize;
		listSize = obj.listSize;
		curr = obj.curr;

		listArray = new T[maxSize];
		for (size_t i = 0; i < maxSize; i++)
			listArray[i] = obj.listArray[i];
	}

	/// O(1) Destructor. Delete the memory allocated by the constructor for this list. 
	template <typename T>
	ArrayBasedList<T>::~ArrayBasedList() { delete[] listArray; }

	/// O(n) Copy-assignment operator overloading.
	template <typename T>
	ArrayBasedList<T>& ArrayBasedList<T>::operator=(const ArrayBasedList& obj)
	{
		if (this != &obj)
		{
			maxSize = obj.maxSize;
			listSize = obj.listSize;
			curr = obj.curr;

			delete[] listArray;
			listArray = new T[maxSize];
			for (size_t i = 0; i < maxSize; i++)
				listArray[i] = obj.listArray[i];
		}

		return *this;
	}

	/// O(1) Subscript operator overloading.
	template <typename T>
	T& ArrayBasedList<T>::operator[](size_t i) const
	{
		if (i >= listSize)
			throw std::out_of_range("Subscript out of range");

		return listArray[i];
	}

	/// O(1) Set listSize to 0 (maxSize remains the same).
	template <typename T>
	void ArrayBasedList<T>::clear() { listSize = curr = 0; }

	/// O(n) Store a new element in the list at the current position.
	template <typename T>
	void ArrayBasedList<T>::insert(const T& item)
	{
		if (listSize == maxSize)
			throw std::out_of_range("List capacity exceeded");

		for (size_t i = listSize; i > curr; i--)
			listArray[i] = listArray[i - 1];

		listArray[curr] = item;
		listSize++;
	}

	/// O(1) Store a new element at the end of the list (listSize).
	template <typename T>
	void ArrayBasedList<T>::append(const T& item)
	{
		if (listSize == maxSize)
			throw std::out_of_range("List capacity exceeded");

		listArray[listSize++] = item;
	}

	/// O(n) Remove the current element from the list.
	template <typename T>
	const T ArrayBasedList<T>::remove()
	{
		if (curr >= maxSize)
			throw std::out_of_range("No current element");

		T item = listArray[curr];

		for (int i = curr; i < listSize - 1; i++)
			listArray[i] = listArray[i + 1];

		listSize--;
		return item;
	}

	/// O(1) Move curr to the first element.
	template <typename T>
	void ArrayBasedList<T>::moveToStart() { curr = 0; }

	/// O(1) Move curr to element one-past-the-end.
	template <typename T>
	void ArrayBasedList<T>::moveToEnd() { curr = listSize; }

	/// O(1) Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void ArrayBasedList<T>::moveToPos(size_t pos)
	{
		if (pos > listSize)
			throw std::out_of_range("Pos out of range");

		curr = pos;
	}

	/// O(1) Move curr to the previous element, except when curr==0.
	template <typename T>
	void ArrayBasedList<T>::prev() { if (curr != 0) curr--; }

	/// O(1) Move curr to the next element, it it exists (including one-past-the-end).
	template <typename T>
	void ArrayBasedList<T>::next() { if (curr < listSize) curr++; }

	/// O(1) Get the number of elements in the list.
	template <typename T>
	size_t ArrayBasedList<T>::length() const { return listSize; }

	/// O(1) Get the position number of the current element.
	template <typename T>
	size_t ArrayBasedList<T>::currPos() const { return curr; }

	/// O(1) Get the element stored in the current position.
	template <typename T>
	const T& ArrayBasedList<T>::getValue() const
	{
		if (curr >= listSize)
			throw std::out_of_range("No current element");

		return listArray[curr];
	}

	/// O(n) External template function. If item is found, returns its position. Otherwise, returns array size.
	template <typename T>
	size_t find(ArrayBasedList<T>& list, const T& item)
	{
		for (list.moveToStart(); list.currPos() < list.length(); list.next())
			if (item == list.getValue())
				return list.currPos();

		return list.currPos();
	}


	// ---------- Node ------------------------------

	template <typename T>
	Node<T>::Node() { };

	template <typename T>
	Node<T>::Node(T content) : content(content) { };

	template <typename T>
	Node<T>::Node(const Node& obj) : content(obj.content) { };

	template <typename T>
	Node<T>::~Node() { };

	template <typename T>
	Node<T>& Node<T>::operator=(const Node& obj) const 
	{ 
		if (this != &obj) 
			content = obj.content; 

		return *this; 
	};

	/// Get the item (content) that this node contains.
	template <typename T>
	const T& Node<T>::getContent() const { return content; }

	/// Set the item (content) that this node contains.
	template <typename T>
	const T& Node<T>::setContent(const T& content) { return this->content = content; }

	// ---------- SNode ------------------------------

	/// Static list for storing removed nodes (already created nodes that aren't being used). Used to avoid calling "new" too much for creating new nodes.
	template <typename T>
	SNode<T>* SNode<T>::freelist = nullptr;

	/// Number of SNode objects that aren't in the freelist. When it reaches 0, the content in freelist is deleted by calling clearFreelist().
	template <typename T>
	size_t SNode<T>::activeNodes = 0;

	/// Constructor. Specify the item (content) and next node.
	template <typename T>
	SNode<T>::SNode(const T& content, SNode* nextNode) : Node(content), next(nextNode) { activeNodes++; }

	/// Constructor. Specify next node.
	template <typename T>
	SNode<T>::SNode(SNode* nextNode) : next(nextNode) { activeNodes++; }

	/// Copy constructor. Be careful: The pointer to next node is copied (multiple pointers pointing to the same node may cause problems when such node is destroyed).
	template <typename T>
	SNode<T>::SNode(const SNode& obj) : Node(obj.content), next(obj.next) { activeNodes++; }

	/// Destructor. Destroys the next node (which causes the destruction of subsequent nodes).
	template <typename T>
	SNode<T>::~SNode() 
	{ 
		if (--activeNodes == 0)	clearFreelist();
		if (next != nullptr)	delete next; 
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

	/// Get the pointer to the next node.
	template <typename T>
	SNode<T>* SNode<T>::getNext() const { return next; }

	/// Set the pointer to the next node.
	template <typename T>
	SNode<T>* SNode<T>::setNext(SNode *nextNode) { return next = nextNode; }

	/// Allocate memory for a node (or take one node's address from freelist, if available), configure the new node, and return a pointer to it.
	template <typename T>
	SNode<T>* SNode<T>::get(const T &content, SNode *nextNode)
	{
		activeNodes++;

		if (freelist == nullptr)
			return new SNode(content, nextNode);

		SNode* newNode	= freelist;
		freelist		= freelist->getNext();
		newNode->setContent(content);
		newNode->setNext(nextNode);
		return newNode;
	}

	/// Save this node in the freelist (head)
	template <typename T>
	void SNode<T>::release()
	{
		next		= freelist;
		freelist	= this;
		activeNodes--;
	}

	/// Move all nodes between this and tail (inclusive) to the freelist. Required in singlyLinkedList::clear() for getting O(1) performance.
	template <typename T>
	void SNode<T>::release(SNode* tail, size_t size)
	{
		tail->setNext(freelist);
		freelist = this;
		activeNodes -= size;
	}

	/// Delete (deallocate) all nodes in the freelist. Automatically called when nodesCount==0 (no nodes<T> in existence, which implies that it's called when no linked lists exist because each one has a header node).
	template <typename T>
	void SNode<T>::clearFreelist() const
	{
		delete freelist;
		freelist = nullptr;
	}


	// ---------- DNode ------------------------------

	/// Static list for storing removed nodes (already created nodes that aren't being used). Used to avoid calling "new" too much for creating new nodes.
	template <typename T>
	DNode<T>* DNode<T>::freelist = nullptr;

	/// Number of DNode objects that aren't in the freelist. When it reaches 0, the content in freelist is deleted by calling clearFreelist().
	template <typename T>
	size_t DNode<T>::activeNodes = 0;

	/// Constructor. Specify the item (content) and previous and next nodes.
	template <typename T>
	DNode<T>::DNode(const T& content, DNode* prevNode, DNode* nextNode) : Node(content), prev(prevNode), next(nextNode) { activeNodes++; }

	/// Constructor. Specify previous and next nodes.
	template <typename T>
	DNode<T>::DNode(DNode* prevNode, DNode* nextNode) : prev(prevNode), next(nextNode) { activeNodes++; }

	/// Copy constructor. Be careful: The pointers to previous and next node are copied (multiple pointers pointing to the same node may cause problems when such node is destroyed).
	template <typename T>
	DNode<T>::DNode(const DNode& obj) : Node(obj.content), prev(obj.prev), next(obj.next) { activeNodes++; }

	/// Destructor. Destroys the next node (which causes the destruction of subsequent nodes).
	template <typename T>
	DNode<T>::~DNode()
	{
		--activeNodes;
		if (activeNodes == 0)	clearFreelist();
		if (prev != nullptr)	delete prev;		// <<< problem when removing a node or similar action??
		if (next != nullptr)	delete next;
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

	/// Get the pointer to the previous node.
	template <typename T>
	DNode<T>* DNode<T>::getPrev() const { return prev; }

	/// Set the pointer to the previous node.
	template <typename T>
	DNode<T>* DNode<T>::setPrev(DNode* prevNode) { return prev = prevNode; }

	/// Get the pointer to the next node.
	template <typename T>
	DNode<T>* DNode<T>::getNext() const { return next; }

	/// Set the pointer to the next node.
	template <typename T>
	DNode<T>* DNode<T>::setNext(DNode* nextNode) { return next = nextNode; }

	/// Allocate memory for a node (or take one node's address from freelist, if available), configure the new node, and return a pointer to it.
	template <typename T>
	DNode<T>* DNode<T>::get(const T& content, DNode* prevNode, DNode* nextNode)
	{
		activeNodes++;

		if (freelist == nullptr)
			return new DNode(content, prevNode, nextNode);

		DNode* newNode = freelist;
		freelist = freelist->getNext();
		newNode->setContent(content);
		newNode->setPrev(prevNode);
		newNode->setNext(nextNode);
		return newNode;
	}

	/// Save this node in the freelist (head)
	template <typename T>
	void DNode<T>::release()
	{
		if(freelist != nullptr) freelist->prev = this;
		next = freelist;
		freelist = this;
		activeNodes--;
	}

	/// Move all nodes between this and tail (inclusive) to the freelist. Required in singlyLinkedList::clear() for getting O(1) performance.
	template <typename T>
	void DNode<T>::release(DNode* tail, size_t size)
	{
		if (freelist != nullptr) freelist->prev = tail->next;
		tail->setNext(freelist);
		freelist = this;
		activeNodes -= size;
	}

	/// Delete (deallocate) all nodes in the freelist. Automatically called when nodesCount==0 (no nodes<T> in existence, which implies that it's called when no linked lists exist because each one has a header node).
	template <typename T>
	void DNode<T>::clearFreelist() const
	{
		freelist->prev = nullptr;
		delete freelist;
		freelist = nullptr;
	}


	// ---------- SinglyLinkedList ------------------------------

	/// O(1) Constructor. The parameter "size" is ignored.
	template <typename T>
	SinglyLinkedList<T>::SinglyLinkedList(size_t size) 
	{ 
		curr = head = tail = new SNode<T>(nullptr);	// header node
		count = 0;	
	}

	/// O(n) Constructor. It takes an initialization list.
	template <typename T>
	SinglyLinkedList<T>::SinglyLinkedList(const std::initializer_list<T>& il)
	{
		curr = head = tail = new SNode<T>(nullptr);	// header node
		count = 0;

		const T* item = il.begin();
		for(size_t i = 0; i < il.size(); i++)
			append(item[i]);
	}

	/// O(n) Copy constructor.
	template <typename T>
	SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& obj)
	{
		curr = head = tail = new SNode<T>(nullptr);	// header node
		count = 0;

		for (SNode<T>* pos = obj.head; pos->getNext() != nullptr; pos = pos->getNext())
			append(pos->getNext()->getContent());
	}

	/// O(n) Destructor. Delete all nodes in the list, including header node.
	template <typename T>
	SinglyLinkedList<T>::~SinglyLinkedList() { delete head;	}

	/// O(n) Copy-assignment operator overloading.
	template <typename T>
	SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& obj)
	{
		if (this != &obj)
		{
			clear();

			for (SNode<T>* pos = obj.head; pos->getNext() != nullptr; pos = pos->getNext())
				append(pos->getNext()->getContent());
		}

		return *this;
	}

	/// O(n) Subscript operator overloading. It returns "const T&" instead of "T&" because node<T>::getContent() returns "const T&". The current node is not changed.
	template <typename T>
	const T& SinglyLinkedList<T>::operator[](size_t i) const
	{
		if (i >= count)
			throw std::out_of_range("No current element");

		SNode<T>* nod = head;
		size_t pos = 0;
		while (pos != i) 
		{ 
			nod = nod->getNext();
			pos++;
		}

		return nod->getNext()->getContent();
	}

	/// O(1) Move all nodes in the list to the freelist, except header node.
	template <typename T>
	void SinglyLinkedList<T>::clear()
	{
		//delete head->getNext();						// O(n) Delete all items in the linked list, except header node.
		//moveToStart(); while(curr != tail) remove();	// O(n) Move all nodes to the freelist, except header node.
		head->getNext()->release(tail, count);			// O(1) Move all nodes to the freelist, except header node.

		head->setNext(nullptr);
		curr = tail = head;
		count = 0;
	}

	/// O(1) Store a new node in the list at the current position.
	template <typename T>
	void SinglyLinkedList<T>::insert(const T &content)
	{
		curr->setNext(SNode<T>::get(content, curr->getNext()));	// New node inserted after curr (to insert in the head, we use header node)
		if (tail == curr) tail = curr->getNext();				// In case we inserted in the tail
		count++;
	}
	
	/// O(1) Store a new node at the end of the list (tail).
	template <typename T>
	void SinglyLinkedList<T>::append(const T& content)
	{
		tail = tail->setNext(SNode<T>::get(content, nullptr));
		count++;
	}

	/// O(1) Remove the current node from the list and save it in the freelist.
	template <typename T>
	const T SinglyLinkedList<T>::remove()
	{	
		if (tail == curr)				throw std::out_of_range("No current element");	// If the item to remove is one-past-the-end
		if (tail == curr->getNext())	tail = curr;									// If the object to remove is the tail
			
		T tempContent		= curr->getNext()->getContent();
		SNode<T>* tempNode	= curr->getNext();

		curr->setNext(curr->getNext()->getNext());
		tempNode->release();
		count--;
		return tempContent;
	}

	/// O(1) Get the number of nodes in the list.
	template <typename T>
	size_t SinglyLinkedList<T>::length() const { return count; }

	/// O(n) Get the position number of the current node.
	template <typename T>
	size_t SinglyLinkedList<T>::currPos() const
	{
		SNode<T> *temp = head;
		size_t i;

		for (i = 0; curr != temp; i++) 
			temp = temp->getNext();

		return i;
	}

	/// O(1) Get the item stored in the current node.
	template <typename T>
	const T& SinglyLinkedList<T>::getValue() const
	{
		if (curr == tail)
			throw std::out_of_range("No current element");

		return curr->getNext()->getContent();
	}

	/// O(1) Move curr to the header node.
	template <typename T>
	void SinglyLinkedList<T>::moveToStart() { curr = head; }

	/// O(1) Move curr to the tail (node one-past-the-end).
	template <typename T>
	void SinglyLinkedList<T>::moveToEnd() { curr = tail; }

	/// O(n) Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void SinglyLinkedList<T>::moveToPos(size_t pos)
	{
		if (pos > count)
			throw std::out_of_range("No current element");

		curr = head;
		for (size_t i = 0; i < pos; i++) 
			curr = curr->getNext();
	}

	/// O(n) Move curr to the previous node, except when curr==head.
	template <typename T>
	void SinglyLinkedList<T>::prev()
	{
		if (curr != head)
		{
			SNode<T>* temp = head;
			while (temp->getNext() != curr) temp = temp->getNext();
			curr = temp;
		}
	}

	/// O(1) Move curr to the next node, if it exists (including one-past-the-end).
	template <typename T>
	void SinglyLinkedList<T>::next() { if (curr != tail) curr = curr->getNext(); }
	

	// ---------- DoubleLinkedList ------------------------------

	/// O(1) Constructor. The parameter "size" is ignored.
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(size_t size)
	{
		head = curr = new DNode<T>(nullptr, nullptr);
		tail = new DNode<T>(head, nullptr);
		head->setNext(tail);	/// <<< BUG
		count = 0;
	}

	/// O(n) Constructor. It takes an initialization list.
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(const std::initializer_list<T>& il)
	{
		head = curr = new DNode<T>(nullptr, nullptr);
		tail = new DNode<T>(head, nullptr);
		head->setNext(tail);
		count = 0;

		const T* item = il.begin();
		for (size_t i = 0; i < il.size(); i++)
			append(item[i]);
	}

	/// O(n) Copy constructor.
	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& obj)
	{
		head = curr = new DNode<T>(nullptr, nullptr);
		tail = new DNode<T>(head, nullptr);
		head->setNext(tail);
		count = 0;

		for (DNode<T>* pos = obj.head; pos->getNext() != tail; pos = pos->getNext())
			append(pos->getNext()->getContent());
	}

	/// O(n) Destructor. Delete all nodes in the list, including header node.
	template <typename T>
	DoubleLinkedList<T>::~DoubleLinkedList() { delete head; }

	/// O(n) Copy-assignment operator overloading.
	template <typename T>
	DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& obj)
	{
		if (this != &obj)
		{
			clear();

			for (DNode<T>* pos = obj.head; pos->getNext() != tail; pos = pos->getNext())
				append(pos->getNext()->getContent());
		}

		return *this;
	}

	/// O(n) Subscript operator overloading. It returns "const T&" instead of "T&" because node<T>::getContent() returns "const T&". The current node is not changed.
	template <typename T>
	const T& DoubleLinkedList<T>::operator[](size_t i) const
	{
		if (i >= count)
			throw std::out_of_range("No current element");

		DNode<T>* nod = head;
		size_t pos = 0;
		while (pos != i)
		{
			nod = nod->getNext();
			pos++;
		}

		return nod->getNext()->getContent();
	}

	/// O(1) Move all nodes in the list to the freelist, except header node.
	template <typename T>
	void DoubleLinkedList<T>::clear()
	{
		//delete head->getNext();	this->DoubleLinkedList();			// O(n) Delete all items in the linked list, except header node.
		//moveToStart(); while(curr->getNext() != tail) remove();	// O(n) Move all nodes to the freelist, except header node.
		head->getNext()->release(tail->getPrev(), count);			// O(1) Move all nodes to the freelist, except header node.

		head->setNext(tail);
		tail->setPrev(head);
		curr = head;
		count = 0;
	}

	/// O(1) Store a new node in the list at the current position.
	template <typename T>
	void DoubleLinkedList<T>::insert(const T& content)
	{
		curr->setNext(DNode<T>::get(content, curr, curr->getNext()));	// New node inserted after curr (to insert in the head, we use header node)
		curr->getNext()->getNext()->setPrev(curr->getNext());
		count++;
	}

	/// O(1) Store a new node at the end of the list (tail).
	template <typename T>
	void DoubleLinkedList<T>::append(const T& content)
	{
		tail->setPrev(DNode<T>::get(content, tail->getPrev(), tail));
		tail->getPrev()->getPrev()->setNext(tail->getPrev());
		count++;
	}

	/// O(1) Remove the current node from the list and save it in the freelist.
	template <typename T>
	const T DoubleLinkedList<T>::remove()
	{
		if(curr->getNext() == tail || curr->getNext() == tail->getPrev()) throw std::out_of_range("No current element");

		T removedItem = curr->getNext()->getContent();
		DNode<T>* removedNode = curr->getNext();

		curr->getNext()->getNext()->setPrev(curr);
		curr->setNext(curr->getNext()->getNext());
		removedNode->release();
		count--;
		return removedItem;
	}

	/// O(1) Get the number of nodes in the list.
	template <typename T>
	size_t DoubleLinkedList<T>::length() const { return count; }

	/// O(n) Get the position number of the current node.
	template <typename T>
	size_t DoubleLinkedList<T>::currPos() const
	{
		DNode<T>* temp = head;
		size_t i;

		for (i = 0; curr != temp; i++)
			temp = temp->getNext();

		return i;
	}

	/// O(1) Get the item stored in the current node.
	template <typename T>
	const T& DoubleLinkedList<T>::getValue() const
	{
		if (curr == tail || curr == tail->getPrev())
			throw std::out_of_range("No current element");

		return curr->getNext()->getContent();
	}

	/// O(1) Move curr to the header node.
	template <typename T>
	void DoubleLinkedList<T>::moveToStart() { curr = head; }

	/// O(1) Move curr to the tail (node one-past-the-end).
	template <typename T>
	void DoubleLinkedList<T>::moveToEnd() { curr = tail; }

	/// O(n) Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void DoubleLinkedList<T>::moveToPos(size_t pos)
	{
		if (pos > count)
			throw std::out_of_range("No current element");

		curr = head;
		for (size_t i = 0; i < pos; i++)
			curr = curr->getNext();
	}

	/// O(n) Move curr to the previous node, except when curr==head.
	template <typename T>
	void DoubleLinkedList<T>::prev() { if (curr != head) curr = curr->getPrev(); }

	/// O(1) Move curr to the next node, if it exists (including one-past-the-end).
	template <typename T>
	void DoubleLinkedList<T>::next() { if (curr != tail) curr = curr->getNext(); }

}

#endif