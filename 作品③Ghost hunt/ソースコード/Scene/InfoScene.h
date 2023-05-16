#pragma once
#include "BaseScene.h"
class InfoScene :
    public BaseScene
{
public:
    InfoScene();
    InfoScene(uniqueScene beforScene);
    ~InfoScene();
private:
    bool Init(void) override;
    uniqueScene Update(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;
    Scene GetSceneID(void) override ;
    // 操作説明の切り替わり時間
    double info_;
    // 操作説明の種類
    int infoKinds_;
    // キーが連続して押されないようにディレイをかける
    double delay;
    double second;
    double delayTime_;
    uniqueScene beforScene_;
    // キーボードかパッドか
    int input_;
    // 音楽
    int SoundHandle;
    int soundHandle1;
};

