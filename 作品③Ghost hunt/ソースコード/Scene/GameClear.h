#pragma once
#include <string>
#include "BaseScene.h"
class GameClear :
	public BaseScene
{
public:
    GameClear();
    GameClear(std::string filename,std::string map, std::string pos, int dethenemy,int time);
    ~GameClear();
private:
    bool Init(void) override;
    bool Init(std::string filename);
    uniqueScene Update(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;
    Scene GetSceneID(void) override { return Scene::GameClear; };
    // キーが連続して押されないようにディレイをかける
    double delay;
    double second;
    int dethEnemy;
    // マップの情報とそのマップに使っている画像を渡せるようにしておく
    std::string fileName_;
    std::string map_;
    // objの座標をファイルから読み取り
    std::string objPos_;
    // 選択している項目が点滅するようにする
    int Select_;
    double Blink_;
    int time_;
    // キーボードかパッドか
    int input_;
    // 音楽
    int SoundHandle;
    int soundHandle1;
};

