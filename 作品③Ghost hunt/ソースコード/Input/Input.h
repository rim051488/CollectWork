#pragma once
#include <array>
#include <map>
#include "InputID.h"

enum class CntType
{
	Key,
	Pad,
	Max
};

enum class Trg
{
	Now,
	Old,
	Max
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID, TrgBool>;

class Input
{
public:
	Input() {};
	virtual ~Input() {};
	virtual void Updata(void) = 0;
	virtual CntType GetCntType(void) = 0;
	const CntData& GetCntData(void)
	{
		return cntData_;
	}

private:
protected:
	CntData cntData_;
};

