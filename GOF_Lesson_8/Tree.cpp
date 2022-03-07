#include"Tree.h"

//Class Tree
Tree::Tree()
{
	treeState = std::dynamic_pointer_cast<TreeState>(std::make_shared<SmallTree>());
}
void Tree::Move(uint16_t time)
{
	treeState = treeState->Grow(time);
}

void Tree::Draw() const
{
	treeState->Draw();
}

//Class SmallTree
std::shared_ptr<TreeState> SmallTree::Grow(uint16_t time)
{
	return (std::make_shared<MiddleTree>());
}

void SmallTree::Draw() const
{
	std::cout << "SmallTree";
}

//class MiddleTree
std::shared_ptr<TreeState> MiddleTree::Grow(uint16_t time)
{
	return (std::make_shared<BigTree>());
}

void MiddleTree::Draw() const
{

}

//class BigTree
std::shared_ptr<TreeState> BigTree::Grow(uint16_t time)
{
	return (std::make_shared<BigTree>());
}

void BigTree::Draw() const
{

}