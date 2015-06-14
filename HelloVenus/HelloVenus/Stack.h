#ifndef STACK_H
#define STACK_H

#include "StackNode.h"

template <class ItemType>
class Stack
{
private:
	StackNode<ItemType>* pHead = nullptr;
	StackNode<ItemType>* pUnused = nullptr;
public:
	Stack();
	Stack(unsigned int Size);
	~Stack();

	inline bool isEmpty() const{ return (pHead == nullptr) ? true:false; }
	inline ItemType peek();
	void pop();
	void push(ItemType &);

	void increaseSize(unsigned int Size);
	void clear();
};


template <class ItemType>
Stack<ItemType>::Stack()
:pHead(nullptr)
{
}


template <class ItemType>
Stack<ItemType>::Stack(unsigned int Size)
{
	StackNode<ItemType>* Chain = new StackNode<ItemType>;
	pUnused = Chain;
	StackNode<ItemType>* NewNode;
	while (--Size)
	{
		NewNode = new StackNode<ItemType>;
		Chain->SetNext(NewNode);
		Chain = NewNode;
	}
}


template <class ItemType>
Stack<ItemType>::~Stack()
{
	clear();
}

template <class ItemType>
inline ItemType Stack<ItemType>::peek()
{
	return pHead->GetItem();
}

template <class ItemType>
void Stack<ItemType>::pop()
{
	StackNode<ItemType>* OldNode = pHead;
	pHead = pHead->GetNext();
	OldNode->SetNext(pUnused);
	pUnused = OldNode;
}

template <class ItemType>
void Stack<ItemType>::push(ItemType &NewItem)
{
	StackNode<ItemType>* NewNode;
	if (pUnused != nullptr)
	{
		NewNode = pUnused;
		pUnused = pUnused->GetNext();
		NewNode->SetItem(NewItem);
		NewNode->SetNext(pHead);
	}
	else
		NewNode = new StackNode<ItemType>(pHead,NewItem);
	pHead = NewNode; //assign the new node to the top
}

template <class ItemType>
void Stack<ItemType>::increaseSize(unsigned int Size)
{
	StackNode<ItemType>* NewNode;
	while (Size--)
	{
		NewNode = new StackNode<ItemType>*(pUnused);
		pUnused = NewNode;
	}
}

template <class ItemType>
void Stack<ItemType>::clear()
{
	if (pHead != nullptr)
	{
		delete pHead;
	}
	if (pUnused != nullptr)
	{
		delete pUnused;
	}
}

#endif //STACK_H