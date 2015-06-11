#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "RedBlackNode.h"

template <class ItemType>
class RedBlackTree
{
private:
	RedBlackNode<ItemType> pRoot = nullptr;
public:
	RedBlackTree();
	~RedBlackTree();
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
		else if (curNode->getVal() > pRoot)
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

}

template <class ItemType>
void RedBlackTree<ItemType>::clear()
{

}

#endif //REDBLACKTREE_H