#pragma once
#include "Camera.h"

void Camera::init( const Vector& p, const Vector& r, const Vector& l, const Vector& u )
{
	position = p;
	right = r;
	look = l;
	up = u;
}

// 前后左右上下走, 移动position
void Camera::walk( const float& x, const float& y, const float& z )
{
	Matrix ts;
	ts.translate( up * -y + look * -z + right * -x );
	position = position * ts;
}

// 倾斜 绕right轴旋转 抬头/低头
void Camera::pitch( const float& r )
{
	Matrix rt;
	rt.rotate( right, r );
	look = look * rt;
	up = up * rt;
}

// 偏航 绕up轴旋转 左右转头
void Camera::yaw( const float& r )
{
	Matrix rt;
	rt.rotate( up, r );
	right = right * rt;
	look = look * rt;
}

// 滚转	绕look轴旋转 侧头
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
