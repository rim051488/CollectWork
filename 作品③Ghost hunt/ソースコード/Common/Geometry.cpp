#include "Geometry.h"


bool Geometry::IsHit(const Vector2Dbl plPos, const Vector2Dbl enPos, const int radius1, const int radius2)
{
	auto totalradius = radius1 + radius2;

	return ((plPos.x_ - enPos.x_) * (plPos.x_ - enPos.x_)) +
		((plPos.y_ - enPos.y_) * (plPos.y_ - enPos.y_)) <=
		totalradius * totalradius;
}

double Geometry::Rad2DegD(double rad)
{
	return rad * (180.0f / DX_PI);
}

double Geometry::Deg2RadD(double deg)
{
	return deg * (DX_PI / 180.0);
}

double Geometry::DegIn360(double deg)
{
	deg = fmod(deg, 360.0);
	if (deg < 0.0)
	{
		deg += 360.0;
	}
	return deg;
}

double Geometry::RadIn2PI(double rad)
{
	rad = fmod(rad, DX_TWO_PI);
	if (rad < 0.0)
	{
		rad += DX_TWO_PI;
	}
	return rad;
}

