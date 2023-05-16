#pragma once
#include "Enemy.h"
class RedEnemy :
    public Enemy
{
public:
    RedEnemy();
    RedEnemy(Vector2Dbl Pos);
    ~RedEnemy();
    bool Init(void) override;
    //void Draw(void) override;
    //void EnemyDraw(void) override;
    EnemyID GetEnemyID(void) { return EnemyID::Red; };
    ObjID GetObjID(void) override { return ObjID::RedEnemy; };
    Vector2Dbl pos;
};

