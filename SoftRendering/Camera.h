#pragma once
#include "math.h"
#include "Matrix.h"

class Camera
{
public:
	void init( const Vector& position, const Vector& right, const Vector& look, const Vector& up );
	void walk( const float& x, const float& y, const float& z );	// 前后左右上下走, 移动position
	void pitch( const float& r );	// 倾斜 绕right轴旋转 抬头/低头
	void yaw( const float& r );	// 偏航 绕up轴旋转 左右转头
	void roll( const float& r );	// 滚转	绕look轴旋转 侧头
	Vector getPosition( );
	Vector getRight( );
	Vector getLook( );
	Vector getUp( );

private:
	Vector position;
	Vector right;
	Vector look;
	Vector up;
};
