#ifndef TwoThreeTree_H
#define TwoThreeTree_H

#include "TriNode.h"

template <class ItemType>
class TwoThreeTree
{
private:
	void inOrder(TriNode<ItemType>*, void visit(ItemType&));
	void postOrder(TriNode<ItemType>*, void visit(ItemType&));
	void preOrder(TriNode<ItemType>*, void visit(ItemType&));

	bool findItemHelper(TriNode<ItemType>* Node, const ItemType&);
	TriNode<ItemType>* insertHelper(TriNode<ItemType>* Node, const ItemType&);
	void split(TriNode<ItemType>* Node);

	TriNode<ItemType>* pRoot;
public:
	TwoThreeTree();
	~TwoThreeTree();
	bool isEmpty() const{ return pRoot; }

	bool findItem(const ItemType&);
	void insertItem(const ItemType&);
	bool removeItem(const ItemType&);

	void clear();

	void traverseInOrder(void visit(ItemType&));
	void traversePostOrder(void visit(ItemType&));
	void traversePreOrder(void visit(ItemType&));
};

template <class ItemType>
void TwoThreeTree<ItemType>::inOrder(TriNode<ItemType>* Node, void visit(ItemType&))
{
	if (Node->isLeaf())
	{
		visit(Node->getSmallItem);
	}
	else if (Node->isThreeNode())
	{
		inOrder(Node->getLeftChildPtr(), visit);
		visit(Node->getSmallItem());
		inOrder(Node->getMidChildPtr(), visit);
		visit(Node->getRightChildPtr());
		inOrder(Node->getRightChildPtr(), visit);
	}
	else
	{
		inOrder(Node->getLeftChildPtr(), visit);
		visit(Node->getSmallItem());
		inOrder(Node->getRightChildPtr(), visit);
	}
}

template <class ItemType>
void TwoThreeTree<ItemType>::postOrder(TriNode<ItemType>* Node, void visit(ItemType&))
{
	if (Node->isLeaf())
	{
		visit(Node->getSmallItem);
	}
	else if (Node->isThreeNode())
	{
		inOrder(Node->getLeftChildPtr(), visit);
		inOrder(Node->getMidChildPtr(), visit);
		visit(Node->getSmallItem());
		inOrder(Node->getRightChildPtr(), visit);
		visit(Node->getRightChildPtr());
	}
	else
	{
		inOrder(Node->getLeftChildPtr(), visit);
		inOrder(Node->getRightChildPtr(), visit);
		visit(Node->getSmallItem());
	}
}

template <class ItemType>
void TwoThreeTree<ItemType>::preOrder(TriNode<ItemType>* Node, void visit(ItemType&))
{
	if (Node->isLeaf())
	{
		visit(Node->getSmallItem);
	}
	else if (Node->isThreeNode())
	{
		visit(Node->getSmallItem());
		inOrder(Node->getLeftChildPtr(), visit);
		visit(Node->getRightChildPtr());
		inOrder(Node->getMidChildPtr(), visit);
		inOrder(Node->getRightChildPtr(), visit);
	}
	else
	{
		visit(Node->getSmallItem());
		inOrder(Node->getLeftChildPtr(), visit);
		inOrder(Node->getRightChildPtr(), visit);
	}
}

template <class ItemType>
TwoThreeTree<ItemType>::TwoThreeTree()
:pRoot(nullptr)
{}

template <class ItemType>
TwoThreeTree<ItemType>::~TwoThreeTree()
{
	clear();
}

template <class ItemType>
bool TwoThreeTree<ItemType>::findItemHelper(TriNode<ItemType>* Node, const ItemType& item)
{
	if ((Node->getSmallItem() == item) || (Node->getLargeItem() == item))
	{
		return true;
	}
	else if (Node->isLeaf())
	{
		return false;
	}

	else if (Node->isThreeNode())
	{
		if (Node->getSmallItem() > item)
			return findItemHelper(Node->getLeftChildPtr(), item);
		else if (Node->getLargeItem() > item)
			return findItemHelper(Node->getMidChildPtr(), item);
		else
			return findItemHelper(Node->getRightChildPtr(), item);
	}
	else
	{
		if (item < Node->getSmallItem())
			return findItemHelper(Node->getLeftChildPtr(), item);
		else
			return findItemHelper(Node->getRightChildPtr(), item);
	}
}

template <class ItemType>
bool TwoThreeTree<ItemType>::findItem(const ItemType& item)
{
	return findItemHelper(pRoot, item);
}

template <class ItemType>
void TwoThreeTree<ItemType>::split(TriNode<ItemType>* Node)
{
	TriNode<ItemType> *parentPtr, *n1, *n2;
	if (Node == pRoot)
	{
		parentPtr = new TriNode<ItemType>(Node->getMediumItem(), nullptr);
		pRoot = parentPtr;
	}
	else
	{
		parentPtr = Node->getParentPtr();
		parentPtr->enterItem(Node->getMediumItem());
		parentPtr->deleteChildPtr(Node);
	}

	n1 = new TriNode<ItemType>(Node->getSmallItem(), parentPtr);
	n2 = new TriNode<ItemType>(Node->getLargeItem(), parentPtr);

	
	parentPtr->enterChildPtr(n1);
	parentPtr->enterChildPtr(n2);


	if (!Node->isLeaf())
	{
		n1->setLeftChildPtr(Node->getLeftChildPtr());
		n1->setRightChildPtr(Node->getMidChildPtr());
		n2->setLeftChildPtr(Node->getRightMidChildPtr());
		n2->setRightChildPtr(Node->getRightChildPtr());
	}
	if (parentPtr->getItemNum() == 3)
		split(parentPtr);

	delete Node;
}

template <class ItemType>
TriNode<ItemType>* TwoThreeTree<ItemType>::insertHelper(TriNode<ItemType>* Node, const ItemType& item)
{
	if (Node->isLeaf())
	{
		Node->enterItem(item);
	}

	else if (Node->isThreeNode())
	{
		if (Node->getSmallItem() > item)
			return insertHelper(Node->getLeftChildPtr(), item);
		else if (Node->getLargeItem() > item)
			return insertHelper(Node->getMidChildPtr(), item);
		else
			return insertHelper(Node->getRightChildPtr(), item);
	}
	else
	{
		if (item < Node->getSmallItem())
			return insertHelper(Node->getLeftChildPtr(), item);
		else
			return insertHelper(Node->getRightChildPtr(), item);
	}
	if (Node->getItemNum() == 3)
		split(Node);
}

template <class ItemType>
void TwoThreeTree<ItemType>::insertItem(const ItemType& item)
{
	if (pRoot == nullptr)
		pRoot = new TriNode<ItemType>();
	insertHelper(pRoot, item);
}

template <class ItemType>
bool TwoThreeTree<ItemType>::removeItem(const ItemType& item)
{

}

template <class ItemType>
void TwoThreeTree<ItemType>::clear()
{
	
}

template <class ItemType>
void TwoThreeTree<ItemType>::traverseInOrder(void visit(ItemType&))
{
	inOrder(pRoot, visit);
}
template <class ItemType>
void TwoThreeTree<ItemType>::traversePostOrder(void visit(ItemType&))
{
	postOrder(pRoot, visit);
}

template <class ItemType>
void TwoThreeTree<ItemType>::traversePreOrder(void visit(ItemType&))
{
	preOrder(pRoot, visit);
}


#endif //TwoThreeTree_H