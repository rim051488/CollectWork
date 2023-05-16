#include "Black2Enemy.h"
#include "State/EnemyState.h"
#include "../Common/ImageMng.h"

Black2Enemy::Black2Enemy()
{
    Init();
}

Black2Enemy::Black2Enemy(Vector2Dbl Pos)
{
    pos = Pos;
    Init();
}

Black2Enemy::~Black2Enemy()
{
}

bool Black2Enemy::Init(void)
{
	//読み込み
	lpAnimMng.LoadAnim("data/BlackEnemyAct.list");
	//pos_ = Vector2Dbl{ 500.0,50.0 };
	pos_ = pos;
	oldPos_ = pos_;
	// 読み込んだ内容にアニメーション
	animeData_ = std::move(lpAnimMng.SetAnime("enemy", "Bottom2"));
	rapidxml::file<> moduleListfile = "data/BlackEnemyModule.list";
	stateVec_ = moduleListfile.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("moduleList");
	moduleNode_ = new EnemyModuleNode();
	return true;
}
