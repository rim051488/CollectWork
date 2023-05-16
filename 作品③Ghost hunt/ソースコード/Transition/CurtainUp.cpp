#include "CurtainUp.h"

CurtainUp::CurtainUp(double TimeLimit, uniqueScene beforScene, uniqueScene afterScene, Vector2Dbl pos, double delta) :
	TransitionScene(std::move(beforScene), std::move(afterScene))
{
	count_ = 0;
	ScreenSize = pos;
	delta_ = delta;
	Init();
}

CurtainUp::~CurtainUp()
{
}

bool CurtainUp::UpdateTransition(double delta)
{
	DrawOwnScreen(0);
	count_ += delta_ * 1500;
	return (0 >= ScreenSize.y_ + ScreenSize.y_ * 2 / 3 - count_);
}

void CurtainUp::DrawOwnScreen(double delta)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	afterScene_->Draw(0);
	DrawGraph(0, -count_, Screen[0], true);
	if (count_ > ScreenSize.y_ / 3)
	{
		DrawGraph(ScreenSize.x_ / 3, ScreenSize.y_ / 3 - count_, Screen[1], true);
	}
	else
	{
		DrawGraph(ScreenSize.x_ / 3, 0, Screen[1], true);
	}
	if (count_ > ScreenSize.y_ / 3 * 2)
	{
		DrawGraph(ScreenSize.x_ / 3 * 2, ScreenSize.y_ / 3 * 2 - count_, Screen[2], true);
	}
	else
	{
		DrawGraph(ScreenSize.x_ / 3 * 2, 0, Screen[2], true);
	}
}

bool CurtainUp::Init(void)
{
	beforScreen = MakeScreen(ScreenSize.x_, ScreenSize.y_, 255);
	SetDrawScreen(beforScreen);
	ClsDrawScreen();
	beforScene_->Draw(0);
	for (int a = 0; a < NUM; a++)
	{
		Screen[a] = MakeScreen(ScreenSize.x_ / 3, ScreenSize.y_, 255);
		SetDrawScreen(Screen[a]);
		ClsDrawScreen();
		if (a == 0)
		{
			DrawGraph(0, 0, beforScreen, true);
		}
		else if (a == 1)
		{
			DrawGraph(-(ScreenSize.x_ / 3), 0, beforScreen, true);
		}
		else
		{
			DrawGraph(-(ScreenSize.x_ / 3 * 2), 0, beforScreen, true);
		}
	}
	return true;
}
