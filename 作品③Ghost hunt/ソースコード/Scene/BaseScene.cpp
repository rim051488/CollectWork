#include "BaseScene.h"

BaseScene::BaseScene()
{
	SetDrawScreen(DX_SCREEN_BACK);
	GetDrawScreenSize(&screenSize_.x_, &screenSize_.y_);
	screenID_ = MakeScreen(screenSize_.x_, screenSize_.y_, true);
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw(double delta)
{
	DrawGraph(0, 0, screenID_, true);
}

bool BaseScene::IsAlive(void)
{
	return Alive_;
}
