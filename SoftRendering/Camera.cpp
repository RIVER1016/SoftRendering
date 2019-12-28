#pragma once
#include "Camera.h"

void Camera::init( const Vector& p, const Vector& r, const Vector& l, const Vector& u )
{
	position = p;
	right = r;
	look = l;
	up = u;
}

// ǰ������������, �ƶ�position
void Camera::walk( const float& x, const float& y, const float& z )
{
	Matrix ts;
	ts.translate( up * -y + look * -z + right * -x );
	position = position * ts;
}

// ��б ��right����ת ̧ͷ/��ͷ
void Camera::pitch( const float& r )
{
	Matrix rt;
	rt.rotate( right, r );
	look = look * rt;
	up = up * rt;
}

// ƫ�� ��up����ת ����תͷ
void Camera::yaw( const float& r )
{
	Matrix rt;
	rt.rotate( up, r );
	right = right * rt;
	look = look * rt;
}

// ��ת	��look����ת ��ͷ
void Camera::roll( const float& r )
{
	Matrix rt;
	rt.rotate( look, r );
	right = right * rt;
	up = up * rt;
}

Vector Camera::getPosition( )
{
	return position;
}

Vector Camera::getRight( )
{
	return right;
}

Vector Camera::getLook( )
{
	return look;
}

Vector Camera::getUp( )
{
	return up;
}
