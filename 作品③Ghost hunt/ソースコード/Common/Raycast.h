#pragma once
#include "Vector2.h"
#include "Collision.h"

class Raycast
{
public:
	struct Ray
	{
		Vector2Dbl p;			// 始点
		Vector2Dbl vec;		// 方向ベクトル
	};
	struct Line
	{
		Vector2Dbl p;			// 始点
		Vector2Dbl end;		// 終点
		//Vector2 vec() { return end - p; }		// 方向ベクトル
	};
	std::pair<bool, Vector2Dbl> CheckCollision(Ray ray,Collision col);
	std::pair<bool, Vector2Dbl> CheckRay(Ray ray, Line line);
private:
};

