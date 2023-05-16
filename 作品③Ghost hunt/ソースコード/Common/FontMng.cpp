#include <DxLib.h>
#include "FontMng.h"

bool FontMng::DefaultFont(std::string str, Vector2Dbl pos, int size, int thick)
{
	int FontHandle;

	FontHandle = CreateFontToHandle(NULL, size, thick);

	DrawStringToHandle(static_cast<int>(pos.x_), static_cast<int>(pos.y_), str.c_str(), 0xffffff, FontHandle);

	return true;
}

bool FontMng::DefaultFont(std::string str, Vector2Dbl pos, int size, int thick, int color)
{
	int FontHandle;

	FontHandle = CreateFontToHandle(NULL, size, thick);

	DrawStringToHandle(static_cast<int>(pos.x_), static_cast<int>(pos.y_), str.c_str(), color, FontHandle);

	return true;
}

bool FontMng::ChangeFont(std::string FontName,std::string str, Vector2Dbl pos, int size, int thick)
{
	int FontHandle;

	FontHandle = CreateFontToHandle(FontName.c_str(), size, thick);

	DrawStringToHandle(static_cast<int>(pos.x_), static_cast<int>(pos.y_), str.c_str(), 0xffffff, FontHandle);

	DeleteFontToHandle(FontHandle);
	return true;
}

bool FontMng::ChangeFont(std::string FontName, std::string str, Vector2Dbl pos, int size, int thick, int color)
{
	int FontHandle;

	FontHandle = CreateFontToHandle(FontName.c_str(), size, thick);

	DrawStringToHandle(static_cast<int>(pos.x_), static_cast<int>(pos.y_), str.c_str(), color, FontHandle);

	DeleteFontToHandle(FontHandle);
	return true;
}

FontMng::FontMng()
{

}

FontMng::~FontMng()
{
}
