#pragma once
#include "../Common/Vector2.h"
#include <string>

#define lpFontMng FontMng::GetInstance()

class FontMng
{
public:
	static FontMng& GetInstance()
	{
		static FontMng s_Instance;
		return s_Instance;
	}
	// デフォルトフォント
	bool DefaultFont(std::string str,Vector2Dbl pos,int size,int thick);
	bool DefaultFont(std::string str,Vector2Dbl pos,int size,int thick, int color);
	// フォントの種類を変更できる
	bool ChangeFont(std::string FontName, std::string str,Vector2Dbl pos, int size, int thick);
	bool ChangeFont(std::string FontName, std::string str,Vector2Dbl pos, int size, int thick, int color);
private:
	FontMng();
	~FontMng();
};

