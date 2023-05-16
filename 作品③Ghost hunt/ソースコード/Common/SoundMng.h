#pragma once
#pragma once
#include "../Common/Vector2.h"
#include <string>

#define lpFontMng SoundMng::GetInstance()

class SoundMng
{
public:
	static SoundMng& GetInstance()
	{
		static SoundMng s_Instance;
		return s_Instance;
	}
	void SetSound(void);
private:
	SoundMng();
	~SoundMng();
};

