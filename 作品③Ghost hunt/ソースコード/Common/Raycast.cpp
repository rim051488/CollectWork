#include "Raycast.h"
#include "../../_debug/_DebugDispOut.h"

std::pair<bool, Vector2Dbl> Raycast::CheckCollision(Ray ray, Collision col)
{
	bool flag = false;
	Vector2Dbl moveVec{ ray.vec };
	Line points[4] =
	{
		{
			col.first,
			col.first + Vector2Dbl{col.second.x_,0},
		},						// è„ï”
		{
			col.first + Vector2Dbl{col.second.x_,0},
			col.first + col.second,
		},						// âEï”
		{
			col.first + col.second,
			col.first + Vector2Dbl{0,col.second.y_},
		},						// â∫ï”
		{
			col.first + Vector2Dbl{0,col.second.y_},
			col.first,
		}						// ç∂ï”
	};
	for (auto point : points)
	{
		auto result = CheckRay(ray, point);
		flag |= result.first;
		moveVec = result.first ? result.second : moveVec;
	}
	return { flag ,moveVec };
}

std::pair<bool, Vector2Dbl> Raycast::CheckRay(Ray ray, Line line)
{
	//auto vec = ray.vec;
	//auto pos = ray.p;
	//auto vector = line.end.x_ * pos.y_ - line.end.y_ * pos.x_;
	//if (vector == 0)
	//{
	//	return false;
	//}

	// Ç±ÇÃÇ‚ÇËï˚Ç≈ÇÕÇ«Ç§Ç‚Ç¡ÇƒåvéZÇµÇƒÇ¢ÇÈÇ©ÇóùâÇ∑ÇÈ
	auto checkCross = [](Vector2Dbl& vec1, Vector2Dbl& vec2) {
		return ((vec1.x_ * vec2.y_) - (vec2.x_ * vec1.y_));
	};
	Vector2Dbl& vecRay = ray.vec;
	Vector2Dbl&& vecLine = line.end - line.p;
	auto crossRayLine = checkCross(vecRay, vecLine);
	if (crossRayLine == 0)
	{
		return { false,ray.vec };
	}
	Vector2Dbl v = Vector2Dbl{ line.p.x_ - ray.p.x_,line.p.y_ - ray.p.y_ };
	auto cross_vRay = checkCross(v, vecRay);
	auto cross_vLine = checkCross(v, vecLine);

	double ans1 = cross_vRay / crossRayLine;
	double ans2 = cross_vLine / crossRayLine;

	if (ans1 > 0.0f && ans1 <= 1.0f &&
		ans2 > 0.0f && ans2 <= 1.0f)
	{
		//_dbgDrawCircle(ray.p.x_ + vecRay.x_ * ans2, ray.p.y_ + vecRay.y_ * ans2, 5, 0xffffff, true);
		return { true,vecRay * ans2 };
	}

	return { false,ray.vec };
}

