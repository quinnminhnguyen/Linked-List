#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;
template<class T>
class DoublyLinkedList; // class declaration

// list node
template<class T>
struct DListNode {
  T obj;
  DListNode<T> *prev, *next;
  DListNode(T e = T(), DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : obj(e), prev(p), next(n) {}
  friend class DoublyLinkedList<T>;
};

// doubly linked list
template<class T>
class DoublyLinkedList {
private:
  DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList(const DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void insertAfter(DListNode<T> *p, T newobj);
  void insertBefore(DListNode<T> *p, T newobj);
  T removeAfter(DListNode<T> *p);
  T removeBefore(DListNode<T> *p);
};

// output operator
template<class T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);
// return the list length
template<class T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll);


// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  // Initialize the list
  DListNode<T> *current = dll.getFirst();	//get current to iterate through dll
  header.next = &trailer; trailer.prev = &header;	// header and trailer point to each other
  while(current != dll.getAfterLast()){	//while current is not trailer
  	DListNode<T> *newNode = new DListNode<T>(current->obj, trailer.prev, &trailer); //insert last method
  	trailer.prev->next = newNode;
  	trailer.prev = newNode;
  	current = current->next; //next element to copy
  }
  /* Complete this function */
}

// assignment operator
template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
  // Delete the whole list
  DListNode<T> *prev_node, *node = header.next;
  while(node != &trailer){
  	prev_node = node;
  	node = node->next;
  	delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;

  DListNode<T> *current = dll.getFirst();	//get current to iterate through dll
  while(current != dll.getAfterLast()){	//while current is not trailer
  	DListNode<T> *newNode = new DListNode<T>(current->obj, trailer.prev, &trailer); //insert last method
  	trailer.prev->next = newNode;
  	trailer.prev = newNode;
  	current = current->next; //next element to copy
  }
  return *this;
  /* Complete this function */
}

// insert the new object as the first one
template<class T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{
	DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next); //initialize a node
  	header.next->prev = newNode;
  	header.next = newNode;
    /* Complete this function */
}

// insert the new object as the last one
template<class T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
    /* Complete this function */
  	DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev, &trailer); //insert last method
  	trailer.prev->next = newNode;
  	trailer.prev = newNode;
}

// remove the first object from the list
template<class T>
T DoublyLinkedList<T>::removeFirst()
{
	if(isEmpty()) 
		throw  EmptyDLinkedListException("Cannot remove. Empty list.");
    DListNode<T> *node = header.next;
    header.next = node->next;
    node->next->prev = &header;
    T obj = node->obj;
    delete node;
    return obj;
    /* Complete this function */
}

// remove the last object from the list
template<class T>
T DoublyLinkedList<T>::removeLast()
{
	if(isEmpty()) 
		throw  EmptyDLinkedListException("Cannot remove. Empty list.");
	DListNode<T> *node = trailer.prev;
	trailer.prev = node->prev; //switch?
	trailer.prev->next = &trailer;
	T obj = node->obj;
	delete node;
	return obj;
    /* Complete this function */
}

// destructor
template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    /* Complete this function */
  DListNode<T> *prev_node, *node = header.next;
  while(node != &trailer){
  	prev_node = node;
  	node = node->next;
  	delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// return the first object
template<class T>
T DoublyLinkedList<T>::first() const
{
	if(isEmpty()) 
		throw  EmptyDLinkedListException("Cannot remove. Empty list.");
 	return header.next->obj;
    /* Complete this function */
}

// return the last object
template<class T>
T DoublyLinkedList<T>::last() const
{
	if(isEmpty()) 
		throw  EmptyDLinkedListException("Cannot remove. Empty list.");
	return trailer.prev->obj;
    /* Complete this function */
}

// insert the new object after the node p
template<class T>
void DoublyLinkedList<T>::insertAfter(DListNode<T> *p, T newobj)
{
	if(p == &trailer){
		throw  EmptyDLinkedListException("cannot insert after trailer.");
	}
	else if(isEmpty()){
		DListNode<T> *newnode = new DListNode<T>(newobj, &header, &trailer);
		header.next = newnode;
		trailer.prev = newnode;
		return;
	}
	else{
		DListNode<T> *node = new DListNode<T>(newobj,p,p->next);
		node->next->prev = node;
		node->prev->next = node;
		return;
		}
	
/* Complete this function */
}

// insert the new object before the node p
template<class T>
void DoublyLinkedList<T>::insertBefore(DListNode<T> *p, T newobj)
{
	if(p == &header){
		throw  EmptyDLinkedListException("cannot insert after trailer.");
	}
	else if(isEmpty()){
		DListNode<T> *newnode = new DListNode<T>(newobj, &header, &trailer);
		header.next = newnode;
		trailer.prev = newnode;
		return;
	}
	else{
		DListNode<T> *node = new DListNode<T>(newobj,p->prev,p);
		node->prev->next = node;
		node->next->prev = node;
		return;
	}  /* Complete this function */
}

// remove the node after the node p
template<class T>
T DoublyLinkedList<T>::removeAfter(DListNode<T> *p)
{
	if(p == &trailer || isEmpty()){
		throw  EmptyDLinkedListException("cannot insert.");
	}
	else{
		DListNode<T> *node = p->next;
		T obj = node->obj;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		return obj;
	} /* Complete this function */
}

// remove the node before the node p
template<class T>
T DoublyLinkedList<T>::removeBefore(DListNode<T> *p)
{
	if(p == &header || isEmpty()){
		throw  EmptyDLinkedListException("cannot insert.");
	}
	else{
		DListNode<T> *node = p->prev;
		T obj = node->obj;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		return obj;
	}
    /* Complete this function */
}

// return the list length
template<class T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll)
{
	DListNode<T> *node = dll.getFirst();
	int count = 0;
	while(node != dll.getAfterLast()){
		count ++;
		node = node->next;
	}
	return count;
    /* Complete this function */
}

// output operator
template<class T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
  DListNode<T> *node = dll.getFirst();
	while(node != dll.getAfterLast()){
		out << node->obj << " ";
		node = node->next;
	}
  /* Complete this function */
  
  return out;
}
