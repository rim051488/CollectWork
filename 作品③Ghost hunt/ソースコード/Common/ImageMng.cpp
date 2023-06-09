#include <DxLib.h>
#include "ImageMng.h"
#include "../../_debug/_DebugConOut.h"

const VecInt& ImageMng::GetID(std::string key)
{
    // 画像読み込んでなかったら
    if (imageMap_.count(key) == 0)
    {
        TRACE("画像の読み込み\n");

        imageMap_[key].resize(1);
        imageMap_[key][0] = LoadGraph(key.c_str());
    }
    return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key)
{
    // 画像読み込んでなかったら
    if (imageMap_.count(key) == 0)
    {
        TRACE("画像の読み込み\n");

        imageMap_[key].resize(1);
        imageMap_[key][0] = LoadGraph(f_name.c_str());
    }
    return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt)
{
    if (imageMap_.count(key) == 0)
    {
        imageMap_[key].resize(divCnt.x_ * divCnt.y_);

        if (LoadDivGraph(f_name.c_str(), divCnt.x_ * divCnt.y_, divCnt.x_, divCnt.y_, divSize.x_, divSize.y_, &imageMap_[key][0], true) == -1)
        {
            TRACE("画像の読み込み失敗\n", f_name.c_str());
        }
    }
    return imageMap_[key];
}

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}
