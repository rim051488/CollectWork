#pragma once
#include "Input.h"
class Keyboard :
	public Input
{
public:
	Keyboard();
	virtual ~Keyboard();
	void Updata(void) override;
	CntType GetCntType(void) override { return CntType::Key; };
private:
	std::array<char, 256U> keyData_;
	std::map<InputID, unsigned int> inputTbl_;
};

