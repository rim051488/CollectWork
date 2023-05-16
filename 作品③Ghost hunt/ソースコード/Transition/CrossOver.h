#pragma once
#include "TransitionScene.h"
class CrossOver :
    public TransitionScene
{
public:
    CrossOver(double TimeLimit, uniqueScene beforScene, uniqueScene afterScene);
    ~CrossOver();
private:
    double TimeLimit_;
    TranID GetTranID(void) { return TranID::Cross; };
    bool UpdateTransition(double delta);
    void DrawOwnScreen(double delta) override;
};

