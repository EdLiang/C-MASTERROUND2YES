//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 19-1.

/** A class of nodes for a link-based 2-3 tree.
 @file TriNode.h */
 
#ifndef _TRI_NODE
#define _TRI_NODE


template<class ItemType>
class TriNode
{
private:
	ItemType smallItem, mediumItem, largeItem;    // Data portion center operates as a temporary value
	TriNode<ItemType>* leftChildPtr = nullptr;  // Left-child pointer
	TriNode<ItemType>* midChildPtr = nullptr;   // Middle-child pointer
	TriNode<ItemType>* rightMidChildPtr = nullptr; //Right of the Middle Child but left of the Right child Pointer
	TriNode<ItemType>* rightChildPtr = nullptr; // Right-child pointer

	TriNode<ItemType>* parentPtr;
	char ItemNum = 0;
public:
	TriNode() :ItemNum(0), leftChildPtr(nullptr), midChildPtr(nullptr), rightMidChildPtr(nullptr), rightChildPtr(nullptr), parentPtr(nullptr)
	{};
	TriNode(const ItemType& anItem, TriNode<ItemType>* parent)
		:smallItem(anItem),leftChildPtr(nullptr), midChildPtr(nullptr), rightMidChildPtr(nullptr), rightChildPtr(nullptr), parentPtr(parent), ItemNum(1) {};

	bool isThreeNode() const { return (leftChildPtr && midChildPtr && rightChildPtr); }
	bool isTwoNode() const { return ((leftChildPtr && rightChildPtr) && (!midChildPtr)); }
	bool isOneNode() const { return (!leftChildPtr != !rightChildPtr); }	//eclusive or
	bool isLeaf() const { return !(leftChildPtr || midChildPtr || rightChildPtr); }

	ItemType getSmallItem() const { return smallItem; }
	ItemType getLargeItem() const { return largeItem; }
	ItemType getMediumItem() const { return mediumItem; }


	void deleteItem(const ItemType& anItem)
	{
		if (anItem == smallItem)
		{
			smallItem = largeItem;
			--ItemNum;
		}
		else if (anItem == largeItem)
		{
			--ItemNum;
		}
		ItemNum = (ItemNum < 0) ? 0 : ItemNum;
	}
	void enterItem(const ItemType& anItem)
	{
		if (ItemNum == 1)
		{
			if (smallItem > anItem)
			{
				largeItem = smallItem;
				smallItem = anItem;
			}
			else
				largeItem = anItem;
		}
		else if (ItemNum == 2)
		{
			if (smallItem < anItem)
			{
				if (largeItem > anItem)
					mediumItem = anItem;
				else
				{
					mediumItem = largeItem;
					largeItem = anItem;
				}
			}
			else
			{
				mediumItem = smallItem;
				smallItem = anItem;
			}
		}
		else
			smallItem = anItem;


		++ItemNum;
	}

	char getItemNum() const { return ItemNum; }

	void setSmallItem(const ItemType& anItem) { 
		smallItem = anItem;
		ItemNum = (ItemNum > 1) ? ItemNum : 1;
	}
	void setLargeItem(const ItemType& anItem) { 
		largeItem = anItem; 
		ItemNum = (ItemNum > 2) ? ItemNum : 2;
	}

	void setMediumItem(const ItemType& anItem){
		mediumItem = anItem;
		ItemNum = (ItemNum > 3) ? ItemNum : 3;
	}

	void enterChildPtr(TriNode<ItemType>* newPtr) {
		if (newPtr == nullptr)
			return;

		newPtr->setParentPtr(this);
		if (isThreeNode())
		{
			if (newPtr->getSmallItem() > leftChildPtr->getSmallItem())
			{
				if (newPtr->getSmallItem() > rightChildPtr->getSmallItem())
				{
					rightMidChildPtr = rightChildPtr;
					rightChildPtr = newPtr;
				}
				else if (newPtr->getSmallItem() > midChildPtr->getSmallItem())
					rightChildPtr = newPtr;
				else
				{
					rightMidChildPtr = midChildPtr;
					midChildPtr = newPtr;
				}
			}
			else
			{
				rightMidChildPtr = midChildPtr;
				midChildPtr = leftChildPtr;
				leftChildPtr = newPtr;
			}
		}
		if (isTwoNode())
		{
			if (newPtr->getSmallItem() > leftChildPtr->getSmallItem())
			{
				if (newPtr->getSmallItem() < rightChildPtr->getSmallItem())
					midChildPtr = newPtr;
				else
				{
					midChildPtr = rightChildPtr;
					rightChildPtr = newPtr;
				}
			}
			else
			{
				midChildPtr = leftChildPtr;
				leftChildPtr = newPtr;
			}
		}
		else if (isOneNode())
		{
			if (newPtr->getSmallItem() > smallItem)
				rightChildPtr = newPtr;
			else
			{
				rightChildPtr = leftChildPtr;
				leftChildPtr = newPtr;
			}
		}
		else
		{
			(newPtr->getSmallItem() > smallItem) ? rightChildPtr : leftChildPtr = newPtr;
		}
	}

	void deleteChildPtr(TriNode<ItemType>* Node) {
		if (leftChildPtr == Node)
			leftChildPtr = nullptr;
		else if (midChildPtr == Node)
			midChildPtr = nullptr;
		else if (rightMidChildPtr == Node)
			rightMidChildPtr = nullptr;
		else if (rightChildPtr == Node)
			rightChildPtr = nullptr;
	}

	TriNode<ItemType>* getLeftChildPtr() const {return leftChildPtr; }
	TriNode<ItemType>* getMidChildPtr() const { return midChildPtr; }
	TriNode<ItemType>* getRightMidChildPtr() const { return rightMidChildPtr; }
	TriNode<ItemType>* getRightChildPtr() const { return rightChildPtr;	}
	TriNode<ItemType>* getParentPtr() const { return parentPtr; }
   
   void setLeftChildPtr(TriNode<ItemType>* leftPtr) { leftChildPtr = leftPtr; }
   void setMidChildPtr(TriNode<ItemType>* midPtr) { midChildPtr = midPtr; }
   void setRightMidChildPtr(TriNode<ItemType>* rightMidPtr) { rightMidChildPtr = rightMidPtr; }
   void setRightChildPtr(TriNode<ItemType>* rightPtr) { rightChildPtr = rightPtr; }
   void setParentPtr(TriNode<ItemType>* parent) { parentPtr = parent; }
}; // end TriNode

#endif