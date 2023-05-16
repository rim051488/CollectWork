#pragma once
#include "Enemy.h"
class BlackEnemy :
    public Enemy
{
public:
    BlackEnemy();
    BlackEnemy(Vector2Dbl Pos);
    ~BlackEnemy();
    bool Init(void) override;
    //void Draw(void) override;
    //void EnemyDraw(void) override;
    EnemyID GetEnemyID(void) { return EnemyID::Black; };
    ObjID GetObjID(void) override { return ObjID::BlackEnemy; };
    Vector2Dbl pos;
};

