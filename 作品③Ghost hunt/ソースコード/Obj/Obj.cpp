#include "Obj.h"

Obj::Obj()
{
}

Obj::~Obj()
{
}

void Obj::Draw(void)
{
}

Vector2Dbl Obj::GetPos(void)
{
	return oldPos_;
}

void Obj::SetRand(double rand)
{
	rand_ = rand;
}

double Obj::GetRand(void)
{
	return rand_;
}

int Obj::GetRad(void)
{
	return radius_;
}

double Obj::GetLost(void)
{
	return Lost_;
}


bool Obj::GetFlag(void)
{
	return flag_;
}

double Obj::GetDelta(void)
{
	return delta_;
}

bool Obj::GetAlive(void)
{
	return Alive_;
}

bool Obj::IsAlive(void)
{
	return alive_;
}

bool Obj::GetPflag(void)
{
	return Pflag;
}

bool Obj::GetEflag(void)
{
	return Eflag;
}

bool Obj::GetPLost(void)
{
	return PLost;
}


void Obj::SetWall(bool wall)
{
	Wall_ = wall;
}

void Obj::SetPfalg(bool pflag)
{
	Pflag = pflag;
}

void Obj::SetPlost(bool plost)
{
	PLost = plost;
}

void Obj::SetAngle(double angle)
{
	Angle_ = angle;
}


Vector2Dbl Obj::GetEnemyPos(void)
{
	return RedEnemyPos_;
}

Vector2Dbl Obj::GetPlayerPos(void)
{
	return PlayerPos_;
}

Vector2Dbl Obj::GetPlBulletPos(void)
{
	return PlBulletPos_;
}

Vector2Dbl Obj::GetEnBulletPos(void)
{
	return EnBulletPos_;
}
