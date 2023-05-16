#pragma once
#include <string>
#include <map>
#include <functional>
#include "../../Input/InputID.h"
#include "../../common/AnimMng.h"
#include "../../Common/Geometry.h"
#include "../Enemy.h"
#include "../../SceneMng.h"
#include "../../../tmx/rapidxml.hpp"
#include "../../../tmx/rapidxml_utils.hpp"
#include "../../common/Raycast.h"
#include "../../../_debug/_DebugConOut.h"
#include "../../../_debug/_DebugDispOut.h"

struct EnemyCheckPlayer
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "angle1")
			{
				double angle1 = atof(atr->value());
				atr = atr->next_attribute();
				std::string atrName = atr->name();
				if (atrName == "angle2")
				{
					double angle2 = atof(atr->value());
					Vector2Dbl pos = (obj->GetPlayerPos() - obj->pos_);
					double rad = atan2(pos.y_, pos.x_);
					rad = Geometry::RadIn2PI(rad);
					double deg = Geometry::Rad2DegD(rad);
					if (deg <= 315.0 && deg > 45.0)
					{
						if (angle1 <= deg && angle2 >= deg)
						{
							if (obj->GetPflag())
							{
								return true;
							}
						}
					}
					else
					{
						if (angle1 >= 316)
						{
							if (angle1 <= deg)
							{
								if (obj->GetPflag())
								{
									return true;
								}
							}
						}
						if (angle2 <= 45)
						{
							if (angle2 > deg)
							{
								if (obj->GetPflag())
								{
									return true;
								}

							}
						}
					}
				}
			}
		}
		return false;
	}
};

struct EnemyCheckBullet
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "flag")
			{
				if (static_cast<std::string>(atr->value()) == "true")
				{
					if (obj->GetEflag())
					{
						return true;
					}
				}
			}
		}
		return false;
	}
};

struct EnemyNonCheckPlayer
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "flag")
			{
				if (static_cast<std::string>(atr->value()) == "false")
				{
					if (!obj->GetPflag())
					{
						if (!obj->GetPLost())
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
};

struct EnemyNonCheckBullet
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "flag")
			{
				if (static_cast<std::string>(atr->value()) == "false")
				{
					if (!obj->GetEflag())
					{
						return true;
					}
				}
			}
		}
		return false;
	}
};

struct EnemyCheckRandom
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			double rand_ = obj->GetRand();
			std::string atrName = atr->name();
			if (atrName == "state")
			{
				if (static_cast<std::string>(atr->value()) == "Cnt")
				{
					atr = atr->next_attribute();
					if (atof(atr->value()) == rand_)
					{
						atr = atr->next_attribute();
						obj->Angle_ = Geometry::Deg2RadD( atof(atr->value()));
						return true;
					}
				}
			}
		}
		return false;
	}
};

struct EnemyCheckCol
{
	Raycast raycast_;
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto checkMove = [&](Vector2Dbl& moveVec) {
			Raycast::Ray ray = { Vector2Dbl{obj->pos_.x_,obj->pos_.y_} + Vector2Dbl{16,16},moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x_), static_cast<int>(ray.p.y_), static_cast<int>(ray.p.x_ + ray.vec.x_), static_cast<int>(ray.p.y_ + ray.vec.y_), 0x00ff00);
			for (auto col : tmxObj->GetColList())
			{
				//_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_), static_cast<int>(col.first.x_ + col.second.x_), static_cast<int>(col.first.y_ + col.second.y_), 0xff0000, false);
				if (raycast_.CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			return true;
		};
		// プレイヤーを発見していない時にプレイヤーの武器があるときその付近をうろうろするようにした
		srand(static_cast<unsigned int>(time(NULL)));
		auto Pflag = obj->GetPflag();
		double rand_ = obj->GetRand();
		Vector2Dbl PBpos = obj->GetPlBulletPos();
		Vector2Dbl pos = (obj->GetPlayerPos() - obj->pos_);
		double rad = atan2(pos.y_, pos.x_);
		rad = Geometry::RadIn2PI(rad);
		double deg = Geometry::Rad2DegD(rad);
		Vector2Dbl MoveVec;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "w")
			{
				MoveVec.x_ += atof(atr->value());
				atr = atr->next_attribute();
				MoveVec.x_ += atof(atr->value());
			}
			if (atrName == "h")
			{
				MoveVec.y_ += atof(atr->value());
				atr = atr->next_attribute();
				MoveVec.y_ += atof(atr->value());
			}
		}
		if (checkMove(MoveVec))
		{
			if (Pflag)
			{
				obj->SetWall(false);
			}
			return true;
		}
		else
		{
			//Vector2Dbl DVec;
			//DVec += pos;
			// プレイヤーを発見していない時に壁があるかどうか
			if (!Pflag)
			{
				if (rand_ == 0 || rand_ == 1)
				{
					if (PBpos.y_ >= obj->pos_.y_)
					{
						rand_ = 3;
						obj->SetRand(rand_);
						return false;
					}
					if (PBpos.y_ <= obj->pos_.y_)
					{
						rand_ = 2;
						obj->SetRand(rand_);
						return false;
					}
				}
				if (rand_ == 2 || rand_ == 3)
				{
					if (PBpos.x_ >= obj->pos_.x_)
					{
						rand_ = 1;
						obj->SetRand(rand_);
						return false;
					}
					if (PBpos.x_ <= obj->pos_.x_)
					{
						rand_ = 0;
						obj->SetRand(rand_);
						return false;
					}
				}
			}
			// 発見時の時に壁があるかどうか
			if (Pflag)
			{
				obj->SetWall(true);
				return false;
			}
			return false;
		}
		//return checkMove(MoveVec);
	}
};

struct EnemyPlayerCheckCol
{
	Raycast raycast_;
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto checkMove = [&](Vector2Dbl& moveVec) {
			Raycast::Ray ray = { Vector2Dbl{obj->pos_.x_,obj->pos_.y_} + Vector2Dbl{16,16},moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x_), static_cast<int>(ray.p.y_), static_cast<int>(ray.p.x_ + ray.vec.x_), static_cast<int>(ray.p.y_ + ray.vec.y_), 0x00ff00);
			for (auto col : tmxObj->GetColList())
			{
				//_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_), static_cast<int>(col.first.x_ + col.second.x_), static_cast<int>(col.first.y_ + col.second.y_), 0xff0000, false);
				if (raycast_.CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			return true;
		};
		// プレイヤーを発見していなくても追いかける
		srand(static_cast<unsigned int>(time(NULL)));
		auto Pflag = obj->GetPflag();
		double rand_ = obj->GetRand();
		Vector2Dbl pos = (obj->GetPlayerPos() - obj->pos_);
		Vector2Dbl PlayerPos = obj->GetPlayerPos();
		double rad = atan2(pos.y_, pos.x_);
		rad = Geometry::RadIn2PI(rad);
		double deg = Geometry::Rad2DegD(rad);
		Vector2Dbl MoveVec;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "w")
			{
				MoveVec.x_ += atof(atr->value());
				atr = atr->next_attribute();
				MoveVec.x_ += atof(atr->value());
			}
			if (atrName == "h")
			{
				MoveVec.y_ += atof(atr->value());
				atr = atr->next_attribute();
				MoveVec.y_ += atof(atr->value());
			}
		}
		if (checkMove(MoveVec))
		{
			if (Pflag)
			{
				obj->SetWall(false);
			}
			return true;
		}
		else
		{
			//Vector2Dbl DVec;
			//DVec += pos;
			// プレイヤーを発見していない時に壁があるかどうか
			if (!Pflag)
			{
				if (rand_ == 0 || rand_ == 1)
				{
					if (PlayerPos.y_ >= obj->pos_.y_)
					{
						rand_ = 3;
						obj->SetRand(rand_);
						return false;
					}
					if (PlayerPos.y_ <= obj->pos_.y_)
					{
						rand_ = 2;
						obj->SetRand(rand_);
						return false;
					}
				}
				if (rand_ == 2 || rand_ == 3)
				{
					if (PlayerPos.x_ >= obj->pos_.x_)
					{
						rand_ = 1;
						obj->SetRand(rand_);
						return false;
					}
					if (PlayerPos.x_ <= obj->pos_.x_)
					{
						rand_ = 0;
						obj->SetRand(rand_);
						return false;
					}
				}
			}
			// 発見時の時に壁があるかどうか
			if (Pflag)
			{
				obj->SetWall(true);
				return false;
			}
			return false;
		}
		//return checkMove(MoveVec);
	}

};

struct EnemyRandomCheckCol
{
	Raycast raycast_;
	Geometry geometry_;
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto checkMove = [&](Vector2Dbl& moveVec) {
			Raycast::Ray ray = { Vector2Dbl{obj->pos_.x_,obj->pos_.y_} + Vector2Dbl{16,16},moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x_), static_cast<int>(ray.p.y_), static_cast<int>(ray.p.x_ + ray.vec.x_), static_cast<int>(ray.p.y_ + ray.vec.y_), 0x00ff00);
			for (auto col : tmxObj->GetColList())
			{
				//_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_), static_cast<int>(col.first.x_ + col.second.x_), static_cast<int>(col.first.y_ + col.second.y_), 0xff0000, false);
				if (raycast_.CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			return true;
		};
		srand(static_cast<unsigned int>(time(NULL)));
		auto Pflag = obj->GetPflag();
		double rand_ = obj->GetRand();
		Vector2Dbl MoveVec;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "w")
			{
				MoveVec.x_ += atof(atr->value());
				atr = atr->next_attribute();
				MoveVec.x_ += atof(atr->value());
			}
			if (atrName == "h")
			{
				MoveVec.y_ += atof(atr->value());
				atr = atr->next_attribute();
				MoveVec.y_ += atof(atr->value());
			}
		}
		if (checkMove(MoveVec))
		{
			return true;
		}
		else
		{
			if (!Pflag)
			{
				if (rand_ == 0 || rand_ == 1)
				{
					rand_ = rand() % 2;
					rand_ += 2;
					obj->SetRand(rand_);
					return false;
				}
				if (rand_ == 2 || rand_ == 3)
				{
					rand_ = rand() % 2;
					obj->SetRand(rand_);
					return false;
				}
			}
			return false;
		}
	}

};

struct EnemyNotCheckCol
{
	Raycast raycast_;
	Geometry geometry_;
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto checkMove = [&](Vector2Dbl& moveVec) {
			Raycast::Ray ray = { Vector2Dbl{obj->pos_.x_,obj->pos_.y_} + Vector2Dbl{16,16},moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x_), static_cast<int>(ray.p.y_), static_cast<int>(ray.p.x_ + ray.vec.x_), static_cast<int>(ray.p.y_ + ray.vec.y_), 0x00ff00);
			for (auto col : tmxObj->GetColList())
			{
				//_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_), static_cast<int>(col.first.x_ + col.second.x_), static_cast<int>(col.first.y_ + col.second.y_), 0xff0000, false);
				if (raycast_.CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			return true;
		};
		auto Pflag = obj->GetPflag();
		double rand_ = obj->GetRand();
		Vector2Dbl Ppos = obj->GetPlayerPos();
		Vector2Dbl Epos = obj->pos_;
		int rad = obj->radius_;
		Vector2Dbl pos = (obj->GetPlayerPos() - obj->pos_);
		Vector2Dbl MoveVec;
		MoveVec += pos;
		if ((geometry_.IsHit(Epos, Ppos, rad * 9, rad)) && !Pflag)
		{
			if (checkMove(MoveVec))
			{
				obj->SetWall(false);
			}
			else
			{
				obj->SetWall(true);
			}
		}
		return true;
	}

};


struct EnemyMove
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto Pflag = obj->GetPflag();
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			double delta = obj->GetDelta();
			std::string atrName = atr->name();
			double DethSpeed = 1;
			if (atrName == "x")
			{
				double val = atof(atr->value());
				atr = atr->next_attribute();
				atrName = atr->name();
				//auto flag = 1;
				//if (atrName == "DethFlag")
				//{
				//	flag = atoi(atr->value());
				//}
				//if (flag == 0)
				//{
				//}
				if (dynamic_cast<Enemy*>(obj)->GetEnemyID() == EnemyID::Boss)
				{
					DethSpeed = dynamic_cast<Enemy*>(obj)->GetDethSpeed();
				}
				obj->pos_.x_ += val * delta * DethSpeed;
			}
			if (atrName == "y")
			{
				double val = atof(atr->value());
				atr = atr->next_attribute();
				atrName = atr->name();
				//auto flag = 1;
				//if (atrName == "DethFlag")
				//{
				//	flag = atoi(atr->value());
				//}
				//double DethSpeed = 1;
				//if (flag == 0)
				//{
				//}
				if (dynamic_cast<Enemy*>(obj)->GetEnemyID() == EnemyID::Boss)
				{
					DethSpeed = dynamic_cast<Enemy*>(obj)->GetDethSpeed();
				}
				obj->pos_.y_ += val * delta * DethSpeed;
			}
			//if (Pflag)
			//{
			//	Vector2Dbl pos = (obj->GetPlayerPos() - obj->pos_).Normalized();
			//	double rad = atan2(pos.y_, pos.x_);
			//	obj->Angle_ = Geometry::RadIn2PI(rad);
			//}
		}
		return true;
	}
};


struct EnemyBulletCheckMove
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			double delta = obj->GetDelta();
			double val = 10.0;
			std::string atrName = atr->name();
			Vector2Dbl pos = (obj->GetEnBulletPos() - obj->pos_).Normalized();
			obj->pos_ += pos * val * delta;
			double rad = atan2(obj->pos_.y_, obj->pos_.x_);
			obj->Angle_ = Geometry::RadIn2PI(rad);
		}
		return true;
	}
};

struct EnemyLoseSight
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		double Losetime = atof(node->first_attribute("T")->value());
		double rad = atof(node->first_attribute("rad")->value());
		if (obj->GetPLost())
		{
			double Losttime = obj->GetLost();
			if (Losttime == Losetime)
			{

				obj->Angle_ = Geometry::Deg2RadD(rad);
				return true;
			}
		}
		return false;
	}
};

struct EnemySetAnime
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		std::string atrState = node->first_attribute("state")->value();
		if (dynamic_cast<Enemy*>(obj)->IsAlive())
		{
			if (dynamic_cast<Enemy*>(obj)->animeData_.state_ != atrState)
			{
				dynamic_cast<Enemy*>(obj)->animeData_ = lpAnimMng.SetAnime(dynamic_cast<Enemy*>(obj)->animeData_.objID_, atrState);
				return true;
			}
		}
		return false;
	}
};

// 関数オブジェクト
struct EnemyModuleNode
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto moduleNode = node->first_node(); moduleNode != nullptr; moduleNode = moduleNode->next_sibling())
		{
			std::string moduleName = moduleNode->first_attribute("name")->value();
			if (modul_.count(moduleName))
			{
				if (!modul_[moduleName](obj, moduleNode, tmxObj))
				{
					continue;
				}
				if (!(*this)(obj, moduleNode, tmxObj))
				{
					return false;
				}
			}
		}
		return true;
	}
	std::map<std::string, std::function<bool(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)>> modul_ = {
		{"CheckRandom",EnemyCheckRandom()},
		{"CheckCol",EnemyCheckCol()},
		{"PlayerCheckCol",EnemyPlayerCheckCol()},
		{"SetAnime",EnemySetAnime()},
		{"NonCheckPlayer",EnemyNonCheckPlayer()},
		{"NonCheckBullet",EnemyNonCheckBullet()},
		{"CheckPlayer",EnemyCheckPlayer()},
		{"EnemyMove",EnemyMove()},
		{"CheckBullet",EnemyCheckBullet()},
		{"BulletCheckMove",EnemyBulletCheckMove()},
		{"LoseTime",EnemyLoseSight()},
		{"NotCheckCol",EnemyNotCheckCol()},
		{"RandomCheckCol",EnemyRandomCheckCol()}
	};
};