#include "CurtainOpen.h"

CurtainOpen::CurtainOpen(double TimeLimit, uniqueScene beforScene, uniqueScene afterScene, Vector2Dbl pos, double delta):
    TransitionScene(std::move(beforScene), std::move(afterScene))
{
    count_ = 0;
    ScreenSize = pos;
    delta_ = delta;
    Init();
}

CurtainOpen::~CurtainOpen()
{
}

bool CurtainOpen::UpdateTransition(double delta)
{
    DrawOwnScreen(0);
    count_ += delta_ * 1500;
    return (0 >= ScreenSize.x_  - count_);
}

void CurtainOpen::DrawOwnScreen(double delta)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	afterScene_->Draw(0);
	DrawGraph(-count_, 0, Screen[0], true);
	DrawGraph(ScreenSize.x_ / 2 + count_, 0, Screen[1], true);
}

bool CurtainOpen::Init(void)
{
	beforScreen = MakeScreen(ScreenSize.x_, ScreenSize.y_, 255);
	SetDrawScreen(beforScreen);
	ClsDrawScreen();
	beforScene_->Draw(0);
	for (int a = 0; a < NUM2; a++)
	{
		Screen[a] = MakeScreen(ScreenSize.x_ / 2, ScreenSize.y_, 255);
		SetDrawScreen(Screen[a]);
		ClsDrawScreen();
		if (a == 0)
		{
			DrawGraph(0, 0, beforScreen, true);
		}
		else if (a == 1)
		{
			DrawGraph(-(ScreenSize.x_ / 2), 0, beforScreen, true);
		}
	}
	return true;
}
