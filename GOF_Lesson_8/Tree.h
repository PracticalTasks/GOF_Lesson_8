#pragma once
#include"DynamicObject.h"
#include<memory>
#include<iostream>
#include"MyTools.h"

class TreeState;
class SmallTree;

class Tree : public DynamicObject
{
	std::shared_ptr<TreeState> treeState;
public:
	Tree();
	void Move(uint16_t time)override;
	void Draw() const override;
	DynamicObject* clone()override { return nullptr; }

};

class TreeState
{
public:
	virtual std::shared_ptr<TreeState> Grow(uint16_t time) = 0;
	virtual void Draw() const = 0;

};

//SmallTree, MiddleTree, BigTree
class SmallTree : public TreeState
{
public:
	std::shared_ptr<TreeState> Grow(uint16_t time) override;
	void Draw() const override;

};

class MiddleTree : public TreeState
{
public:
	std::shared_ptr<TreeState> Grow(uint16_t time) override;
	void Draw() const override;

};

class BigTree : public TreeState
{
public:
	std::shared_ptr<TreeState> Grow(uint16_t time) override;
	void Draw() const override;

};