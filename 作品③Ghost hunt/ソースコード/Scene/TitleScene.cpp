#include <DxLib.h>
#include <cmath>
#include "TitleScene.h"
#include "SelectScene.h"
#include "InfoScene.h"
#include "../Common/FontMng.h"
#include "../Common/ImageMng.h"
#include "../Input/Keyboard.h"
#include "../Input/Pad.h"
#include "../Transition/CrossOver.h"
#include "../../class/Common/Geometry.h"

const static int Stage1_Y = 500;
const static int Stage2_Y = 570;
//const static int End_Y = 560;

typedef enum {
	eScene_INFO,
	eScene_SELECT,
	//eScene_END,

	eScene_Num,
} eScene;

static int NowSelect = eScene_SELECT;

TitleScene::TitleScene()
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
	Init();
	DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{
	DeleteSoundMem(SoundHandle);
	DeleteSoundMem(soundHandle1);
}

bool TitleScene::Init(void)
{
	appFlag_ = true;
	speed_ = 0.0;
	Alive_ = true;
	Blink_ = 0.0;
	delay = 0.25;
	second = 0.25;
	Flag_ = true;
	speed_X = -300;
	speed_Y = -200;
	color_ = 0xffffff;
	apptitle_ = true;
	delayTime_ = 0.0;
	titletime_ = 0.0;
	SoundHandle = LoadSoundMem("bgm/select10.mp3");
	soundHandle1 = LoadSoundMem("bgm/se_maoudamashii_system37.mp3");
	return false;
}

uniqueScene TitleScene::Update(double delta, uniqueScene ownScene)
{
	//if (!controller_)
	//{
	//	return ownScene;
	//}
	//controller_->Updata();
	// 音の読み込み
	if (speed_Y < 300)
	{
		speed_Y += delta * 600;
	}
	else
	{
		{
			delayTime_ += delta;
			speed_X = 400;
			if ((CheckHitKey(KEY_INPUT_DOWN) && delay <= second && input_ == 0 )||
				((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) && delay <= second && input_ == 1)) // 下キーが押されていたら
			{
				//PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
				ChangeNextPlayVolumeSoundMem(128, SoundHandle);
				PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
				NowSelect = (NowSelect + 1) % eScene_Num;
				second = 0.0;
				Blink_ = 0.0;
			}
			if ((CheckHitKey(KEY_INPUT_UP) && delay <= second && input_ == 0)||
				((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) && delay <= second && input_ == 1)) // 上キーが押されていたら
			{
				//PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
				ChangeNextPlayVolumeSoundMem(128, SoundHandle);
				PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
				NowSelect = (NowSelect + (eScene_Num - 1)) % eScene_Num;
				second = 0.0;
				Blink_ = 0.0;
			}

			//if (CheckHitKey(KEY_INPUT_DOWN) && delay <= second) // 下キーが押されていたら
			//{
			//	PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
			//	NowSelect = (NowSelect + 1) % eScene_Num;
			//	second = 0.0;
			//	Blink_ = 0.0;
			//}
			//if (CheckHitKey(KEY_INPUT_UP) && delay <= second) // 上キーが押されていたら
			//{
			//	PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
			//	NowSelect = (NowSelect + (eScene_Num - 1)) % eScene_Num;
			//	second = 0.0;
			//	Blink_ = 0.0;
			//}

			second += delta;
			if ((CheckHitKey(KEY_INPUT_SPACE) && delayTime_ >= 1 && input_ == 0) ||
				((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) && delayTime_ >= 1 && input_ == 1))
			{
				//PlaySound("bgm/se_maoudamashii_system37.mp3", DX_PLAYTYPE_BACK);
				ChangeNextPlayVolumeSoundMem(128, soundHandle1);
				PlaySoundMem(soundHandle1, DX_PLAYTYPE_BACK);
				delayTime_ = 0.0;
				switch (NowSelect)
				{
				case eScene_INFO:
					//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<InfoScene>());
					return std::make_unique<InfoScene>(std::move(ownScene));
					break;
				case eScene_SELECT:
					return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<SelectScene>());
					Alive_ = true;
					break;
				//case eScene_END:
				//	Alive_ = false;
				//	break;
				default:
					break;
				}
			}
		}
	}
	DrawOwnScreen(delta);
	return ownScene;
}


void TitleScene::DrawOwnScreen(double delta)
{
	int y = 0;
	int rad = 0;
	SetDrawScreen(screenID_);
	ClsDrawScreen();	
	SetDrawBright(128, 128, 128);
	DrawGraph(0, 0, lpImageMng.GetID("image/Icon/TitleBack.png")[0], true);
	SetDrawBright(255, 255, 255);
	// フォントの種類を変えたり、サイズや太さを変えれる
	lpFontMng.ChangeFont("HGS行書体", "↑↓で選択　Spaceで決定", Vector2Dbl(0, 700), 30, 9);
	// タイトルの後ろに幽霊が現れたり消えたりする
	if (speed_X >= 400.0)
	{
		speed_ += delta * 100;
		if (speed_ <= 128)
		{
			SetDrawBright(static_cast<int>(speed_), static_cast<int>(speed_), static_cast<int>(speed_));
			DrawGraph(230, static_cast<int>(speed_Y), lpImageMng.GetID("image/Icon/title.png")[0], true);
			DrawGraph(700, static_cast<int>(speed_Y), lpImageMng.GetID("image/Icon/title.png")[0], true);
			appFlag_ = false;
		}
		else if (!appFlag_ && speed_ <= 255)
		{
			SetDrawBright(255 - static_cast<int>(speed_), 255 - static_cast<int> (speed_), 255 - static_cast<int>( speed_));
			DrawGraph(230, static_cast<int>(speed_Y), lpImageMng.GetID("image/Icon/title.png")[0], true);
			DrawGraph(700, static_cast<int>(speed_Y), lpImageMng.GetID("image/Icon/title.png")[0], true);
		}
		else
		{
			speed_ = 0.0;
			appFlag_ = true;
		}
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(300, static_cast<int>(speed_Y), lpImageMng.GetID("image/Icon/Titleicon.png")[0], true);
	Blink_ += delta * 2;
	if ((titletime_ <= 255 && apptitle_ && speed_X >= 400.0) ||( Blink_ <= 2 && apptitle_ == false ))
	{
		SetDrawBright(static_cast<int>(titletime_), static_cast<int>(titletime_), static_cast<int>(titletime_));
		DrawGraph(static_cast<int>(speed_X) + 30, Stage1_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
		DrawGraph(static_cast<int>(speed_X), Stage2_Y, lpImageMng.GetID("image/Icon/start.png")[0], true);
		SetDrawBright(255, 255, 255);
		if (speed_ <= 254)
		{
			titletime_ += delta * 100;
		}
		else
		{
			apptitle_ = false;
		}
		//DrawGraph(static_cast<int>(speed_X), End_Y, lpImageMng.GetID("image/Icon/End.png")[0], true);
	}
	else
	{
		if (Select_ == 0)
		{
			if ((static_cast<int>(Blink_) % 2) == 0)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(static_cast<int>(speed_X) + 30, Stage1_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(static_cast<int>(speed_X) + 30, Stage1_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
			}
			DrawGraph(static_cast<int>(speed_X), Stage2_Y, lpImageMng.GetID("image/Icon/start.png")[0], true);
			//DrawGraph(static_cast<int>(speed_X), End_Y, lpImageMng.GetID("image/Icon/End.png")[0], true);
		}

		if (Select_ == 1)
		{
			DrawGraph(static_cast<int>(speed_X) + 30, Stage1_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 0)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(static_cast<int>(speed_X), Stage2_Y, lpImageMng.GetID("image/Icon/start.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(static_cast<int>(speed_X), Stage2_Y, lpImageMng.GetID("image/Icon/start.png")[0], true);
			}
			//DrawGraph(static_cast<int>(speed_X), End_Y, lpImageMng.GetID("image/Icon/End.png")[0], true);
		}

		if (Select_ == 2)
		{
			DrawGraph(static_cast<int>(speed_X) + 30, Stage1_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
			DrawGraph(static_cast<int>(speed_X), Stage2_Y, lpImageMng.GetID("image/Icon/start.png")[0], true);
			//if ((static_cast<int>(Blink_) % 2) == 0)
			//{
			//	SetDrawBright(128, 128, 128);
			//	DrawGraph(static_cast<int>(speed_X), End_Y, lpImageMng.GetID("image/Icon/End.png")[0], true);
			//	SetDrawBright(255, 255, 255);
			//}
			//else
			//{
			//	DrawGraph(static_cast<int>(speed_X), End_Y, lpImageMng.GetID("image/Icon/End.png")[0], true);
			//}
		}
	}
	switch (NowSelect)
	{
	case eScene_INFO:
		y = Stage1_Y;
		Select_ = 0;
		break;
	case eScene_SELECT:
		y = Stage2_Y;
		Select_ = 1;
		break;
	//case eScene_END:
	//	y = End_Y;
	//	Select_ = 2;
	default:
		break;
	}
	if (speed_X == 400)
	{
		rad += 1;
		DrawBox(350, y + 10, 375, y + 35, 0xffffff, false);
	}
	////シーンの画像調整の時に使用すること
	//DrawLine(screenSize_.x_ / 2, 0, screenSize_.x_ / 2, screenSize_.y_, 0xffffff);
	//DrawLine(0, screenSize_.y_ / 2, screenSize_.x_, screenSize_.y_ / 2, 0xffffff);
}

