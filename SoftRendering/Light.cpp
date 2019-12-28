#pragma once
#include "Light.h"
#include "math.h"
#include "Transform.h"

Light::Light( const Vector& lc, const Vector& d, const Vector& msc, const float& s )
{
	lightColor = lc;
	dir = d;
	materialSpecColor = msc;
	shine = s;
}

Vector Light::diffuse( const Vertex& v )
{
	Vector l = dir * -1;
	l.normalize( );
	Vector n = v.normal;
	Vector diffuse = lightColor * saturate( n * l );
	return diffuse;
};

Vector Light::phongSpecularReflection( const Vertex& v, Transform* ts )
{
	Vector l = dir;
	l.normalize( );
	Vector n = v.normal;
	Vector eye = ts->getEye( );
	Vector view = eye - v.worldpos;
	view.normalize( );
	Vector reflect = l - n * ( n * l ) * 2;
	reflect.normalize( );
	Vector spec = materialSpecColor * pow( saturate( reflect * view ), shine );
	return spec;
};

Vector Light::blinnPhongSpecularReflection( const Vertex& v, Transform* ts )
{
	Vector l = dir;
	Vector n = v.normal;
	Vector eye = ts->getEye( );
	Vector view = eye - v.worldpos;
	view.normalize( );
	Vector halfway = l * -1 + view;
	halfway.normalize( );
	Vector spec = materialSpecColor * pow( saturate( halfway * n ), shine );
	return spec;
};

Vector Light::getLightDir( )
{
	return dir;
}

Vector Light::getLightColor( )
{
	return lightColor;
}
