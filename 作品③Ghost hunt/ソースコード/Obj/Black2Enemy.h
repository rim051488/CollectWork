#pragma once
#include "Enemy.h"
class Black2Enemy :
    public Enemy
{
public:
    Black2Enemy();
    Black2Enemy(Vector2Dbl Pos);
    ~Black2Enemy();
    bool Init(void) override;
    //void Draw(void) override;
    //void EnemyDraw(void) override;
    EnemyID GetEnemyID(void) { return EnemyID::Black; };
    ObjID GetObjID(void) override { return ObjID::Black2Enemy; };
    Vector2Dbl pos;
};

