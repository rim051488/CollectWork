#pragma once
#include <memory>
#include <list>
#include <map>
#include "BaseScene.h"
#include "../Common/Vector2.h"
#include "../Common/Geometry.h"
#include "../../Tmx/TmxObj.h"
#include "../Obj/Enemy.h"
#include "../Obj/Obj.h"
struct GetPos;
struct Getpos;
class GameScene :
    public BaseScene
{
public:
    GameScene();
    GameScene(std::string filename, std::string map, std::string pos);
    ~GameScene();
private:
    bool Init(void) override;
    bool Init(std::string filename);
    uniqueScene Update(double delta, uniqueScene ownScene) override;
    void DrawOwnScreen(double delta) override;
    Scene GetSceneID(void) override { return Scene::Game; };

    // 簡易的なカウントダウン用の変数(デルタも使うのでdoubleにしておく)
    double time_;
    double Endtime_;
    // 制限時間
    double timeLimit_;
    // プレイヤーが生きているかどうか
    bool PlayerAlive_;
    // キーが連続して押されないようにディレイをかける
    double delay;
    double second;
    double count_;
    int timelimit;
    // 弾の残弾数
    int outBullet_;
    // マップの情報とそのマップに使っている画像を渡せるようにしておく
    std::string fileName_;
    std::string map_;
    // objの座標をファイルから読み取り
    std::string objPos_;
    // Objをlist化する
    std::list<std::unique_ptr<Obj>> objList_;
    // 敵の座標を違う場所にもう2つ作る
    std::list<std::unique_ptr<Obj>> EnemyList_;
    std::list<std::unique_ptr<Obj>> enemyList_;
    // ボスのobj
    std::list<std::unique_ptr<Obj>> bossList_;
    bool Bossflag_;
    double BossTime_;
    bool bossdeth;
    bool bossApp_;
    size_t objsize;
    // 敵が死んだ数
    int dethEnemy_;
    //std::map<std::string, std::unique_ptr<Obj>> objListMap_;
    CntType cntType_;
    Geometry geometry;
    TmxObj tmxObj_;
    std::vector<char> stateVec_;
    rapidxml::xml_node<>* stateNode_;
    rapidxml::xml_document<> stateDoc_;
    GetPos* moduleNode_;
    // キーボードかパッドか
    int input_;
    // 音楽
    int SoundHandle;
    int soundHandle1;
};

