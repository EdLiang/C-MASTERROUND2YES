#ifndef TwoThreeTree_H
#define TwoThreeTree_H

#include "TriNode.h"
#include <iostream>
using namespace std;

template <class ItemType>
class TwoThreeTree
{
private:
	void inOrder(TriNode<ItemType>*, void visit(ItemType&));
	void postOrder(TriNode<ItemType>*, void visit(ItemType&));
	void preOrder(TriNode<ItemType>*, void visit(ItemType&));

	bool findItemHelper(TriNode<ItemType>* Node, const ItemType&);
	TriNode<ItemType> * findNodeHelper(TriNode<ItemType>* Node, const ItemType&);
	TriNode<ItemType>* SwapInorder(TriNode<ItemType>* Node, const ItemType& val);
	void fixTree(TriNode<ItemType>* Node);
	TriNode<ItemType>* insertHelper(TriNode<ItemType>* Node, const ItemType&);
	void split(TriNode<ItemType>* Node);

	TriNode<ItemType>* pRoot;
public:
	TwoThreeTree();
	~TwoThreeTree();
	bool isEmpty() const{ return (pRoot == nullptr) ? true: false; }

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
		postOrder(Node->getLeftChildPtr(), visit);
		postOrder(Node->getMidChildPtr(), visit);
		visit(Node->getSmallItem());
		postOrder(Node->getRightChildPtr(), visit);
		visit(Node->getRightChildPtr());
	}
	else
	{
		postOrder(Node->getLeftChildPtr(), visit);
		postOrder(Node->getRightChildPtr(), visit);
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
		preOrder(Node->getLeftChildPtr(), visit);
		visit(Node->getRightChildPtr());
		preOrder(Node->getMidChildPtr(), visit);
		preOrder(Node->getRightChildPtr(), visit);
	}
	else
	{
		visit(Node->getSmallItem());
		preOrder(Node->getLeftChildPtr(), visit);
		preOrder(Node->getRightChildPtr(), visit);
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
	if (((Node->getSmallItem() == item) || (Node->getLargeItem() == item)) && Node->getItemNum() == 2)
	{
		return true;
	}
	else if ((Node->getItemNum() == 1) && Node->getSmallItem() == item)
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
	if (pRoot)
	{
		return findItemHelper(pRoot, item);
	}
	else
	{
		return false;
	}
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
		n1->getLeftChildPtr()->setParentPtr(n1);
		n1->getRightChildPtr()->setParentPtr(n1);
		n2->getLeftChildPtr()->setParentPtr(n2);
		n2->getRightChildPtr()->setParentPtr(n2);
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
TriNode<ItemType>* TwoThreeTree<ItemType>::findNodeHelper(TriNode<ItemType>* Node, const ItemType& item)
{
	if (((Node->getSmallItem() == item) || (Node->getLargeItem() == item)) && (Node->getItemNum() == 2))
	{
		return Node;
	}
	else if (Node->getSmallItem() == item && Node->getItemNum())
	{
		return Node;
	}
	else if (Node->isLeaf())
	{
		return nullptr;
	}

	else if (Node->isThreeNode())
	{
		if (Node->getSmallItem() > item)
			return findNodeHelper(Node->getLeftChildPtr(), item);
		else if (Node->getLargeItem() > item)
			return findNodeHelper(Node->getMidChildPtr(), item);
		else
			return findNodeHelper(Node->getRightChildPtr(), item);
	}
	else
	{
		if (item < Node->getSmallItem())
			return findNodeHelper(Node->getLeftChildPtr(), item);
		else
			return findNodeHelper(Node->getRightChildPtr(), item);
	}
}

template <class ItemType>
void TwoThreeTree<ItemType>::fixTree(TriNode<ItemType>* Node)
{
	if (Node->getParentPtr() == nullptr)
	{
		if (Node->isLeaf())
		{
			delete Node;
			pRoot = nullptr;	//Tree is empty
		}
		else
		{
			pRoot->getLeftChildPtr()->enterChildPtr(pRoot->getRightChildPtr());
			pRoot = pRoot->getLeftChildPtr();
			delete pRoot->getParentPtr();
			pRoot->setParentPtr(nullptr);
		}
		return;
	}
	TriNode<ItemType>* P = Node->getParentPtr();
	if (P->isThreeNode())
	{
		if (P->getLeftChildPtr() == Node)
		{
			delete P->getLeftChildPtr();
			P->setLeftChildPtr(P->getMidChildPtr());
			P->setMidChildPtr(nullptr);
			P->getLeftChildPtr()->enterItem(P->getSmallItem());
			P->deleteItem(P->getSmallItem());
		}
		else if (P->getMidChildPtr() == Node)
		{
			P->getRightChildPtr()->enterItem(P->getLargeItem());
			P->deleteItem(P->getLargeItem());
		}
		else //P->getRightChildPtr() == Node
		{
			delete P->getRightChildPtr();
			P->setRightChildPtr(P->getMidChildPtr());
			P->setMidChildPtr(nullptr);
			P->getRightChildPtr()->enterItem(P->getLargeItem());
			P->deleteItem(P->getLargeItem());
		}
		return;
	}
	else			//P is two node
	{
		if (P->getLeftChildPtr()->getItemNum() == 2)
		{
			TriNode<ItemType>* leftNode = P->getLeftChildPtr();
			TriNode<ItemType>* rightNode = P->getRightChildPtr();

			rightNode->setSmallItem(P->getSmallItem());
			P->deleteItem(P->getSmallItem());
			P->enterItem(leftNode->getLargeItem());
			leftNode->deleteItem(leftNode->getLargeItem());

			//change children
			rightNode->enterChildPtr(leftNode->getRightChildPtr());
			leftNode->setRightChildPtr(leftNode->getMidChildPtr());
			leftNode->setMidChildPtr(nullptr);
			return;
		}
		else if (P->getItemNum() == 2)
		{
			P->getRightChildPtr()->enterItem(P->getLargeItem());
			P->deleteItem(P->getLargeItem());
			return;
		}
		else  //merge
		{
			if (Node == P->getLeftChildPtr())
			{
				Node->enterItem(P->getSmallItem());						//move parent value into Node
				Node->enterItem(P->getRightChildPtr()->getSmallItem()); //move right sibling into Node
				P->getRightChildPtr()->deleteItem(P->getRightChildPtr()->getSmallItem()); //delete value of sibling
				P->deleteItem(P->getSmallItem()); //delete value of Parent
				Node->enterChildPtr(P->getRightChildPtr()->getRightChildPtr());
				Node->enterChildPtr(P->getRightChildPtr()->getLeftChildPtr());
				P->setRightChildPtr(nullptr);
				fixTree(P);
			}
			else //Node == P->getRightChildPtr()
			{
				P->getLeftChildPtr()->enterItem(P->getSmallItem());
				P->deleteItem(P->getSmallItem());
				fixTree(P);
			}
		}

	}
}

template <class ItemType>
TriNode<ItemType>* TwoThreeTree<ItemType>::SwapInorder(TriNode<ItemType>* Node, const ItemType& val)
{
	if (Node->isLeaf())
		return Node;

	if (Node->getSmallItem() == val)
	{
		if (Node->getMidChildPtr() != nullptr)
		{
			Node->deleteItem(val);
			Node->setLargeItem(Node->getMidChildPtr()->getSmallItem());
			Node->getMidChildPtr()->enterItem(val);
			return SwapInorder(Node->getMidChildPtr(), val);

		}
		else	//Node only has two children
		{
			Node->deleteItem(val);
			Node->setSmallItem(Node->getRightChildPtr()->getSmallItem());
			Node->getRightChildPtr()->enterItem(val);
			return SwapInorder(Node->getRightChildPtr(), val);
		}
	}
	else //Node large item has val
	{
		Node->deleteItem(val);
		Node->setLargeItem(Node->getRightChildPtr()->getSmallItem());
		Node->getRightChildPtr()->enterItem(val);
		return SwapInorder(Node->getRightChildPtr(), val);
	}
	return nullptr;
}

template <class ItemType>
bool TwoThreeTree<ItemType>::removeItem(const ItemType& item)
{
	TriNode<ItemType>* nodeToBeDeleted;
	nodeToBeDeleted = findNodeHelper(pRoot, item);
	if (!nodeToBeDeleted)
		return false;
	if (!nodeToBeDeleted->isLeaf())
	{
		nodeToBeDeleted = SwapInorder(nodeToBeDeleted, item);
	}
	nodeToBeDeleted->deleteItem(item);
	if (nodeToBeDeleted->getItemNum() == 0)
		fixTree(nodeToBeDeleted);
	
	return true;
}

template <class ItemType>
void TwoThreeTree<ItemType>::clear()
{
	while (isEmpty() == false)
	{
		removeItem(pRoot->getSmallItem());
	}
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