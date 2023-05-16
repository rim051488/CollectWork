#pragma once
#include "Scene/BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	// 静的なシングルトン
	static SceneMng& GetInstance()
	{
		static SceneMng s_Instance;
		return s_Instance;
	}

	void Run(void);			// 実行処理
private:
	bool SysInit(void);		// 初期化処理
	void Update(void);
	void Draw(double delta);
	bool InitFlag_;
	uniqueScene scene_;
	SceneMng();
	~SceneMng();
	bool SceneAlive_;		// 終了ボタンが押されたかどうか

};

