#pragma once
#include <memory>
#include "../Common/Vector2.h"
class BaseScene;
using uniqueScene = std::unique_ptr<BaseScene>;

// シーンの種別
enum class Scene
{
	Title /*タイトルシーン*/,
	Select/*セレクトシーン*/,
	Game/*ゲームシーン*/,
	GameClear/*ゲームクリア*/,
	GameOver/*ゲームオーバー*/,
	Transition/*トランジションシーン*/,
	Info,/*操作説明*/
	Max	
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual bool Init(void) = 0;
	virtual uniqueScene Update(double delta,uniqueScene ownScene) = 0;
	virtual void Draw(double delta);
	virtual void DrawOwnScreen(double delta) = 0;
	virtual Scene GetSceneID(void) = 0;
	// シーンの中でゲームを終了するを押されたら
	virtual bool IsAlive(void);
private:
protected:
	int screenID_;				// 現在のシーンのidを取得
	Vector2 screenSize_;		// スクリーンのサイズ
	bool Alive_;				// 終了するを選んだかどうか
};

