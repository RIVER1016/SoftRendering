#pragma once
#include "Matrix.h"
#include "math.h"

Matrix Matrix::operator * ( const Matrix& mat ) const
{
	Matrix temp;
	for ( int i = 0; i < 4; i ++ )
	{
		for ( int j = 0; j < 4; j ++ )
			temp.m[i][j] = m[i][0] * mat.m[0][j] + m[i][1] * mat.m[1][j] + m[i][2] * mat.m[2][j] + m[i][3] * mat.m[3][j];
	}
	return temp;
}

void Matrix::translate( const Vector& v )
{
	identity( );
	m[3][0] = v.x;
	m[3][1] = v.y;
	m[3][2] = v.z;
}

void Matrix::rotate( const Vector& d, float r )
{
	identity( );
	float c = 1 - cosf( r );
	float d_xx = d.x * d.x;
	float d_xy = d.x * d.y;
	float d_xz = d.x * d.z;
	float d_yy = d.y * d.y;
	float d_zz = d.z * d.z;
	float d_yz = d.y * d.z;
	m[0][0] = d_xx * c + cosf( r );
	m[0][1] = d_xy * c + d.z * sinf( r );
	m[0][2] = d_xz * c - d.y * sinf( r );
	
	m[1][0] = d_xy * c - d.z * sinf( r );
	m[1][1] = d_yy * c + cosf( r );
	m[1][2] = d_yz * c + d.x * sinf( r );;
	
	m[2][0] = d_xz * c + d.y * sinf( r );
	m[2][1] = d_yz * c - d.x * sinf( r );
	m[2][2] = d_zz * c + cosf( r );	
}

void Matrix::setZero( )
{
	for ( int i = 0; i < 4; i ++ )
		for ( int j = 0; j < 4; j ++ )
			m[i][j] = 0.f;
}

void Matrix::identity( )
{
	setZero( );
	m[0][0] = 1.f;
	m[1][1] = 1.f;
	m[2][2] = 1.f;
	m[3][3] = 1.f;
}
