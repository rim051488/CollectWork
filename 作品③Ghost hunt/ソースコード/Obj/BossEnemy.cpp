#include "BossEnemy.h"
#include "State/EnemyState.h"
#include "../Common/ImageMng.h"

BossEnemy::BossEnemy()
{
    Init();
}

BossEnemy::BossEnemy(Vector2Dbl Pos)
{
    pos = Pos;
	SoundHandle = LoadSoundMem("bgm/sibou.mp3");
    Init();
}

BossEnemy::~BossEnemy()
{
}

bool BossEnemy::Init(void)
{
	//読み込み
	lpAnimMng.LoadAnim("data/BossEnemyAct.list");
	//pos_ = Vector2Dbl{ 500.0,50.0 };
	pos_ = pos;
	oldPos_ = pos_;
	hp_ = 3;
	oldHp_ = hp_;
	// 読み込んだ内容にアニメーション
	animeData_ = std::move(lpAnimMng.SetAnime("enemy", "Bottom3"));
	rapidxml::file<> moduleListfile = "data/BossEnemyModule.list";
	stateVec_ = moduleListfile.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("moduleList");
	moduleNode_ = new EnemyModuleNode();
	return true;
}
