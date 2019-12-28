#pragma once

class Vector;

class Matrix
{
public:
	float m[4][4];
	Matrix operator * ( const Matrix& mat ) const;
	void translate( const Vector& v );
	void rotate( const Vector& d, float r );
	void setZero( );
	void identity( );
};
