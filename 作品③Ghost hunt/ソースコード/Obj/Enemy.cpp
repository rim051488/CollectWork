#include <DxLib.h>
#include <ctime>
#include "PlayerBullet.h"
#include "Player.h"
#include "State/EnemyState.h"
#include "../Input/Keyboard.h"
#include "../Input/Pad.h"
#include "../Common/ImageMng.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
#include "Enemy.h"

Enemy::Enemy(void)
{
	Angle_ = geometry_.Deg2RadD(90.0);
	color_ = 0xffffff;
	radius_ = 16;
	flag_ = true;
	ChaseFlag_ = true;
	Alive_ = true;
	Detection_ = radius_ * 2;
	srand(static_cast<unsigned int>(time(NULL)));
	playerRad_ = 0;
	plBRad_ = 0;
	PlayerHp = 1;
	stime_ = 0.0;
	Pflag = false;
	Eflag = false;
	Pbalive_ = false;
	PlayerFlag_ = true;
	ChaseFlag_ = true;
	PLost = false;
	Lost_ = 0;
	Time_ = 0.0;
	wTime_ = 0.0;
	count_ = 0.0;
	TimeLimit_ = 2;
	alive_ = true;
	deth_ = false;
	vanishDeth_ = 0.0;
	vanishFlag_ = false;
	appearFlag_ = false;
	SurprisFlag_ = false;
	SurprisTime_ = 0.0;
	AliveEnemy_ = 0;
	DethSpeed_ = 1;
	WaitTime_ = 0;
}

Enemy::~Enemy()
{
	DeleteSoundMem(SoundHandle);
}


//bool Enemy::Init(void)
//{
//	 //読み込み
//	lpAnimMng.LoadAnim("data/EnemyAct.list");
//	oldPos_ = pos_;
//	// 読み込んだ内容にアニメーション
//	animeData_ = std::move(lpAnimMng.SetAnime("enemy", "Bottom1"));
//	rapidxml::file<> moduleListfile = "data/EnemyModule.list";
//	stateVec_ = moduleListfile.vecData();
//	stateDoc_.parse<0>(stateVec_.data());
//	stateNode_ = stateDoc_.first_node("moduleList");
//	moduleNode_ = new EnemyModuleNode();
//	return true;
//}

bool Enemy::Init(CntType cntType)
{
	rapidxml::file<> moduleListfile = "data/EnemyModule.list";
	stateVec_ = moduleListfile.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("moduleList");
	moduleNode_ = new EnemyModuleNode();
	return true;
}

void Enemy::Update(double delta, TmxObj& tmxObj, std::list<std::unique_ptr<Obj>>& objlist)
{
	delta_ = delta;

	if (oldHp_ != hp_)
	{
		DethSpeed_ += 0.5;
		
		oldHp_ = hp_;
	}
	if (!deth_)
	{
		if (alive_)
		{
			for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
			{
				(*moduleNode_)(this, node, &tmxObj);
			}

			lpAnimMng.UpdateAnime(animeData_);
		}
	}
	oldPos_ = pos_;
	for (auto& obj : objlist)
	{
		if (this->GetObjID() == obj.get()->GetObjID())
		{
			continue;
		}
		if (ObjID::Player == obj.get()->GetObjID())
		{
			PlayerPos_ = obj.get()->GetPos();
			playerRad_ = obj.get()->GetRad();
			PlayerFlag_ = obj.get()->GetFlag();
			Palive_ = obj.get()->GetAlive();
			InvFlag_ = dynamic_cast<Player*>(obj.get())->GetInvincible();
		}
		if (ObjID::PlayerBullet == obj.get()->GetObjID())
		{
			PlBulletPos_ = obj.get()->GetPos();
			plBRad_ = obj.get()->GetRad();
			Pbalive_ = obj.get()->GetAlive();
			// プレイヤーの弾との当たり判定
			if (Pbalive_)
			{
				if (geometry_.IsHit(pos_, PlBulletPos_, radius_, plBRad_))
				{
					//flag_ = false;
					if (!deth_)
					{
						//PlaySound("bgm/sibou.mp3", DX_PLAYTYPE_BACK);
						ChangeNextPlayVolumeSoundMem(128, SoundHandle);
						PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
						deth_ = true;
						hp_--;
						dynamic_cast<PlayerBullet*>(obj.get())->SetHit(false);
					}
				}
			}
		}
	}
	if (!deth_)
	{
		if (WaitTime_ >= 2)
		{
			// 視線にプレイヤーが入ったかどうかの処理
			Vector2Dbl diff = PlayerPos_ - pos_;
			// diffでとった方向ベクトルを距離にする
			double distance = std::pow(diff.x_, 2.0) + std::pow(diff.y_, 2.0);
			// distanceでとった距離と視線の距離の2乗を比べる
			if (!InvFlag_)
			{
				if (distance < std::pow(ENEMY_RANGE, 2.0))
				{
					double rad = atan2(diff.y_, diff.x_);
					double viewRad = rad - Angle_;
					double viewDeg = geometry_.DegIn360(geometry_.Rad2DegD(viewRad));
					if (viewDeg <= 30.0 || viewDeg >= 360.0 - 30.0)
					{
						if (!Wall_)
						{
							if (SurprisTime_ == 0.0)
							{
								SurprisTime_ += delta;
							SurprisFlag_ = true;
							}
							else
							{
								SurprisTime_ += delta;
								if (SurprisTime_ >= 1)
								{
									SurprisFlag_ = true;
								}
								Pflag = true;
								color_ = 0xff0000;
								wTime_ = 0.0;
								stime_ = 0.0;
								//if (PLost)
								//{
								//	Pflag = true;
								//	PLost = false;
								//	Lost_ = 0;
								//	stime_ = 0;
								//}
								if (PLost)
								{
									PLost = false;
									Lost_ = 0;
								}
							}
						}
						if (wTime_ <= 1.0)
						{
							oldPpod_ = PlayerPos_;
						}
					}
					else if (geometry_.IsHit(pos_, PlayerPos_, radius_ * 5, playerRad_))
					{
						// プレイヤーが検知範囲内にいるかどうか
						if (!Wall_)
						{
							if (ChaseFlag_)
							{
								if (SurprisTime_ == 0.0)
								{
									SurprisTime_ += delta;
								SurprisFlag_ = true;
								}
								else
								{
									SurprisTime_ += delta;
									if (SurprisTime_ >= 1)
									{
										SurprisFlag_ = false;
									}
									Pflag = true;
									wTime_ = 0.0;
									stime_ = 0.0;
									if (PLost)
									{
										PLost = false;
										Lost_ = 0;
									}
								}
							}
							else if (!geometry_.IsHit(pos_, PlayerPos_, Detection_, playerRad_))
							{
								if (SurprisTime_ == 0.0)
								{
									SurprisTime_ += delta;
								SurprisFlag_ = true;
								}
								else
								{
									SurprisTime_ += delta;
									if (SurprisTime_ >= 1.0)
									{
										SurprisFlag_ = false;
									}
									Pflag = true;
									stime_ = 0.0;
									wTime_ = 0.0;
									if (PLost)
									{
										PLost = false;
										Lost_ = 0;
									}
								}
							}
							if (wTime_ <= 1.0)
							{
								oldPpod_ = PlayerPos_;
							}
						}
					}
				}
				else
				{
					color_ = 0xffffff;
					if (wTime_ <= 1.0)
					{
						oldPpod_ = PlayerPos_;
					}
					if (Pflag)
					{
						stime_ += delta_;
						if (stime_ >= 3)
						{
							stime_ = 0;
							Pflag = false;
							PLost = true;
							color_ = 0xffffff;
						}

					}
					else if (PLost == true)
					{
						stime_ += delta_;
						if (Lost_ == 0 && stime_ >= 0.5)
						{
							stime_ = 0;
							Lost_ = 1;
						}
						if (Lost_ == 1 && stime_ >= 0.5)
						{
							stime_ = 0;
							Lost_ = 2;
						}
						if (Lost_ == 2 && stime_ >= 0.5)
						{
							stime_ = 0;
							Lost_ = 3;
						}
						if (Lost_ == 3 && stime_ >= 0.5)
						{
							stime_ = 0;
							Lost_ = 0;
							PLost = false;
							Wall_ = false;
						}
					}
					else
					{
						Pflag = false;
						SurprisTime_ = 0.0;
					}
				}
			}
		}
		if (Pflag && Wall_)
		{
			vanishFlag_ = true;
		}
		if (Pflag && !Wall_)
		{
			vanishFlag_ = false;
			appearFlag_ = false;
			count_ = 0.0;
			wTime_ = 0.0;
		}

		if (geometry_.IsHit(pos_, PlayerPos_, radius_, playerRad_) && PlayerFlag_)
		{
			SurprisFlag_ = false;
			Pflag = false;
			PLost = true;
		}

		if (SurprisFlag_)
		{
			SurprisTime_ += delta;
		}
		if (SurprisTime_ >= 1)
		{
			SurprisTime_ = 0.0;
			SurprisFlag_ = false;
		}
	}
	else
	{
		PLost = false;
		Wall_ = false;
		Pflag = false;
		SurprisFlag_ = false;
		vanishFlag_ = false;
		appearFlag_ = false;
		// 死亡時に消える演出を
		vanishDeth_ += delta;
		if (vanishDeth_ > 1 && hp_ == 0)
		{
			flag_ = false;
		}
	}
	if (!flag_ )
	{
		Alive_ = false;
		alive_ = false;
	}
	else if (hp_ != 0)
	{
		deth_ = false;
	}
	// ワープするときに消えるようにして移動するようにする
	if (vanishFlag_)
	{
		wTime_ += delta_;
		count_ += delta_;
		if (count_ > TimeLimit_)
		{
			vanishFlag_ = false;
			appearFlag_ = true;
			pos_ = oldPpod_;
			wTime_ = 0.0;
			count_ = 0.0;
		}
	}
	if (appearFlag_)
	{
		count_ += delta_;
		if (count_ > TimeLimit_)
		{
			count_ = 0.0;
			appearFlag_ = false;
		}
	}

	WaitTime_ += delta;
}

void Enemy::Draw(void)
{
	auto Alpha = static_cast<int>(255 * count_ / TimeLimit_);
	// 死亡時用
	auto alpha = static_cast<int>(255 * vanishDeth_);
	if (vanishFlag_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - Alpha);
		EnemyDraw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (appearFlag_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
		EnemyDraw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (deth_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - alpha);
		EnemyDraw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
	}
	else if(!vanishFlag_ && !appearFlag_)
	{
		EnemyDraw();
	}
}

void Enemy::EnemyDraw(void)
{
	if (flag_)
	{
		DrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID(animeData_.state_)[(*animeData_.animItr_)[GraphHD]], true);
	}
	if (SurprisFlag_)
	{
		DrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_) - 32, lpImageMng.GetID("image/Icon/o.png")[0], true);
	}
}

bool Enemy::AtackHit(int damage)
{
	return (PlayerHp -= damage) > 0;
}

void Enemy::DethEnemy(void)
{
	pos_ = Vector2Dbl{ static_cast<double>(rand() % 1024) ,static_cast<double>(rand() % 768) };
}

bool Enemy::GetDeth(void)
{
	return deth_;
}

void Enemy::RandomMove(double delta)
{
	speed_ = delta * 200.0;
	color_ = 0xff0000;
}

//bool Enemy::Discover(double delta, Vector2Dbl plPos)
//{
//	// 視線に入ったかどうかを確認する処理
//	Vector2Dbl diff = plPos - pos_;
//
//	// diffでとった方向ベクトルを距離にする
//	double distance = std::pow(diff.x_, 2.0) + std::pow(diff.y_, 2.0);
//	// distanceでとった距離と視線の距離の2乗を比べる
//	if (distance < std::pow(150, 2.0))
//	{
//		double rad = atan2(diff.y_, diff.x_);
//		double Rad =Angle_ - rad;
//		double Deg = geometry.DegIn360(geometry.Rad2DegD(Rad));
//		if (Deg >= 20.0 || Deg <= 360.0 - 20.0)
//		{
//			color_ = 0x0000ff;
//			return true;
//		}
//	}
//
//	return false;
//}

int Enemy::GetDetection(void)
{
	return Detection_;
}

double Enemy::GetWaitTime_(void)
{
	return WaitTime_;
}

double Enemy::GetDethSpeed(void)
{
	return DethSpeed_;
}

