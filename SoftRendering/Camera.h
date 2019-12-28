#pragma once
#include "math.h"
#include "Matrix.h"

class Camera
{
public:
	void init( const Vector& position, const Vector& right, const Vector& look, const Vector& up );
	void walk( const float& x, const float& y, const float& z );	// ǰ������������, �ƶ�position
	void pitch( const float& r );	// ��б ��right����ת ̧ͷ/��ͷ
	void yaw( const float& r );	// ƫ�� ��up����ת ����תͷ
	void roll( const float& r );	// ��ת	��look����ת ��ͷ
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
