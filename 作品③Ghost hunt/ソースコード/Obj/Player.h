#pragma once
#include <vector>
#include <string>
#include "../Common/AnimMng.h"
#include "../Common/Raycast.h"
#include "../Common/Geometry.h"
#include "Obj.h"

struct PlayerModuleNode;
struct PlayerModuleNodeN;
struct PlayerSetAnime;

class Player :
    public Obj
{
public:
    Player();
    Player(CntType cntType,Vector2Dbl Pos);
    ~Player();
    bool Init(void) override;
    bool Init(CntType cntType) override;
    void Update(double delta, TmxObj& tmxObj, std::list<std::unique_ptr<Obj>>& objlist) override;
    void Draw(void) override;
    bool AtackHit(int damage) override;
    std::string GetState(void);
    double GetInvincible(void);
private:

    AnimeData animeData_;
    AnimeData shaderData_;
    Raycast raycast_;

    ObjID GetObjID(void) override { return ObjID::Player; };
    std::vector<char> stateVec_;
    rapidxml::xml_node<>* stateNode_;
    rapidxml::xml_document<> stateDoc_;
    PlayerModuleNode* moduleNode_;
    std::vector<char> stateVecN_;
    rapidxml::xml_node<>* stateNodeN_;
    rapidxml::xml_document<> stateDocN_;
    PlayerModuleNodeN* moduleNodeN_;

    // 敵の大きさ
    int enemyRad;
    // 弾の大きさ
    int buRad;
    // 弾が生存しているかどうか
    bool PBalive;

    // プレイヤーのフラグ
    bool flag;
    double time_;
    double Time_;

    // シェーダ用変数
    int ps_;
    int cbuff_;
    float* threshold_;
    float angle_;
    // 残機を表示するかどうか
    bool Hpflag_;
    // 最初の残機を表示する時間
    double Hptime_;
    Vector2Dbl pos;
    // 無敵時間
    double InvTime_;
    bool Invincible_;
    // 待機時間
    double waitTime_;
    // 浮かび上がる感じでhpを表示
    double count_;
    double timelimit_;
    friend CheckKey;
    friend PlayerSetAnime;
    // 音楽
    int SoundHandle;
};

