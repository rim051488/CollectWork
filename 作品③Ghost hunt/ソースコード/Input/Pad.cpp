#include "Pad.h"
#include <DxLib.h>

Pad::Pad(int padID)
{
	inputTbl_ = {
	{InputID::Up,PAD_INPUT_UP},
	{InputID::Down,PAD_INPUT_DOWN},
	{InputID::Left ,PAD_INPUT_LEFT},
	{InputID::Right,PAD_INPUT_RIGHT},
	{InputID::Btn1,PAD_INPUT_1},
	{InputID::Btn2,PAD_INPUT_2},
	};
	for (auto id : InputID())
	{
		cntData_.try_emplace(id, TrgBool{ 0,0 });
	}
	padID_ = padID;
}

Pad::~Pad()
{
}

void Pad::Updata(void)
{
	auto inputData = GetJoypadInputState(padID_);
	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = ((inputData & inputTbl_[id]) > 0);
	}
}
