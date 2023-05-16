#include <DxLib.h>

#include "State/PlayerState.h"
#include "../Common/ImageMng.h"
#include "../Common/ShaderDrawGraph.h"
#include "../Input/Keyboard.h"
#include "../Input/Pad.h"
#include "Player.h"
#include "RedEnemy.h"
#include "BlackEnemy.h"
#include "BossEnemy.h"
#include "../../_debug/_DebugDispOut.h"
#include "../../_debug/_DebugConOut.h"

Player::Player()
{
	color_ = 0x00ff00;
	radius_ = 16;
	PlayerHp = 3;
	flag_ = true;
	flag = true;
	Alive_ = true;
	Time_ = 0.0;
	time_ = 0.0;
	// 読み込み
	lpAnimMng.LoadAnim("data/PlayerAct.list");
	lpAnimMng.LoadAnim("data/PlayerNAct.list");
	oldPos_ = pos_;
	// 読み込んだ内容にアニメーション
	animeData_ = std::move(lpAnimMng.SetAnime("player", "Bottom"));
	shaderData_ = std::move(lpAnimMng.SetAnime("player", "BottomN"));
	rapidxml::file<> moduleListfile = "data/PlayerModule.list";
	stateVec_ = moduleListfile.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("moduleList");
	moduleNode_ = new PlayerModuleNode();
}

Player::Player(CntType cntType, Vector2Dbl Pos)
{
	alive_ = true;
	Hptime_ = 0.0;
	pos = Pos;
	color_ = 0x00ff00;
	radius_ = 16;
	PlayerHp = 3;
	flag_ = true;
	flag = true;
	Alive_ = true;
	Time_ = 0.0;
	time_ = 0.0;
	enemyRad = 0;
	buRad = 0;
	PBalive = false;
	waitTime_ = 0.0;
	count_ = 0.0;
	timelimit_ = 1.0;
	Init(cntType);
}

Player::~Player()
{
	DeleteSoundMem(SoundHandle);
	DeleteShader(ps_);
	DeleteShaderConstantBuffer(cbuff_);
}

bool Player::Init(CntType cntType)
{
	InvTime_ = 3;
	Invincible_ = true;
	pos_ = pos;
	// 読み込み
	lpAnimMng.LoadAnim("data/PlayerAct.list");
	lpAnimMng.LoadAnim("data/PlayerNAct.list");
	oldPos_ = pos_;
	// 読み込んだ内容にアニメーション
	animeData_ = std::move(lpAnimMng.SetAnime("player", "Bottom"));
	shaderData_ = std::move(lpAnimMng.SetAnime("player", "BottomN"));
	//cbuff_ = CreateShaderConstantBuffer(sizeof(float) * 4);
	//threshold_ = static_cast<float*>(GetBufferShaderConstantBuffer(cbuff_));
	//angle_ = 0.0f;
	ps_ = LoadPixelShader("Shader/2D.pso");
	if (cntType == CntType::Key)
	{
		controller_ = std::make_unique<Keyboard>();
	}
	if (cntType == CntType::Pad)
	{
		for (int padnum = 1; padnum <= GetJoypadNum(); padnum++)
		{
			controller_ = std::make_unique<Pad>(padnum);
		}
	}
	rapidxml::file<> moduleListfile = "data/PlayerModule1.list";
	stateVec_ = moduleListfile.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("moduleList");
	moduleNode_ = new PlayerModuleNode();

	moduleListfile = "data/PlayerModule1N.list";
	stateVecN_ = moduleListfile.vecData();
	stateDocN_.parse<0>(stateVecN_.data());
	stateNodeN_ = stateDocN_.first_node("moduleList");
	moduleNodeN_ = new PlayerModuleNodeN();
	SoundHandle = LoadSoundMem("bgm/don.mp3");
	return true;
}

bool Player::Init(void)
{
	Hpflag_ = true;
	pos_ = pos;
	color_ = 0x00ff00;
	radius_ = 16;
	animeData_ = std::move(lpAnimMng.SetAnime("player", "Bottom"));
	shaderData_ = std::move(lpAnimMng.SetAnime("player", "BottomN"));
	InvTime_ = 3;
	Invincible_ = true;
	return true;
}

void Player::Update(double delta, TmxObj& tmxObj, std::list<std::unique_ptr<Obj>>& objlist)
{
	delta_ = delta;
	Hptime_ += delta_;
	if (flag_)
	{
		Hpflag_ = false;
		if (!controller_)
		{
			return;
		}
		controller_->Updata();

		auto cntData = controller_->GetCntData();

		if (alive_)
		{
			for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
			{
				(*moduleNode_)(this, node, &tmxObj);
			}
			//for (auto node = stateNodeN_->first_node(); node != nullptr; node = node->next_sibling())
			//{
			//	(*moduleNodeN_)(this, node, &tmxObj);
			//}
			lpAnimMng.UpdateAnime(animeData_);
			//lpAnimMng.UpdateAnime(shaderData_);
		}
		if (oldPos_ == pos_)
		{
			waitTime_ += delta_;
		}
		else
		{
			waitTime_ = 0.0;
			count_ = 0.0;
		}
		oldPos_ = pos_;
		InvTime_ -= delta_;
		if (InvTime_ < 0.0)
		{
			Invincible_ = false;
		}
	}
	for (auto& obj : objlist)
	{
		if (this->GetObjID() == obj.get()->GetObjID())
		{
			continue;
		}
		if (ObjID::RedEnemy == obj.get()->GetObjID())
		{
			auto EnemyPos = obj.get()->GetPos();
			auto EnemyRad = obj.get()->GetRad();
			auto waitTime = dynamic_cast<RedEnemy*>(obj.get())->GetWaitTime_();
			auto deth = dynamic_cast<RedEnemy*>(obj.get())->GetDeth();
			if (waitTime >= 2)
			{
				if (geometry_.IsHit(pos_, EnemyPos, radius_, EnemyRad) && PlayerHp > 0)
				{
					if (flag_ && !Invincible_ && !deth)
					{
						//PlaySound("bgm/don.mp3", DX_PLAYTYPE_BACK);
						ChangeNextPlayVolumeSoundMem(128, SoundHandle);
						PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
						flag = AtackHit(1);
						flag_ = false;
						Init();
					}
				}
			}

		}
		if (ObjID::BlackEnemy == obj.get()->GetObjID())
		{
			auto EnemyPos = obj.get()->GetPos();
			auto EnemyRad = obj.get()->GetRad();
			auto waitTime = dynamic_cast<BlackEnemy*>(obj.get())->GetWaitTime_();
			auto deth = dynamic_cast<BlackEnemy*>(obj.get())->GetDeth();
			if (waitTime >= 2)
			{
				if (geometry_.IsHit(pos_, EnemyPos, radius_, EnemyRad) && PlayerHp > 0)
				{
					if (flag_ && !Invincible_ && !deth)
					{
						//PlaySound("bgm/don.mp3", DX_PLAYTYPE_BACK);
						ChangeNextPlayVolumeSoundMem(128, SoundHandle);
						PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
						flag = AtackHit(1);
						flag_ = false;
						Init();
					}
				}
			}
		}
		if (ObjID::BossEnemy == obj.get()->GetObjID())
		{
			auto EnemyPos = obj.get()->GetPos();
			auto EnemyRad = obj.get()->GetRad();
			auto waitTime = dynamic_cast<BossEnemy*>(obj.get())->GetWaitTime_();
			auto deth = dynamic_cast<BossEnemy*>(obj.get())->GetDeth();
			if (waitTime >= 2)
			{
				if (geometry_.IsHit(pos_, EnemyPos, radius_, EnemyRad) && PlayerHp > 0)
				{
					if (flag_ && !Invincible_ && !deth)
					{
						//PlaySound("bgm/don.mp3", DX_PLAYTYPE_BACK);
						ChangeNextPlayVolumeSoundMem(128, SoundHandle);
						PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
						flag = AtackHit(1);
						flag_ = false;
						Init();
					}
				}
			}
		}
		if (ObjID::EnemyBullet == obj.get()->GetObjID())
		{
			EnBulletPos_ = obj.get()->GetPos();
			buRad = obj.get()->GetRad();
			PBalive = obj.get()->GetAlive();
		}
	}
	if (!flag_)
	{
		time_ += delta_;
		if (time_ < 0.25 || (time_ > 0.5 && time_ < 0.75) ||
			(time_ > 1.0 && time_ < 1.25) || (time_ > 1.5 && time_ < 1.75))
		{
			flag = false;
		}
		else
		{
			flag = true;
		}
		if (time_ >= 2)
		{
			flag_ = true;
			flag = true;
			time_ = 0;
		}
	}
	if (PlayerHp == 0)
	{
		if (flag == false)
		{
			Time_ += delta_;
		}
		if (Time_ >= 0.25)
		{
			Alive_ = false;
			alive_ = false;
		}
	}
	if (waitTime_ >= 2)
	{
		count_ += delta_;
	}
}

void Player::Draw(void)
{
	auto Alpha = static_cast<int>(255 * count_ / timelimit_);
	if (flag)
	{
		if (Hpflag_ || (Hptime_ <= 1))
		{
			for (int hp = 0; hp < PlayerHp; hp++)
			{
				SetDrawBright(255, 0, 0);
				DrawGraph((static_cast<int>(pos_.x_) - 6) + hp * 15, static_cast<int>(pos_.y_) + 32, lpImageMng.GetID("image/PlayerList/heart.png")[0], true);
			}
			SetDrawBright(255, 255, 255);
		}
		if (waitTime_ >= 2)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
			for (int hp = 0; hp < PlayerHp; hp++)
			{
				SetDrawBright(255, 0, 0);
				DrawGraph((static_cast<int>(pos_.x_) - 6) + hp * 15, static_cast<int>(pos_.y_) + 32, lpImageMng.GetID("image/PlayerList/heart.png")[0], true);
				SetDrawBright(255, 255, 255);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,Alpha);
		}
		DrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID(animeData_.state_)[(*animeData_.animItr_)[GraphHD]], true);
		//DrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID(shaderData_.state_)[(*shaderData_.animItr_)[GraphHD]], true);
		// シェーダを使ってDraw
		//threshold_[0] = 0.0f;
		//threshold_[1] = angle_;
		//UpdateShaderConstantBuffer(cbuff_);
		//SetShaderConstantBuffer(cbuff_, DX_SHADERTYPE_PIXEL, 0);
		//MyDrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID(animeData_.state_)[(*animeData_.animItr_)[GraphHD]]);
		//MyDrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID(animeData_.state_)[(*animeData_.animItr_)[GraphHD]],
		//				lpImageMng.GetID(shaderData_.state_)[(*shaderData_.animItr_)[GraphHD]],ps_);
	}
}

bool Player::AtackHit(int damage)
{
	return (PlayerHp -= damage) > 0;
}

std::string Player::GetState(void)
{
	return animeData_.state_;
}

double Player::GetInvincible(void)
{
	return Invincible_;
}
