#pragma once
#include <string>
#include "../../Tmx/TmxObj.h"
#include "BaseScene.h"
class SelectScene :
	public BaseScene
{
public:
    SelectScene();
    ~SelectScene();
private:
    bool Init(void) override;
    uniqueScene Update(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;
    Scene GetSceneID(void) override { return Scene::Select; };
    std::string fileName_;
    // キーが連続して押されないようにディレイをかける
    double delay;
    double second;
    TmxObj tmxObj_;
    // マップの情報を背景に描画するかどうか
    bool mapDraw_;
    // マップを表示するまでのフェードイン
    double count_;
    int timelimit;

    // 選択している項目が点滅するようにする
    int Select_;
    double Blink_;
    int input_;
    // 音楽
    int SoundHandle;
    int soundHandle1;
    Vector2Dbl screensize;
};

