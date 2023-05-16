#include "Keyboard.h"
#include <DxLib.h>

Keyboard::Keyboard()
{
	inputTbl_ = {
		{InputID::Up,KEY_INPUT_UP},
		{InputID::Down,KEY_INPUT_DOWN},
		{InputID::Left ,KEY_INPUT_LEFT},
		{InputID::Right,KEY_INPUT_RIGHT},
		{InputID::Btn1,KEY_INPUT_Z},
		{InputID::Btn2,KEY_INPUT_SPACE},
	};
	for (auto id : InputID())
	{
		cntData_.try_emplace(id, TrgBool{ 0,0 });
	}
}

Keyboard::~Keyboard()
{
}

void Keyboard::Updata(void)
{
	GetHitKeyStateAll(keyData_.data());
	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[inputTbl_[id]];
	}
}
