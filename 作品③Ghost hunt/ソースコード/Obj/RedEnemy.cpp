#include "RedEnemy.h"
#include "State/EnemyState.h"
#include "../Common/ImageMng.h"

RedEnemy::RedEnemy()
{
	Init();
}

RedEnemy::RedEnemy(Vector2Dbl Pos)
{
	pos = Pos;
	SoundHandle = LoadSoundMem("bgm/sibou.mp3");
	Init();
}

RedEnemy::~RedEnemy()
{
}

bool RedEnemy::Init(void)
{
	//読み込み
	lpAnimMng.LoadAnim("data/EnemyAct.list");
	//pos_ = Vector2Dbl{ 450.0,500.0 };
	pos_ = pos;
	oldPos_ = pos_;
	hp_ = 1;
	oldHp_ = hp_;
	// 読み込んだ内容にアニメーション
	animeData_ = std::move(lpAnimMng.SetAnime("enemy", "Bottom1"));
	rapidxml::file<> moduleListfile = "data/EnemyModule.list";
	stateVec_ = moduleListfile.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("moduleList");
	moduleNode_ = new EnemyModuleNode();
	return true;
}

//void RedEnemy::Draw(void)
//{
//	auto Alpha = static_cast<int>(255 * count_ / TimeLimit_);
//	if (vanishFlag_)
//	{
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - Alpha);
//		EnemyDraw();
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//	}
//	else if (appearFlag_)
//	{
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
//		EnemyDraw();
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//	}
//	if (!vanishFlag_ && !appearFlag_)
//	{
//		EnemyDraw();
//	}
//}
//
//void RedEnemy::EnemyDraw(void)
//{
//	double viewRad = geometry_.Deg2RadD(ENEMY_ANGLE);
//	double x1 = cos(Angle_);
//	double y1 = sin(Angle_);
//	double x2 = cos(Angle_ - viewRad);
//	double y2 = sin(Angle_ - viewRad);
//	double x3 = cos(Angle_ + viewRad);
//	double y3 = sin(Angle_ + viewRad);
//	Vector2Dbl pos0_ = pos_ + Vector2Dbl{ 16,16 };
//	// 正面の座標
//	Vector2Dbl pos1_ = pos_ + Vector2Dbl{ 16,16 };
//	pos1_.x_ += (x1 * ENEMY_RANGE);
//	pos1_.y_ += (y1 * ENEMY_RANGE);
//	// 左の座標
//	Vector2Dbl pos2_ = pos_ + Vector2Dbl{ 16,16 };
//	pos2_.x_ += (x2 * ENEMY_RANGE);
//	pos2_.y_ += (y2 * ENEMY_RANGE);
//	// 右の座標
//	Vector2Dbl pos3_ = pos_ + Vector2Dbl{ 16,16 };
//	pos3_.x_ += (x3 * ENEMY_RANGE);
//	pos3_.y_ += (y3 * ENEMY_RANGE);
//	if (flag_)
//	{
//		DrawCircle(static_cast<int>(pos_.x_) + 16, static_cast<int>(pos_.y_) + 16, Detection_, 0xffff00, false);
//		DrawCircle(static_cast<int>(pos_.x_) + 16, static_cast<int>(pos_.y_) + 16, radius_ * 5, 0xff00ff, false);
//
//		//視野の描画
//	   //DrawLine(static_cast<int>(pos0_.x_), static_cast<int>( pos0_.y_), static_cast<int>( pos1_.x_), static_cast<int>( pos1_.y_), 0xffffff);
//		DrawTriangle(static_cast<int>(pos0_.x_), static_cast<int>(pos0_.y_), static_cast<int>(pos1_.x_), static_cast<int> (pos1_.y_), static_cast<int>(pos2_.x_), static_cast<int>(pos2_.y_), color_, false);
//		DrawTriangle(static_cast<int>(pos0_.x_), static_cast<int>(pos0_.y_), static_cast<int>(pos1_.x_), static_cast<int> (pos1_.y_), static_cast<int>(pos3_.x_), static_cast<int>(pos3_.y_), color_, false);
//		// 敵の描画
//		DrawGraph(static_cast<int>(pos_.x_), static_cast<int>(pos_.y_), lpImageMng.GetID(animeData_.state_)[(*animeData_.animItr_)[GraphHD]], true);
//	}
//}
