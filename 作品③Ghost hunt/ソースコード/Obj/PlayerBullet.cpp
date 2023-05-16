#include "PlayerBullet.h"
#include "../Common/ImageMng.h"
#include "Player.h"
#include "../../_debug/_DebugDispOut.h"
#include "../../_debug/_DebugConOut.h"

PlayerBullet::PlayerBullet()
{
	alive_ = true;
	enemypos_ = {0.0,0.0};
	Init();
}

PlayerBullet::PlayerBullet(Vector2Dbl Pos1,Vector2Dbl Pos2,Vector2Dbl Pos3)
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

	pos = Pos1;
	pos2 = Pos2;
	pos3 = Pos3;
	enemypos_ = { 0.0,0.0 };
	radius_ = 12;
	lpImageMng.GetID("image/Icon/App.png", "App", { 110,110 }, { 5,2 });
	imagekey_ = "App";
	//enemyFlag_ = false;
	//alive_ = true;
	Init();
}

PlayerBullet::~PlayerBullet()
{
	DeleteSoundMem(SoundHandle);
}

bool PlayerBullet::Init(void)
{
	SoundHandle = LoadSoundMem("bgm/juu.mp3");
	hit_ = true;
	srand(static_cast<unsigned int>(time(NULL)));
	rand_ = rand() % 3;
	if (rand_ == 0)
	{
		pos_ = pos;
	}
	if (rand_ == 1)
	{
		pos_ = pos2;
	}
	if (rand_ == 2)
	{
		pos_ = pos3;
	}
	flag_ = true;
	NextFlag_ = false;
	AppTime_ = 0.0;
	Prad = 0;
	Erad = 0;
	dtime = 0.0;
	bulletVel = Vector2Dbl{ 0.0 ,0.0 };
	Alive_ = false;
	ChaseFlag = true;
	bulletFlag_ = false;
	enemyFlag_ = false;
	alive = false;
	alive_ = true;
	MoveVec = Vector2Dbl{ 0.0,0.0 };
	outBullet_ = 0;
	count_ = 0.0;
	timelimit = 2;
	HighlightFlag_ = true;
	outFlag_ = true;
	return true;
}

bool PlayerBullet::Init(CntType cntType)
{
	return false;
}

bool PlayerBullet::SetNextPos(void)
{
	int nextRand = rand() % 2;
	if (rand_ == 0)
	{
		if (nextRand == 0)
		{
			NextPos_ = pos2;
			NextRand_ = 1;
			AppTime_ = 0.0;
		}
		else
		{
			NextPos_ = pos3;
			NextRand_ = 2;
			AppTime_ = 0.0;
		}
	}
	if (rand_ == 1)
	{
		if (nextRand == 0)
		{
			NextPos_ = pos;
			NextRand_ = 0;
			AppTime_ = 0.0;
		}
		else
		{
			NextPos_ = pos3;
			NextRand_ = 2;
			AppTime_ = 0.0;
		}
	}
	if (rand_ == 2)
	{
		if (nextRand == 0)
		{
			NextPos_ = pos;
			NextRand_ = 0;
			AppTime_ = 0.0;
		}
		else
		{
			NextPos_ = pos2;
			NextRand_ = 1;
			AppTime_ = 0.0;
		}
	}
	return true;
}

bool PlayerBullet::Setpos(void)
{
	pos_ = NextPos_;
	rand_ = NextRand_;
	hit_ = true;
	flag_ = true;
	NextFlag_ = false;
	Prad = 0;
	Erad = 0;
	dtime = 0.0;
	bulletVel = Vector2Dbl{ 0.0 ,0.0 };
	Alive_ = false;
	ChaseFlag = true;
	bulletFlag_ = false;
	enemyFlag_ = false;
	alive = false;
	alive_ = true;
	MoveVec = Vector2Dbl{ 0.0,0.0 };
	outBullet_ = 0;
	count_ = 0.0;
	timelimit = 2;
	HighlightFlag_ = true;
	outFlag_ = true;

	return true;
}

void PlayerBullet::Update(double delta, TmxObj& tmxObj, std::list<std::unique_ptr<Obj>>& objlist)
{
	delta_ = delta;
	AppTime_ += delta * 7;
	auto checkMove = [&](Vector2Dbl& moveVec) {
		Raycast::Ray ray = { Vector2Dbl{pos_.x_,pos_.y_} + Vector2Dbl{16,16},moveVec };
		for (auto col : tmxObj.GetColList())
		{
			if (raycast_.CheckCollision(ray, col).first)
			{
				return false;
			}
		}
		return true;
	};

	bool GetBullet = false;
	for (auto& obj : objlist)
	{
		if (this->GetObjID() == obj.get()->GetObjID())
		{
			continue;
		}
		if (ObjID::Player == obj.get()->GetObjID())
		{
			PlayerPos_ = obj->GetPos();
			playerFlag_ = obj->GetFlag();
			Prad = obj->GetRad();
			state_ = dynamic_cast<Player*>(obj.get())->GetState();
		}
		if (ObjID::RedEnemy == obj.get()->GetObjID())
		{
			auto enemyPos = obj->GetPos();
			auto eRad = obj->GetRad();
			auto eFlag = obj->GetPflag();
			if (!GetBullet)
			{
				if (((!geometry_.IsHit(PlayerPos_, enemyPos, Prad, eRad * 5)) && !eFlag))
				{
					GetBullet = true;
				}
				else
				{
					GetBullet = false;
				}
			}
		}
		if (ObjID::BlackEnemy == obj.get()->GetObjID())
		{
			auto enemyPos = obj->GetPos();
			auto eRad = obj->GetRad();
			auto eFlag = obj->GetPflag();
			if (!GetBullet)
			{
				if (((!geometry_.IsHit(PlayerPos_, enemyPos, Prad, eRad * 5)) && !eFlag))
				{
					GetBullet = true;
				}
				else
				{
					GetBullet = false;
				}
			}
		}
		if (ObjID::BossEnemy == obj.get()->GetObjID())
		{
			auto enemyPos = obj->GetPos();
			auto eRad = obj->GetRad();
			auto eFlag = obj->GetPflag();
			if (!GetBullet)
			{
				if (((!geometry_.IsHit(PlayerPos_, enemyPos, Prad, eRad * 5)) && !eFlag))
				{
					GetBullet = true;
				}
				else
				{
					GetBullet = false;
				}
			}
		}
	}
	if (!ChaseFlag && !Alive_ && playerFlag_)
	{
		if ((CheckHitKey(KEY_INPUT_Z) && input_ == 0) ||
			((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) && input_ == 1))
		{
			//PlaySound("bgm/juu.mp3", DX_PLAYTYPE_BACK);
			ChangeNextPlayVolumeSoundMem(128, SoundHandle);
			PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
			outBullet_ -= 1;
			pos_ = PlayerPos_;
			bulletFlag_ = true;
			Alive_ = true;
			if (state_ == "Top")
			{
				bulletVel = Vector2Dbl(0.0, 0.0);
				MoveVec = Vector2Dbl(0.0, 0.0);
				MoveVec.y_ += -16;
				bulletVel.y_ = -delta_ * 300;
			}
			if (state_ == "Bottom")
			{
				bulletVel = Vector2Dbl(0.0, 0.0);
				MoveVec = Vector2Dbl(0.0, 0.0);
				MoveVec.y_ += 16;
				bulletVel.y_ = delta_ * 300;
			}
			if (state_ == "Left")
			{
				bulletVel = Vector2Dbl(0.0, 0.0);
				MoveVec = Vector2Dbl(0.0, 0.0);
				MoveVec.x_ += -16;
				bulletVel.x_ = -delta_ * 300;
			}
			if (state_ == "Right")
			{
				bulletVel = Vector2Dbl(0.0, 0.0);
				MoveVec = Vector2Dbl(0.0, 0.0);
				MoveVec.x_ += 16;
				bulletVel.x_ = delta_ * 300;
			}
		}
	}
	if (bulletFlag_)
	{
		if (checkMove(MoveVec))
		{
			pos_ += bulletVel;
		}
		else
		{
			pos_ = PlayerPos_;
			bulletFlag_ = false;
			Alive_ = false;
			if (outBullet_ == 0)
			{
				outFlag_ = false;
			}
		}
	}
	if (!hit_)
	{
		pos_ = PlayerPos_;
		bulletFlag_ = false;
		Alive_ = false;
		hit_ = true;
		if (outBullet_ == 0)
		{
			outFlag_ = false;
		}
	}
	if (!outFlag_)
	{
		Setpos();
	}
	if (ChaseFlag)
	{
		//if (((!geometry_.IsHit(PlayerPos_, RedEnemyPos_, Prad, Erad * 5)) && !REflag_) &&
		//	((!geometry_.IsHit(PlayerPos_, BlackEnemyPos_, Prad, Erad * 5)) && !BEflag_))
		//	//((!geometry_.IsHit(PlayerPos_, enemypos_, Prad, Erad * 5)) && !enemyFlag_))
		if (GetBullet)
		{
			if (geometry_.IsHit(pos_, PlayerPos_, radius_, Prad))
			{
				outBullet_ = 5;
				flag_ = false;
				bulletFlag_ = false;
				alive = true;
				ChaseFlag = false;
				NextFlag_ = true;
				SetNextPos();
			}
		}
	}
	// ïêäÌÇÃã≠í≤ï\é¶
	if (count_ < timelimit && HighlightFlag_)
	{
		count_ += delta_;
	}
	else if (!HighlightFlag_ && count_ > 0)
	{
		count_ -= delta_;
	}
	else if (HighlightFlag_)
	{
		HighlightFlag_ = false;
	}
	else
	{
		HighlightFlag_ = true;
		count_ = 0.0;
	}
	if (AppTime_ > 10)
	{
		AppTime_ = 0;
	}
	oldPos_ = pos_;
}

bool PlayerBullet::AtackHit(int damage)
{
	return (PlayerHp -= damage) > 0;
}

void PlayerBullet::Draw(void)
{
	auto Alpha = static_cast<int>(255 * count_ / timelimit);
	if (flag_)
	{
		DrawGraph((static_cast<int>(pos_.x_) - 32), static_cast<int>(pos_.y_) - 32, lpImageMng.GetID(imagekey_)[AppTime_], true);
		DrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID("image/Icon/juu.png")[0], true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, Alpha);
		DrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID("image/Icon/juu.png")[0], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
	}
	if (NextFlag_)
	{
		DrawGraph((static_cast<int>(NextPos_.x_) - 32), static_cast<int>(NextPos_.y_) - 32, lpImageMng.GetID(imagekey_)[AppTime_], true);
		DrawGraph(static_cast<int>(NextPos_.x_), static_cast<int>(NextPos_.y_), lpImageMng.GetID("image/Icon/juu.png")[0], true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, Alpha);
		DrawGraph(static_cast<int>(NextPos_.x_), static_cast<int>(NextPos_.y_), lpImageMng.GetID("image/Icon/juu.png")[0], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);
	}
	if (bulletFlag_)
	{
		DrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID("image/Icon/bullet.png")[0], true);
	}
	
}

void PlayerBullet::SetHit(bool hit)
{
	hit_ = hit;
}

int PlayerBullet::GetOutBullet(void)
{
	return outBullet_;
}
