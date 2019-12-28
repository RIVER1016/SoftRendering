#pragma once

#include "math.h"
#include "Transform.h"
#include "Light.h"

typedef unsigned int uint32;

class Device
{
public:
	void init( const int& w, const int& h, uint32* fb, Transform* ts, Light* li );
	void drawPoint( const Vector& v , const Vector& c );
	void drawLine( const Vertex& vertex1, const Vertex& vertex2 );
	void drawLine3D( const Vertex& vertex1, const Vertex& vertex2 );
	void drawTriangle3D( const int& changeShader, const Triangle& tr );
	void drawTriangle3DFlat( const int& changeShader, const Triangle& tr );
	void draw3DRectangle(const Vertex& p1, const Vertex& p2, const Vertex& p3, const Vertex& p4);
	void draw3DFullTriangleLight( const int& changeShader, const Triangle& tri );
	void close( );
	void clear( );
	Light* getLight( );

private:
	void fillBottomFlatTriangle( const int& changeShader, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3 );
	void fillTopFlatTriangle( const int& changeShader, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3 );
	uint32** framebuffer;
	Transform* transform;
	float* zbuffer;
	Light* light;
	int width;
	int height;
};
