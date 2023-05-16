#include "GameScene.h"
#include "TitleScene.h"
#include "../Common/ImageMng.h"
#include "../Transition/CrossOver.h"
#include "../Transition/CurtainUp.h"
#include"../Transition/CurtainOpen.h"
#include "SelectScene.h"

const static int Stage_Y1 = 450;
//const static int Stage12_Y = 530;
//const static int Stage13_Y = 560;
const static int Stage_Y2 = 490;
const static int Stage_Y3 = 530;
//const static int Stage22_Y = 620;
const static int Title_Y = 680;
const static int Stage_X1 = 240;
const static int Stage_X2 = 440;
const static int Stage_X3 = 640;
const static int Title_X = 375;

typedef enum {
	eScene_Stage1,
	eScene_Stage12,
	eScene_Stage13,
	eScene_Stage2,
	eScene_Stage22,
	eScene_Stage23,
	eScene_Stage31,
	eScene_Stage32,
	eScene_Stage33,


	eScene_Title,
	eScene_Num,
} eScene;

static int NowSelect = eScene_Stage1;

SelectScene::SelectScene()
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

SelectScene::~SelectScene()
{
	DeleteSoundMem(SoundHandle);
	DeleteSoundMem(soundHandle1);
}

bool SelectScene::Init(void)
{
	Alive_ = true;
	timelimit = 2;
	count_ = 0.0;
	mapDraw_ = true;
	Blink_ = 0.0;
	delay = 0.25;
	second = 0.0;
	screensize = Vector2Dbl(static_cast<double>(screenSize_.x_), static_cast<double>(screenSize_.y_));
	NowSelect = eScene_Stage1;
	SoundHandle = LoadSoundMem("bgm/select10.mp3");
	soundHandle1 = LoadSoundMem("bgm/se_maoudamashii_system37.mp3");
	return true;
}

uniqueScene SelectScene::Update(double delta, uniqueScene ownScene)
{
	if ((CheckHitKey(KEY_INPUT_RIGHT) && delay <= second && input_ == 0) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) && delay <= second && input_ == 1)) // 上キーが押されていたら
	{
		//PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
		ChangeNextPlayVolumeSoundMem(128, SoundHandle);
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
		NowSelect = (NowSelect + 1) % eScene_Num;
		second = 0.0;
		Blink_ = 0.0;
	}
	if ((CheckHitKey(KEY_INPUT_LEFT) && delay <= second && input_ == 0) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) && delay <= second && input_ == 1)) // 下キーが押されていたら
	{
		//PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
		ChangeNextPlayVolumeSoundMem(128, SoundHandle);
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
		NowSelect = (NowSelect + (eScene_Num - 1)) % eScene_Num;
		second = 0.0;
		Blink_ = 0.0;
	}
	if ((CheckHitKey(KEY_INPUT_DOWN) && delay <= second && input_ == 0) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) && delay <= second && input_ == 1)) // 下キーが押されていたら
	{
		//PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
		ChangeNextPlayVolumeSoundMem(128, SoundHandle);
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
		if (NowSelect == eScene_Stage31 || NowSelect == eScene_Stage32 || NowSelect == eScene_Stage33)
		{
			NowSelect = eScene_Title;
		}
		else if (NowSelect == eScene_Title)
		{
			NowSelect = eScene_Stage1;
		}
		else
		{
			NowSelect = (NowSelect + 3) % eScene_Num;
		}
		second = 0.0;
		Blink_ = 0.0;
	}
	if ((CheckHitKey(KEY_INPUT_UP) && delay <= second && input_ == 0) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) && delay <= second && input_ == 1)) // 上キーが押されていたら
	{
		//PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
		ChangeNextPlayVolumeSoundMem(128, SoundHandle);
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
		if (NowSelect != eScene_Stage1 && NowSelect != eScene_Stage12 && NowSelect != eScene_Stage13)
		{
			NowSelect = (NowSelect + (eScene_Num - 3)) % eScene_Num;
		}
		second = 0.0;
		Blink_ = 0.0;
	}
	if (second == 0.0)
	{
		switch (NowSelect)
		{
		case eScene_Stage1:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map.tmx");
			count_ = 0.0;
			break;
		case eScene_Stage12:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map1-2.tmx");
			count_ = 0.0;
			break;
		case eScene_Stage13:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map1-3.tmx");
			count_ = 0.0;
			break;
		case eScene_Stage2:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map2.tmx");
			count_ = 0.0;
			break;
		case eScene_Stage22:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map2-2.tmx");
			count_ = 0.0;
			break;
		case eScene_Stage23:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map2-3.tmx");
			count_ = 0.0;
			break;
		case eScene_Stage31:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map3-1.tmx");
			count_ = 0.0;
			break;
		case eScene_Stage32:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map3-2.tmx");
			count_ = 0.0;
			break;
		case eScene_Stage33:
			mapDraw_ = true;
			tmxObj_.LoadTMX("./tmx/map3-3.tmx");
			count_ = 0.0;
			break;
		case eScene_Title:
			mapDraw_ = false;
			count_ = 0.0;
			break;
		default:
			break;
		}
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
		case eScene_Stage1:
			return std::make_unique<CurtainOpen>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map.tmx", "map.png", "./data/ObjPos/ObjPos11.list"),screensize,delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map.tmx", Vector2Dbl(32, 32), Vector2Dbl(200, 700), Vector2Dbl(700.0, 50.0), Vector2Dbl(450.0, 500.0), Vector2Dbl(800, 500), "map.png"));
			break;
		case eScene_Stage12:
			return std::make_unique<CurtainOpen>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map1-2.tmx", "map.png", "./data/ObjPos/ObjPos12.list"), screensize, delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map1-2.tmx", Vector2Dbl(32, 32), Vector2Dbl(200, 700), Vector2Dbl(700.0, 250.0), Vector2Dbl(450.0, 700.0), Vector2Dbl(900, 500), "map.png"));
			break;
		case eScene_Stage13:
			return std::make_unique<CurtainOpen>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map1-3.tmx", "map.png", "./data/ObjPos/ObjPos13.list"), screensize, delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map1-3.tmx", Vector2Dbl(32, 32), Vector2Dbl(800, 700), Vector2Dbl(500.0, 50.0), Vector2Dbl(450.0, 500.0), Vector2Dbl(900, 600), "map.png"));
			break;
		case eScene_Stage2:
			return std::make_unique<CurtainUp>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2.tmx", "map4.png", "./data/ObjPos/ObjPos21.list"), screensize, delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2.tmx", Vector2Dbl(32, 32), Vector2Dbl(100, 625), Vector2Dbl(700.0, 700.0), Vector2Dbl(400.0, 500.0), Vector2Dbl(500, 500), "map4.png"));
			break;
		case eScene_Stage22:
			return std::make_unique<CurtainUp>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2-2.tmx", "map4.png", "./data/ObjPos/ObjPos22.list"), screensize, delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2-2.tmx", Vector2Dbl(32, 32), Vector2Dbl(700, 250), Vector2Dbl(400.0, 500.0), Vector2Dbl(950.0, 200.0), Vector2Dbl(800, 600), "map4.png"));
			break;
		case eScene_Stage23:
			return std::make_unique<CurtainUp>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2-3.tmx", "map4.png", "./data/ObjPos/ObjPos23.list"), screensize, delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2-2.tmx", Vector2Dbl(32, 32), Vector2Dbl(700, 250), Vector2Dbl(400.0, 500.0), Vector2Dbl(950.0, 200.0), Vector2Dbl(800, 600), "map4.png"));
			break;
		case eScene_Stage31:
			return std::make_unique<CurtainUp>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map3-1.tmx", "map3.png", "./data/ObjPos/ObjPos31.list"), screensize, delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2-2.tmx", Vector2Dbl(32, 32), Vector2Dbl(700, 250), Vector2Dbl(400.0, 500.0), Vector2Dbl(950.0, 200.0), Vector2Dbl(800, 600), "map4.png"));
			break;
		case eScene_Stage32:
			return std::make_unique<CurtainUp>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map3-2.tmx", "map3.png", "./data/ObjPos/ObjPos32.list"), screensize, delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2-2.tmx", Vector2Dbl(32, 32), Vector2Dbl(700, 250), Vector2Dbl(400.0, 500.0), Vector2Dbl(950.0, 200.0), Vector2Dbl(800, 600), "map4.png"));
			break;
		case eScene_Stage33:
			return std::make_unique<CurtainUp>(4.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map3-3.tmx", "map3.png", "./data/ObjPos/ObjPos33.list"), screensize, delta);
			//return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameScene>("./tmx/map2-2.tmx", Vector2Dbl(32, 32), Vector2Dbl(700, 250), Vector2Dbl(400.0, 500.0), Vector2Dbl(950.0, 200.0), Vector2Dbl(800, 600), "map4.png"));
			break;
		case eScene_Title:
			return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<TitleScene>());
			break;
		default:
			break;
		}
	}
	count_ += delta * 2;
	DrawOwnScreen(delta);
	return ownScene;

}

void SelectScene::DrawOwnScreen(double delta)
{
	int y = 0;
	int x = 0;
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	auto Alpha = static_cast<int>(255 * count_ / timelimit);
	auto WorldArea = tmxObj_.GetWorldArea();
	auto TileSize = tmxObj_.GetTileSize();
	if (mapDraw_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
		SetDrawBright(128, 128, 128);
		for (const auto& layer : tmxObj_.GetMapData())
		{
			for (int y = 0; y < WorldArea.y_; y++)
			{
				for (int x = 0; x < WorldArea.x_; x++)
				{
					auto image = y * WorldArea.x_ + x;
					if (image < layer.second.size())
					{
						// グラフィックidの取得
						int gid = layer.second[static_cast<__int64>(y) * WorldArea.x_ + x] - tmxObj_.GetFirstGID();
						if (gid >= 0)
						{
							// x,yのところを座標に戻す
							switch (NowSelect)
							{
							case eScene_Stage1:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map.png")[gid], true);
								break;
							case eScene_Stage12:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map.png")[gid], true);
								break;
							case eScene_Stage13:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map.png")[gid], true);
								break;
							case eScene_Stage2:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map4.png")[gid], true);
								break;
							case eScene_Stage22:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map4.png")[gid], true);
								break;
							case eScene_Stage23:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map4.png")[gid], true);
								break;
							case eScene_Stage31:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map3.png")[gid], true);
								break;
							case eScene_Stage32:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map3.png")[gid], true);
								break;
							case eScene_Stage33:
								DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID("map3.png")[gid], true);
								break;
							case eScene_Title:
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
		SetDrawBright(255, 255, 255);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
	DrawGraph(300, 300, lpImageMng.GetID("image/Icon/Selecticon.png")[0], true);
	Blink_ += delta * 2.0;
	if (Blink_ <= 2)
	{
		DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
		DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
		DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
		DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
		DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
		DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
		DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
		DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
		DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
		DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
	}
	else
	{
		if (Select_ == 0)
		{
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			}
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 1)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			}
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 2)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			}
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 3)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			}
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 4)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			}
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 5)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			}
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 6)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			}
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 7)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			}
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 8)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			}
			DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
		}
		if (Select_ == 9)
		{
			DrawGraph(Stage_X1, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y1, lpImageMng.GetID("image/Icon/Stage1-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y2, lpImageMng.GetID("image/Icon/Stage2-3.png")[0], true);
			DrawGraph(Stage_X1, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-1.png")[0], true);
			DrawGraph(Stage_X2, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-2.png")[0], true);
			DrawGraph(Stage_X3, Stage_Y3, lpImageMng.GetID("image/Icon/Stage3-3.png")[0], true);
			if ((static_cast<int>(Blink_) % 2) == 1)
			{
				SetDrawBright(128, 128, 128);
				DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			else
			{
				DrawGraph(Title_X, Title_Y, lpImageMng.GetID("image/Icon/tiltle.png")[0], true);
			}
		}
	}

	switch (NowSelect)
	{
	case eScene_Stage1:
		y = Stage_Y1;
		x = Stage_X1;
		Select_ = 0;
		break;
	case eScene_Stage12:
		y = Stage_Y1;
		Select_ = 1;
		x = Stage_X2;
		break;
	case eScene_Stage13:
		y = Stage_Y1;
		Select_ = 2;
		x = Stage_X3;
		break;
	case eScene_Stage2:
		y = Stage_Y2;
		Select_ = 3;
		x = Stage_X1;
		break;
	case eScene_Stage22:
		y = Stage_Y2;
		Select_ = 4;
		x = Stage_X2;
		break;
	case eScene_Stage23:
		y = Stage_Y2;
		Select_ = 5;
		x = Stage_X3;
		break;
	case eScene_Stage31:
		y = Stage_Y3;
		Select_ = 6;
		x = Stage_X1;
		break;
	case eScene_Stage32:
		y = Stage_Y3;
		Select_ = 7;
		x = Stage_X2;
		break;
	case eScene_Stage33:
		y = Stage_Y3;
		Select_ = 8;
		x = Stage_X3;
		break;
	case eScene_Title:
		y = Title_Y;
		Select_ = 9;
		x = Title_X;
		break;
	default:
		break;
	}
	DrawCircle(x -10, y+15, 5, 0xffffff, true);
	//SetFontSize(25);
	//DrawString(0, 700, "↑↓で選択　Spaceで決定", 0xffffff);
	//SetFontSize(20);
	// 
	//	//シーンの画像調整の時に使用すること
	//DrawLine(screenSize_.x_ / 2, 0, screenSize_.x_ / 2, screenSize_.y_, 0xffffff);
	//DrawLine(0, screenSize_.y_ / 2, screenSize_.x_, screenSize_.y_ / 2, 0xffffff);

}

