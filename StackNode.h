#ifndef STACKNODE_H
#define STACKNODE_H

template <class ItemType>
class StackNode
{
private:
	StackNode* Next = nullptr;
	ItemType Item;
public:
	StackNode() {};
	StackNode(StackNode* pNextNode) :Next(pNextNode) {};
	StackNode(ItemType& NodeItem) :Item(NodeItem) {};
	StackNode(StackNode* pNextNode, ItemType& NodeItem) :Next(pNextNode), Item(NodeItem) {};
	virtual ~StackNode() 
	{
		if (this->Next != nullptr)
		{
			delete Next;
		}
	}

	//-----------get + set
	inline StackNode* GetNext() const{ return Next; }
	inline ItemType GetItem() const{ return Item; }

	inline void SetNext(StackNode* NewNext) { Next = NewNext; }
	inline void SetItem(const ItemType& NewItem) { Item = NewItem; }
};

#endif

