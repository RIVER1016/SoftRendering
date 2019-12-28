#pragma once
#include "math.h"

Vector::Vector( )
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 1.f;
}

Vector::Vector( const float& x, const float& y, const float& z )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1.0f;
}

Vector::Vector( const float& x, const float& y, const float& z, const float& w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vertex::Vertex( ){}

Vertex::Vertex( const Vector& pos, const Vector& c, const Vector& n )
{
	position = pos;
	color = c;
	normal = n;
	position = pos;
}

void Vertex::setNormal( const Vector& n )
{
	normal = n;
}

Vector Vector::operator - ( const Vector& v ) const
{
	Vector temp = Vector( );
	temp.x = x - v.x;
	temp.y = y - v.y;
	temp.z = z - v.z;
	temp.w = 1.f;
	return temp;
}

Vector Vector::operator + ( const Vector& v ) const
{
	Vector temp = Vector( );
	temp.x = x + v.x;
	temp.y = y + v.y;
	temp.z = z + v.z;
	temp.w = 1.f;
	return temp;
}
float Vector::operator * ( const Vector& v ) const
{
	return x * v.x + y * v.y + z * v.z;;
}

Vector Vector::operator * ( const float& a ) const
{
	Vector temp = Vector( );
	temp.x = x * a;
	temp.y = y * a;
	temp.z = z * a;
	temp.w = 1.f;
	return temp;
}

Vector Vector::operator * ( Matrix& mat ) const
{
	Vector temp = Vector( );
	temp.x = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + w * mat.m[3][0];
	temp.y = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + w * mat.m[3][1];
	temp.z = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + w * mat.m[3][2];
	temp.w = x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + w * mat.m[3][3];
	return temp;
}

Vector Vector::operator % ( const Vector& v ) const
{
	Vector temp = Vector( );
	temp.x = y * v.z - z * v.y;
	temp.y = z * v.x - x * v.z;
	temp.z = x * v.y - y * v.x;
	temp.w = 1.f;
	return temp;
}

bool Vector::operator == ( const Vector& v ) const
{
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

Vector Vector::mul( const Vector& v ) const
{
	Vector temp;
	temp.x = x * v.x;
	temp.y = y * v.y;
	temp.z = z * v.z;
	temp.w = 1.f;
	return temp;
}

void Vector::normalize( )
{
	float m = sqrtf( pow( x, 2 ) + pow( y, 2 ) + pow( z, 2 ) );
	if ( m != 0 )
	{
		x /= m;
		y /= m;
		z /= m;
	}
	else
		return;
}

bool Vector::checkCvv( const Vector& v )
{
	return v.z > 0 && v.z < v.w && v.x > -v.w && v.x < v.w && v.y > -v.w && v.y < v.w;
}

Triangle::Triangle( ){}

Triangle::Triangle( const Vertex& vt1, const Vertex& vt2, const Vertex& vt3 )
{
	vertex1 = vt1;
	vertex2 = vt2;
	vertex3 = vt3;
}

float saturate( const float& x )
{
	if ( x < 0.f )
		return 0.f;
	else if ( x > 1.f )
		return 1.f;
	else
		return x;
}

float caculate( Vector phom1, Vector phom2, Vector phom3, int x, int y )
{
	float f = ((phom1.y - phom2.y) * x + (phom2.x - phom1.x) * y + phom1.x * phom2.y - phom2.x * phom1.y) 
		/ ((phom1.y - phom2.y) * phom3.x + (phom2.x - phom1.x) * phom3.y + phom1.x * phom2.y - phom2.x * phom1.y);
	return f;
}