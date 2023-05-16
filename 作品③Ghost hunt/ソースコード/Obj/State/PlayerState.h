#pragma once
#include <string>
#include <map>
#include <functional>
#include "../../Input/InputID.h"
#include "../../common/AnimMng.h"
#include "../Player.h"
#include "../../SceneMng.h"
#include "../../../tmx/rapidxml.hpp"
#include "../../../tmx/rapidxml_utils.hpp"
#include "../../common/Raycast.h"
#include "../../../_debug/_DebugConOut.h"
#include "../../../_debug/_DebugDispOut.h"

struct PlayerNotCheckKey2
{
	std::map<std::string, InputID> KeyTbl_ = {
	{"Left",InputID::Left},
	{"Right",InputID::Right},
	{"Top",InputID::Up},
	{"Bottom",InputID::Down},
	{"LeftN",InputID::Left},
	{"RightN",InputID::Right},
	{"TopN",InputID::Up},
	{"BottomN",InputID::Down}
	};

	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "state")
			{
				if (static_cast<std::string>(atr->value()) == "Cnt")
				{
					auto key1 = KeyTbl_.at(atr->next_attribute("key1")->value());
					auto key2 = KeyTbl_.at(atr->next_attribute("key2")->value());
					auto key3 = KeyTbl_.at(atr->next_attribute("key3")->value());
					auto key4 = KeyTbl_.at(atr->next_attribute("key4")->value());
					if (obj->controller_->GetCntData().at(key1)[static_cast<int>(Trg::Now)] && obj->controller_->GetCntData().at(key3)[static_cast<int>(Trg::Now)])
					{
						return false;
					}
					if (obj->controller_->GetCntData().at(key1)[static_cast<int>(Trg::Now)] && obj->controller_->GetCntData().at(key4)[static_cast<int>(Trg::Now)])
					{
						return false;
					}
					if (obj->controller_->GetCntData().at(key2)[static_cast<int>(Trg::Now)] && obj->controller_->GetCntData().at(key3)[static_cast<int>(Trg::Now)])
					{
						return false;
					}
					if (obj->controller_->GetCntData().at(key2)[static_cast<int>(Trg::Now)] && obj->controller_->GetCntData().at(key4)[static_cast<int>(Trg::Now)])
					{
						return false;
					}
				}
			}
		}
		return true;
	}
};

struct CheckKey
{
	std::map<std::string, InputID> KeyTbl_ = {
		{"Left",InputID::Left},
		{"Right",InputID::Right},
		{"Top",InputID::Up},
		{"Bottom",InputID::Down}
	};

	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "state")
			{
				if (static_cast<std::string>(atr->value()) == "Cnt")
				{
					atr = atr->next_attribute();
					auto checkKey = KeyTbl_.at(atr->value());
					return obj->controller_->GetCntData().at(checkKey) [ static_cast<int>(Trg::Now) ];
				}
			}
		}
		return false;
	}
};

struct CheckKey2
{
	std::map<std::string, InputID> KeyTbl_ = {
{"Left",InputID::Left},
{"Right",InputID::Right},
{"Top",InputID::Up},
{"Bottom",InputID::Down}
	};

	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			if (atrName == "state")
			{
				if (static_cast<std::string>(atr->value()) == "Cnt")
				{
					auto key1 = KeyTbl_.at(atr->next_attribute("key1")->value());
					auto key2 = KeyTbl_.at(atr->next_attribute("key2")->value());
					if (obj->controller_->GetCntData().at(key1)[static_cast<int>(Trg::Now)] && obj->controller_->GetCntData().at(key2)[static_cast<int>(Trg::Now)])
					{
						return true;
					}
				}
			}
		}
		return false;
	}
};

struct PlayerCheckCol2
{
	Raycast raycast_;
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto checkMove = [&](Vector2Dbl& moveVec) {
			Raycast::Ray ray = { Vector2Dbl{obj->pos_.x_,obj->pos_.y_} + Vector2Dbl{16,16},moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x_), static_cast<int>( ray.p.y_), static_cast<int>( ray.p.x_ + ray.vec.x_), static_cast<int>( ray.p.y_ + ray.vec.y_), 0x00ff00);
			for (auto col : tmxObj->GetCol2List())
			{
				//_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_), static_cast<int>( col.first.x_ + col.second.x_), static_cast<int>( col.first.y_ + col.second.y_), 0xff0000, false);
				if (raycast_.CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			return true;
		};
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
		return checkMove(MoveVec);
	}
};

struct PlayerCheckCol
{
	Raycast raycast_;
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto checkMove = [&](Vector2Dbl& moveVec) {
			Raycast::Ray ray = { Vector2Dbl{obj->pos_.x_,obj->pos_.y_} +Vector2Dbl{16,16},moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x_), static_cast<int>( ray.p.y_), static_cast<int>( ray.p.x_ + ray.vec.x_), static_cast<int>( ray.p.y_ + ray.vec.y_), 0x00ff00);
			for (auto col : tmxObj->GetColList())
			{
				//_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_), static_cast<int>( col.first.x_ + col.second.x_), static_cast<int>( col.first.y_ + col.second.y_), 0xff0000, false);
				if (raycast_.CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			return true;
		};
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
		return checkMove(MoveVec);
	}
};

struct PlayerCheckColKey
{
	Raycast raycast_;
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto checkMove = [&](Vector2Dbl& moveVec) {
			Raycast::Ray ray = { Vector2Dbl{obj->pos_.x_,obj->pos_.y_} + Vector2Dbl{16,16},moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x_), static_cast<int>( ray.p.y_), static_cast<int>( ray.p.x_ + ray.vec.x_), static_cast<int>( ray.p.y_ + ray.vec.y_), 0x00ff00);
			for (auto col : tmxObj->GetColList())
			{
				//_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_), static_cast<int>( col.first.x_ + col.second.x_), static_cast<int>( col.first.y_ + col.second.y_), 0xff0000, false);
				if (raycast_.CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			return true;
		};
		Vector2Dbl MoveVec;
		Vector2Dbl MoveVec2;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			// 幅
			if (atrName == "w")
			{
				MoveVec.x_ += atof(atr->value());
				atr = atr->next_attribute("speedX");
				MoveVec.x_ += atof(atr->value());
			}
			// 高さ
			if (atrName == "h")
			{
				MoveVec.y_ += atof(atr->value());
				atr = atr->next_attribute("speedY");
				MoveVec.y_ += atof(atr->value());
			}
		}
		return checkMove(MoveVec);
	}
};

struct PlayerCheckColKey2
{
	Raycast raycast_;
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		auto checkMove = [&](Vector2Dbl& moveVec) {
			Raycast::Ray ray = { Vector2Dbl{obj->pos_.x_,obj->pos_.y_} + Vector2Dbl{16,16},moveVec };
			//_dbgDrawLine(static_cast<int>(ray.p.x_), static_cast<int>( ray.p.y_), static_cast<int>( ray.p.x_ + ray.vec.x_), static_cast<int>( ray.p.y_ + ray.vec.y_), 0x00ff00);
			for (auto col : tmxObj->GetCol2List())
			{
				//_dbgDrawBox(static_cast<int>(col.first.x_), static_cast<int>(col.first.y_), static_cast<int>( col.first.x_ + col.second.x_), static_cast<int>( col.first.y_ + col.second.y_), 0xff0000, false);
				if (raycast_.CheckCollision(ray, col).first)
				{
					return false;
				}
			}
			return true;
		};
		Vector2Dbl MoveVec;
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			std::string atrName = atr->name();
			// 幅
			if (atrName == "w")
			{
				MoveVec.x_ += atof(atr->value());
				atr = atr->next_attribute("speedX");
				MoveVec.x_ += atof(atr->value());
			}
			// 高さ
			if (atrName == "h")
			{
				MoveVec.y_ += atof(atr->value());
				atr = atr->next_attribute("speedY");
				MoveVec.y_ += atof(atr->value());
			}
		}
		return checkMove(MoveVec);
	}
};

struct PlayerMove
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			double delta = obj->GetDelta();
 			std::string atrName = atr->name();
			if (atrName == "x")
			{
				double val = atof(atr->value());
				obj->pos_.x_ += val * delta;
			}
			if (atrName == "y")
			{
				double val = atof(atr->value());
				obj->pos_.y_ += val * delta;
			}
		}
		return true;
	}
};

struct PlayerMove2
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto atr = node->first_attribute(); atr != nullptr; atr = atr->next_attribute())
		{
			double delta = obj->GetDelta();
			std::string atrName = atr->name();
			if (atrName == "x")
			{
				double val = atof(atr->value());
				obj->pos_.x_ += val * delta;
			}
			if (atrName == "y")
			{
				double val = atof(atr->value());
				obj->pos_.y_ += val * delta;
			}
		}
		return true;
	}
};

struct PlayerSetAnime
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		std::string atrState = node->first_attribute("state")->value();
		if (dynamic_cast<Player*>(obj)->IsAlive())
		{
			if (dynamic_cast<Player*>(obj)->animeData_.state_ != atrState)
			{
				dynamic_cast<Player*>(obj)->animeData_ = lpAnimMng.SetAnime(dynamic_cast<Player*>(obj)->animeData_.objID_, atrState);
				return true;
			}
		}
		return false;
	}
};

// 関数オブジェクト
struct PlayerModuleNode
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto moduleNode = node->first_node(); moduleNode != nullptr;moduleNode = moduleNode->next_sibling())
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
		{"CheckKey2",CheckKey2()},
		{"CheckKey",CheckKey()},
		{"CheckCol",PlayerCheckCol()},
		{"CheckCol2",PlayerCheckCol2()},
		{"CheckColKey",PlayerCheckColKey()},
		{"CheckColKey2",PlayerCheckColKey2()},
		{"SetAnime",PlayerSetAnime()},
		{"Move",PlayerMove()},
		{"Move2",PlayerMove2()},
		{"NotCheckKey2",PlayerNotCheckKey2()},
	};
};
// 仮置きでノーマルマップ用のリストを作成
struct PlayerModuleNodeN
{
	bool operator()(Obj* obj, rapidxml::xml_node<>* node, TmxObj* tmxObj)
	{
		for (auto moduleNode = node->first_node(); moduleNode != nullptr;moduleNode = moduleNode->next_sibling())
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
		{"CheckKey2",CheckKey2()},
		{"CheckKey",CheckKey()},
		{"CheckCol",PlayerCheckCol()},
		{"CheckCol2",PlayerCheckCol2()},
		{"CheckColKey",PlayerCheckColKey()},
		{"CheckColKey2",PlayerCheckColKey2()},
		{"SetAnime",PlayerSetAnime()},
		{"Move",PlayerMove()},
		{"Move2",PlayerMove2()},
		{"NotCheckKey2",PlayerNotCheckKey2()},
	};
};