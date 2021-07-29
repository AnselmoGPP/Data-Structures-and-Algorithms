#ifndef HEADER_HPP
#define HEADER_HPP

/*
	myList:
		arrayBasedList
		singlyLinkedList
		doubleLinkedList


Empty number of elements currently stored
Head: Beginn: When it contains no elements
Length of the list: Ning of the list
Tail: End of the list
Sorted list: Its elements are positioned in ascending order of value
Unsorted list: No particular relationship between element values and positions

insert/remove elements, read/modify element, create/clear list, access next/previous element...
*/

#include <initializer_list>
#include <stdexcept>

namespace ans	// <<< Some members (append, get...) should use const
{

	template <typename T>
	class list
	{
	public:
		typedef	T			value_type;
		typedef	size_t		size_type;

							list()										= default;
							list(size_t size)							{ };
							list(const std::initializer_list<T>& il)	{ };
							list(const list& obj)						{ };				// Copy constructor
		virtual				~list()										{ };

		virtual	list&		operator=(const list& obj)					{ return *this; };	// Copy-assignment operator
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


	/**
	* Array based list class. It stores a dynamic number of elements ("listSize") of type T in an internal array of capacity "maxSize".  
	*/
	template <typename T>
	class arrayBasedList : public list<T>	// <<< override keyword
	{
		T*				listArray;
		size_t			maxSize;	// x
		size_t			listSize;	// n (contained in x)
		size_t			curr;		// Range: [0, n] (not n-1)

	public:
						arrayBasedList(size_t size = 100);
						arrayBasedList(const std::initializer_list<T>& il);
						arrayBasedList(const arrayBasedList& obj);
						~arrayBasedList();
		arrayBasedList&	operator=(const arrayBasedList& obj);
		T&				operator[](size_t i) const;	// Bonus method

		void			clear();
		void			insert(const T& item)								= override;//<<< add override
		void			append(const T& item);
		const T			remove();

		size_t			length() const;
		size_t			currPos() const;
		const T&		getValue() const;

		void			moveToStart();
		void			moveToEnd();
		void			moveToPos(size_t pos);
		void			prev();
		void			next();
	};

	template <typename T>
	size_t find(arrayBasedList<T>& list, const T& item);


	/*
		Freelist: Stores deleted nodes for future use. Used to avoid calling "new" too much for creating new nodes.
	*/
	template <typename T>
	class node
	{
		T					content;
		node*				next;
		static node*		freelist;	// <<< How to delete?

	public:
		typedef				T		value_type;
		typedef				size_t	size_type;

							node(const T &content, node *nextNode = nullptr);
							node(node* nextNode = nullptr);
							node(const node &obj);
							~node();
		node&				operator=(const node& obj);

		node*				getNext();
		node*				setNext(node *nextNode);
		const T&			getContent();
		const T&			setContent(const T &content);

		static node*		get(const T &content, node *nextNode);	// <<<
		void				release();								// <<<

		// Bonus methods
		static void			emptyFreelist();
		static node*&		getFreelist();
	};


	/**
		Header node: Additional first node whose value is ignored. I helps with special cases (empty list, inserting at head...).
		This data structure stores a set of linked nodes, each one containing some item of type T (content).
	*/
	template <typename T>
	class singlyLinkedList : public list<T>
	{
		node<T>*			head;		// header node
		node<T>*			tail;
		size_t				count;

	protected:
		node<T>*			curr;		// Node preceding the current node

	public:
							singlyLinkedList(size_t size = 0);
							singlyLinkedList(const std::initializer_list<T>& il);
							singlyLinkedList(const singlyLinkedList& obj);
							~singlyLinkedList();
		singlyLinkedList&	operator=(const singlyLinkedList& obj);
		//T&				operator[](size_t i) const;	// <<< Doesn't work because getContent() returns a const T&  <<< should I implement node<T> as T

		void				clear();					// <<< check complexity of all methods in this header file
		void				insert(const T& content);
		void				append(const T& content);
		const T				remove();

		size_t				length() const;
		size_t				currPos() const;
		const T&			getValue() const;

		void				moveToStart();
		void				moveToEnd();
		void				moveToPos(size_t pos);
		void				prev();
		void				next();
	};


	// ---------- arrayBasedList ------------------------------

	/// O(n) External function. If item is found, returns its position. Otherwise, returns array size.
	template <typename T>
	size_t find(arrayBasedList<T>& list, const T& item)
	{
		for (list.moveToStart(); list.currPos() < list.length(); list.next())
			if (item == list.getValue())
				return list.currPos();

		return list.currPos();
	}

	/// O(1) Constructor. Allocate memory for a number of elements.
	template <typename T>
	arrayBasedList<T>::arrayBasedList(size_t size) : maxSize(size), listSize(0), curr(0) { listArray = new T[size]; }

	/// O(n) Constructor. Allocate memory for the elements in the initializer list and copy them into our list.
	template <typename T>
	arrayBasedList<T>::arrayBasedList(const std::initializer_list<T>& il) : maxSize(il.size()), listSize(il.size()), curr(0)
	{
		listArray = new T[il.size()];

		const T* item = il.begin();
		for (size_t i = 0; i < il.size(); i++)
			listArray[i] = item[i];
	}

	/// O(1) Constructor. Delete the memory allocated by the constructor for this list. 
	template <typename T>
	arrayBasedList<T>::~arrayBasedList() { delete[] listArray; }

	/// O(n) Copy constructor.
	template <typename T>
	arrayBasedList<T>::arrayBasedList(const arrayBasedList& obj)
	{
		maxSize = obj.maxSize;
		listSize = obj.listSize;
		curr = obj.curr;

		listArray = new T[maxSize];
		for (size_t i = 0; i < maxSize; i++)
			listArray[i] = obj.listArray[i];
	}

	/// O(n) Copy-assignment operator overloading.
	template <typename T>
	arrayBasedList<T>& arrayBasedList<T>::operator=(const arrayBasedList& obj)
	{
		maxSize = obj.maxSize;
		listSize = obj.listSize;
		curr = obj.curr;

		delete[] listArray;
		listArray = new T[maxSize];
		for (size_t i = 0; i < maxSize; i++)
			listArray[i] = obj.listArray[i];

		return *this;
	}

	/// O(1) Subscript operator overloading.
	template <typename T>
	T& arrayBasedList<T>::operator[](size_t i) const
	{
		if (i >= listSize)
			throw std::out_of_range("Subscript out of range");

		return listArray[i];
	}

	/// O(1) Set listSize to 0 (maxSize remains the same).
	template <typename T>
	void arrayBasedList<T>::clear() { listSize = curr = 0; }

	/// O(n) Store a new element in the list at the current position.
	template <typename T>
	void arrayBasedList<T>::insert(const T& item)
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
	void arrayBasedList<T>::append(const T& item)
	{
		if (listSize == maxSize)
			throw std::out_of_range("List capacity exceeded");

		listArray[listSize++] = item;
	}

	/// O(n) Remove the current element from the list.
	template <typename T>
	const T arrayBasedList<T>::remove()
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
	void arrayBasedList<T>::moveToStart() { curr = 0; }

	/// O(1) Move curr to element one-past-the-end.
	template <typename T>
	void arrayBasedList<T>::moveToEnd() { curr = listSize; }

	/// O(1) Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void arrayBasedList<T>::moveToPos(size_t pos)
	{
		if (pos > listSize)
			throw std::out_of_range("Pos out of range");

		curr = pos;
	}

	/// O(1) Move curr to the previous element, except when curr==0.
	template <typename T>
	void arrayBasedList<T>::prev() { if (curr != 0) curr--; }

	/// O(1) Move curr to the next element, it it exists (including one-past-the-end).
	template <typename T>
	void arrayBasedList<T>::next() { if (curr < listSize) curr++; }

	/// O(1) Get the number of elements in the list.
	template <typename T>
	size_t arrayBasedList<T>::length() const { return listSize; }

	/// O(1) Get the position number of the current element.
	template <typename T>
	size_t arrayBasedList<T>::currPos() const { return curr; }

	/// O(1) Get the element stored in the current position.
	template <typename T>
	const T& arrayBasedList<T>::getValue() const
	{
		if (curr >= listSize)
			throw std::out_of_range("No current element");

		return listArray[curr];
	}


	// ---------- node ------------------------------

	template <typename T>
	node<T>* node<T>::freelist = nullptr;

	template <typename T>
	node<T>::node(const T &content, node *nextNode) : content(content), next(nextNode)
	{ 
		/*
		if (nextNode == nullptr) next = nullptr;
		else 
		{
			next  = new node;
			*next = *nextNode;	// <<< new constructs / freellist initialization / const 
		}
		*/
	}

	template <typename T>	// <<< content not assigned
	node<T>::node(node* nextNode) : next(nextNode)
	{
		/*
		if (nextNode == nullptr) next = nullptr;
		else
		{
			next = new node;
			*next = *nextNode;
		}
		*/
	}

	template <typename T>
	node<T>::~node() { if(next != nullptr) delete next; }

	template <typename T>
	node<T>::node(const node &obj) : content(obj.content), next(obj.nextNode)
	{
		/*
		if (obj.next == nullptr) next = nullptr;
		else
		{
			next = new node;
			*next = *obj.nextNode;
		}
		*/
	}

	template <typename T>
	node<T>& node<T>::operator=(const node &obj)
	{
		content = obj.content;
		next	= obj.next;
		/*
		content = obj.content;

		if (next != nullptr)	 delete next;
		if (obj.next == nullptr) next = nullptr;
		else {
			 next = new node;
			*next = *(obj.next);
		}
		*/
		return *this;
	}

	template <typename T>
	node<T>* node<T>::getNext() { return next; }

	template <typename T>
	node<T>* node<T>::setNext(node *nextNode) 
	{ 	
		return next = nextNode;
		/*
		if (next != nullptr)	 delete next;
		if (nextNode == nullptr) return next = nullptr;
		else {
			//new(next) node; <<<
			next = new node;
			*next = *nextNode;
			return next;
			//return &(*next = *nextNode);
		}
		*/
	}

	template <typename T>
	const T& node<T>::getContent() { return content; }

	template <typename T>
	const T& node<T>::setContent(const T& content) { return this->content = content; }

	/// Allocate memory and create a new node. Returns a pointer to that memory. Remember to delete (deallocate) it when it's no longer needed.
	template <typename T>
	node<T>* node<T>::get(const T &content, node *nextNode)
	{
		if (freelist == nullptr)
			return new node(content, nextNode);

		node* newNode	= freelist;
		freelist		= freelist->getNext();
		newNode->setContent(content);
		newNode->setNext(nextNode);
		return newNode;
	}

	/// Save this node in the freelist (head)
	template <typename T>
	void node<T>::release()
	{
		//content = null;
		next = freelist;
		freelist = this;
	}

	/// Delete (deallocate) all nodes in the freelist (maybe when no linked lists exist or no nodes an in use) 	// <<< USAR
	template <typename T>
	void node<T>::emptyFreelist()
	{
		delete freelist;
		freelist = nullptr;
		/*
		while (freelist != nullptr)
		{
			node<T>* nod = freelist;
			freelist = freelist->getNext();
			delete nod;
		}
		*/
	}

	/// Get a reference to the freelist. Required in singlyLinkedList<T>::clear() for getting O(1) performance.
	template <typename T>
	node<T>*& node<T>::getFreelist() { return freelist; }


	// ---------- singlyLinkedList ------------------------------

	/// O(1) Constructor. The parameter "size" is ignored.
	template <typename T>
	singlyLinkedList<T>::singlyLinkedList(size_t size) 
	{ 
		curr = head = tail = new node<T>(nullptr);
		count = 0;	
	}

	/// O(n) Constructor. It takes an initialization list.
	template <typename T>
	singlyLinkedList<T>::singlyLinkedList(const std::initializer_list<T>& il)
	{
		curr = head = tail = new node<T>(nullptr);
		count = 0;

		const T* item = il.begin();
		for(size_t i = 0; i < il.size(); i++)
			append(item[i]);
	}

	/// O(n) Copy constructor.
	template <typename T>
	singlyLinkedList<T>::singlyLinkedList(const singlyLinkedList& obj)
	{
		curr = head = tail = new node<T>(nullptr);
		count = 0;

		for (node<T>* pos = obj.head; pos->getNext() != nullptr; pos = pos->getNext())
			append(pos->getNext()->getContent());
	}

	/// O(n) Delete all nodes in the list, including header node.
	template <typename T>
	singlyLinkedList<T>::~singlyLinkedList() 
	{ 
		delete head;
	}	// <<< see clear() too

	/// O(n) Copy-assignment operator overloading.
	template <typename T>
	singlyLinkedList<T>& singlyLinkedList<T>::operator=(const singlyLinkedList& obj)
	{
		clear();

		for (node<T>* pos = obj.head; pos->getNext() != nullptr; pos = pos->getNext())
			append(pos->getNext()->getContent());

		return *this;
	}
/*
	/// O(n) Subscript operator overloading.
	template <typename T>
	T& singlyLinkedList<T>::operator[](size_t i) const
	{
		node<T>* originalCurr	= curr;
		moveToPos(i);
		const T& result			= *(curr->getNext()->getContent());
		curr					= originalCurr;
		return result;
	}
*/
	/// O(1) Move all nodes in the list to the freelist, except header node.
	template <typename T>
	void singlyLinkedList<T>::clear()
	{
		//delete head->getNext();					// O(n) Delete all items in the linked list, except header node.

		//moveToStart();
		//while (curr != tail) remove();			// O(n) Move all nodes to the freelist, except header node.

		tail->setNext(node<T>::getFreelist());		// O(1) Move all nodes to the freelist, except header node.
		node<T>::getFreelist() = head->getNext();

		head->setNext(nullptr);
		curr = tail = head;
		count = 0;
	}

	/// O(1) Store a new node in the list at the current position.
	template <typename T>
	void singlyLinkedList<T>::insert(const T &content)
	{
		curr->setNext(node<T>::get(content, curr->getNext()));	// New node inserted after curr (to insert in the head, we use header node)
		if (tail == curr) tail = curr->getNext();				// In case we inserted in the tail
		count++;
	}
	
	/// O(1) Store a new node at the end of the list (tail).
	template <typename T>
	void singlyLinkedList<T>::append(const T& content)
	{
		tail = tail->setNext(node<T>::get(content, nullptr));
		count++;
	}

	/// O(1) Remove the current node from the list and save it in the freelist.
	template <typename T>
	const T singlyLinkedList<T>::remove()
	{	
		if (tail == curr)				throw std::out_of_range("No current element");	// If the item to remove is one-past-the-end
		if (tail == curr->getNext())	tail = curr;									// If the object to remove is the tail
			
		T tempContent		= curr->getNext()->getContent();
		node<T>* tempNode	= curr->getNext();

		curr->setNext(curr->getNext()->getNext());
		tempNode->release();
		count--;
		return tempContent;
	}

	/// O(1) Get the number of nodes in the list.
	template <typename T>
	size_t singlyLinkedList<T>::length() const { return count; }

	/// O(n) Get the position number of the current node.
	template <typename T>
	size_t singlyLinkedList<T>::currPos() const
	{
		node<T> *temp = head;
		size_t i;

		for (i = 0; curr != temp; i++) 
			temp = temp->getNext();

		return i;
	}

	/// O(1) Get the item stored in the current node.
	template <typename T>
	const T& singlyLinkedList<T>::getValue() const
	{
		if (curr == tail)
			throw std::out_of_range("No current element");

		return curr->getNext()->getContent();
	}

	/// O(1) Move curr to the header node.
	template <typename T>
	void singlyLinkedList<T>::moveToStart() { curr = head; }

	/// O(1) Move curr to the tail (node one-past-the-end).
	template <typename T>
	void singlyLinkedList<T>::moveToEnd() { curr = tail; }

	/// O(n) Move curr to any position from 0 to one-past-the-end.
	template <typename T>
	void singlyLinkedList<T>::moveToPos(size_t pos)
	{
		if (pos > count)
			throw std::out_of_range("No current element");

		curr = head;
		for (size_t i = 0; i < pos; i++) 
			curr = curr->getNext();
	}

	/// O(n) Move curr to the previous node, except when curr==head.
	template <typename T>
	void singlyLinkedList<T>::prev()
	{
		if (curr == head) return;

		node<T> *temp = head;
		while (temp->getNext() != curr) temp = temp->getNext();
		curr = temp;
	}

	/// O(1) Move curr to the next node, if it exists (including one-past-the-end).
	template <typename T>
	void singlyLinkedList<T>::next() { if (curr != tail) curr = curr->getNext(); }
	

	// ---------- doubleLinkedList ------------------------------





}

#endif