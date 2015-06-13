#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "RedBlackNode.h"
#include "Stack.h"

template <class ItemType>
class RedBlackTree
{
private:
	RedBlackNode<ItemType>* pRoot = nullptr;
	Stack<RedBlackNode<ItemType>*> Tracer = Stack<RedBlackNode<ItemType>*>(50); //50 is amount of nodes in stack for use
public:
	RedBlackTree() {};
	~RedBlackTree() { clear(); }
	bool isEmpty() const{ (pRoot == nullptr) ? true : false; }
	bool findItem(ItemType&);
	bool removeItem(ItemType&);
	void insertItem(ItemType&);
	void clear();
};

template <class ItemType>
bool RedBlackTree<ItemType>::findItem(ItemType& item)
{
	RedBlackNode<ItemType>* curNode = pRoot;
	while (curNode != nullptr)
	{
		if (curNode->getVal() == item)
		{
			return true;
		}
		else if (curNode->getVal() > item)
		{
			curNode = curNode->getRightNode();
		}
		else
		{
			curNode = curNode->getLeftNode();
		}
	}
	return false;
}

template <class ItemType>
bool RedBlackTree<ItemType>::removeItem(ItemType& item)
{

}

template <class ItemType>
void RedBlackTree<ItemType>::insertItem(ItemType& item)
{
	RedBlackNode<ItemType>* newNode = new RedBlackNode<ItemType>;
	newNode->setVal(item);
	if (pRoot == nullptr)
	{
		pRoot = newNode;
	}
	else
	{
		Tracer.clear(); //clear the stack that traces the redblack tree
		RedBlackNode<ItemType>* curNode = pRoot;
		while (curNode != nullptr)
		{
			Tracer.push(curNode);
			if (curNode->getVal() > item)
			{
				curNode = curNode->getRightNode();
			}
			else
			{
				curNode = curNode->getLeftNode();
			}
		}
		curNode = Tracer.peek();
		Tracer.pop();
		if (curNode->getVal() > item)
		{
			
		}
		else
		{

		}
		RedBlackNode<ItemType>* parentNode;
		if (!Tracer.isEmpty())
		{
			parentNode = Tracer.peek();
			Tracer.pop();
		}
	}
}

template <class ItemType>
void RedBlackTree<ItemType>::clear()
{
	
}

#endif //REDBLACKTREE_H