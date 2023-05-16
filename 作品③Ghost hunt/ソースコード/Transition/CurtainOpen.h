#pragma once
#include "TransitionScene.h"
#define NUM2 (2)
class CurtainOpen :
    public TransitionScene
{
public:
    CurtainOpen(double TimeLimit, uniqueScene beforScene, uniqueScene afterScene, Vector2Dbl pos, double delta);
    ~CurtainOpen();
private:
    bool UpdateTransition(double delta);
    void DrawOwnScreen(double delta) override;

    bool Init(void);
    TranID GetTranID(void) { return TranID::CutainUp; };
    Vector2Dbl ScreenSize;
    double TimeLimit_;
    int beforScreen;
    int Screen[NUM2];
    int count_;									// アルファ値のカウント
    double delta_;
};

