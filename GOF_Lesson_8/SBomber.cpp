
#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"

using namespace std;
using namespace MyTools;

SBomber::SBomber()
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0),
    passedTime(0),
    fps(0),
    bombsNumber(10),
    score(0),
    stateTime(0)
{
	FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    std::shared_ptr<Plane> p(new Plane);
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    shared_ptr<LevelGUI> pGUI(new LevelGUI);
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    shared_ptr<Ground> pGr(new Ground);
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.push_back(pGr);

    std::shared_ptr<Tree> pTree(new Tree);
    pTree->SetWidth(5);
    pTree->SetPos(12, groundY - 7);
    vecStaticObj.push_back(pTree);

    shared_ptr<Tank> pTank(new Tank);
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    vecStaticObj.push_back(pTank);

    //make_unique(new Tank);
    pTank = make_unique<Tank>();
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    vecStaticObj.push_back(pTank);

    shared_ptr<House> pHouse(new House);
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

void SBomber::MoveObjects()
{
	FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Move(deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
	FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
    {
        exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround() 
{
    vector<shared_ptr<Bomb>> vecBombs = FindAllBombs();
    shared_ptr<Ground> pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            DeleteDynamicObj(vecBombs[i]);
        }
    }

}

void SBomber::CheckDestoyableObjects(shared_ptr<Bomb> pBomb)
{
    vector<shared_ptr<DestroyableGroundObject>> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

void SBomber::DeleteDynamicObj(std::shared_ptr<DynamicObject> pObj)
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecDynamicObj.erase(it);
            break;
        }
    }
}

void SBomber::DeleteStaticObj(shared_ptr<GameObject> pObj)
{
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecStaticObj.erase(it);
            break;
        }
    }
}

vector<shared_ptr<DestroyableGroundObject>> SBomber::FindDestoyableGroundObjects() const
{
    vector<shared_ptr<DestroyableGroundObject>> vec;
    shared_ptr<Tank> pTank;
    shared_ptr<House> pHouse;
    shared_ptr<Tree> pTree;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_pointer_cast<Tank>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_pointer_cast<House>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }

        pTree = dynamic_pointer_cast<Tree>(vecStaticObj[i]);
        if (pTree != nullptr)
        {
            vec.push_back(pTree);
            continue;
        }
    }

    return vec;
}

shared_ptr<Ground> SBomber::FindGround() const
{
    shared_ptr<Ground> pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_pointer_cast<Ground>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

vector<shared_ptr<Bomb>> SBomber::FindAllBombs() const
{
    vector<shared_ptr<Bomb>> vecBombs;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        std::shared_ptr<Bomb> pBomb = std::dynamic_pointer_cast<Bomb>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

shared_ptr<Plane> SBomber::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        shared_ptr<Plane> p = dynamic_pointer_cast<Plane>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

shared_ptr<LevelGUI> SBomber::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        shared_ptr<LevelGUI> p = dynamic_pointer_cast<LevelGUI>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

	FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        exitFlag = true;
        break;

    case 72: // up
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        DropBomb();
        break;

    case 'B':
        DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
	FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            vecStaticObj[i]->Draw();
        }
    }

	ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart()
{
	FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;
    stateTime += deltaTime;
    if ((stateTime / 1000) > 3)
    {
        for (size_t i = 0; i < vecStaticObj.size(); i++)
        {
            shared_ptr<Tree> pTree = dynamic_pointer_cast<Tree>(vecStaticObj[i]);
            if (pTree != nullptr)
            {
                pTree->SetState(pTree.get());

            }
        }
        stateTime = 0;
    }

	FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::DropBomb()
{
    if (bombsNumber > 0)
    {
		FileLoggerSingleton::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

        shared_ptr<Plane> pPlane = FindPlane();
        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        shared_ptr<Bomb> pBomb(new Bomb);
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        shared_ptr<Bomb> pBombClone(pBomb->clone());
        pBombClone->SetPos(x + 2, y);
        
        vecDynamicObj.push_back(pBombClone);
        bombsNumber--;
        score -= Bomb::BombCost;

        vecDynamicObj.push_back(pBomb);
        bombsNumber--;
        score -= Bomb::BombCost;
    }
}
