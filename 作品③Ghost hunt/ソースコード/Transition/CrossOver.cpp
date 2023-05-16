#include <DxLib.h>
#include "CrossOver.h"

CrossOver::CrossOver(double TimeLimit, uniqueScene beforScene, uniqueScene afterScene):
	TransitionScene(std::move(beforScene),std::move(afterScene))
{
	TimeLimit_ = TimeLimit;
}

CrossOver::~CrossOver()
{
}

bool CrossOver::UpdateTransition(double delta)
{
	count_ += delta *2;
	if (count_ > TimeLimit_)
	{
		return true;
	}
	return false;
}

void CrossOver::DrawOwnScreen(double delta)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	auto Alpha = static_cast<int>(255 * count_ / TimeLimit_);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - Alpha);
	beforScene_->Draw(delta);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	afterScene_->Draw(delta);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
}
