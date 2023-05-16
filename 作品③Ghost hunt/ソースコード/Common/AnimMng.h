#pragma once
#include <map>
#include <string>
#include <list>
#include <array>

using AnimData = std::array<int, 2>;
using AnimNode = std::pair<int, std::list<AnimData>>;
using AnimItr = std::list<AnimData>::iterator;

constexpr int GraphHD = 0;
constexpr int InvLimit = 1;
constexpr int ColLeft = 2;
constexpr int ColTop = 3;
constexpr int ColRight = 4;
constexpr int ColBottom = 5;

struct AnimeData
{
	std::string objID_;
	std::string state_;
	AnimItr animItr_;
	int animCount_ =0;
	int animPlayerCount_ =0;
};

#define lpAnimMng AnimMng::GetInstance()

class AnimMng
{
public:
	static AnimMng& GetInstance()
	{
		static AnimMng s_instance;
		return s_instance;
	}
	bool LoadAnim(std::string filename);
	bool UpdateAnime(AnimeData& animeData);
	AnimeData SetAnime(std::string objID, std::string state);
private:
	AnimeData animeData_;
	std::map<std::string, AnimNode> animTbl_;
	AnimMng();
	~AnimMng();
};

