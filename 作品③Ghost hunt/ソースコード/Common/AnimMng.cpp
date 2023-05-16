#include <sstream>
#include "../../Tmx/rapidxml.hpp"
#include "../../Tmx/rapidxml_utils.hpp"
#include "ImageMng.h"
#include "Vector2.h"
#include "AnimMng.h"
#include "../../_debug/_DebugConOut.h"

bool AnimMng::LoadAnim(std::string filename)
{
	// 読み込み
	rapidxml::xml_document<> actDoc;
	rapidxml::file<> xmlFileName = filename.c_str();
	actDoc.parse<0>(xmlFileName.data());
	rapidxml::xml_node<>* actList = actDoc.first_node("actionList");
	if (actList == nullptr)
	{
		return false;
	}
	auto version = actList->first_attribute("version");
	std::string verStr = version->value();
	if (verStr != "1.0")
	{
		TRACE("アニメーション定義ファイルの非対応バージョン\n");
		return false;
	}
	std::string objID = actList->first_attribute("name")->value();

	for (auto action = actList->first_node("action"); action != nullptr; action = action->next_sibling())
	{
		auto source = action->first_attribute("source")->value();
		auto keyID = action->first_attribute("imageKey")->value();
		Vector2 divSize = { atoi(action->first_attribute("divSizeX")->value()),atoi(action->first_attribute("divSizeY")->value()) };
		Vector2 divCnt = { atoi(action->first_attribute("divCntX")->value()),atoi(action->first_attribute("divCntY")->value()) };

		lpImageMng.GetID(source, keyID, divSize, divCnt);

		std::string actName = objID + action->first_attribute("name")->value();
		animTbl_.try_emplace(actName);
		auto anime = action->first_node("anime");
		animTbl_[actName].first = atoi(anime->first_attribute("loop")->value());

		auto animData = anime->first_node();
		if (animData == nullptr)
		{
			TRACE("アニメーション定義ファイル異常\n");
			return false;
		}
		std::stringstream dataStream;
		dataStream << animData->value();
		std::string numStr;
		while (getline(dataStream, numStr, ','))
		{
			auto id = atoi(numStr.c_str());
			getline(dataStream, numStr, ',');
			auto frame = atoi(numStr.c_str());
			animTbl_[actName].second.emplace_back(AnimData{ id,frame });
			TRACE("%d,%d\n", id, frame);
		}

	}
	return true;
}

bool AnimMng::UpdateAnime(AnimeData& animeData)
{
	if (animeData.animCount_++ >= (*animeData.animItr_)[InvLimit])
	{
		animeData.animCount_ = 0;
		++animeData.animItr_;
		if (animeData.animItr_ == animTbl_[animeData.objID_ + animeData.state_].second.end()/*最終要素まで到達しているか*/)
		{
			animeData.animPlayerCount_++;
			if (animeData.animPlayerCount_ < animTbl_[animeData.objID_ + animeData.state_].first/*規定回数到達チェック*/ || animTbl_[animeData.objID_ + animeData.state_].first == -1/*無限回数か*/)
			{
				// ループ時
				animeData.animItr_ = animTbl_[animeData.objID_ + animeData.state_].second.begin();
			}
			else
			{
				// 再生終了
				animeData.animItr_ = --animTbl_[animeData.objID_ + animeData.state_].second.end();

			}
		}
	}
	return false;
}

AnimeData AnimMng::SetAnime(std::string objID, std::string state)
{
	return AnimeData{
		objID,
		state,
		animTbl_[objID + state].second.begin(),
		0,
		0
	};
}

AnimMng::AnimMng()
{
}

AnimMng::~AnimMng()
{
}
