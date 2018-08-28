#include "TemplateDoublyLinkedList.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

template<class T>
class MinQueue{
private: 
	DoublyLinkedList<T> ll;
public:
	MinQueue(): ll() {}
	~MinQueue() { ll.~DoublyLinkedList();}
	void enqueue(T elem){
		ll.insertLast(elem);
	} 
	T dequeue();
	int size(){
		return DoublyLinkedListLength(ll);
	}
	void printQueue(){
		cout << "Queue: " <<ll << endl;
		return;
	}

	bool isEmpty(){
		return ll.isEmpty();
	}

	T min();
};

struct QueueEmptyException : std::range_error {
  explicit QueueEmptyException(char const* msg=NULL): range_error(msg) {}
};

template<class T>
T MinQueue<T>::dequeue(){
	if(ll.isEmpty())
		throw QueueEmptyException("Access to empty queue.");
	return ll.removeFirst();
}

template<class T>
T MinQueue<T>::min(){
	if(ll.isEmpty())
		throw QueueEmptyException("Access to empty queue.");
	DListNode<T> * minNode = ll.getFirst();
	DListNode<T> * iterNode = ll.getFirst();
	while(iterNode != ll.getAfterLast()){
		if(iterNode->obj < minNode->obj)
			minNode = iterNode;
		iterNode = iterNode->next;
	}
	T obj = minNode->obj;
	//delete minNode;
	//delete iterNode;
	
	return obj;
}



int main () {
	cout << "create a queue." <<endl;
	MinQueue<int> q1;
	q1.printQueue();

	if(q1.isEmpty())
		cout << "Queue is empty" <<endl;

	cout << "push 10 elements" <<endl;
	for(int i = 10; i > 0; --i){
		q1.enqueue(i);
	}
	q1.printQueue();
	cout << "size: " <<q1.size() <<endl;


	cout << "pop 2 elements" <<endl;
	q1.dequeue();
	q1.dequeue();
	q1.printQueue();
	cout << "size: " <<q1.size() <<endl;
	cout << "min: " <<q1.min() <<endl;


	if(q1.isEmpty())
		cout << "Queue is empty" <<endl;

  return 0;
}
