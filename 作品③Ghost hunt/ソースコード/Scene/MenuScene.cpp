#include <DxLib.h>
#include "InfoScene.h"
#include "SelectScene.h"
#include "../Common/ImageMng.h"
#include "../Transition/CrossOver.h"
#include "MenuScene.h"

const static int Info_Y = 400;
const static int Select_Y = 450;
const static int Game_Y = 525;

typedef enum {
    eScene_Info,
    eScene_Select,
    eScene_Game,

    eScene_Num,
} eScene;

static int NowSelect = eScene_Game;

MenuScene::MenuScene()
{
    Init();
    DrawOwnScreen(0.0);
}

MenuScene::MenuScene(uniqueScene beforScene, int dethEnemy)
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
    dethEnemy_ = dethEnemy;
    beforScene_ = std::move(beforScene);
    NowSelect = eScene_Info;
    Alive_ = true;
    Blink_ = 0.0;
    delay = 0.25;
    second = 0.25;
    Init();
    DrawOwnScreen(0.0);
}

MenuScene::~MenuScene()
{
    DeleteSoundMem(SoundHandle);
    DeleteSoundMem(soundHandle1);
}

bool MenuScene::Init(void)
{
    SoundHandle = LoadSoundMem("bgm/select10.mp3");
    soundHandle1 = LoadSoundMem("bgm/se_maoudamashii_system37.mp3");
    Alive_ = true;
    return true;
}

uniqueScene MenuScene::Update(double delta, uniqueScene ownScene)
{
    if ((CheckHitKey(KEY_INPUT_DOWN) && delay <= second && input_ == 0) ||
        ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) && delay <= second && input_ == 1)) // 下キーが押されていたら
    {
        //PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
        ChangeNextPlayVolumeSoundMem(128, SoundHandle);
        PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
        NowSelect = (NowSelect + 1) % eScene_Num;
        second = 0.0;
        Blink_ = 0.0;
    }
    if ((CheckHitKey(KEY_INPUT_UP) && delay <= second && input_ == 0) ||
        ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) && delay <= second && input_ == 1)) // 上キーが押されていたら
    {
        //PlaySound("bgm/select10.mp3", DX_PLAYTYPE_BACK);
        ChangeNextPlayVolumeSoundMem(128, SoundHandle);
        PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
        NowSelect = (NowSelect + (eScene_Num - 1)) % eScene_Num;
        second = 0.0;
        Blink_ = 0.0;
    }

    second += delta;
    if ((CheckHitKey(KEY_INPUT_SPACE) && delay <= second && input_ == 0) ||
        ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) && delay <= second && input_ == 1))
    {
        //PlaySound("bgm/se_maoudamashii_system37.mp3", DX_PLAYTYPE_BACK);
        ChangeNextPlayVolumeSoundMem(128, soundHandle1);
        PlaySoundMem(soundHandle1, DX_PLAYTYPE_BACK);
        switch (NowSelect)
        {
        case eScene_Info:
            //return std::make_unique<CrossOver>(5.0, std::move(ownScene), std::make_unique<InfoScene>());
            second = 0.0;
            return std::make_unique<InfoScene>(std::move(ownScene));
            break;
        case eScene_Select:
            second = 0.0;
            return std::make_unique <CrossOver>(5.0, std::move(ownScene), std::make_unique<SelectScene>());
            break;
        case eScene_Game:
            second = 0.0;
            return std::move(beforScene_);
            break;
        default:
            break;
        }
    }
    DrawOwnScreen(delta);
    return ownScene;
}

void MenuScene::DrawOwnScreen(double delta)
{
    int y = 0;
    SetDrawScreen(screenID_);
    ClsDrawScreen();
    SetDrawBright(200, 200, 200);
    beforScene_->Draw(delta);
    SetDrawBright(255, 255, 255);
    // ここを画像に変える
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(150, 100, 874, 668, 0x696969, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawGraph(150,100, lpImageMng.GetID("image/Icon/waku.png")[0], true);

    DrawGraph(screenSize_.x_/4 + 20, 300, lpImageMng.GetID("image/Icon/PauseMenu.png")[0], true);

    Blink_ += delta * 2;
    if (Blink_ <= 2)
    {
        DrawGraph(874 / 2, Info_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
        DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
        DrawGraph(screenSize_.x_ /2 -60, Game_Y, lpImageMng.GetID("image/Icon/modoru.png")[0], true);
    }
    else
    {
        if (Select_ == 0)
        {
            if ((static_cast<int>(Blink_) % 2) == 1)
            {
                SetDrawBright(128, 128, 128);
                DrawGraph(874 / 2, Info_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
                SetDrawBright(255, 255, 255);
            }
            else
            {
                DrawGraph(874 / 2, Info_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
            }
            DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
            DrawGraph(screenSize_.x_ / 2 -60, Game_Y, lpImageMng.GetID("image/Icon/modoru.png")[0], true);
        }
        if (Select_ == 1)
        {
            DrawGraph(874 / 2, Info_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
            if ((static_cast<int>(Blink_) % 2) == 1)
            {
                SetDrawBright(128, 128, 128);
                DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
                SetDrawBright(255, 255, 255);
            }
            else
            {
                DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
            }
            DrawGraph(screenSize_.x_ / 2 -60, Game_Y, lpImageMng.GetID("image/Icon/modoru.png")[0], true);
        }
        if (Select_ == 2)
        {
            DrawGraph(874 / 2, Info_Y, lpImageMng.GetID("image/Icon/sousa.png")[0], true);
            DrawGraph(380, Select_Y, lpImageMng.GetID("image/Icon/select.png")[0], true);
            if ((static_cast<int>(Blink_) % 2) == 1)
            {
                SetDrawBright(128, 128, 128);
                DrawGraph(screenSize_.x_ / 2 - 60, Game_Y, lpImageMng.GetID("image/Icon/modoru.png")[0], true);
                SetDrawBright(255, 255, 255);
            }
            else
            {
                DrawGraph(screenSize_.x_ / 2 -60, Game_Y, lpImageMng.GetID("image/Icon/modoru.png")[0], true);
            }
        }
    }
    switch (NowSelect)
    {
    case eScene_Info:
        y = Info_Y;
        Select_ = 0;
        break;
    case eScene_Select:
        y = Select_Y;
        Select_ = 1;
        break;
    case eScene_Game:
        y = Game_Y;
        Select_ = 2;
        break;
    default:
        break;
    }
    DrawBox(350, y + 10, 375, y + 35, 0xffffff, false);
}

Scene MenuScene::GetSceneID(void)
{
    return beforScene_->GetSceneID();
}
