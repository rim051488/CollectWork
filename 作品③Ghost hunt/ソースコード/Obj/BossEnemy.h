#pragma once
#include "Enemy.h"
class BossEnemy :
    public Enemy
{
public:
    BossEnemy();
    BossEnemy(Vector2Dbl Pos);
    ~BossEnemy();
    bool Init(void) override;
    //void Draw(void) override;
    //void EnemyDraw(void) override;
    EnemyID GetEnemyID(void) { return EnemyID::Boss; };
    ObjID GetObjID(void) override { return ObjID::BossEnemy; };
    Vector2Dbl pos;
};

