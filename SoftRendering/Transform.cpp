#pragma once
#include "Transform.h"

void Transform::init( const float& w, const float& h, const Camera& ca )
{
	width = w;
	height = h;
	camera = ca;
	world.identity( );
	lookAt( );
	perspective( 0.5f * 3.1415926f, 1.f, 500.f );
	update( );
}

Vector Transform::homogenize( const Vector& v )
{
	Vector temp;
	temp.x = ( 0.5f + v.x * 0.5f / v.w ) * width;
	temp.y = ( 0.5f - v.y * 0.5f / v.w ) * height;
	temp.z = v.z / v.w;
	temp.w = 1.f;
	return temp;
}

void Transform::lookAt( )
{
	eye = camera.getPosition( );
	Vector zaxis = camera.getLook( );
	zaxis.normalize( );
	Vector xaxis = camera.getUp( ) % zaxis;
	xaxis.normalize( );
	Vector yaxis = zaxis % xaxis;

	Vector _eye = Vector( -eye.x, -eye.y, -eye.z );
	Matrix eyeMove;
	eyeMove.translate( _eye );
	Matrix cameraRotate;
	cameraRotate.identity( );
	cameraRotate.m[0][0] = xaxis.x;
	cameraRotate.m[0][1] = yaxis.x;
	cameraRotate.m[0][2] = zaxis.x;
	
	cameraRotate.m[1][0] = xaxis.y;
	cameraRotate.m[1][1] = yaxis.y;
	cameraRotate.m[1][2] = zaxis.y;
	
	cameraRotate.m[2][0] = xaxis.z;
	cameraRotate.m[2][1] = yaxis.z;
	cameraRotate.m[2][2] = zaxis.z;
	
	view = eyeMove * cameraRotate;
}

void Transform::perspective( const float& a, const float& n, const float& f )
{
	float aspect = height / width;
	projection.setZero( );
	projection.m[0][0] = aspect / tanf( a * 0.5f );
	projection.m[1][1] = 1.f / tanf( a * 0.5f );
	projection.m[2][2] = f / ( f - n );
	projection.m[2][3] = 1.f;
	projection.m[3][2] = f * n / ( n - f );
}

bool Transform::backFaceCulling( const Vector& v1, const Vector& v2, const Vector& v3 )
{
	Vector v21 = v2 - v1;
	Vector v31 = v3 - v1;
	if ( ( v21 % v31 ).z < 0 )
		return true;
	else
		return false;
}

void Transform::setWorld( const Vector& translate, const Vector& rotate, const float& theta )
{
	Matrix tr, ro;
	tr.translate( translate );
	ro.rotate( rotate, theta );
	
	world = tr * ro;
}

void Transform::setView( )
{
	lookAt( );
	update( );
}

void Transform::update( )
{
	wvp = world * view * projection;
}

Matrix Transform::getWorld( )
{
	return world;
}

Matrix Transform::getView( )
{
	return view;
}

Matrix Transform::getProjection( )
{
	return projection;
}

Matrix Transform::getWVP( )
{
	return wvp;
}

Camera Transform::getCamera( )
{
	return camera;
}

Vector Transform::getEye( )
{
	return eye;
}

void Transform::setCamera( const Camera& ca )
{
	camera = ca;
}
