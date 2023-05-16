#include "InfoScene.h"
#include "TitleScene.h"
#include "../Common/ImageMng.h"
#include "../Transition/CrossOver.h"

typedef enum {
    INFO1,
    INFO2,
    INFO3,

    NUM
} Info;

static int nowInfo = INFO1;

InfoScene::InfoScene()
{
    info_ = 0.0;
    infoKinds_ = 0;
    Init();
    DrawOwnScreen(0.0);
}

InfoScene::InfoScene(uniqueScene beforScene)
{
    if (GetJoypadNum())
    {
        //controller_ = std::make_unique<Pad>(1);
        input_ = 1;
    }
    else
    {
        //controller_ = std::make_unique<Keyboard>();
        input_ = 0;
    }
    beforScene_ = std::move(beforScene);
    info_ = 0.0;
    infoKinds_ = 0;
    Init();
    DrawOwnScreen(0.0);

}

InfoScene::~InfoScene()
{
    DeleteSoundMem(SoundHandle);
    DeleteSoundMem(soundHandle1);
}

bool InfoScene::Init(void)
{
    Alive_ = true;
    delay = 0.25;
    second = 0.25;
    delayTime_ = 0.0;
    SoundHandle = LoadSoundMem("bgm/select10.mp3");
    soundHandle1 = LoadSoundMem("bgm/se_maoudamashii_system37.mp3");
    return true;
}

uniqueScene InfoScene::Update(double delta, uniqueScene ownScene)
{
    delayTime_ += delta;
    if ((CheckHitKey(KEY_INPUT_SPACE) && delayTime_ >= 2)||
        ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) && delayTime_ >= 2))
    {
        delayTime_ = 0.0;
        return std::move(beforScene_);
    }
    if ((CheckHitKey(KEY_INPUT_RIGHT) && delay <= second) ||
        ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) && delay <= second)) // 上キーが押されていたら
    {
        if (nowInfo < NUM -1)
        {
            nowInfo = (nowInfo + 1);
        }
        second = 0.0;
    }
    if ((CheckHitKey(KEY_INPUT_LEFT) && delay <= second) ||
        ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) && delay <= second)) // 下キーが押されていたら
    {
        if (nowInfo > INFO1)
        {
            nowInfo = (nowInfo - 1);
        }
        second = 0.0;
    }
    second += delta;
    DrawOwnScreen(delta);
    return ownScene;
}

void InfoScene::DrawOwnScreen(double delta)
{
    SetDrawScreen(screenID_);
    ClsDrawScreen();
    switch (nowInfo)
    {
    case INFO1:
        DrawGraph(0, 0, lpImageMng.GetID("image/Icon/INFO1.png")[0], true);
        break;
    case INFO2:
        DrawGraph(0, 0, lpImageMng.GetID("image/Icon/INFO2.png")[0], true);
        break;
    case INFO3:
        DrawGraph(0, 0, lpImageMng.GetID("image/Icon/INFO3.png")[0], true);
        break;
    default:
        break;
    }
}

Scene InfoScene::GetSceneID(void)
{
    return beforScene_->GetSceneID();
}


