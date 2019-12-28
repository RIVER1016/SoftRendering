#pragma once
#include "Device.h"
class Geo
{
public:
	void setDevice( Device dv );	
protected:
	Device device;
};

class Cube : public Geo
{
public:
	Cube( );
	Cube( Vertex vt1, Vertex vt2, Vertex vt3, Vertex vt4, Vertex vt5, Vertex vt6, Vertex vt7, Vertex vt8 );
	void draw( );
	Vertex v1;
	Vertex v2;
	Vertex v3;
	Vertex v4;
	Vertex v5;
	Vertex v6;
	Vertex v7;
	Vertex v8;
};

class Sphere : public Geo
{
public:
	float radius;
	Sphere( );
	Sphere( float r );
	void drawFlat( int n );
	void drawGourand( int n );
protected:
	int drawTriFlat( Triangle tri, float r, int n );
	int drawTriGourand( Triangle tri, float r, int n );
	Triangle* getBallTri( Triangle tri, float r );
};