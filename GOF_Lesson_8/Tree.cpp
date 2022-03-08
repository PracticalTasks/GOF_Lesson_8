#include"Tree.h"

//Class Tree
Tree::Tree()
{
	treeState = new SmallTree(this);
}

Tree::~Tree()
{
	delete treeState;
}
void Tree::SetState(Tree* ptr)
{
	treeState = treeState->Grow(ptr);
}

void Tree::Draw() const
{
	treeState->Draw();
}

bool Tree::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

//Class SmallTree
TreeState *SmallTree::Grow(Tree* ptr)
{
	pTree = ptr;
	return (new MiddleTree(ptr));
}

void SmallTree::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(MyTools::CC_LightGreen);
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 4);
	std::cout << "  ^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 5);
	std::cout << " ^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 6);
	std::cout << "^^^^^";
}

//class MiddleTree
TreeState *MiddleTree::Grow(Tree* ptr)
{
	pTree = ptr;
	return (new BigTree(ptr));
}

void MiddleTree::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(MyTools::CC_LightGreen);
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 2);
	std::cout << "    ^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 3);
	std::cout << "   ^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 4);
	std::cout << "  ^^^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 5);
	std::cout << " ^^^^^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 6);
	std::cout << "^^^^^^^^^";
}

//class BigTree
TreeState *BigTree::Grow(Tree* ptr)
{
	pTree = ptr;
	return (new BigTree(ptr));
}

void BigTree::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(MyTools::CC_LightGreen);
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY());
	std::cout << "      ^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 1);
	std::cout << "     ^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 2);
	std::cout << "    ^^^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 3);
	std::cout << "   ^^^^^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 4);
	std::cout << "  ^^^^^^^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 5);
	std::cout << " ^^^^^^^^^^^";
	MyTools::ScreenSingleton::getInstance().GotoXY(pTree->GetX(), pTree->GetY() + 6);
	std::cout << "^^^^^^^^^^^^^";
}