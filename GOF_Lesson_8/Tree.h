#pragma once
#include"DestroyableGroundObject.h"
#include<memory>
#include<iostream>
#include"MyTools.h"

class TreeState;
class SmallTree;

class Tree : public DestroyableGroundObject
{
	TreeState* treeState;
public:
	Tree();
	~Tree();
	bool isInside(double x1, double x2) const override;
	uint16_t GetScore() const override { return score; }
	void SetState(Tree* ptr);
	void Draw() const override;
private:
	const uint16_t score = 10;
};

class TreeState
{
public:
	virtual ~TreeState() {}
	virtual TreeState *Grow(Tree* ptr) = 0;
	virtual void Draw() const = 0;

};

//SmallTree, MiddleTree, BigTree
class SmallTree : public TreeState
{
	Tree* pTree;
public:
	SmallTree(Tree* ptr): pTree(ptr) {}
	TreeState *Grow(Tree* ptr) override;
	void Draw() const override;

};

class MiddleTree : public TreeState
{
	Tree* pTree;
public:
	MiddleTree(Tree* ptr) : pTree(ptr) {}
	TreeState *Grow(Tree* ptr) override;
	void Draw() const override;

};

class BigTree : public TreeState
{
	Tree* pTree;
public:
	BigTree(Tree* ptr) : pTree(ptr) {}
	TreeState *Grow(Tree* ptr) override;
	void Draw() const override;

};