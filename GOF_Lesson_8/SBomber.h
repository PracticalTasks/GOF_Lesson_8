#pragma once

#include<vector>
#include<memory>

#include"LevelGUI.h"
#include"Plane.h"
#include"Bomb.h"
#include"Ground.h"
#include"Tank.h"
#include"Tree.h"

class SBomber
{
public:
    SBomber();
    ~SBomber();
    
    bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:
    std::vector<std::shared_ptr<DynamicObject>> vecDynamicObj;
    std::vector<std::shared_ptr<GameObject>> vecStaticObj;

    bool exitFlag;

    uint64_t startTime;
    uint64_t finishTime;
    uint64_t passedTime;
    uint16_t bombsNumber;
    uint16_t deltaTime;
    uint16_t fps;
    int16_t score;

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void CheckDestoyableObjects(std::shared_ptr<Bomb> pBomb);

    void DeleteDynamicObj(std::shared_ptr<DynamicObject> pBomb);
    void DeleteStaticObj(std::shared_ptr<GameObject> pObj);

    std::shared_ptr<Ground> FindGround() const;
    std::shared_ptr<Plane> FindPlane() const;
    std::shared_ptr<LevelGUI> FindLevelGUI() const;
    std::vector<std::shared_ptr<DestroyableGroundObject>> FindDestoyableGroundObjects() const;
    std::vector<std::shared_ptr<Bomb>> FindAllBombs() const;

    void DropBomb();
};