#pragma once
#include "math.h"
#include "Matrix.h"
#include "Camera.h"

class Transform
{
public:
	void init( const float& w, const float& h, const Camera& ca );
	Vector homogenize( const Vector& v );
	bool backFaceCulling( const Vector& v1, const Vector& v2, const Vector& v3 );
	void setWorld( const Vector& translate, const Vector& rotate, const float& theta );
	void setCamera( const Camera& ca );
	void setView( );
	void update( );
	Matrix getWorld( );
	Matrix getView( );
	Matrix getProjection( );
	Matrix getWVP( );
	Camera getCamera( );
	Vector getEye( );

private:
	float width, height;
	Matrix world;
	Matrix view;
	Matrix projection;
	Matrix wvp;
	Vector eye;
	Camera camera;
	void perspective( const float& a, const float& n, const float& f );
	void lookAt( );
};
