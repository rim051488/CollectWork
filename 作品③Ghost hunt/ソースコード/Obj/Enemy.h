#pragma once
#include <vector>
#include "../Common/AnimMng.h"
#include "../Common/Geometry.h"
#include "../Common/Raycast.h"
#include "../Common/Collision.h"
#include "Obj.h"

// 長さ
#define ENEMY_RANGE (150.0)
// 角度
#define ENEMY_ANGLE (20.0)

struct EnemyModuleNode;
struct EnemySetAnime;
struct EnemyNonCheckPlayer;
struct EnemyNonCheckBullet;

enum class EnemyID
{
    Red,
    Black,
    Boss
};

class Enemy :
    public Obj
{
public:
    Enemy(void);
    ~Enemy();
    bool Init(CntType cntType) override;
    virtual bool Init(void) = 0;
    void Update(double delta, TmxObj& tmxObj, std::list<std::unique_ptr<Obj>>& objlist) override;
    //virtual void Draw(void);
    //virtual void EnemyDraw(void);
    void Draw(void);
    void EnemyDraw(void);
    bool AtackHit(int damage) override;
    // エネミーが死んだときの処理
    void DethEnemy(void);

    bool GetDeth(void);

    // ランダム移動
    void RandomMove(double delta);

    // 検知範囲をほかのクラスに渡す
    int GetDetection(void);
    // 待機時間を渡す
    double GetWaitTime_(void);

    // 敵が死んで速度を上げる
    double GetDethSpeed(void);

    virtual EnemyID GetEnemyID(void) = 0;

private:
    // エネミーが弾を追いかけるかどうか
    bool ChaseFlag_;

    // プレイヤーを見失ってからの時間
    double stime_;
    // ランダムで移動するため
    double randd_;

    // プレイヤーの当たり判定用の大きさ
    int playerRad_;
    // プレイヤーの弾の当たり判定用の大きさ
    int plBRad_;
    
    // 敵が死んでいくにつれてスピードが上がる
    double DethSpeed_;

    // エネミーの生きている数
    size_t AliveEnemy_;

    // プレイヤーの前の座標
    Vector2Dbl oldPpod_;
    // 壁に当たって何秒たったか
    double wTime_;

    // 弾が生きているかどうか
    bool Pbalive_;

    // 視野にプレイヤーが入っているかどうかのフラグ
    bool PEhit_;

    // エネミーの死亡演出
    bool deth_;
    double vanishDeth_;

    // 検知範囲
    int Detection_;
    // 敵が消えるフラグ
    bool vanishFlag_;
    // 敵が現れるフラグ
    bool appearFlag_;
    // 敵が現れたり、消えたりするときのカウント
    double count_;
    // 敵が現れたり、消えたりした時の時間指定
    double TimeLimit_;

    // プレイヤーが無敵時間内かどうか
    bool InvFlag_;

    // 出現してからプレイヤーを攻撃するまでの待機時間
    double WaitTime_;

    // プレイヤーが死んでいなかったら範囲外になっても追いかける
    bool PlayerFlag_;
    bool ChaseFlag;

    // ビックリマークの表示
    bool SurprisFlag_;
    double SurprisTime_;

    bool buflag_;
    // 視野の座標
    Raycast raycast_;

    double Time_;

    friend EnemySetAnime;
    friend EnemyNonCheckPlayer;
    friend EnemyNonCheckBullet;

protected:


    AnimeData animeData_;
    int hp_;
    int oldHp_;
    std::vector<char> stateVec_;
    rapidxml::xml_node<>* stateNode_;
    rapidxml::xml_document<> stateDoc_;
    EnemyModuleNode* moduleNode_;
    // 音楽
    int SoundHandle;


};

