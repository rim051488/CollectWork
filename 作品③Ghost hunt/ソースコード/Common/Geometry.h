#pragma once
#include "Vector2.h"

class Geometry
{
public:
	// 円と円の当たり判定
	bool IsHit(const Vector2Dbl plPos, const Vector2Dbl enPos, const int plradius, const int enradius);

	// ラジアン(rad)から度(deg)
	static double Rad2DegD(double rad);

	// 度(deg)からラジアン(rad)
	static double Deg2RadD(double deg);

	// 0～360度の範囲に収める
	static double DegIn360(double deg);

	// 0～2π(360度)の範囲に収める
	static double RadIn2PI(double rad);
};
