#pragma once
#include "./Vector2.h"
#include "../Vector2.h"
#include <DxLib.h>
#include <cmath>

template <class T>
Vector2Template<T>::Vector2Template()
{
	x_ = 0;
	y_ = 0;
}

template <class T>
Vector2Template<T>::Vector2Template(T x, T y)
{
	//Vector2::x_ = x;			// ‚à‚µ‚­‚Í (this-> x = x)
	//Vector2::y_ = y;			// ‚à‚µ‚­‚Í (this-> y = y)
	x_ = x;
	y_ = y;
}
template<class T>
Vector2Template<T>::~Vector2Template()
{

}
template<class T>
inline double Vector2Template<T>::Magnitude(void) const
{
	return sqrt(x_ * x_ + y_ * y_);
}
template<class T>
inline double Vector2Template<T>::SQMagnitude(void) const
{
	return x_ * x_ + y_ * y_;
}
template<class T>
inline void Vector2Template<T>::Normalize(void)
{
	float mag = Magnitude();
	x_ /= mag;
	y_ /= mag;
}
template<class T>
inline Vector2Template<T> Vector2Template<T>::Normalized(void)
{
	double mag = Magnitude();
	return Vector2Dbl(x_ / mag, y_ / mag);
}
template <class T>
Vector2Template<T>& Vector2Template<T>::operator=(const Vector2Template<T>& vec)
{
	x_ = vec.x_;
	y_ = vec.y_;
	return *this;
}
template <class T>
const int& Vector2Template<T>::operator[](int i)
{
	//if (i == 1)
	//{
	//	return y_;
	//}
	//if (i != 1)
	//{
	//	return x_;
	//}
	switch (i)
	{
	case 0:
		return x_;
	case 1:
		return y_;
	default:
		return x_;
		//break;
	}
}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator+=(const Vector2Template<T>& vec)
{
	x_ += vec.x_;
	y_ += vec.y_;
	return *this;
}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator-=(const Vector2Template<T>& vec)
{
	x_ -= vec.x_;
	y_ -= vec.y_;
	return *this;
}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator*=(const Vector2Template<T>& vec)
{
	x_ *= vec.x_;
	y_ *= vec.y_;
	return *this;
}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator/=(const Vector2Template<T>& vec)
{
	if (x_ == 0)
	{
		x_ = 0;
	}
	else
	{
		x_ /= vec.x_;
	}
	if (y_ == 0)
	{
		y_ = 0;
	}
	else
	{
		y_ /= vec.y_;
	}

	return *this;

}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator%=(const Vector2Template<T>& vec)
{
	if (x_ == 0)
	{
		x_ = 0;
	}
	else
	{
		x_ %= vec.x_;
	}
	if (y_ == 0)
	{
		y_ = 0;
	}
	else
	{
		y_ %= vec.y_;
	}
	return *this;

}

template <class T>
Vector2Template<T> Vector2Template<T>::operator+() const
{
	return *this;
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator-() const
{
	return {-x_,-y_ };
	//return -(*this);
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator+(Vector2Template<T> vec)
{
	return { x_ + vec.x_,y_ + vec.y_ };
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator-(Vector2Template<T> vec)
{
	return { x_ - vec.x_,y_ - vec.y_ };
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator*(Vector2Template<T> vec)
{
	return { x_ * vec.x_,y_ * vec.y_ };
}


template <class T>
Vector2Template<T> Vector2Template<T>::operator/(Vector2Template<T> vec)
{
	if (x_ == 0)
	{
		return { 0,y_ / vec.y_ };
	}
	if (y_ == 0)
	{
		return { x_ / vec.x_,0 };
	}
	return { x_ / vec.x_,y_ / vec.y_ };
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator%(Vector2Template<T> vec)
{
	if (x_ == 0)
	{
		return { 0,y_ % vec.y_ };
	}
	if (y_ == 0)
	{
		return { x_ % vec.x_,0 };
	}

	return { x_ % vec.x_,y_ % vec.y_ };
}

//Vector2 Vector2::operator*(float num)
//{
//	return { x_ * num,y_ * num };
//}
template <class T>
bool Vector2Template<T>::operator==(const Vector2Template<T>& vec) const
{
	return ((x_ == vec.x_) && (y_ == vec.y_));
}
template <class T>
bool Vector2Template<T>::operator!=(const Vector2Template<T>& vec) const
{
	return !((x_ == vec.x_) && (y_ == vec.y_));
}
template <class T>
bool Vector2Template<T>::operator<(const Vector2Template<T>& vec) const
{
	return ((x_ < vec.x_) && (y_ < vec.y_));
}
template <class T>
bool Vector2Template<T>::operator>(const Vector2Template<T>& vec) const
{
	return ((x_ > vec.x_) && (y_ > vec.y_));
}
template <class T>
bool Vector2Template<T>::operator<=(const Vector2Template<T>& vec) const
{
	return ((x_ <= vec.x_) && (y_ <= vec.y_));
}
template <class T>
bool Vector2Template<T>::operator>=(const Vector2Template<T>& vec) const
{
	return ((x_ >= vec.x_) && (y_ >= vec.y_));
}


template <class T>
Vector2Template<T> operator*(const Vector2Template<T>& vec, T num)
{
	return { vec.x_ * num,vec.y_ * num };
}

template <class T>
Vector2Template<T> operator*(T num, const Vector2Template<T>& vec)
{
	return { vec.x_ * num,vec.y_ * num };
}
