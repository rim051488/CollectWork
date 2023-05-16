#include <DxLib.h>
#include <ctime>
#include "../Scene/GameOverScene.h"
#include "../Scene/GameClear.h"
#include "../Transition/CrossOver.h"
#include "../Common/ImageMng.h"
#include "../Common/FontMng.h"
#include "../Obj/Player.h"
#include "../Obj/BlackEnemy.h"
#include "../Obj/RedEnemy.h"
#include "../Obj/BossEnemy.h"
#include "../Obj/PlayerBullet.h"
#include "../Obj/EnemyBullet.h"
#include "../Scene/MenuScene.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
#include "GameScene.h"

GameScene::GameScene()
{
	Init();
	DrawOwnScreen(0.0);
}

GameScene::GameScene(std::string filename, std::string map, std::string pos)
{
 	rapidxml::file<> moduleListfile = pos.c_str();
	stateVec_ = moduleListfile.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("moduleList");
	objPos_ = pos;
	Vector2Dbl Getpos;
	std::string objName;
	Vector2Dbl Getpos2;
	Vector2Dbl Getpos3;
	for (auto moduleNode = stateNode_->first_node("ActNode"); moduleNode != nullptr; moduleNode = moduleNode->next_sibling())
	{
		objName = moduleNode->first_attribute("objname")->value();
		Getpos = Vector2Dbl{ atof(moduleNode->first_attribute("posX")->value()) ,atof(moduleNode->first_attribute("posY")->value()) };
		if (objName == "Player")
		{
			objList_.emplace_back(std::make_unique<EnemyBullet>());
			if (GetJoypadNum())
			{
				objList_.emplace_back(std::make_unique<Player>(CntType::Pad, Getpos));
				input_ = 1;
				cntType_ = CntType::Pad;
			}
			else
			{
				objList_.emplace_back(std::make_unique<Player>(CntType::Key, Getpos));
				input_ = 0;
				cntType_ = CntType::Key;
			}
		}
		if (objName == "BlackEnemy")
		{
			objList_.emplace_back(std::make_unique<BlackEnemy>(Getpos));
			EnemyList_.emplace_back(std::make_unique<BlackEnemy>(Getpos));
			enemyList_.emplace_back(std::make_unique<BlackEnemy>(Getpos));
		}
		if (objName == "RedEnemy")
		{
			objList_.emplace_back(std::make_unique<RedEnemy>(Getpos));
			EnemyList_.emplace_back(std::make_unique<RedEnemy>(Getpos));
			enemyList_.emplace_back(std::make_unique<RedEnemy>(Getpos));
		}
		if (objName == "BossEnemy")
		{
			bossList_.emplace_back(std::make_unique<BossEnemy>(Getpos));
		}
		if (objName == "PlayerBullet")
		{
			Getpos2 = Vector2Dbl{ atof(moduleNode->first_attribute("pos2X")->value()) ,atof(moduleNode->first_attribute("pos2Y")->value()) };
			Getpos3 = Vector2Dbl{ atof(moduleNode->first_attribute("pos3X")->value()) ,atof(moduleNode->first_attribute("pos3Y")->value()) };
			objList_.emplace_back(std::make_unique<PlayerBullet>(Getpos, Getpos2, Getpos3));
		}

	}
	objsize = objList_.size();
	map_ = map;
	Init(filename);
	delay = 1;
	second = 0.25;
	dethEnemy_ = 0;
	bossApp_ = true;
	DrawOwnScreen(0.0);
}

GameScene::~GameScene()
{
	DeleteSoundMem(SoundHandle);
	DeleteSoundMem(soundHandle1);
}

bool GameScene::Init(void)
{
	//time_ = 3.0;
	//tmxObj_.LoadTMX("./tmx/map.tmx");
	//objList_.emplace_back(std::make_unique<RedEnemy>());
	//objList_.emplace_back(std::make_unique<PlayerBullet>());
	//objList_.emplace_back(std::make_unique<EnemyBullet>());
	//// パッドでやりたいと言われたときは実装
	////if (GetJoypadNum())
	////{
	////	objList_.emplace_back(std::make_unique<Player>(CntType::Pad));
	////}
	////else
	////{
	//	objList_.emplace_back(std::make_unique<Player>(CntType::Key,player_));
	////}
	return true;
}

bool GameScene::Init(std::string filename)
{
	Endtime_ = 0.0;
	timeLimit_ = 60.0;
	Alive_ = true;
	PlayerAlive_ = true;
	timelimit = 2,0;
	time_ = 4.0;
	tmxObj_.LoadTMX(filename);
	BossTime_ = 0;
	Bossflag_ = false;
	bossdeth = false;
	fileName_ = filename;
	SoundHandle = LoadSoundMem("bgm/bossshtugennkari1.mp3");
	return true;
}

uniqueScene GameScene::Update(double delta, uniqueScene ownScene)
{
	// 簡易的なカウントダウン
	double delta_ = delta;
	//std::list<std::unique_ptr<Obj>>::iterator it = objList_.end();
	if (enemyList_.size() == 0)
	{
		enemyList_ = std::move(EnemyList_);
	}
	if (time_ <= 0 && Bossflag_ == false)
	{
		for (const auto& obj : objList_)
		{
			obj->Update(delta, tmxObj_, objList_);
			if (ObjID::Player == obj.get()->GetObjID())
			{
				if (!obj.get()->IsAlive())
				{
					PlayerAlive_ = false;
				}
			}
			if (ObjID::PlayerBullet == obj.get()->GetObjID())
			{
				outBullet_ = dynamic_cast<PlayerBullet*>(obj.get())->GetOutBullet();
			}
			if (ObjID::BossEnemy == obj.get()->GetObjID())
			{
				if (!obj.get()->IsAlive())
				{
					bossdeth = true;
				}
			}
		}
		timeLimit_ -= delta;
	}
	// シフトを押すとメニュー画面になる
	if (CheckHitKey(KEY_INPUT_LSHIFT) && delay <= second ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_10) && delay <= second) )
	{
		return std::make_unique<MenuScene>(std::move(ownScene),dethEnemy_);
		second = 0.0;
	}
	second += delta;
	objList_.remove_if([](std::unique_ptr<Obj>& obj) {return (*obj).IsAlive() == false; });
	// 敵が死んだときに敵を1体追加
	if (objList_.size() != objsize/* && dethEnemy_ != 5*/)
	{
		if (dethEnemy_ == 4 && bossList_.size() != 0)
		{
			objList_.splice(objList_.end(), std::move(bossList_), bossList_.begin());
			//objsize = objList_.size();
			Bossflag_ = true;
			dethEnemy_++;
		}
		else if (enemyList_.size() > 0)
		{
			objList_.splice(objList_.end(), std::move(enemyList_), enemyList_.begin());
			dethEnemy_++;
		}
		else
		{
			dethEnemy_++;
		}
	}
	// プレイヤーが死んだら or 制限時間が０になったら
	if (!PlayerAlive_ || timeLimit_ <= 0)
	{
		return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameOverScene>(fileName_,map_,objPos_));
	}
	// ボスを倒したら
	if (bossdeth)
	{
		return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameClear>(fileName_, map_, objPos_, dethEnemy_, static_cast<int>(timeLimit_)));
	}
	if (Bossflag_ == true)
	{
		if (BossTime_ == 0)
		{
			//PlaySound("bgm/bossshtugennkari1.mp3", DX_PLAYTYPE_BACK);
			ChangeNextPlayVolumeSoundMem(128, SoundHandle);
			PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
		}
		if (BossTime_ < 2)
		{
			BossTime_ += delta;
			if (BossTime_ <= 0.5 || (1 < BossTime_ && BossTime_ <= 1.5))
			{
				bossApp_ = true;
			}
			else
			{
				bossApp_ = false;
			}
		}
		else
		{
			BossTime_ = 0;
			Bossflag_ = false;
		}
	}
	//if (objList_.size() == 2)
	//{
	//	Endtime_ += delta_;
	//	if (Endtime_ >= 0.5)
	//	{
	//		return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<GameClear>(fileName_, map_, objPos_));
	//	}
	//}
	count_ += delta_ * 2;
	DrawOwnScreen(delta);
	return ownScene;
}

void GameScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	auto Alpha = static_cast<int>(255 * count_ / timelimit);
	auto WorldArea = tmxObj_.GetWorldArea();
	auto TileSize = tmxObj_.GetTileSize();
	SetFontSize(20);
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
						DrawGraph(x * TileSize.x_, y * TileSize.y_, lpImageMng.GetID(map_)[gid], true);
					}
				}
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	if (Alpha >= 255)
	{
		time_ -= delta;
		int limittime = static_cast<int>(time_);
		if (time_ >= 0)
		{
			lpFontMng.ChangeFont("HGS行書体", "制限時間内にボスを倒そう！",
				Vector2Dbl(static_cast<double>(static_cast<unsigned __int64>(screenSize_.x_ / 4) - 75), screenSize_.y_ / 2), 50, 9);
		}
		ChangeFont("HGS行書体");
		SetFontSize(50);
		DrawFormatString(screenSize_.x_ / 2 - 25, 0, 0xffffff, "%d", static_cast<int>(timeLimit_));
		SetFontSize(20);
		SetFontSize(30);
		DrawFormatString(0, screenSize_.y_ - 30, 0xffffff, "残弾数:%d", outBullet_);
		SetFontSize(10);
	}
	for (const auto& obj : objList_)
	{
		if ((obj->GetObjID() == ObjID::RedEnemy) ||
			(obj->GetObjID() == ObjID::BlackEnemy) ||
			(obj->GetObjID() == ObjID::BossEnemy))
		{
			obj->Draw();
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
	for (const auto& obj : objList_)
	{
		if (!(obj->GetObjID() == ObjID::RedEnemy) &&
			!(obj->GetObjID() == ObjID::BlackEnemy) &&
			!(obj->GetObjID() == ObjID::BossEnemy))
		{
			obj->Draw();
		}
	}
	if (Bossflag_)
	{
		if (bossApp_)
		{
			lpFontMng.ChangeFont("HGS行書体", "ボスが出現！",
				Vector2Dbl(static_cast<double>(static_cast<unsigned __int64>(screenSize_.x_ / 3) + 30),
					static_cast<double>(static_cast<unsigned __int64>(screenSize_.y_ / 2) - 25)),
				50, 9);
		}
		else
		{
			lpFontMng.ChangeFont("HGS行書体", "ボスが出現！",
				Vector2Dbl(static_cast<double>(static_cast<unsigned __int64>(screenSize_.x_ / 3) - 30),
					static_cast<double>(static_cast<unsigned __int64>(screenSize_.y_ / 2) - 35)),
				70, 9, 0xff0000);
		}
	}
//		//シーンの画像調整の時に使用すること
//DrawLine(screenSize_.x_ / 2, 0, screenSize_.x_ / 2, screenSize_.y_, 0xffffff);
//DrawLine(0, screenSize_.y_ / 2, screenSize_.x_, screenSize_.y_ / 2, 0xffffff);
}
