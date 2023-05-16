#include "GameClear.h"
#include "../Common/ImageMng.h"
#include "../Scene/SelectScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Transition/CrossOver.h"
#include "../Common/FontMng.h"

const static int Game_Y = 525;
const static int Select_Y = 575;
const static int Title_Y = 625;

typedef enum {
	eScene_Game,
	eScene_Select,

	eScene_Title,
	eScene_Num,
} eScene;

static int NowSelect = eScene_Game;

GameClear::GameClear()
{
	Init();
	DrawOwnScreen(0.0);
}

GameClear::GameClear(std::string filename, std::string map, std::string pos,int dethenemy, int time)
{
	if (GetJoypadNum())
	{
		//controller_ = std::make_unique<Pad>(1);
		input_ = 1;
	}
	else
	{
		//controller_ = std::make_unique<Keyboard>();
		input_ = 0;
	}
	map_ = map;
	objPos_ = pos;
	dethEnemy = dethenemy;
	time_ = time;
	Init(filename);
	DrawOwnScreen(0.0);
}

GameClear::~GameClear()
{
	DeleteSoundMem(SoundHandle);
	DeleteSoundMem(soundHandle1);
}

bool GameClear::Init(void)
{
	delay = 0.25;
	second = 0.25;
	return true;
}

bool GameClear::Init(std::string filename)
{
	Alive_ = true;
	Blink_ = 0.0;
	fileName_ = filename;
	delay = 0.25;
	second = 0.25;
	NowSelect = eScene_Game;
	SoundHandle = LoadSoundMem("bgm/select10.mp3");
	soundHandle1 = LoadSoundMem("bgm/se_maoudamashii_system37.mp3");
	return true;
}

uniqueScene GameClear::Update(double delta, uniqueScene ownScene)
{
	if ((CheckHitKey(KEY_INPUT_DOWN) && delay <= second && input_ == 0) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) && delay <= second && input_ == 1)) // 下キーが押されていたら
	{
		//PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
		ChangeNextPlayVolumeSoundMem(128, SoundHandle);
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
		NowSelect = (NowSelect + 1) % eScene_Num;
		second = 0.0;
		Blink_ = 0.0;
	}
	if ((CheckHitKey(KEY_INPUT_UP) && delay <= second && input_ == 0) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) && delay <= second && input_ == 1)) // 上キーが押されていたら
	{
		//PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
		ChangeNextPlayVolumeSoundMem(128, SoundHandle);
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
		NowSelect = (NowSelect + (eScene_Num - 1)) % eScene_Num;
		second = 0.0;
		Blink_ = 0.0;
	}

	second += delta;

	if ((CheckHitKey(KEY_INPUT_SPACE) && input_ == 0) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) && input_ == 1))
	{
		//PlaySound("bgm/se_maoudamashii_system37.mp3", DX_PLAYTYPE_BACK);
		ChangeNextPlayVolumeSoundMem(128, soundHandle1);
		PlaySoundMem(soundHandle1, DX_PLAYTYPE_BACK);
		switch (NowSelect)
		{
		case eScene_Game:
			return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>(fileName_,map_,objPos_));
			break;
		case eScene_Select:
			return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<SelectScene>());
			break;
		case eScene_Title:
			return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<TitleScene>());
			break;
		default:
			break;
		}
	}

	DrawOwnScreen(delta);
	return ownScene;
}

void GameClear::DrawOwnScreen(double delta)
{
	int y = 0;
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/Icon/TitleBack.png")[0], true);
	DrawGraph(130, 200, lpImageMng.GetID("image/Icon/Clear.png")[0], true);
	Blink_ += delta * 2;
	if (Blink_ <= 2)
	{
		DrawGraph(380, Game_Y, lpImageMng.GetID("image/Icon/replay.png")[0], true);
		DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
		DrawGraph(380, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
	}
	else
	{
		if (Select_ == 0)
		{
			if ((static_cast<int>(Blink_) % 2) == 0)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(380, Game_Y, lpImageMng.GetID("image/Icon/replay.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(380, Game_Y, lpImageMng.GetID("image/Icon/replay.png")[0], true);
			}
			DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
			DrawGraph(380, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 1)
		{
			DrawGraph(380, Game_Y, lpImageMng.GetID("image/Icon/replay.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 0)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
			}
			DrawGraph(380, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 2)
		{
			DrawGraph(380, Game_Y, lpImageMng.GetID("image/Icon/replay.png")[0], true);
			DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 0)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(380, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(380, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
			}
		}
	}
	SetFontSize(40);
	DrawFormatString(screenSize_.x_ / 3 + 25, 300, 0xffff00, "残り時間：%d秒", time_);
	if (time_ >= 20 && dethEnemy >= 8)
	{
		DrawGraph(screenSize_.x_ / 2 - 25, 350, lpImageMng.GetID("image/Icon/A.png")[0], true);
	}
	else if (time_ >= 20)
	{
		DrawGraph(screenSize_.x_ / 2 - 20, 350, lpImageMng.GetID("image/Icon/B.png")[0], true);
	}
	else if (time_ >= 10)
	{
		//DrawString(screenSize_.x_ /2, 400, "D", 0xffffff);
		DrawGraph(screenSize_.x_ / 2 - 20, 350, lpImageMng.GetID("image/Icon/C.png")[0], true);
	}
	else
	{
		DrawGraph(screenSize_.x_ / 2 - 20, 350, lpImageMng.GetID("image/Icon/D.png")[0], true);
	}
	DrawFormatString(410, 450, 0xff00ff, "撃破数：%d", dethEnemy);
	SetFontSize(20);
	switch (NowSelect)
	{
	case eScene_Game:
		y = Game_Y;
		Select_ = 0;
		break;
	case eScene_Select:
		y = Select_Y;
		Select_ = 1;
		break;
	case eScene_Title:
		y = Title_Y;
		Select_ = 2;
		break;
	default:
		break;
	}
	DrawBox(350, y + 10, 375, y + 35, 0xffffff, false);
////シーンの画像調整の時に使用すること
//DrawLine(screenSize_.x_ / 2, 0, screenSize_.x_ / 2, screenSize_.y_, 0xffffff);
//DrawLine(0, screenSize_.y_ / 2, screenSize_.x_, screenSize_.y_ /2, 0xffffff);
	//SetFontSize(25);
	//DrawString(0, 700, "↑↓で選択　Spaceで決定", 0xffffff);
	//SetFontSize(20);
}

