#pragma once
#include "../Scene/BaseScene.h"
class MenuScene:
	public BaseScene
{
public:
	MenuScene();
	MenuScene(uniqueScene beforScene,int dethEnemy);
	~MenuScene();
private:
	bool Init(void) override;
	uniqueScene Update(double delta, uniqueScene ownScene) override;
	void DrawOwnScreen(double delta) override;
	virtual Scene GetSceneID(void) override;
	int dethEnemy_;
	// キーが連続して押されないようにディレイをかける
	double delay;
	double second;
	// 選択している項目が点滅するようにする
	int Select_;
	double Blink_;
	uniqueScene beforScene_;
	// キーボードかパッドか
	int input_;
	// 音楽
	int SoundHandle;
	int soundHandle1;
};

