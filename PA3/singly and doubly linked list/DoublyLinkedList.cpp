#include "DoublyLinkedList.h"
#include <stdexcept>

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll)
{
  // Initialize the list
  DListNode *current = dll.getFirst();	//get current to iterate through dll
  header.next = &trailer; trailer.prev = &header;	// header and trailer point to each other
  while(current != dll.getAfterLast()){	//while current is not trailer
  	DListNode * newNode = new DListNode(current->obj, trailer.prev, &trailer); //insert last method
  	trailer.prev->next = newNode;
  	trailer.prev = newNode;
  	current = current->next; //next element to copy
  }
  /* Complete this function */
}

// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll)
{
  // Delete the whole list
  DListNode *prev_node, *node = header.next;
  while(node != &trailer){
  	prev_node = node;
  	node = node->next;
  	delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;

  DListNode *current = dll.getFirst();	//get current to iterate through dll
  while(current != dll.getAfterLast()){	//while current is not trailer
  	DListNode * newNode = new DListNode(current->obj, trailer.prev, &trailer); //insert last method
  	trailer.prev->next = newNode;
  	trailer.prev = newNode;
  	current = current->next; //next element to copy
  }
  return *this;
  /* Complete this function */
}

// insert the new object as the first one
void DoublyLinkedList::insertFirst(int newobj)
{
	DListNode * newNode = new DListNode(newobj, &header, header.next); //initialize a node
  	header.next->prev = newNode;
  	header.next = newNode;
    /* Complete this function */
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj)
{
    /* Complete this function */
  	DListNode * newNode = new DListNode(newobj, trailer.prev, &trailer); //insert last method
  	trailer.prev->next = newNode;
  	trailer.prev = newNode;
}

// remove the first object from the list
int DoublyLinkedList::removeFirst()
{
	if(isEmpty()) 
		throw  EmptyDLinkedListException("Cannot remove. Empty list.");
    DListNode * node = header.next;
    header.next = node->next;
    node->next->prev = &header;
    int obj = node->obj;
    delete node;
    return obj;
    /* Complete this function */
}

// remove the last object from the list
int DoublyLinkedList::removeLast()
{
	if(isEmpty()) 
		throw  EmptyDLinkedListException("Cannot remove. Empty list.");
	DListNode *node = trailer.prev;
	trailer.prev = node->prev; //switch?
	trailer.prev->next = &trailer;
	int obj = node->obj;
	delete node;
	return obj;
    /* Complete this function */
}

// destructor
DoublyLinkedList::~DoublyLinkedList()
{
    /* Complete this function */
  DListNode *prev_node, *node = header.next;
  while(node != &trailer){
  	prev_node = node;
  	node = node->next;
  	delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// return the first object
int DoublyLinkedList::first() const
{
	if(isEmpty()) 
		throw  EmptyDLinkedListException("Cannot remove. Empty list.");
 	return header.next->obj;
    /* Complete this function */
}

// return the last object
int DoublyLinkedList::last() const
{
	if(isEmpty()) 
		throw  EmptyDLinkedListException("Cannot remove. Empty list.");
	return trailer.prev->obj;
    /* Complete this function */
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode *p, int newobj)
{
	if(p == &trailer){
		throw  EmptyDLinkedListException("cannot insert after trailer.");
	}
	else if(isEmpty()){
		DListNode *newnode = new DListNode(newobj, &header, &trailer);
		header.next = newnode;
		trailer.prev = newnode;
		return;
	}
	else{
		DListNode *node = new DListNode(newobj,p,p->next);
		node->next->prev = node;
		node->prev->next = node;
		return;
		}
	
/* Complete this function */
}

// insert the new object before the node p
void DoublyLinkedList::insertBefore(DListNode *p, int newobj)
{
	if(p == &header){
		throw  EmptyDLinkedListException("cannot insert after trailer.");
	}
	else if(isEmpty()){
		DListNode *newnode = new DListNode(newobj, &header, &trailer);
		header.next = newnode;
		trailer.prev = newnode;
		return;
	}
	else{
		DListNode *node = new DListNode(newobj,p->prev,p);
		node->prev->next = node;
		node->next->prev = node;
		return;
	}  /* Complete this function */
}

// remove the node after the node p
int DoublyLinkedList::removeAfter(DListNode *p)
{
	if(p == &trailer || isEmpty()){
		throw  EmptyDLinkedListException("cannot insert.");
	}
	else{
		DListNode *node = p->next;
		int obj = node->obj;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		return obj;
	} /* Complete this function */
}

// remove the node before the node p
int DoublyLinkedList::removeBefore(DListNode *p)
{
	if(p == &header || isEmpty()){
		throw  EmptyDLinkedListException("cannot insert.");
	}
	else{
		DListNode *node = p->prev;
		int obj = node->obj;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		return obj;
	}
    /* Complete this function */
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll)
{
	DListNode *node = dll.getFirst();
	int count = 0;
	while(node != dll.getAfterLast()){
		count ++;
		node = node->next;
	}
	return count;
    /* Complete this function */
}

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll)
{
  DListNode *node = dll.getFirst();
	while(node != dll.getAfterLast()){
		out << node->obj << " ";
		node = node->next;
	}
  /* Complete this function */
  
  return out;
}
