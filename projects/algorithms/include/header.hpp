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
		virtual				~list()										{ };
		
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
		
		// Bonus methods
							list(const std::initializer_list<T>& il)	{ };
							list(const list& obj)						{ };				// Copy constructor
		virtual	list&		operator=(const list& obj)					{ return *this; };	// Copy-assignment operator
		//virtual			T& operator[](size_t i)						= 0;
	};


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
		T&				operator[](size_t i);

		void			clear();
		void			insert(const T& item);
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
		T				content;
		node*			next;
		static node*	freelist;	// <<< How to delete?

	public:
		typedef			T		value_type;
		typedef			size_t	size_type;

						node(const T &content, node *nextNode = nullptr);
						node(node* nextNode = nullptr);
						node(const node &obj);
						~node();
		node&			operator=(const node& obj);

		node*			getNext();
		node*			setNext(node *nextNode);
		const T&		getContent();
		const T&		setContent(const T &content);

		static node*	get(const T &content, node *nextNode);	// <<<
		void			release();							// <<<
	};


	/*
		Header node: Additional first node whose value is ignored. I helps with special cases (empty list, inserting at head...).
		This data structure stores a set of linked items (nodes), each one containing some object (content).
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
							singlyLinkedList(size_t size = 0);				// Size is ignored
							singlyLinkedList(const std::initializer_list<T>& il);
							singlyLinkedList(const singlyLinkedList& obj);
							~singlyLinkedList();
		singlyLinkedList&	operator=(const singlyLinkedList& obj);
		//T&				operator[](size_t i);							// Doesn't work because getContent() returns a const T&  <<< should I implement node<T> as T

		void				clear();				// 1 <<< check complexity of all methods in this header file
		void				insert(const T& content);		// 1
		void				append(const T& content);// 1
		const T				remove();				// 1

		size_t				length() const;				// 1
		size_t				currPos() const;				// 1
		const T&			getValue() const;				// 1

		void				moveToStart();			// 1
		void				moveToEnd();			// 1
		void				moveToPos(size_t pos);	// n
		void				prev();					// n
		void				next();					// 1
	};


	// ---------- arrayBasedList ------------------------------

	template <typename T>
	size_t find(arrayBasedList<T>& list, const T& item)
	{
		for (list.moveToStart(); list.currPos() < list.length(); list.next())
			if (item == list.getValue())
				return list.currPos();

		return list.currPos();
	}

	template <typename T>
	arrayBasedList<T>::arrayBasedList(size_t size) : maxSize(size), listSize(0), curr(0) { listArray = new T[size]; }// <<< size == 0?

	template <typename T>// <<< size == 0?
	arrayBasedList<T>::arrayBasedList(const std::initializer_list<T>& il) : maxSize(il.size()), listSize(il.size()), curr(0)
	{
		listArray = new T[il.size()];

		const T* item = il.begin();
		for (size_t i = 0; i < il.size(); i++)
			listArray[i] = item[i];
	}

	template <typename T>
	arrayBasedList<T>::~arrayBasedList() { delete[] listArray; }

	template <typename T>
	arrayBasedList<T>::arrayBasedList(const arrayBasedList& obj)
	{
		maxSize = obj.maxSize;
		listSize = obj.listSize;
		curr = obj.curr;

		listArray = new T[maxSize];
		for (int i = 0; i < maxSize; i++)
			listArray[i] = obj.listArray[i];
	}

	template <typename T>
	arrayBasedList<T>& arrayBasedList<T>::operator=(const arrayBasedList& obj)
	{
		maxSize = obj.maxSize;
		listSize = obj.listSize;
		curr = obj.curr;

		delete[] listArray;
		listArray = new T[maxSize];
		for (int i = 0; i < maxSize; i++)
			listArray[i] = obj.listArray[i];

		return *this;
	}

	template <typename T>
	void arrayBasedList<T>::clear() { listSize = curr = 0; }

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

	template <typename T>
	void arrayBasedList<T>::append(const T& item)
	{
		if (listSize == maxSize)
			throw std::out_of_range("List capacity exceeded");

		listArray[listSize++] = item;
	}

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

	template <typename T>
	void arrayBasedList<T>::moveToStart() { curr = 0; }

	template <typename T>
	void arrayBasedList<T>::moveToEnd() { curr = listSize; }

	template <typename T>
	void arrayBasedList<T>::prev() { if (curr != 0) curr--; }

	template <typename T>
	void arrayBasedList<T>::next() { if (curr < listSize) curr++; }

	template <typename T>
	size_t arrayBasedList<T>::length() const { return listSize; }

	template <typename T>
	size_t arrayBasedList<T>::currPos() const { return curr; }

	template <typename T>
	void arrayBasedList<T>::moveToPos(size_t pos)
	{
		if (pos > listSize)
			throw std::out_of_range("Pos out of range");

		curr = pos;
	}

	template <typename T>
	const T& arrayBasedList<T>::getValue() const
	{
		if (curr >= listSize)
			throw std::out_of_range("No current element");

		return listArray[curr];
	}

	template <typename T>
	T& arrayBasedList<T>::operator[](size_t i)
	{
		if (i >= listSize)
			throw std::out_of_range("Subscript out of range");

		return listArray[i];
	}


	// ---------- node ------------------------------

	template <typename T>
	node<T>* node<T>::freelist = nullptr;

	template <typename T>
	node<T>::node(const T &content, node *nextNode) : content(content)
	{ 
		if (nextNode == nullptr) next = nullptr;
		else 
		{
			next  = new node;
			*next = *nextNode;	// <<< new constructs / freellist initialization / const 
		}
	}

	template <typename T>
	node<T>::node(node* nextNode)
	{
		if (nextNode == nullptr) next = nullptr;
		else
		{
			next = new node;
			*next = *nextNode;
		}
	}

	template <typename T>
	node<T>::~node() { if(next != nullptr) delete next; }

	template <typename T>
	node<T>::node(const node &obj) : content(obj.content)
	{
		if (obj.next == nullptr) next = nullptr;
		else
		{
			next = new node;
			*next = *obj.nextNode;
		}
	}

	template <typename T>
	node<T>& node<T>::operator=(const node &obj)
	{
		content = obj.content;

		if (next != nullptr)	 delete next;
		if (obj.next == nullptr) next = nullptr;
		else {
			 next = new node;
			*next = *obj.next;
		}

		return *this;
	}

	template <typename T>
	node<T>* node<T>::getNext() { return next; }

	template <typename T>
	node<T>* node<T>::setNext(node *nextNode) 
	{ 
		if (next != nullptr)	 delete next;
		if (nextNode == nullptr) return next = nullptr;
		else {
			next = new node;
			return &(*next = *nextNode);
		}
	}

	template <typename T>
	const T& node<T>::getContent() { return content; }

	template <typename T>
	const T& node<T>::setContent(const T& content) { return this->content = content; }

	template <typename T>
	node<T>* node<T>::get(const T &content, node *nextNode)
	{
		if (freelist == nullptr)
			return new node(content, nextNode);

		node* temp = freelist;
		freelist = freelist->getNext();
		temp->setContent(content);
		temp->setNext(nextNode);
		return temp;
	}

	template <typename T>
	void node<T>::release()
	{
		//content = null;
		next = freelist;
		freelist = this;
	}


	// ---------- singlyLinkedList ------------------------------

	template <typename T>
	singlyLinkedList<T>::singlyLinkedList(size_t size) 
	{ 
		curr = head = tail = new node<T>(nullptr);
		count = 0;	
	}

	template <typename T>
	singlyLinkedList<T>::singlyLinkedList(const std::initializer_list<T>& il)
	{
		curr = head = tail = new node<T>(nullptr);
		count = 0;

		const T* item = il.begin();
		for(size_t i = 0; i < il.size(); i++)
			append(item[i]);
	}

	template <typename T>
	singlyLinkedList<T>::singlyLinkedList(const singlyLinkedList& obj)
	{
		curr = head = tail = new node<T>(nullptr);
		count = 0;

		for (node<T>* pos = obj.head; pos->getNext() != nullptr; pos = pos->getNext())
			append(pos->getNext()->getContent());
	}

	template <typename T>
	singlyLinkedList<T>::~singlyLinkedList() { delete head;	}

	template <typename T>
	singlyLinkedList<T>& singlyLinkedList<T>::operator=(const singlyLinkedList& obj)
	{
		clear();

		for (node<T>* pos = obj.head; pos->getNext() != nullptr; pos = pos->getNext())
			append(pos->getNext()->getContent());

		return *this;
	}
/*
	template <typename T>
	T& singlyLinkedList<T>::operator[](size_t i)
	{
		node<T>* originalCurr	= curr;
		moveToPos(i);
		const T& result			= *(curr->getNext()->getContent());
		curr					= originalCurr;
		return result;
	}
*/
	template <typename T>
	void singlyLinkedList<T>::clear()
	{
		head->setNext(nullptr);		// This deletes all items in the linked list (except header node)
		curr = tail = head;
		//curr = head = tail = new node(nullptr);
		count = 0;
	}

	template <typename T>
	void singlyLinkedList<T>::insert(const T &content)
	{
		curr->setNext(node<T>::get(content, curr->getNext()));	// New node inserted after curr (to insert in the head, we use header node)
		if (tail == curr) tail = curr->getNext();			// In case we inserted in the tail
		count++;
	}
		
	template <typename T>
	void singlyLinkedList<T>::append(const T& content)
	{
		tail = tail->setNext(node<T>::get(content, nullptr));
		count++;
	}

	template <typename T>
	const T singlyLinkedList<T>::remove()
	{			
		if (curr->getNext() == nullptr) throw std::out_of_range("No current element");	// If the item to remove is one-past-the-end
		if (tail == curr->getNext())    tail = curr;									// If the object to remove is the tail
			
		T tempContent		= curr->getNext()->getContent();
		node<T>* tempNode	= curr->getNext();
		
		curr->setNext(curr->getNext()->getNext());
		tempNode->release();
		count--;
		return tempContent;
	}

	template <typename T>
	size_t singlyLinkedList<T>::length() const { return count; }

	template <typename T>
	size_t singlyLinkedList<T>::currPos() const
	{
		node<T> *temp = head;
		size_t i;
		for (i = 0; curr != temp; i++) 
			temp = temp->getNext();
		return i;
	}

	template <typename T>
	const T& singlyLinkedList<T>::getValue() const
	{
		if (curr->getNext() == nullptr)
			throw std::out_of_range("No current element");

		return curr->getNext()->getContent();
	}

	template <typename T>
	void singlyLinkedList<T>::moveToStart() { curr = head; }

	template <typename T>
	void singlyLinkedList<T>::moveToEnd() { curr = tail; }

	template <typename T>
	void singlyLinkedList<T>::moveToPos(size_t pos)
	{
		if (pos > count)
			throw std::out_of_range("No current element");

		curr = head;
		for (int i = 0; i < pos; i++) 
			curr = curr->getNext();
	}

	template <typename T>
	void singlyLinkedList<T>::prev()
	{
		if (curr == head) return;

		node<T> *temp = head;
		while (temp->getNext() != curr) temp = temp->getNext();
		curr = temp;
	}

	template <typename T>
	void singlyLinkedList<T>::next() { if (curr != tail) curr = curr->getNext(); }
	

	// ---------- doubleLinkedList ------------------------------





}

#endif