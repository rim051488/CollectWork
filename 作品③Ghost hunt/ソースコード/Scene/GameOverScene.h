#pragma once
#include <string>
#include "BaseScene.h"
class GameOverScene :
	public BaseScene
{
public:
    GameOverScene();
    GameOverScene(std::string filename, std::string map, std::string pos);
    ~GameOverScene();
private:
    bool Init(void) override;
    bool Init(std::string filename);
    uniqueScene Update(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;
    Scene GetSceneID(void) override { return Scene::GameOver; };
    // キーが連続して押されないようにディレイをかける
    double delay;
    double second;
    // 現在のステージ情報を受け取る
    std::string fileName_;
    std::string map_;
    // objの座標をファイルから読み取り
    std::string objPos_;
    // 選択している項目が点滅するようにする
    int Select_;
    double Blink_;
    // キーボードかパッドか
    int input_;
    // 音楽
    int SoundHandle;
    int soundHandle1;
};

