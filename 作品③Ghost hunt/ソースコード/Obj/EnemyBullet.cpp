#include "EnemyBullet.h"
#include "../../_debug/_DebugDispOut.h"
#include "../../_debug/_DebugConOut.h"

EnemyBullet::EnemyBullet()
{
	Init();

}

EnemyBullet::~EnemyBullet()
{
}

bool EnemyBullet::Init(void)
{
	pos_ = Vector2Dbl{ 500,200 };
	radius_ = 12;
	flag_ = false;
	Prad = 0;
	Erad = 0;
	bulletVel = Vector2Dbl{ 0.0 ,0.0 };
	//ChaseFlag = true;
	RedAlive = true;
	BlackAlive = true;
	dtime = 2.0;
	return true;
}

bool EnemyBullet::InitAlive(void)
{
	Alive_ = true;
	return true;
}

bool EnemyBullet::Init(CntType cntType)
{
	return false;
}

void EnemyBullet::Update(double delta, TmxObj& tmxObj, std::list<std::unique_ptr<Obj>>& objlist)
{
	delta_ = delta;
	for (auto& obj : objlist)
	{
		if (this->GetObjID() == obj.get()->GetObjID())
		{
			continue;
		}
		if (ObjID::Player == obj.get()->GetObjID())
		{
			PlayerPos_ = obj->GetPos();
			Prad = obj->GetRad();
		}
		if (ObjID::RedEnemy == obj.get()->GetObjID())
		{
			RedEnemyPos_ = obj->GetPos();
			Erad = obj->GetRad();
		}
		if (ObjID::BlackEnemy == obj.get()->GetObjID())
		{
			BlackEnemyPos_ = obj->GetPos();
			Erad = obj->GetRad();
		}
	}
	//if (ChaseFlag == true)
	//{
	//	if (geometry_.IsHit(pos_, EnemyPos_, radius_, Erad))
	//	{
	//		flag_ = false;
	//		Alive_ = false;
	//		Alive = true;
	//		ChaseFlag = false;
	//	}
	//}
	//else
	//{
		if (dtime >= 4)
		{
			if (RedAlive)
			{
				if (geometry_.IsHit(PlayerPos_, RedEnemyPos_, Prad, Erad * 2))
				{
					if (!flag_)
					{
						pos_ = RedEnemyPos_;
						flag_ = true;
						Alive_ = true;
					}
				}
				if (flag_)
				{
					bulletVel = Vector2Dbl((PlayerPos_ - pos_).Normalized() * (delta_ * 300));
					pos_ += bulletVel;
					if (geometry_.IsHit(pos_, PlayerPos_, radius_, Prad))
					{
						flag_ = false;
						dtime = 0;
					}
				}
				else
				{
					pos_ = RedEnemyPos_;
				}
			}
			else if (BlackAlive)
			{
				if (geometry_.IsHit(PlayerPos_, BlackEnemyPos_, Prad, Erad * 2))
				{
					if (!flag_)
					{
						pos_ = BlackEnemyPos_;
						flag_ = true;
						Alive_ = true;
					}
				}
				if (flag_)
				{
					bulletVel = Vector2Dbl((PlayerPos_ - pos_).Normalized() * (delta_ * 300));
					pos_ += bulletVel;
					if (geometry_.IsHit(pos_, PlayerPos_, radius_, Prad))
					{
						flag_ = false;
						dtime = 0;
					}
				}
				else
				{
					pos_ = BlackEnemyPos_;
				}
			}
		}
		else
		{
			Alive_ = false;
			dtime += delta_;
		}
	//}
	oldPos_ = pos_;
}

void EnemyBullet::Draw(void)
{
	if (flag_)
	{
		DrawCircle(static_cast<int>(pos_.x_) + 12, static_cast<int>(pos_.y_) + 12, radius_, 0xff00ff, true);
	}
}

bool EnemyBullet::AtackHit(int damage)
{
	return (PlayerHp -= damage) > 0;
}

