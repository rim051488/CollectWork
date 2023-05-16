#pragma once
#include "TransitionScene.h"
#define NUM (3)
class CurtainUp :
    public TransitionScene
{
public:
    CurtainUp(double TimeLimit, uniqueScene beforScene, uniqueScene afterScene,Vector2Dbl pos, double delta);
    ~CurtainUp();
private:
    double TimeLimit_;
    bool UpdateTransition(double delta);
    void DrawOwnScreen(double delta) override;

    bool Init(void);
    TranID GetTranID(void) { return TranID::CutainUp; };
    Vector2Dbl ScreenSize;

    int beforScreen;
    int Screen[NUM];
    int count_;									// アルファ値のカウント
    double delta_;

};

