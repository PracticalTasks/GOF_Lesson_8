
#include <iostream>

#include "Bomb.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

Bomb::Bomb(const Bomb& ref)
{
    this->speed = ref.speed;
    this->xDirction = ref.xDirction;
    this->yDirection = ref.yDirection;
    this->width = ref.width;
    this->x = ref.x;
    this->y = ref.y;
}

void Bomb::Draw() const
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
	ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "*";
}

Bomb* Bomb::clone()
{
    return new Bomb(*this);
}