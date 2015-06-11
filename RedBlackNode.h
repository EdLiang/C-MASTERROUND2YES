#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H

enum Colour {red,black};

template <class ItemType>
class RedBlackNode
{
private:
	ItemType val;
	Colour leftColour, rightColour;
	RedBlackNode<ItemType> *leftNode, *rightNode;
public:
	RedBlackNode();
	~RedBlackNode();

	Colour getLeftColour() const { return leftColour; }
	Colour getRightColour() const { return rightColour; }
	void setLeftColour(Colour &col) { leftColour = col; }
	void setRightColour(Colour &col) { rightColour = col; }

	RedBlackNode<ItemType>* getLeftNode() const { return leftNode; }
	RedBlackNode<ItemType>* getRightNode() const { return rightNode; }
	void setLeftNode(RedBlackNode<ItemType>* newNode) { leftNode = newNode; }
	void setRightNode(RedBlackNode<ItemType>* newNode) { rightNode = newNode; }

	ItemType getVal() const{ return val; }
	void setVal(ItemType& newVal) { val = newVal; }
};

#endif //REDBLACKNODE_H

