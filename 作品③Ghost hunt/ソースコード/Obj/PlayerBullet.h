#pragma once
#include <string>
#include "Obj.h"
#include "../../Tmx/TmxObj.h"
#include "../Common/Raycast.h"
#include "../Common/Geometry.h"
class PlayerBullet :
	public Obj
{
public:
    PlayerBullet();
    PlayerBullet(Vector2Dbl Pos, Vector2Dbl Pos2, Vector2Dbl Pos3);
    ~PlayerBullet();
    bool Init(void) override;
    bool Init(CntType cntType) override;
    // 武器を取得すると次の武器の場所がわかるようにする
    bool SetNextPos(void);
    // Nextにある座標を今の座標に切り替える
    bool Setpos(void);
    void Update(double delta, TmxObj& tmxObj, std::list<std::unique_ptr<Obj>>& objlist) override;
    void Draw(void) override;
    void SetHit(bool hit);
    int GetOutBullet(void);
    bool AtackHit(int damage) override;
private:
    ObjID GetObjID(void) override { return ObjID::PlayerBullet; };
    int Prad;
    int Erad;
    bool REflag_;
    bool BEflag_;
    // 敵に弾がヒットしたとき
    bool hit_;
    // 敵に弾が当たった場合
    bool alive;
    // 残弾数
    int outBullet_;
    Vector2Dbl bulletVel;
    // エネミーが弾を追いかけるかどうか
    bool ChaseFlag;
    bool bulletFlag_;
    bool outFlag_;
    // 出現する位置
    Vector2Dbl pos;
    Vector2Dbl pos2;
    Vector2Dbl pos3;
    // 次の出現する位置を保存
    Vector2Dbl NextPos_;
    int NextRand_;
    bool NextFlag_;
    // 2体目の適用
    Vector2Dbl enemypos_;
    Vector2Dbl MoveVec;
    bool enemyFlag_;
    // 弾が消滅するタイミング
    double dtime;
    std::string state_;
    Raycast raycast_;
    TmxObj* tmxobj;
    // 武器を目立たせる処理
    double count_;
    int timelimit;
    bool HighlightFlag_;
    // 出現演出
    std::string imagekey_;
    double AppTime_;
    // プレイヤーのフラグ
    bool playerFlag_;
    // キーボードかパッドか
    int input_;
    // 音楽
    int SoundHandle;
};

