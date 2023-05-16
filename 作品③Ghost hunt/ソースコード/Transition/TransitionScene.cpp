#include "TransitionScene.h"

TransitionScene::TransitionScene(uniqueScene beforScene, uniqueScene afterScene)
{
	beforScene_ = std::move(beforScene);
	afterScene_ = std::move(afterScene);
	Init();
}

TransitionScene::~TransitionScene()
{
}

bool TransitionScene::Init(void)
{
	Alive_ = true;
	count_ = 0;
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	beforScene_->Draw(0);
	return true;
}

uniqueScene TransitionScene::Update(double delta, uniqueScene ownScene)
{
	if (UpdateTransition(delta))
	{
		return std::move(afterScene_);
	}
	DrawOwnScreen(delta);
	return ownScene;
}
