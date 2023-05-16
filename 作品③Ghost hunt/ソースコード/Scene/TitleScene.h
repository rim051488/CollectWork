#pragma once
#include "BaseScene.h"
#include "../Obj/Obj.h"
#include "../Input/Input.h"


class TitleScene :
	public BaseScene
{
public:
    TitleScene();
    ~TitleScene();
private:
    bool Init(void) override;
    uniqueScene Update(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;
    Scene GetSceneID(void) override { return Scene::Title; };
    // 画面が変わろうとすると
    // 選択されたら色が変わるようにする
    bool Flag_;
    int color_;
    double speed_;
    double speed_X;
    double speed_Y;
    // 現れるか消えるか
    bool appFlag_;
    // 現れる
    bool apptitle_;
    double titletime_;
    // キーが連続して押されないようにディレイをかける
    double delay;
    double second;
    double delayTime_;
    // 選択している項目が点滅するようにする
    int Select_;
    double Blink_;
    int GraphH;
    // キーボードかPADか
    //CntType cntType_;
    //std::unique_ptr<Input> controller_;
    int input_;
    // 音楽
    int SoundHandle;
    int soundHandle1;
};

