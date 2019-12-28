#pragma once
#include <math.h>
#include "Matrix.h"

class Vector
{
public:
	float x, y, z, w;
	Vector( );
	Vector( const float& x, const float& y, const float& z, const float& w );
	Vector( const float& x, const float& y, const float& z );
	Vector operator - ( const Vector& v ) const;
	Vector operator + ( const Vector& v ) const;
	float operator * ( const Vector& v ) const;
	Vector operator * ( const float& a ) const;
	Vector operator * ( Matrix& mat ) const;
	Vector operator % ( const Vector& v ) const;	// X multiply
	bool operator == ( const Vector& v ) const;
	Vector mul( const Vector& v ) const;
	void normalize( );
	bool checkCvv( const Vector& v );
};

class Vertex
{
public:
	Vector position;
	Vector color;
	Vector worldpos;
	Vector normal;
	Vertex( );
	Vertex( const Vector& pos, const Vector& c, const Vector& n );
	void setNormal( const Vector& n );
};

class Triangle
{
public:
	Vertex vertex1, vertex2, vertex3;
	Triangle( );
	Triangle( const Vertex& vt1, const Vertex& vt2, const Vertex& vt3 );
};

float saturate( const float& x );

float caculate( Vector phom1, Vector phom2, Vector phom3, int x, int y );