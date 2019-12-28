#pragma once
#include "math.h"

class Transform;
class Vertex;
class Light
{
public:
	Light( const Vector& lc, const Vector& d, const Vector& msc, const float& s );
	Vector diffuse( const Vertex& v );	// ������
	Vector phongSpecularReflection( const Vertex& v, Transform* ts );	// ���淴��
	Vector blinnPhongSpecularReflection( const Vertex& v, Transform* ts );
	Vector getLightDir( );
	Vector getLightColor( );

private:
	Vector lightColor;
	Vector dir;
	Vector materialSpecColor;
	float shine;
};
