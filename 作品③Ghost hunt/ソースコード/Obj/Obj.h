#pragma once
#include <memory>
#include <string>
#include "../../Tmx/TmxObj.h"
#include "../Common/Geometry.h"
#include "../Common/Vector2.h"
#include "../Input/Input.h"

struct CheckKey;
struct CheckKey2;
struct PlayerNotCheckKey2;
struct PlayerCheckCol;
struct PlayerCheckCol2;
struct PlayerCheckColKey;
struct PlayerCheckColKey2;
struct PlayerMove;
struct PlayerMove2;
struct EnemyCheckCol;
struct EnemyPlayerCheckCol;
struct EnemyNotCheckCol;
struct NotEnemyCol;
struct EnemyCheckRandom;
struct EnemyMove;
struct EnemyCheckPlayer;
struct EnemyBulletCheckMove;
struct EnemyPCheckCol;
struct EnemyRandomCheckCol;
struct EnemyLoseSight;

enum class ObjID
{
	Player,
	RedEnemy,
	BlackEnemy,
	BossEnemy,
	PlayerBullet,
	EnemyBullet
};

class Obj
{
public:
	Obj();
	~Obj();
	// 後々こっちの方に変える
	virtual bool Init(CntType cntType) = 0;
	virtual bool Init(void) = 0;

	virtual void Update(double delta,TmxObj& tmxObj, std::list<std::unique_ptr<Obj>>& objlist) = 0;
	virtual void Draw(void);

	virtual bool AtackHit(int damage) = 0;

	virtual Vector2Dbl GetPos(void);
	virtual void SetRand(double rand);
	virtual double GetRand(void);
	virtual int GetRad(void);
	virtual double GetLost(void);
	virtual bool GetFlag(void);
	virtual double GetDelta(void);
	virtual bool GetAlive(void);
	virtual bool IsAlive(void);
	virtual bool GetPflag(void);
	virtual bool GetEflag(void);
	virtual bool GetPLost(void);

	virtual void SetWall(bool wall);
	virtual void SetPfalg(bool pflag);
	virtual void SetPlost(bool plost);
	virtual void SetAngle(double angle);

	virtual Vector2Dbl GetEnemyPos(void);
	virtual Vector2Dbl GetPlayerPos(void);
	virtual Vector2Dbl GetPlBulletPos(void);
	virtual Vector2Dbl GetEnBulletPos(void);

	virtual ObjID GetObjID(void) = 0;
private:
protected:
	Vector2Dbl pos_;	// 現在の座標

	Vector2Dbl oldPos_;	// 前の座標

	// プレイヤーが検知範囲に入っていたら
	bool Pflag;
	// エネミーの武器が検知範囲に入っていたら
	bool Eflag;
	// プレイヤーを見失ったら
	bool PLost;
	// エネミーの座標
	Vector2Dbl RedEnemyPos_;
	Vector2Dbl BlackEnemyPos_;
	// プレイヤーの座標
	Vector2Dbl PlayerPos_;
	// プレイヤーの武器の座標
	Vector2Dbl PlBulletPos_;
	// エネミーの武器の座標
	Vector2Dbl EnBulletPos_;
	// プレイヤーのhp
	int PlayerHp;
	// 移動速度
	double delta_;
	// 移動速度
	double speed_;

	// プレイヤーが生きていつかどうか
	bool Palive_;

	// どの方向に移動するか
	double rand_;

	// 見失って上、右、下、左と確認する
	double Lost_;
	// 円で当たり判定をするので半径を求める
	int radius_;
	// 後から消すが範囲に入った時に色を指定
	int color_;
	// 描画するかどうか
	bool flag_;
	// 生存しているか
	bool Alive_;
	// 死んでいたら
	bool alive_;
	// 敵とプレイヤーの間に壁があるかどうか
	bool Wall_;

	// 角度
	double Angle_;

	Geometry geometry_;

	std::unique_ptr<Input> controller_;
	friend PlayerNotCheckKey2;
	friend CheckKey;
	friend CheckKey2;
	friend PlayerCheckCol;
	friend PlayerCheckCol2;
	friend PlayerCheckColKey;
	friend PlayerCheckColKey2;
	friend PlayerMove;
	friend PlayerMove2;
	friend EnemyCheckCol;
	friend EnemyCheckRandom;
	friend EnemyCheckPlayer;
	friend EnemyMove;
	friend EnemyBulletCheckMove;
	friend EnemyNotCheckCol;
	friend EnemyPCheckCol;
	friend EnemyLoseSight;
	friend EnemyRandomCheckCol;
	friend EnemyPlayerCheckCol;
};

