#pragma once
#include "Input.h"
class Pad :
	public Input
{
public:
	Pad(int padID);
	virtual ~Pad();
	void Updata(void) override;
	CntType GetCntType(void) override { return CntType::Pad; };
private:
	std::map<InputID, unsigned int> inputTbl_;
	int padID_;
};

